 #include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "stack.h" /* STACK API */

/* construct a new stack */
struct stack_st
{
	size_t element_size;
	size_t capacity;
	size_t size;
	char data[1]; /* malloc should be right afer the struct created on the stack */
};

/*
DESCRIPTION
	StackCreate - initialized a new stack with num of elements & size
RETRUN VALUE
	returns a pointer to the new stack initialized
*/
stack_t *StackCreate(size_t num_elements, size_t element_size)
{
	/* create a stack with its members */
	stack_t *new_stack = 0;

	assert(num_elements > 0);
	assert(element_size > 0);

	new_stack = (stack_t *)malloc(sizeof(stack_t) + (num_elements * element_size));
	assert(new_stack != NULL);

	new_stack->element_size = element_size;
	new_stack->capacity = num_elements; /* maximum storage available */
	new_stack->size = 0; /* the number of elements */

	return (new_stack);
}

/*
DESCRIPTION
	StackDestroy - delete an instace of stack
*/
void StackDestroy(stack_t *stack)
{
	assert(stack != NULL);

	stack->size = 0;
	free(stack);
	stack = NULL;

	return;
}

/*
DESCRIPTION
	StackPop  - pop the first variable in the stack. (return 1 if size is 0)
*/
int StackPop(stack_t *stack)
{
	assert(stack != NULL);

	if(stack->size == 0)
	{
		return (1);
	}

	--(stack->size);

	return (0);
}

/*
DESCRIPTION
	StackPush - push a given variable into the stack
RETURN VALUE
	return 0 if pushed successfully or 1 for stack-overflow
*/
int StackPush(stack_t *stack, const void *new_element)
{
	assert(stack != NULL);
	assert(new_element != NULL);

	if(stack->size == stack->capacity)
	{
		return (1);
	}
	/* copies the element into the stack*/
	memcpy(stack->data + (stack->size * stack->element_size),
												 new_element, stack->element_size);
	++(stack->size);

	return(0);
}

/*
DESCRIPTION
	StackPeek - returns the first element in the stack. (return NULL if stack size is empty)
*/
void *StackPeek(const stack_t *stack)
{
	assert(stack != NULL);

	if(0 == stack->size)
	{
		return NULL;
	}

	return ((void *)(stack->data + stack->element_size*(stack->size - 1)));
}

/*
DESCRIPTION
	StackSize - returns the current stack usage
*/
size_t StackSize(const stack_t *stack)
{
	assert(stack != NULL);

	return (stack->size);
}
