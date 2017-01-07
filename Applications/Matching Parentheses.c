#include<stdio.h>
#include"stack.h"

/* Match: match the parentheses and returns 1 if they match and 0 if not */
int Match(void)
{
	StackEntry item, poped; /* item: is the char. from the user. poped: is the element poped from the stack. */
	int flag = 1;	/* flag: is 1 parentheses match and 0 otherwise */
	Stack stack;
	CreatStack(&stack);	/* initialize the stack */


	while ((item = getchar()) != '\n'){

		switch (item){
			/* if opened parentheses push in the stack */
		case '(':
			Push(item, &stack);
			flag = 0;
			break;
		case '[':
			Push(item, &stack);
			flag = 0;
			break;
		case '{':
			Push(item, &stack);
			flag = 0;
			break;

			/* if closed parentheses pop from the stack and compaire */
		case ')':
			if (Pop(&poped, &stack)){
				if (poped == '(')
					flag = 1;
				else
					flag = 0;
			}
			else
				flag = 0;
			break;
		case ']':
			if (Pop(&poped, &stack)){
				if (poped == '[')
					flag = 1;
				else
					flag = 0;
			}
			else
				flag = 0;
			break;
		case '}':
			if(Pop(&poped, &stack)){
				if (poped == '{')
					flag = 1;
				else
					flag = 0;
			}
			else
				flag = 0;
			break;

		}	/* end switch */
	}	/* end while */

	/* check if the stack is empty or the are still some elements */
		if (!StackEmpty(&stack))
			flag = 0;

		return flag;
		
}	/*end function Match */


/* Function main program begins execution */
void main()
{
	Stack s;
	int x = Match();
	if (x == 1)
		printf("Correct matching parentheses\n");
	else
		printf("Incorrect matching parentheses\n");
}