#include <stdio.h>

int dotPOINTER(int* a, int b[])
{
	int result = 0;
	result = *a * *b;
	a++; b++;
	result += *a * *b;
	return result;
}

int dotPLUS(int* a, int b[])
{
	return *(a + 0) * *b + a[1] * *(b + 1);
}

int dotARR(int a[], int* b)
{
	return a[0] * b[0] + a[1] * b[1];
}

void main()
{
	int a[] = { 1, 2 };
	int b[2] = { 4, 5 };
	int DOTresult = a[0] * b[0] + a[1] * b[1];

	printf("DOT main %d\n", DOTresult);
	printf("DOT array %d\n", dotARR(a, b));
	printf("DOT plus %d\n", dotPLUS(a, b));
	printf("DOT pointer %d\n", dotPOINTER(a, b));
}
