#include "queue.h"
#include <stdlib.h>

/*Linked Definitions*/
void CreateQueue ( Queue *pq )
{
	pq -> front=NULL;
	pq -> rear=NULL;
	pq -> size=0;
}
void ClearQueue ( Queue *pq )
{
	QueueNode *pn = pq->front;
	while ( pq->front )
	{
		pn = pn->next;
		free( pq->front );
		pq->front = pn;
	}
	pq->size=0;
	pq->rear=NULL;
}
int  QueueFull ( Queue *pq )
{
	return 0;
}
int  QueueEmpty ( Queue *pq )
{
	return !(pq->size);
}
int  QueueSize ( Queue *pq )
{
	return pq->size;
}
void Append ( QueueEntry e , Queue *pq )
{
	QueueNode *pn = (QueueNode*)malloc(sizeof(QueueNode));
	pn->entry=e;
	pn->next = NULL;

	if ( !(pq->size) )
	{
		pq->front = pn;
		pq->rear = pn;
	}
	else
	{
		pq->rear->next = pn;
		pq->rear = pn;
	}
	pq->size++;
}
void Serve ( QueueEntry *e , Queue *pq )
{
	QueueNode *pn = pq->front;
	*e=pn->entry;
	
	pq->front = pn->next;
	free(pn);
	if( !(pq->front) )
		pq->rear = NULL;
	pq->size--;
}
void Retrieve ( QueueEntry *e , Queue *pq )
{
	*e = pq->front->entry;
}
void TraverseQueue ( Queue *pq, void (*Visit)(QueueEntry) )
{
	QueueNode *p=pq->front;
	while ( p )
	{
		(*Visit)(p->entry);
		p=p->next;
	}
}
