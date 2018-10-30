

#ifndef PRINT_TREE_H_
#define PRINT_TREE_H_

typedef struct node_st node_t;

typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
  asciinode *left;
	asciinode *right;

/*  length of the edge from this node to its children*/
  int edge_length;
  int height;
  int lablen;

/*  -1=I am left, 0=I am root, 1=right   */
  int parent_dir;
/*  max supported unit32 in dec, 10 digits max*/
  char label[11];
};

int MIN (int X, int Y)  ;
int MAX (int X, int Y)  ;

asciinode * build_ascii_tree_recursive(node_t * t) ;

/*//Copy the tree into the ascii node structre*/
asciinode * build_ascii_tree(node_t * t) ;

/*//Free all the nodes of the given tree*/
void free_ascii_tree(asciinode *node) ;

/*//The following function fills in the lprofile array for the given tree.*/
/*//It assumes that the center of the label of the root of this tree*/
/*//is located at a position (x,y).  It assumes that the edge_length*/
/*//fields have been computed for this tree.*/
void compute_lprofile(asciinode *node, int x, int y) ;

void compute_rprofile(asciinode *node, int x, int y) ;

/*//This function fills in the edge_length and */
/*//height fields of the specified tree*/
void compute_edge_lengths(asciinode *node) ;

/*//This function prints the given level of the given tree, assuming*/
/*//that the node has the given x cordinate.*/
void print_level(asciinode *node, int x, int level) ;

/*//prints ascii tree for given node_t structure*/
void print_ascii_tree(node_t * t) ;

#endif /*PRINT_TREE_H_*/

