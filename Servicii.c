#include "Servicii.h"
#include "Repository.h"
#include "Validatori.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
												   // char* mem = (char*)calloc(dim, sizeof(char));
	                                               // char* mem = (char*)calloc(dim, 1);
	//if (mem == NULL)
	//{
	//	perror("Heap Overflow!");
	//	exit(-1);
	//}
	return mem;
}

char* realocareStr(char* str)
{
	const unsigned lungime = strlen(str);
	str = (char*)realloc(str, lungime + 1);
	return str;
}

void dezalocare(void* memory_block)
{
	free(memory_block);
}

unsigned char compareStr(const char* str_1, const char* str_2)
{
	/// Varianta I
	if (!strlen(str_1))
		return !strlen(str_2);
	return !strcmp(str_1, str_2);

	/// Varianta II (cu ternary operator = operator ternar)
	/**
	return !strlen(str_1) ? !strlen(str_2) : !strcmp(str_1, str_2);
	**/
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
	const int cantitateValida = conversieDeLaStringLaIntreg(cantitate);
	if (cantitateValida == -1)
		return 3;
	Materie materie = constructorEntitate(nume, producator, cantitateValida);
	const unsigned short err = validareMaterie(materie);
	if (!err)
	{
		const unsigned short foobar = adaugaMaterie(materie);
		destructorEntitate(&materie);
		return foobar;
	}
	destructorEntitate(&materie);
	return err + 3;
}

unsigned short modifica(const char* nume, const char* producator, const char* cantitate)
{
	const int cantitateValida = conversieDeLaStringLaIntreg(cantitate);
	if (cantitateValida == -1)
		return 2;
	Materie materie = constructorEntitate(nume, producator, cantitateValida);
	const unsigned short err = validareMaterie(materie);
	if (!err)
	{
		const unsigned char foobar = modificaMaterie(materie);
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
	//if (lista_filtrata == NULL)
	//{
	//	perror("Heap Overflow!");
	//	exit(-1);
	//}
	*dim = 0;
	for (unsigned i = 0; i < numar_materii; ++i)
	{
		const Materie materie = lista_materii[i];
		unsigned char valid;
		if (!id_filtru)
		{
			const char* nume = getNume(materie);
			valid = (tolower(nume[0]) == tolower(criteriu[0]));
		}
		else valid = (getCantitate(materie) < (const unsigned)conversieDeLaStringLaIntreg(criteriu));
		if (valid)
		{
			lista_filtrata[*dim] = materie;
			++(*dim);
		}
	}
	return lista_filtrata;
}

int comparareNume(const char* nume_1, const char* nume_2, const unsigned char reversed)
{
	int resultCompare;
	if(!reversed)
		resultCompare = _stricmp(nume_1, nume_2);
	else resultCompare = _stricmp(nume_2, nume_1);
	return resultCompare;
}

int comparareCantitate(const unsigned cantitate_1, const unsigned cantitate_2, const unsigned char reversed)
{
	int resultCompare;
	if (!reversed)
		resultCompare = cantitate_1 - cantitate_2;
	else resultCompare = cantitate_2 - cantitate_1;
	return resultCompare;
}

unsigned char comparareNumeGen(const Materie materie_1, const Materie materie_2, const unsigned char reversed)
{
	const int resultCompare = comparareNume(getNume(materie_1), getNume(materie_2), reversed);
	return resultCompare <= 0; // return (resultCompare <= 0) ? (1) : (0);
}

unsigned char comparareCantitateGen(const Materie materie_1, const Materie materie_2, const unsigned char reversed)
{
	const int resultCompare = comparareCantitate(getCantitate(materie_1), getCantitate(materie_2), reversed);
	return resultCompare <= 0; // return (resultCompare <= 0) ? (1) : (0);
}

Materie* sortareMateriiPrime(const unsigned char reversed, unsigned char (*comparare)(const Materie, const Materie, const unsigned char))
{
	const unsigned numar_materii = numarMaterii();
	Materie* lista_sortata = (Materie*)malloc(numar_materii * sizeof(Materie));
	//if (lista_sortata == NULL)
	//{
	//	perror("Heap Overflow!");
	//	exit(-1);
	//}
	const Materie* lista_materii = materiiPrime();
	for (unsigned i = 0; i < numar_materii; lista_sortata[i] = lista_materii[i++]);
	#define interschimbare(type, a, b)\
		{type aux = a; a = b; b = aux;}
	for (unsigned i = 0; i + 1 < numar_materii; ++i)
		for (unsigned j = i + 1; j < numar_materii; ++j)
		{
			const unsigned char resultCompare = comparare(lista_sortata[i], lista_sortata[j], reversed);
			if(!resultCompare)
				interschimbare(Materie, lista_sortata[i], lista_sortata[j]);
		}
	#undef interschimbare
	return lista_sortata;
}