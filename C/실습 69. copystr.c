#include "stdio.h" 

void mystrcpyHPointer(char ori[1], char copyHere[100000]) 
{ 
    for (; *copyHere = *ori; ++ori, copyHere++);
} 

void mystrcpyLPointer(char* ori, char copyHere[]) 
{
    for (; *ori != NULL; ++ori)
        *copyHere = *ori;
    *copyHere = NULL;
}

void mystrcpyPLUS(char* ori, char copyHere[])
{

    int i;
    for (i = 0; ori[i] != NULL; ++i)
        *(copyHere + i) = *(ori + i);
    copyHere[i] = NULL; 
}

void mystrcpyHPLUS(char ori[1], char copyHere[100000]) 
{ 
    int i;  for (i = 0; *(copyHere + i) = *(ori + i); ++i);
}

void mystrcpyH(char ori[1], char copyHere[100000])
{ 
    int i;  for (i = 0; copyHere[i] = ori[i]; ++i);
}

void mystrcpy(char ori[1], char copyHere[100000])
{ 
    int i;
    for (i = 0; ori[i] != NULL; ++i) 
        copyHere[i] = ori[i];
    copyHere[i] = NULL; //  
}

void main()
{
    char name[10] = "jinho"; 
    printf("%s\n", name);

    mystrcpy("copy", name); 
    printf("%s\n", name);

    name[0] = NULL;

    mystrcpyHPointer("copycopy", name);
    printf("%s\n", name);
}

