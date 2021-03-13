#include "Servicii.h"
#include "Repository.h"
#include "Validatori.h"

#include <stdlib.h>
#include <string.h>

int conversieDeLaStringLaIntreg(const char* str)
{
	if (!strlen(str))
		return -1;
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
	char* mem = (char*)malloc(dim * sizeof(char)); // char* mem = (char*)malloc(dim);
	//if (mem == NULL)
	//{
	//	perror("Heap Overflow!");
	//	exit(-1);
	//}
	return mem;
}

char* realocareStr(char* str)
{
	str = (char*)realloc(str, strlen(str) + 1);
	return str;
}

void dezalocare(void* memory_block)
{
	free(memory_block);
}

unsigned char compareStr(const char* str_1, const char* str_2)
{
	if (!strlen(str_1))
		return !strlen(str_2);
	return !strcmp(str_1, str_2);

	// return !strlen(str_1) ? !strlen(str_2) : !strcmp(str_1, str_2);
}

unsigned numarMaterii()
{
	return len();
}

Materie* materiiPrime()
{
	return getAll();
}

unsigned short adauga(const char* nume, const char* producator, const char* cantitate)
{
	int cantitateValida = conversieDeLaStringLaIntreg(cantitate);
	if (cantitateValida == -1)
		return 3;
	Materie materie = constructorEntitate(nume, producator, cantitateValida);
	unsigned short err = validareMaterie(materie);
	if (!err)
	{
		unsigned short foobar = adaugaMaterie(materie);
		destructorEntitate(&materie);
		return foobar;
	}
	destructorEntitate(&materie);
	return err + 3;
}

unsigned short modifica(const char* nume, const char* producator, const char* cantitate)
{
	int cantitateValida = conversieDeLaStringLaIntreg(cantitate);
	if (cantitateValida == -1)
		return 2;
	Materie materie = constructorEntitate(nume, producator, cantitateValida);
	unsigned short err = validareMaterie(materie);
	if (!err)
	{
		unsigned char foobar = modificaMaterie(materie);
		destructorEntitate(&materie);
		return foobar;
	}
	destructorEntitate(&materie);
	return err + 2;
}

unsigned short sterge(const char* nume)
{
	return !validareString(nume) ? 2 : stergeMaterie(nume);

	/**
	if (!validareString(nume))
		return 2;
	return stergeMaterie(nume);
	**/
}

Materie* cauta(const char* nume)
{
	return !validareString(nume) ? NULL : cautaDupaNume(nume);

	/**
	if (!validareString(nume))
		return NULL;
	return cautaDupaNume(nume);
	**/
}

unsigned char evaluareCriteriu(const char* criteriu, const unsigned char id_filtru)
{
	if (!id_filtru)
	{
		if (strlen(criteriu) != 1)
			return 0;
		return tolower(criteriu[0]) >= 'a' && tolower(criteriu[0]) <= 'z';
	}
	return conversieDeLaStringLaIntreg(criteriu) != -1;
}

Materie* filtrareMateriiPrime(unsigned* dim, const char* criteriu, const unsigned char id_filtru)
{
	const unsigned numar_materii = numarMaterii();
	Materie* lista_materii = materiiPrime();
	Materie* lista_filtrata = (Materie*)malloc(numar_materii * sizeof(Materie));
	*dim = 0;
	for (unsigned i = 0; i < numar_materii; ++i)
	{
		Materie materie = lista_materii[i];
		unsigned char valid;
		if (!id_filtru)
		{
			const char* nume = getNume(materie);
			valid = (tolower(nume[0]) == tolower(criteriu[0]));
		}
		else valid = (getCantitate(materie) < conversieDeLaStringLaIntreg(criteriu));
		if (valid)
		{
			lista_filtrata[*dim] = materie;
			*dim += 1;
		}
	}
	return lista_filtrata;
}

Materie* sortareMateriiPrime(const unsigned char criteriu, const unsigned char ordine)
{
	const unsigned numar_materii = numarMaterii();
	Materie* lista_sortata = (Materie*)malloc(numar_materii * sizeof(Materie));
	Materie* lista_materii = materiiPrime();
	for (unsigned i = 0; i < numar_materii; lista_sortata[i] = lista_materii[i++]);
	#define interschimbare(type, a, b)\
		{type aux = a; a = b; b = aux;}
	for (unsigned i = 0; i + 1 < numar_materii; ++i)
		for (unsigned j = i + 1; j < numar_materii; ++j)
		{
			int comparare;
			if (!criteriu)
				comparare = _stricmp(getNume(lista_sortata[i]), getNume(lista_sortata[j]));
			else comparare = getCantitate(lista_sortata[i]) - getCantitate(lista_sortata[j]);
			if (!ordine && comparare > 0)
			{
				interschimbare(Materie, lista_sortata[i], lista_sortata[j]);
			}
			else if (ordine && comparare < 0)
			{
				interschimbare(Materie, lista_sortata[i], lista_sortata[j]);
			}
		}
	#undef interschimbare
	return lista_sortata;
}