#include <stdio.h>

char lastPointer(char* s) 
{ 
    for (; *s != NULL; ++s);
    return *(s - 1);
}

char lastPlus(char* s)
{
    int i = 0; //   s[i] == *(s+i) 
    for (i = 0; *(s + i) != NULL; ++i);
    return *(s + i - 1);
}

char lastARR(char* s) 
{
    int i = 0;
    for (i = 0; s[i] != NULL; ++i);
    return s[i - 1];
}

void main()
{
    char* s1 = "ho";
    char s2[] = "hO";
    char s3[] = { 'h', 'i', '\0' };
    printf("%c\n", lastARR(s1)), printf("%c\n", lastPlus(s2)), printf("%c\n", lastPointer(s3));
}
