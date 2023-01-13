#include "stdio.h" 
#include "stdlib.h" // VS에서 안하면 치명적!!!!!!!!

void main()
{
    char* str; 
    str = (char*)malloc(20); 
    scanf("%s", str);
    printf("입력확인%s\n", str);
    free(str); 
}
