#include <stdio.h> /* printf */
#include "stack.h" /* STACK API */

static int errors = 0;

int main()
{
	stack_t *stack_p = StackCreate(13, 4);

	int num1 = 1, num2 = 2, num3 = 3;
	printf("size\tstack\n");

	/* check single item push to the stack */
	errors += StackPush(stack_p, &num1) ? 1 : (printf("%lu\t%d\n", StackSize(stack_p), *((int *)StackPeek(stack_p))), 0);
	errors += StackPush(stack_p, &num2) ? 1 : (printf("%lu\t%d\n", StackSize(stack_p), *((int *)StackPeek(stack_p))), 0);
	errors += StackPush(stack_p, &num3) ? 1 : (printf("%lu\t%d\n", StackSize(stack_p), *((int *)StackPeek(stack_p))), 0);

	printf("\n");
	/* check StackPop item push to the stack */
	printf("%lu\t%d\n", StackSize(stack_p), *(int *)StackPeek(stack_p));
	StackPop(stack_p);
	printf("%lu\t%d\n", StackSize(stack_p), *(int *)StackPeek(stack_p));
	StackPop(stack_p);
	printf("%lu\t%d\n", StackSize(stack_p), *(int *)StackPeek(stack_p));

	StackDestroy(stack_p);

	return 0;
}
