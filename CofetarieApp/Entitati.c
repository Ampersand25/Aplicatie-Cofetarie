#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Entitati.h"

#include <stdlib.h>
#include <string.h>

Materie constructorEntitate(const char* nume, const char* producator, const unsigned cantitate)
{
	Materie materie;

	unsigned lungime = strlen(nume);
	materie.nume = (char*)malloc(lungime + 1);
	//if (materie.nume == NULL)
	//{
	//	perror("Heap Overflow!");
	//	exit(-1);
	//}
	strcpy_s(materie.nume, lungime + 1, nume);

	lungime = strlen(producator);
	materie.producator = (char*)malloc(lungime + 1);
	//if (materie.producator == NULL)
	//{
	//	perror("Heap Overflow!");
	//	exit(-1);
	//}
	strcpy_s(materie.producator, lungime + 1, producator);

	materie.cantitate = cantitate;

	return materie;
}

void destructorEntitate(Materie* materie)
{
	free(materie->nume);
	free(materie->producator);
}

char* getNume(const Materie materie)
{
	return materie.nume;
}

char* getProducator(const Materie materie)
{
	return materie.producator;
}

unsigned getCantitate(const Materie materie)
{
	return materie.cantitate;
}

void setProducator(Materie* materie, const char* new_producator)
{
	const unsigned lungime = strlen(new_producator);
	materie->producator = (char*)realloc(materie->producator, lungime + 1);
	//if (materie->producator == NULL)
	//{
	//	perror("Heap Overflow!");
	//	exit(-1);
	//}
	strcpy_s(materie->producator, lungime + 1, new_producator);
}

void setCantitate(Materie* materie, const unsigned new_cantitate)
{
	materie->cantitate = new_cantitate;
}

unsigned char equals(const Materie materie_1, const Materie materie_2)
{
	return !strcmp(materie_1.nume, materie_2.nume);
}