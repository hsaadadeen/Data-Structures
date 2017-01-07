#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* function StackTop in the user level*//*
void StackTop(StackEntry *pe , Stack *ps)
{
	Pop (pe , ps);
	Push (*pe , ps);
}*/

/*Function StackSize in the user level*/
/*
int StackSize (Stack *ps)
{
	int counter=0;
	if (!StackEmpty(ps))
	{
		
		StackEntry transferedItem;
		Stack a;
		CreateStack (&a);
		
		while (!StackEmpty(ps))
		{
			Pop (&transferedItem , ps);
			Push (transferedItem , &a);
			counter++;
		}
		
		while (!StackEmpty(&a))
		{
			Pop (&transferedItem , &a);
			Push (transferedItem , ps);
		}
		return counter;
	}
	else
		return 0;
}
	
	
	*/

int main()
{
    Stack stack;
	char x=NULL;
    StackEntry item;
    
    CreateStack(&stack);

	printf("(a) Clear the stack.\n(b) Read an element then Push it.\n(c) Pop an element then display it.\n(d) What is the stack size?\n(e) Return a copy of the top of the stack.\n(g) Exit.\n");

	

	 while (x!=EOF){
		 x=getchar();
	 
		switch (x){
			case 'a':
				ClearStack (&stack);
				printf("Stack is Cleared\n");
				break;
	
			case 'b':
				item =getchar();
				
				if (!StackFull(&stack)){
					scanf ("%c", &item);
					Push (item , &stack);
				}
				else
					printf("Stack is Full\n");
				break;
	

			case 'c':
				if (!StackEmpty(&stack)){
					Pop (&item, &stack);
					printf("%c\n", item);
				}
				else
					printf("Stack is Empty\n");
				break;
	

			case 'd':
				printf("Stack size is %d\n",StackSize(&stack));
				break;

			case 'e':
				if (!StackEmpty(&stack)){
					StackTop(&item, &stack);
					printf("%c", item);
				}
				else
					printf("Stack is Empty\n");
				break;

			case 'g':
				x=EOF;
				break;

		}
	 }

    return 0;
}
