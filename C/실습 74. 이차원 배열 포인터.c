#include <stdio.h>

int main(void) {
	int aa[3][2] = { 1, 2, 3, 4, 5, 6 };
	int a[2], b[2], c[2], * cp;
	
	cp = c;
	a[1] = 1; 
	*(b + 1) = 1;    
	cp++; 
	*cp = 1;

	printf("a[1] = %d, b[1] = %d, c[1] = %d\n", a[1], b[1], c[1]);

	printf("%d %d \n", aa[1][2], *(aa[1] + 2));
  // 여기 정확히 이해해야함.
	printf("%d %d \n", aa[2][1], *(*(aa + 2) + 1));
	printf("%d %d \n", *(aa + 2), **(aa + 2));
	return 0;
}
