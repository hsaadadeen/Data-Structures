#include "stack.h"
#include <stdlib.h>

void CreateStack(Stack *ps)
{
	ps->top = NULL;
}

void Push(StackEntry *pe, Stack *ps)
{
	StackNode *pn = (StackNode*)malloc(sizeof(StackNode));
	pn->entry = pe;
	pn->next = ps->top;
	ps->top = pn;
}

void Pop(StackEntry *pe, Stack *ps)
{
	StackNode *pn;
	*pe = ps->top->entry;
	pn = ps->top;
	ps->top = ps->top->next;
	free(pn);
}

int StackEmpty(Stack *ps)
{
	return !ps->top;
}