#include "stdio.h"
#include <stdlib.h> 
void main()
{
	char tmp[100]; int i, st_no; 
	char* name[5];
	for (i = 0; scanf("%s", tmp) > 0 && i < 5; i++) 
	{
		name[i] = (char*)malloc(strlen(tmp) + 1); 
		strcpy(name[i], tmp); 
	}

	st_no = i; 

	for (i = 0; i < st_no; ++i)
	{
		printf("%d %s\n", i, name[i]);
		free(name[i]); 
	}
}
