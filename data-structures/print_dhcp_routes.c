
/*in test file use this way :*/
/*print_ascii_tree(root);*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_dhcp_routes.h"

#define MAX_HEIGHT 1000
#define INFINITY (1 << 20)

typedef struct dhcp_st dhcp_t;

/*STRUCTS*/
typedef enum Dir
{
	LEFT,
	RIGHT,
	MAX_ROUTES
} dir;


struct node_st
{
	int is_used;
	node_t *route[MAX_ROUTES];
};


struct dhcp_st
{
	node_t *root;
	unsigned int host_size;
	unsigned int net;
};
/*END OF STRUCT*/

int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];

/*adjust g_gap between left and right nodes*/
int g_gap = 3;

/*used for printing next node in the same level,
this is the x coordinate of the next char printed*/
int g_print_next;

int MIN (int X, int Y)
{
  return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y)
{
  return ((X) > (Y)) ? (X) : (Y);
}

asciinode *build_ascii_tree_recursive(node_t * t)
{
  asciinode *node = NULL;

  if (NULL == t)
	{
		return (NULL);
	}

  node = (asciinode *)malloc(sizeof(asciinode));
	if (NULL == node)
	{
		return (NULL);
	}

  node->left = build_ascii_tree_recursive(t->route[LEFT]);
  node->right = build_ascii_tree_recursive(t->route[RIGHT]);

  if (node->left != NULL)
  {
    node->left->parent_dir = -1;
  }

  if (node->right != NULL)
  {
    node->right->parent_dir = 1;
  }

  sprintf(node->label, "%d", t->is_used);
  node->lablen = strlen(node->label);

  return (node);
}


/*//Copy the tree into the ascii node structre*/
asciinode *build_ascii_tree(node_t *t)
{
  asciinode *node = NULL;

  if (t == NULL)
	{
		return (NULL);
	}

  node = build_ascii_tree_recursive(t);
  node->parent_dir = 0;

  return (node);
}

/*//Free all the nodes of the given tree*/
void free_ascii_tree(asciinode *node)
{
  if (NULL == node)
	{
		return;
	}

  free_ascii_tree(node->left);
  free_ascii_tree(node->right);
  free(node);

	return;
}

/*//The following function fills in the lprofile array for the given tree.*/
/*//It assumes that the center of the label of the root of this tree*/
/*//is located at a position (x,y).  It assumes that the edge_length*/
/*//route have been computed for this tree.*/
void compute_lprofile(asciinode *node, int x, int y)
{
  int i;
	int isleft;

  if (NULL == node)
	{
		return;
	}

  isleft = (-1 == node->parent_dir);
  lprofile[y] = MIN(lprofile[y], x - ((node->lablen-isleft) / 2));

  if (node->left != NULL)
  {
      for (i = 1;
					(i <= node->edge_length) &&
					(y + (i < MAX_HEIGHT));
					++i)
    {
        lprofile[y + i] = MIN(lprofile[y + i], x - i);
    }
  }

  compute_lprofile(node->left,
									 x - node->edge_length - 1,
									 y + node->edge_length + 1);

  compute_lprofile(node->right,
									 x + node->edge_length + 1,
									 y + node->edge_length + 1);

	return;
}

void compute_rprofile(asciinode *node, int x, int y)
{
  int i = 0;
	int notleft = 0;
  if (node == NULL) return;
  notleft = (node->parent_dir != -1);
  rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
  if (node->right != NULL)
  {
      for (i = 1;
					(i <= node->edge_length) &&
					(y + (i < MAX_HEIGHT));
					++i)
    {
        rprofile[y + i] = MAX(rprofile[y + i], x + i);
    }
  }
  compute_rprofile(node->left,
									 x - node->edge_length - 1,
									 y + node->edge_length + 1);

  compute_rprofile(node->right,
									 x + node->edge_length + 1,
									 y + node->edge_length + 1);
	return;
}

/*//This function fills in the edge_length and */
/*//height route of the specified tree*/
void compute_edge_lengths(asciinode *node)
{
  int h = 0;
	int hmin = 0;
	int i = 0;
	int delta = 0;

  if (NULL == node)
	{
		return;
	}

  compute_edge_lengths(node->left);
  compute_edge_lengths(node->right);

  /* first fill in the edge_length of node */
  if ((NULL == node->right) && (NULL == node->left))
  {
      node->edge_length = 0;
  }
  else
  {
    if (node->left != NULL)
    {
        for (i = 0; (i < node->left->height) && (i < MAX_HEIGHT); i++)
      {
            rprofile[i] = -INFINITY;
        }
        compute_rprofile(node->left, 0, 0);
        hmin = node->left->height;
    }
    else
    {
        hmin = 0;
    }
      if (node->right != NULL)
    {
        for (i=0; (i < node->right->height) && (i < MAX_HEIGHT); i++)
      {
            lprofile[i] = INFINITY;
        }
        compute_lprofile(node->right, 0, 0);
        hmin = MIN(node->right->height, hmin);
    }
    else
    {
        hmin = 0;
    }
      delta = 4;
      for (i = 0; i < hmin; ++i)
    {
        delta = MAX(delta, g_gap + 1 + rprofile[i] - lprofile[i]);
    }

/*    //If the node has two children of height 1, then we allow the*/
/*    //two leaves to be within 1, instead of 2 */
      if (((node->left != NULL && node->left->height == 1) ||
          (node->right != NULL && node->right->height == 1)) &&
					delta > 4)
    {
      --delta;
    }

    node->edge_length = ((delta + 1) / 2) - 1;
  }

/*  //now fill in the height of node*/
  h = 1;
  if (node->left != NULL)
  {
      h = MAX(node->left->height + node->edge_length + 1, h);
  }
  if (node->right != NULL)
  {
      h = MAX(node->right->height + node->edge_length + 1, h);
  }
  node->height = h;

	return;
}

/*//This function prints the given level of the given tree, assuming*/
/*//that the node has the given x cordinate.*/
void print_level(asciinode *node, int x, int level)
{
  int i = 0;
	int isleft = 0;

  if (node == NULL)
	{
		return;
	}

  isleft = (node->parent_dir == -1);

  if (level == 0)
  {
      for (i = 0; i < (x - g_print_next - ((node->lablen - isleft) / 2)); ++i)
    {
        printf(" ");
    }
      g_print_next += i;
      printf("%s", node->label);
      g_print_next += node->lablen;
  }
  else if (node->edge_length >= level)
  {
      if (node->left != NULL)
    {
        for (i=0; i < (x - g_print_next - (level)); ++i)
      {
            printf(" ");
        }
        g_print_next += i;
        printf("/");
        ++g_print_next;
    }
      if (node->right != NULL)
    {
        for (i = 0; i < (x - g_print_next + (level)); ++i)
      {
            printf(" ");
        }
        g_print_next += i;
        printf("\\");
        ++g_print_next;
    }
  }
  else
  {
      print_level(node->left,
									x - node->edge_length - 1,
									level - node->edge_length - 1);
      print_level(node->right,
                x + node->edge_length + 1,
                level - node->edge_length - 1);
  }

	return;
}

/*//prints ascii tree for given Tree structure*/
void print_ascii_tree(node_t * t)
{
  asciinode *proot = NULL;
  int xmin = 0;
	int i = 0;

  if (NULL == t)
	{
		return;
	}

  proot = build_ascii_tree(t);
  compute_edge_lengths(proot);

  for (i = 0; (i < proot->height) && (i < MAX_HEIGHT); ++i)
  {
      lprofile[i] = INFINITY;
  }

  compute_lprofile(proot, 0, 0);

  for (i = 0; (i < proot->height) && (i < MAX_HEIGHT); ++i)
  {
      xmin = MIN(xmin, lprofile[i]);
  }

  for (i = 0; i < proot->height; ++i)
  {
      g_print_next = 0;
      print_level(proot, -xmin, i);
      printf("\n");
  }
  if (proot->height >= MAX_HEIGHT)
  {
      printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
  }

  free_ascii_tree(proot);

	return;
}


