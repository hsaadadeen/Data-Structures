#include"stack.h"
#include<stdio.h>

void ReverseRead(void)
{
	StackEntry item;
	Stack stack;
	CreateStack(&stack);  /* initialize the stack to be epmty */

	while (!StackFull(&stack) && (item = getchar()) != '\n')
		Push(item, &stack);  /* Push item into the stack */

	while (!StackEmpty(&stack)){
		Pop(&item, &stack);  /* Pop item from the stack */
		putchar(item);
	}
	putchar('\n');
}

void main ()
{
	ReverseRead();
}
