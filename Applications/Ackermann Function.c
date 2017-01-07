/* Ackermann's function: is a standard device to determine how well recursion is implemented on a computer.
	From: Data Structure And Program Design In C.
	By: HUSSAM A.DEEN		24 Oct. 2010
*/

#include<stdio.h>


/* A (Ackermann's function */
int A(int m, int n)
{
	if (m > 0 && n > 0)
		return A(m-1, A(m, n-1));
	else{
		if (n >= 0)
			return (n + 1);
		else{
			if (m > 0)
				return A(m-1, 1);
		}
	}
}	/* end function Ackermann */


/******************************************************************************/


int main()
{
	int m, n;
	int value;
	int A(int m, int n);

	printf("For A(m, n), enter 'm' and 'n' respectivly: ");
	scanf("%d%d", &m, &n);

	value = A(m, n);
	printf("The value calculated is %d.\n", value);

	return 0;
}	/* end function main */