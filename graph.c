#include"graph.h"

void CreateGraph(Graph *pg)
{
	int i = 0, j = 0;
	while (i < MAXGRAPH)
	{
		pg->vertices[i] = '0';
		i++;
	}
	for (i = 0; i < MAXGRAPH; i++){
		for (j = 0; j < MAXGRAPH; j++)
			pg->edges[i][j] = 0;
	}
	pg->size = 0;
}	//end function CreateGraph

void ClearGraph(Graph *pg)
{
	int i = 0, j = 0;
	while (i < MAXGRAPH)
	{
		pg->vertices[i] = '0';
		i++;
	}
	for (i = 0; i < MAXGRAPH; i++){
		for (j = 0; j < MAXGRAPH; j++)
			pg->edges[i][j] = 0;
	}
	pg->size = 0;
}	//end function ClearGraph

void ClearRelations(Graph *pg)
{
	int i, j;
	for (i = 0; i < MAXGRAPH; i++)
	{
		for (j = 0; j < MAXGRAPH; j++)
			pg->edges[i][j] = 0;
	}
}

void AddEdge(GraphEntry src, GraphEntry dest, Graph *pg)
{
	int i, j;	// i referes to the position of the src and j referes to the position of the dest in the vertices array
	for (i = 0; src != pg->vertices[i]; i++);	// this loop loops on the vertices arry till it finds the (src) entry
	for (j = 0; dest != pg->vertices[j]; j++);	// this loop loops on the vertices array till it finds the (dest) entry

		pg->edges[i][j] = 1;
		pg->edges[j][i] = 1;

}	// end function AddEdge

void DeleteEdge(GraphEntry src, GraphEntry dest, Graph *pg)
{
	int i, j;	// i referes to the position of the src and j referes to the position of the dest in the vertices array
	for (i = 0; src != pg->vertices[i]; i++);	// this loop loops on the vertices arry till it finds the (src) entry
	for (j = 0; dest != pg->vertices[j]; j++);	// this loop loops on the vertices arry till it finds the (dest) entry

		pg->edges[i][j] = 0;
		pg->edges[j][i] = 0;
		
}	// end function DeleteEdge

void AddVertex (GraphEntry e, Graph *g)
{
	int counter;
	for (counter=0; g->vertices[counter] != '0' ; counter++);
		// this loop loops on the intIndex array till it finds an empty place (0 in it)
		
	g->vertices[counter] = e;		// the entry is put in an empty place in the vertices array
	g->size++;
	
}	// end function AddVertex


void DeleteVertex(GraphEntry e, Graph *g)
{	int counter;
	int i;
	for (counter=0; g->vertices[counter]!=e; counter++);	// this loop loops on the vertices array till it finds the place with the (e) entry in it 
		
	for (i = 0; i < MAXGRAPH; i++){
		DeleteEdge(g->vertices[counter], g->vertices[i], g);
	}	// end for loop

	g->vertices[counter] = '0';		// intIndex[counter] is set to integer 0 indicating that this position in the vertices array is empty
	g->size--;
}	// end function DeleteVertex

int GraphSize(Graph *pg)
{
	return pg->size;
}	//end function GraphSize

int GraphEmpty(Graph *pg)
{
	return (pg->size == 0);
}	//end function GraphEmpty

int GraphFull(Graph *pg)
{
	return (pg->size == MAXGRAPH);
}	//end function GraphFull

void TraverseGraph(Graph *pg, void(*Visit)(GraphEntry) )
{
	int i;	// i counter
	for(i=0; i< pg->size; i++)	// this loop passes the vertices on the function
		(*Visit)(pg->vertices[i]);
}	//end function TraverseGraph

int VertexExists (GraphEntry e , Graph *g)
{
	int flag = 0;
	int counter = 0;
	while (counter < g->size )	// this loop loops on the vertices array untill the given GraphEntry is found
	{
		if (g->vertices[counter] == e)	//the given GraphEntry is checked for validity for every loop
			{flag = 1;
		counter++;}
		else 
			counter++;
	}
	return flag;
}// end of function VertixExists

void CreateAssistant(Assistant *pa)
{
	int i;
	for (i = 0; i < MAXGRAPH; i++){
		pa->vertexconnected[i] = '0';
		pa->vertexconnected2[i] = '0';
	}
	pa->elementCounter = 0;
	pa->elementCounter2 = 0;
}	//end function CreateAssistant