/* GCD (Grand Common Divisor) of two posotive numbers is the largest integer that divides both of them
	By: HUSSAM	24 Oct. 2010
*/

#include<stdio.h>

int main()
{
	int GCD(int x, int y);
	int x, y;

	printf("Enter the two intigers: ");
	scanf("%d%d", &x, &y); 
	printf("The GCD is %d.\n", GCD(x, y));

	return 0;
} /* end function main */