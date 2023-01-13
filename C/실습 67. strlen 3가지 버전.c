#include <stdio.h>

// s에 바로 ++하면서 값이 유효한지 체크한다.
// 미리 시작점을 포인터로 저장해 두고 빼준다.
int mystrlenPointer2(char* s)
{
	char* startAddress = s;
	for (; *s; s++);
	return s - startAddress;
}

// s++하면서 내용이 != 0인지 확인하는데, i도 같이 ++
// i를 출력한다.
int mystrlenPointer(char* s) 
{
	int i;
	for (i = 0; *s != 0; i++, s++);
	return i;
}

// (s + i) 주소가 유효한지 확인
// 끝난 이후 그냥 반환한다.
int mystrlenPLUS(char* s) // s[i] == *(s+i) 
{
	int i;
	for (i = 0; *(s + i) != 0; i++);
	return i;
}

// s[i] 가 true일때만 i를 계속++
// 끝난 이후 그냥 반환한다.
int mystrlenARR(char* s)
{
	int i;
	for (i = 0; s[i] != 0; i++);
	return i;
}

void main()

{
	char str[10] = "ho";
	printf("%d\n", mystrlenPointer2(str));
}
