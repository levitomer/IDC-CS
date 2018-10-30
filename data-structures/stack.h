/* STACK API */
#ifndef STACK_H
#define STACK_H

#include <stddef.h> /* size_t */

typedef struct stack_st stack_t;

/* initialized a new stack with num of elements & size */
stack_t *StackCreate(size_t num_number, size_t element_size);

/* delete an instace of stack */
void StackDestroy(stack_t *stack);

/* pop the first variable in the stack */
int StackPop(stack_t *stack);

/* push a given variable into the stack */
int StackPush(stack_t *stack, const void *new_element);

/* returns the first element in the stack */
void *StackPeek(const stack_t *stack);

/* returns the stack size */
size_t StackSize(const stack_t *stack);

#endif /* STACK_H */
