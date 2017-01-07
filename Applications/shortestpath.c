#include "shortestpath.h"

int ShortestPath (Graph *pg, GraphEntry *src, GraphEntry *dest, Stack *Big_Stack_That_Will_Return)
{
	int SrcIndex;
	int DestIndex;
		List *pNewList, *OneConnectionL;      //A pointer to a list to create a list using malloc during run time, no need to create it here
		ListEntry Lentry;

		Queue NoBackMovingQ;		 //To save the points of the way moved
		Queue BigWayQ;	 //To save the points that will prevent going back to Big Nodes
		Queue LastWayMovedQ;
		Queue OneConnectionQ; //For the special case beta3t zizo*/
		QueueEntry Qentry;

		Stack BigStack;		 //A Big Stack that will include the list of possible ways
		Stack Saux;
		StackEntry Sentry;		 //Stack Entry

		int RowE;	  //row of the matrex
		int ColumnE;  //column of the matrex
		int Break;	  //to break from the next outer loop
		int X;		  //hanshoflo esm tany ynfa3lo
		int minSize;  //Used at the end of the end of the function to help in finding the shortest path
		int n,i,z;

	//To find the src and dest elements and put their index in i and j
	for (SrcIndex=0; pg->vertices[SrcIndex]!=*src && SrcIndex<=pg->size ; SrcIndex++);	//now we have the index of src in i
	if ( SrcIndex>pg->size)
		return 2;// return 2 if the src node was not found
	for (DestIndex=0; pg->vertices[DestIndex]!=*dest && DestIndex<=pg->size ; DestIndex++); //now we have the index of dest in j
	if ( DestIndex>pg->size)
		return 3;//return 3 if the dest node was not found

	if( MatrexRowEmpty(pg, &SrcIndex) || MatrexRowEmpty(pg, &DestIndex) ) //If the nodes have no relations 
		return 4;
	if (pg->edges[SrcIndex][DestIndex]==1) // If there is a direct way from src to dest
		return 1;
	
	if (pg->vertices[SrcIndex]!=*src || pg->vertices[DestIndex]!=*dest)    //if the elements were not found
		return 0;

	else //Lel asf the elements were found :-)
	{
		CreateStack(&BigStack);
		CreateQueue(&LastWayMovedQ);
		CreateQueue(&NoBackMovingQ);
		CreateQueue(&BigWayQ);
		CreateQueue(&OneConnectionQ);
		/*ÈÓã Çááå ÇáÑÍãä ÇáÑÍíã*/
		/*A Special case discovered by Zizo */
		/*If the src node connected to only one node*/
		OneConnectionL=(List*)malloc(sizeof(List));
		CreateList(OneConnectionL);
		while( RowNoOfRelations(pg, &SrcIndex)==1 )//to handle the case of that the src is connected with only one node
		{
			for( ColumnE=0; pg->edges[SrcIndex][ColumnE]!=1 && ColumnE<pg->size; ColumnE++ );
			Lentry.Gentry=pg->vertices[ColumnE];
			Lentry.Row=SrcIndex;
			Lentry.Column=ColumnE;
			InsertList( ListSize(OneConnectionL), Lentry, OneConnectionL);
			DontGoBackR( pg, &SrcIndex, &OneConnectionQ );//to appear to be deleted
			DontGoBackC( pg, &SrcIndex, &OneConnectionQ );//to appear to be deleted
			SrcIndex=ColumnE;
		}

		DontGoBackR (pg, &SrcIndex, &BigWayQ);

		/*First level*/
		/*Outer BIG Loop*/
		while ( !MatrexRowEmpty( pg, &SrcIndex ) ) //BIG OUTER LOOP :S
		{
			//Create a new list here so a new list is created and intialized everytime the Big Loop executed
			pNewList = (List*)malloc(sizeof(List)); 
			CreateList(pNewList);
			
			/*Second Level*/
			if ( !StackEmpty(&BigStack) )
			{
				Pop ( &Sentry, &BigStack );
				Push ( Sentry, &BigStack );

				/*Third Level*/
				if ( ListSize(Sentry.pList) >2 && X==1 )
				{
			int i= ListSize(Sentry.pList)-1;//because the last one is dest and the one before is directly connected to it
					int AnotherWayExist=0; //To know if there was another way found or not
					int NextNodeColumn;//To save the column of the next node to prevent going to it again
					
					DeleteList( i, &Lentry, Sentry.pList );
					InsertList( i, Lentry, Sentry.pList );
					NextNodeColumn = Lentry.Column;
					//To save the column of the next node to prevent going to it again
					i--;//to complete it to be -2

					/*Forth Level*/
					for ( ; !AnotherWayExist && i>=0; i--) //to tests if the node we are stopping at has others connections or not
					{
						DeleteList ( i, &Lentry, Sentry.pList );
						InsertList ( i, Lentry, Sentry.pList );
						
						if(pg->edges[Lentry.Index][DestIndex]!=1) // to not delete the way between the dest and its big node because it can be reached from another way
						{
							pg->edges[Lentry.Column][NextNodeColumn]=0;//delete the way that it moved to before to the next node
							pg->edges[Lentry.Column][Lentry.Row]=0;//delete the way that was moved to achieve this node

							/*Fifth Level*/
							if ( MatrexRowEmpty(pg, &Lentry.Column) )//If that was a wrong way
							{
								if(!i)//to test if it was a big node, and if it's, it will append it in the big way to prevent repeating
								{
									DontGoBackR(pg, &Lentry.Column, &BigWayQ);
									Qentry.Row=Lentry.Column;
									Qentry.Column=NextNodeColumn;
									Append(Qentry, &BigWayQ);/*Bug but resolved*/
									Qentry.Row=Lentry.Column;
									Qentry.Column=Lentry.Row;
									Append(Qentry, &BigWayQ);/*Bug but resolved*/
								}
/*Bug but resolved*/			else
/*Bug but resolved*/			{
									pg->edges[Lentry.Column][NextNodeColumn]=1;//return back the way that it moved to before to the next node because it it was achieved from shorter path
/*Bug but resolved*/				Qentry.Row=Lentry.Column;
/*Bug but resolved*/				Qentry.Column=Lentry.Row;
/*Bug but resolved*/				Append(Qentry, &LastWayMovedQ);//append the way that was moved to achieve this node to not repeat it
								}
							}//end of if matrex empty statement

							/*Fifth Level*/
							else //if another way was found
							{
								Qentry.Row=Lentry.Column;
								Qentry.Column=NextNodeColumn;
								Append(Qentry, &LastWayMovedQ);//delete the way that it moved to before to the next node to avoid moving in it again
							
								Qentry.Row=Lentry.Column;
								Qentry.Column=Lentry.Row;
								Append(Qentry, &LastWayMovedQ);//append the way that was moved to achieve this node to avoid moving in it again
							
								AnotherWayExist=1;//another way is true
							}// end of else of if matrex empty statement
						}
						NextNodeColumn = Lentry.Column;//to make it always equals to the next node
						/*End of Fifth Level*/
					}// end of the last loop that search for another way from another node passed during the last way
					
					/*Forth Level*/
					if (AnotherWayExist) /*To copy the list to a pNewList till the stopped node -1*/
					{
						int b=0;
						/*Fifth Level*/
						for ( ; b < i+1; b++)
						{
							DeleteList ( b, &Lentry, Sentry.pList );
							InsertList ( b, Lentry, Sentry.pList );
							InsertList ( b, Lentry, pNewList );
							DontGoBackR( pg, &Lentry.Column, &NoBackMovingQ);
						}
						RowE = Lentry.Index;
						/*End of Fifth Level*/
					}//end of if(AnotherWayExist) statement
					
					else RowE = SrcIndex; //if AnotherWayExist equal to zero

					/*End of Forth Level*/

				}/*End of Third Level, if List Size > 2 */

				/*Third Level*/
				else /*if(ListSize(Sentry.pList)<2))*/
				// X=0 or the list has less than 2 nodes SO we will delete the way between big nodes
				{
					DeleteList ( 0, &Lentry, Sentry.pList );
					InsertList ( 0, Lentry, Sentry.pList );
					DontGoBackR ( pg, &Lentry.Column, &BigWayQ );
					/*Delete the edges going from the last big node visited and its used also to break the outer loop*/

					RowE = SrcIndex;
				}
				/*End of Third Level*/

			}
			/*End of Second Level*/
			else RowE = SrcIndex;

			ColumnE = 0;
			Break = 0;
/*AWayExists*/X = 1;

			/*Inner BIG LOOP*/
			/*Second Level*/
			while ( Break ==0 )
			{
				if ( pg->edges[RowE][DestIndex]==1 ) //If this node and the dest node are directly connceted
					ColumnE = DestIndex;
				else for ( ; pg->edges[RowE][ColumnE]==0 && ColumnE<pg->size ; ColumnE++ );
						//A loop to find the column that have 1

				if ( ColumnE < pg->size && pg->edges[RowE][ColumnE]==1 )/*Second if to get the list entry and insert it*/
				{
					Lentry.Column = ColumnE;
					Lentry.Row = RowE;
					Lentry.Index = ColumnE;
					Lentry.Gentry = pg->vertices[ColumnE];

					InsertList ( ListSize(pNewList), Lentry, pNewList );

					RowE = ColumnE;
					ColumnE = 0;
					if(pg->vertices[RowE]!=*dest)//To avoid adding something that already added in BigWayQ
						DontGoBackR ( pg, &RowE, &NoBackMovingQ );
					/*To prevent going back to this node*/
				}/*End of Second if statement*/

				if ( MatrexRowEmpty(pg, &RowE) && pg->vertices[RowE]!=*dest )
				/*Third if statement that cheks if the row is empty or not to find the rigth way*/
				/*It will not enter if the dest was found*/
				{
					X = FindRightWay ( pg, pNewList );/*if x=1, it means that there's no rode*/
					if ( X )
					{
						DeleteList ( ListSize(pNewList)-1, &Lentry, pNewList );
						InsertList ( ListSize(pNewList), Lentry, pNewList );
						RowE=Lentry.Index; 
						ColumnE=0;
					}
					else /*No other ways found and dest unreachable*/ 
					{						
						ReturnAllBack ( pg, &NoBackMovingQ );
						ClearQueue(&NoBackMovingQ);//Just for security
						ReturnAllBack ( pg, &LastWayMovedQ );
						ClearQueue (&LastWayMovedQ);//Just for security
						Break=1;
						if(ListEmpty(pNewList)) //To handle if the list has only one node and this node have no ways
							DontGoBackR(pg, &Lentry.Index, &BigWayQ);
					}
				}/*End of third if statement*/

				if ( pg->vertices[RowE]==*dest )
				/*Forth if statement that cheks if the dest was found or not*/
				{
					ReturnAllBack ( pg, &NoBackMovingQ );
					/*Returns the matrex as it was because we have reached the dest*/
					Sentry.pList = pNewList;
					Push ( Sentry, &BigStack);
					/*Pushes the new list into the big stack*/

					DeleteList( 0, &Lentry, pNewList);
					InsertList( 0, Lentry, pNewList);
					DontGoBackR( pg, &Lentry.Index, &BigWayQ);
					if( !MatrexRowEmpty(pg, &Lentry.Index) && DestIndex<SrcIndex )
					{
						pg->edges[Lentry.Row][Lentry.Column]=1;

						DeleteList( 1, &Lentry, pNewList );
						InsertList( 1, Lentry, pNewList );
						pg->edges[Lentry.Row][Lentry.Column]=0;
						Qentry.Row=Lentry.Row;
						Qentry.Column=Lentry.Column;
						Append(Qentry, &BigWayQ);
					}

					Break=1; //To break the inner loop
				}/*End of the forth statement*/

			}/*End of the Big INNER LOOP*/

		}/*END OF THE BIG OUTER LOOP*/ /*UNBELIEVABLE CODE :S*/
		ReturnAllBack ( pg, &BigWayQ );
		ReturnAllBack ( pg, &OneConnectionQ );
		ReturnAllBack ( pg, &NoBackMovingQ );
		ReturnAllBack ( pg, &LastWayMovedQ );
	
		if ( StackEmpty(&BigStack) )
		{
			if( !ListEmpty(OneConnectionL) )
			{
				DeleteList( ListSize(OneConnectionL)-1, &Lentry, OneConnectionL );
				InsertList( ListSize(OneConnectionL), Lentry, OneConnectionL );
				if( Lentry.Gentry=*dest )
				{
					Sentry.pList=OneConnectionL;
					Push( Sentry, Big_Stack_That_Will_Return );
					return 1;
				}
				else return 0;
			}
		}

		
		/*To push the returnable list into the returnable stack*/
		minSize = MAXGRAPH;
		
		CreateStack(&Saux);
		while ( !StackEmpty(&BigStack) )
		{
			Pop ( &Sentry, &BigStack );
			Push ( Sentry, &Saux );
			if ( ListSize(Sentry.pList) <= minSize )
				minSize = ListSize(Sentry.pList); // To take the smallest lists size
		}

		while ( !StackEmpty(&Saux) ) // To save the smallest ways in the returnable stack using aux stack
		{
			Pop ( &Sentry, &Saux );
			if ( ListSize(Sentry.pList) <= minSize )//to push the shortest path
			{
				i=ListSize(OneConnectionL)-1;
				for( ; i>=0; i--)
				{
					DeleteList( i, &Lentry, OneConnectionL);
					InsertList( i, Lentry, OneConnectionL);
					InsertList( 0, Lentry, Sentry.pList);
				}
				Push ( Sentry, Big_Stack_That_Will_Return );
			}
		}

		ClearStack(&BigStack);
		ClearStack(&Saux);
		DestroyList(OneConnectionL);

		return 1;
	}/*END OF THE FIRST ELSE STATEMENT*/
}/*END OF FUNCTION*/

int  FindRightWay  (Graph *pg, List *pl)
{
	int pos, j, count;
	ListEntry e;
	int Break=0;
	while ( !Break && !ListEmpty(pl) )
	{
		pos=ListSize(pl)-1;
		DeleteList ( pos, &e, pl );
		for ( j=0, count=0; j<pg->size ; j++ )
		{
			if ( pg->edges[e.Column][j]==0 ) /*e.Column is the row of the previous node*/
				count++;
		}
		if( count!=pg->size)
		{
			Break=1;
			InsertList( pos, e, pl );
		}
	}

	if( Break )
		return 1;
	else return 0;
}
void DontGoBackR    (Graph *pg, int *pcol, Queue *pq)
{
	int count;
	QueueEntry e;

	for( count=0; count<pg->size; count++ )
	{
		if( pg->edges[count][*pcol]==1 )
		{
			pg->edges[count][*pcol]=0;
			e.Row = count;
			e.Column = *pcol;
			Append ( e, pq );
		}
	}
}
void DontGoBackC    (Graph *pg, int *prow, Queue *pq)
{
	int count;
	QueueEntry e;

	for( count=0; count<pg->size; count++ )
	{
		if( pg->edges[*prow][count]==1 )
		{
			pg->edges[*prow][count]=0;
			e.Row = *prow;
			e.Column = count;
			Append ( e, pq );
		}
	}
}
void ReturnAllBack (Graph *pg, Queue *pq)
{
	QueueEntry e;
	while( !QueueEmpty(pq) )
	{
		Serve( &e, pq );
		pg->edges[e.Row][e.Column]=1;
	}
}
int  MatrexRowEmpty (Graph *pg, int *pr)
{
	int count,i;
	for( count=0, i=0; i<pg->size && pg->edges[*pr][i]==0 ; i++, count++ );

	if( count == pg->size )
		return 1;
	else return 0;
}
int  RowNoOfRelations (Graph *pg, int *pr)
{
	int count,i;
	for( count=0, i=0; i<pg->size ; i++ )
	{
		if(pg->edges[*pr][i]==1)
			count++;
	}

	return count;
}