#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Repository.h"

#include <stdlib.h>
#include <string.h>

void constructorRepository()
{
	repo.lista_materii = NULL;
	repo.nr_materii = 0;
	repo.capacitate = 0;
}

Materie* getAll()
{
	return repo.lista_materii;
}

unsigned len()
{
	return repo.nr_materii;
}

unsigned capacity()
{
	return repo.capacitate;
}

Materie* cautaDupaNume(const char* nume)
{
	unsigned dimensiune_repo = len();
	for (unsigned i = 0; i < dimensiune_repo; ++i)
		if (!strcmp(getNume(repo.lista_materii[i]), nume))
			return &repo.lista_materii[i];
	return NULL;
}

unsigned short adaugaMaterie(const Materie materie)
{
	unsigned dimensiune_repo = len(), capacitate_repo = capacity();
	if (!dimensiune_repo)
	{
		if (!capacitate_repo)
		{
			#define CAPACITATE 1
			repo.capacitate = CAPACITATE;
			#undef CAPACITATE
			repo.lista_materii = (Materie*)calloc(1, sizeof(Materie));
		}
		//if (repo.lista_materii == NULL)
		//{
		//	perror("Heap Overflow!");
		//	exit(-1);
		//}
		goto adaugare;
	}
	for (unsigned i = 0; i < dimensiune_repo; ++i)
	{
		Materie materie_curenta = repo.lista_materii[i];
		if (equals(materie_curenta, materie))
		{
			if (!strcmp(getProducator(materie_curenta), getProducator(materie)))
			{
				repo.lista_materii[i].cantitate = getCantitate(materie);
				return 2;
			}
			return 0;
		}
	}
	if (dimensiune_repo == capacitate_repo)
	{
		repo.capacitate <<= 1; // repo.capacitate *= 2;
		repo.lista_materii = (Materie*)realloc(repo.lista_materii, repo.capacitate * sizeof(Materie));
	}
	adaugare:
	;
	Materie copie_materie = constructorEntitate(getNume(materie), getProducator(materie), getCantitate(materie));
	repo.lista_materii[repo.nr_materii++] = copie_materie;
	return 1;
}

unsigned char modificaMaterie(const Materie materie)
{
	unsigned dimensiune_repo = len();
	for (unsigned i = 0; i < dimensiune_repo; ++i)
	{
		Materie materie_curenta = repo.lista_materii[i];
		if (equals(materie_curenta, materie))
		{
			setProducator(&repo.lista_materii[i], getProducator(materie));
			setCantitate(&repo.lista_materii[i], getCantitate(materie));
			return 1;
		}
	}
	return 0;
}

unsigned char stergeMaterie(const char* nume)
{
	unsigned dimensiune_repo = len();
	for (unsigned i = 0; i < dimensiune_repo; ++i)
		if (!strcmp(getNume(repo.lista_materii[i]), nume))
		{
			for (unsigned j = i; j + 1 < dimensiune_repo; ++j)
			{
				char* new_nume = getNume(repo.lista_materii[j + 1]);
				unsigned lungime = strlen(new_nume);
				repo.lista_materii[j].nume = (char*)realloc(repo.lista_materii[j].nume, lungime + 1);
				strcpy_s(repo.lista_materii[j].nume, lungime + 1, new_nume);
				setProducator(&repo.lista_materii[j], getProducator(repo.lista_materii[j + 1]));
				setCantitate(&repo.lista_materii[j], getCantitate(repo.lista_materii[j + 1]));
			}
			destructorEntitate(&repo.lista_materii[dimensiune_repo - 1]);
			--repo.nr_materii;
			//repo.lista_materii = (Materie*)realloc(repo.lista_materii, repo.nr_materii * sizeof(Materie));
			return 1;
		}
	return 0;
}

void destructorRepository()
{
	if (repo.lista_materii == NULL)
		return;
	unsigned dimensiune_repo = len();
	for (unsigned i = 0; i < dimensiune_repo; ++i)
		destructorEntitate(&repo.lista_materii[i]);
	free(repo.lista_materii);
}