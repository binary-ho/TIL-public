#include "stdio.h"

char lastPointer(char str[])
{
    int leng = 0;
    printf("%x %c ", str, *str);
    for (; *str; str++, leng++, printf("afterInc %x %c\n", str, *str))
        printf("body %x %c ", str, *str);
    return *(--str);
}

char lastPlus(char str[])
{
    int leng = 0;
    for (; *(str + leng); ++leng);
    return *(str + leng - 1);
}

char lastMy(char str[])
{
    int leng = 0;
    for (; str[leng]; ++leng);
    return str[leng - 1];
}

int main()
{
    printf("%c %c %c\n", lastMy("jinho"), lastPlus("jinho"), lastPointer("jinho"));
}
