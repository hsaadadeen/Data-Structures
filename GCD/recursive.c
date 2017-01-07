#include<stdio.h>

/* GCD: tacks two numbers and returns thier grand common divisor */
int GCD(int x, int y)
{
	if (y == 0)
		return x;
	else
		return GCD(y, x%y);
} /* end function gcd */