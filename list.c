#include <stdlib.h>
#include "list.h"

/*Linked Definitions*/
void CreateList(List *pl)
{
	pl->head=NULL;
	pl->size=0;
}

int ListEmpty(List *pl)
{
	return (pl->size==0);
}

int ListFull(List *pl)
{
	return 0;
}

int ListSize(List *pl)
{
	return pl->size;
}

void DestroyList(List *pl)
{
	ListNode *q;
	while(pl->head){
		q=pl->head->next;
		free(pl->head);
		pl->head=q;
	}
	pl->size=0;
}

void TraverseList(List* pl, void(*Visit)(ListEntry))
{
	ListNode *p=pl->head;
	while(p){
		(*Visit)(p->entry);
		p=p->next;
	}
}

void InsertList(int pos, ListEntry e, List *pl)
{
	ListNode *p, *q;
	int i;
	p =(ListNode *)malloc(sizeof(ListNode));
	p->entry=e;
	p->next=NULL;
	
	if (pos==0)
	{
		p->next=pl->head;
		pl->head=p;
	}
	else
	{
		for(q=pl->head, i=0; i<pos-1; i++)
			q=q->next;
		p->next=q->next;
		q->next=p;
	}
	pl->size++;
}

void DeleteList(int pos, ListEntry *pe, List *pl)
{
	int i;
	ListNode *q, *tmp;
   
	if (pos==0)
	{
		*pe=pl->head->entry;
		tmp=pl->head->next;
		free(pl->head);
		pl->head=tmp;
	}
	else
	{
		for(q=pl->head, i=0; i<pos-1; i++)
			q=q->next;

		*pe=q->next->entry;
		tmp=q->next->next;
		free(q->next);
		q->next=tmp;
	}
	pl->size--;
}

void RetrieveList(int pos, ListEntry *pe, List *pl)
{
	int i;
	ListNode *q;
	for(q=pl->head, i=0; i<pos; i++)
		q=q->next;
	*pe=q->entry;
}

void ReplaceList(int pos, ListEntry e, List *pl){
	int i;
	ListNode *q;
	for(q=pl->head, i=0; i<pos; i++)
		q=q->next;
	q->entry=e;
}