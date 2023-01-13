#include <stdio.h>

int vdotPointer(int* a, int* b)
{
	int result = 0;
	result = *a++ * *b++;
	result += *a++ * *b++;
	return  result + *a * *b;
}

int vdotPerror(int* a, int* b)
{
	// 힌 줄에 ++가 많아서 결국 a[0] * b[0]을 3번 더한 꼴이 된다.
	return *a++ * *b++ + *a++ * *b++ + *a * *b;
}

int vdotPLUS(int a[], int b[1000]) //사실상 포인터 변수들임
{
	return a[0] * b[0] + a[1] * *(b + 1) + a[2] * b[2];
}

int vdotARR(int a[1], int b[1000]) //사실상 포인터 변수들임
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void main()
{
	int va[3] = { 1, 2, 3 }, vb[3] = { 4, 5, 6 };
	printf("%d\n %d\n 에러난값: %d\n %d\n", vdotARR(va, vb), vdotPLUS(va, vb), vdotPerror(va, vb), vdotPointer(va, vb));
}
