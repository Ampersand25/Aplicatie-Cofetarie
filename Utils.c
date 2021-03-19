#include "Utils.h"

#include <stdlib.h>
#include <string.h>

int conversieDeLaStringLaIntreg(const char* str)
{
	unsigned numar = 0;
	for (unsigned i = 0; *(str + i) != '\0'; ++i)
	{
		if (i[str] < '0' || i[str] > '9')
			return -1;
		numar = numar * 10 + (str[i] - '0');
	}
	return numar;
}

char* alocareStr(const unsigned dim)
{
	if (!dim)
		return NULL;
	char* mem = (char*)malloc(dim * sizeof(char));
	if (mem == NULL)
	{
		perror("Heap Overflow!");
		exit(-1);
	}
	return mem;
}

void dezalocare(void* memory_block)
{
	free(memory_block);
}

unsigned compareStr(const char* str_1, const char* str_2)
{
	return !strcmp(str_1, str_2);
}