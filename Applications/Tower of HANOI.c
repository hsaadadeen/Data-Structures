/*
The_Towers_of_HANOI: a platform on which were 3 needles. On the first needle were stacked 64 disks, each one slightly smaller than the one under it.
The objective is to move all the disks from the first needle to the third,subject to the conditions that only one disk can be moved at a time, and
that no disk is ever allwed to be placed on top of a smaller disk.
By:HUSSAM   From: Data Structure and program design in C		24 Oct. 2010
*/


#include<stdio.h>
#define DISKS 15
#include<time.h>
#define START 1
#define END 0


/* Time: Calculates run time between two pints.
Pre: START sets the starting time. END terminates the run time.
Post: At START return 0. At END return the time run since function was called with START. 
*/

float Time(int flag)
{
	static clock_t start;
	clock_t end;

	if(flag == START){
		start = clock();
		return 0.0;
	}
	else{
		end = clock();
		return (end - start) / CLOCKS_PER_SEC;
	}
}


/* Move: count disks from start to finish using temp as temporary storage.
Pre: There are at least count disks on the tower start. The top disk(if anly) on each of towers temp and finish is larger than any of the top count
	 disks on tower start.
Post: The top count disks on start have been moved to finish; temp(used for temorary storage) has been returned to its starting position.
*/

void Move(int count, int start, int finish, int temp)
{
	if (count > 0){
		Move(count-1, start, temp, finish);
		printf("Move a disk from %d to %d.\n", start, finish);
		Move(count-1, temp, finish, start);
	}	/* end if */

}	/* end function Move */


/* Towers of HANOI
Pre: None.
Post: The simulation of the Towers of HANOI has terminated
*/

int main()
{
	float elapsedtime;
	(void) Time(START);

	Move(DISKS, 1, 3, 2);

	elapsedtime = Time(END);
	printf("Elapsed time to complete is %f seconds.\n", elapsedtime);

	return 0;
}	/* end function main */