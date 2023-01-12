#include <stdio.h>

void swap(int* a, int* b)
{
	printf("swap 이전 a : a의 주소 = %d, a의 내용값 = %d, a가 가리키는 주소가 가진 값 = %d\n", &a, a, *a);
	printf("swap 이전 b : b의 주소 = %d, b의 내용값 = %d, b가 가리키는 주소가 가진 값 = %d\n", &b, b, *b);
	int temp = *a;
	*a = *b;
	*b = temp;
	printf("swap 이후 a : a의 주소 = %d, a의 내용값 = %d, a가 가리키는 주소가 가진 값 = %d\n", &a, a, *a);
	printf("swap 이후 b : b의 주소 = %d, b의 내용값 = %d, b가 가리키는 주소가 가진 값 = %d\n", &b, b, *b);
}

void main()
{
	int val1 = 10;
	int val2 = 20;
	printf("Before val1: 주소 %d, 값 %d \n", &val1, val1);
	printf("Before val2: 주소 %d, 값 %d \n", &val2, val2);

	swap(&val1, &val2);

	printf("After val1: 주소 %d, 값 %d \n", &val1, val1);
	printf("After val2: 주소 %d, 값 %d \n", &val2, val2);
}
