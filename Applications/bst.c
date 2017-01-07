#include "bst.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void InsertTree(TreeEntry *pe, Tree *pt)
{
	TreeNode *p, *prev, *curr;
	p = (TreeNode*)malloc(sizeof(TreeNode));
	p->entry = *pe;
	p->left = NULL;
	p->right = NULL;
	if(!*pt)
		*pt = p;
	else{
		curr = *pt;
		while (curr){
			prev = curr;
			if (LT(pe->key, curr->entry.key))
				curr = curr->left;
			else
				curr = curr->right;
		}
		if (LT(pe->key, prev->entry.key))
			prev->left = p;
		else
			prev->right = p;
	}
}	//end function Insert

void ClearTreeAux(Tree *pt)
{
	if(*pt){
		ClearTreeAux(&(*pt)->left);
		ClearTreeAux(&(*pt)->right);
		free(*pt);
	}
}

void ClearTree(Tree *pt)
{
	ClearTreeAux(pt);
	*pt = NULL;
}

void InorderRec(Tree *pt, void(*pvisit) (TreeEntry))
{
	clock_t start = clock();
	if(*pt){
		InorderRec(&(*pt)->left, pvisit);
		(*pvisit)((*pt)->entry);
		InorderRec(&(*pt)->right, pvisit);
	}
	printf("time elapced: %f", ((double)clock() - start));
}

void InorderItr(Tree *pt, void(*pvisit)(TreeEntry))
{
	clock_t start = clock();
	Stack s;
	void *p = (void *)(*pt);
	if (p){
		CreateStack(&s);
		do{
			while (p){
				Push(&p, &s);
				p = (void*)((TreeNode *)p->left);
			}
			if (!StackEmpty(&s)){
				Pop (&p, &s);
				(*pvisit)((TreeNode *)p->entry);
				p = (void*)((TreeNode *)p->right);
			}
		}while (!StackEmpty(&s) || p);
	}
	printf("time elapced: %f", ((double)clock() - start));
}