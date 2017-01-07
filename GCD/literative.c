#include<stdio.h>

/* gcd: tacks two numbers and returns thier grand common divisor */
/*int GCD(int x, int y)
{
	int count = 1, i, j;
		
	for (i = 1; i <= x; i++){
		if (x % i == 0){
			for (j = 1; j <= y; j++){
				if (y % j == 0){
					if(i == j)
						count = j;
				}
			}
		}
	}

	return count;
} /* end function gcd */