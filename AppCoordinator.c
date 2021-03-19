#include "Teste.h"
#include "Repository.h"
#include "Consola.h"

#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>

int main(void)
{
	ruleazaTeste(); /// testam functiile (cele care nu tin de interfata cu utilizatorul) implementate in cadrul aplicatiei
	constructorRepository(); /// instantiem repository-ul
	runApplication(); /// lansam in executie aplicatia din Controller
	destructorRepository(); /// distrugem repository-ul instantiat la inceputul intrarii in aplicatie
	_CrtDumpMemoryLeaks(); /// print memory leak
	return 0;
}