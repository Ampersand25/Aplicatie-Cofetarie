#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Consola.h"
#include "Servicii.h"

#include <stdio.h>
#include <windows.h>

void afisareMeniu()
{
	puts("Meniu comenzi aplicatie:");
	puts("1 - adaugare de materie prima (daca exista deza in stoc se actualizeaza cantitatea)");
	puts("2 - modificare materie prima");
	puts("3 - stergere materie prima");
	puts("4 - cauta materie prima dupa nume");
	puts("5 - afisare materii prime disponibile in cofetarie");
	puts("6 - vizualizare materii prime care satisfac un criteriu (nume incepe cu o litera data, cantitatea disponibila e mai mica decat un numar dat)");
	puts("7 - vizualizare materii prime din stoc ordonat dupa nume sau cantitate disponibila (crescator/descrescator)");
	puts("8 - refresh ecran (curatare continut terminal/consola)");
	puts("9 - iesire din aplicatie");
}

void tiparireMaterie(const Materie materie)
{
	printf("Nume: %s\n", getNume(materie));
	printf("Producator: %s\n", getProducator(materie));
	printf("Cantitate: % u\n", getCantitate(materie));
	putchar('\n');
}

char* citireStr(const char* mesaj)
{
	printf(mesaj);
	#define DIM 3e+1
	char* s = alocareStr((unsigned)DIM);
	#undef DIM
	gets(s);
	return realocareStr(s);
}

void adaugareMaterie(char* cmd)
{
	puts("Introduceti informatiile pentru materia prima pe care doriti sa o adaugati");

	char* nume = citireStr("Nume: ");
	char* producator = citireStr("Producator: ");
	char* cantitate = citireStr("Cantitate: ");

	unsigned result = adauga(nume, producator, cantitate);
	if(!result)
		printf("Adaugarea a esuat!\nExista deja o materie prima cu numele %s in cofetarie!\n", nume);
	else if (result == 1)
		puts("Adaugarea s-a realizat cu succes!");
	else if (result == 2)
		puts("Materie deja existenta!\nS-a modificat cantitatea!");
	else if (result == 3)
		puts("Cantitate invalida!\nCantitatea introdusa nu este un numar natural!");
	else {
		result -= 3;
		if (result & 4)
			puts("Nume invalid!");
		if (result & 2)
			puts("Producator invalid!");
		if (result & 1)
			puts("Cantitate invalida!");
	}
	putchar('\n');

	dezalocare(nume), dezalocare(producator), dezalocare(cantitate);
}

void modificareMaterie(char* cmd)
{
	unsigned nr_materii_prime = numarMaterii();
	if (!nr_materii_prime)
	{
		puts("Nu exista materii prime in cofetarie!\n");
		return;
	}

	puts("Introduceti informatiile pentru materia prima pe care doriti sa o modificati");

	char* nume = citireStr("Nume: ");
	char* producator = citireStr("Producator: ");
	char* cantitate = citireStr("Cantitate: ");

	unsigned result = modifica(nume, producator, cantitate);
	if(!result)
		printf("Modificarea a esuat!\nNu exista nicio materie prima cu numele %s in cofetarie!\n", nume);
	if (result == 1)
		puts("Modificarea s-a realizat cu succes!");
	else if (result == 2)
		puts("Cantitate invalida!\nCantitatea introdusa nu este un numar natural!");
	else {
		result -= 2;
		if (result & 4)
			puts("Nume invalid!");
		if (result & 2)
			puts("Producator invalid!");
		if (result & 1)
			puts("Cantitate invalida!");
	}
	putchar('\n');

	dezalocare(nume), dezalocare(producator), dezalocare(cantitate);
}

void stergereMaterie(char* cmd)
{
	unsigned nr_materii_prime = numarMaterii();
	if (!nr_materii_prime)
	{
		puts("Nu exista materii prime in cofetarie!\n");
		return;
	}

	char* nume = citireStr("Introduceti numele materiei prime pe care doriti sa o eliminati din cofetarie: ");

	unsigned result = sterge(nume);
	if (!result)
		printf("Stergerea nu a avut loc!\nNu exista nicio materie prima cu numele %s in cofetarie!\n", nume);
	else if(result == 2)
		printf("Stergerea nu a avut loc!\nNume materie prima invalid!\n");
	else puts("Materia prima a fost stearsa cu succes!");
	putchar('\n');

	dezalocare(nume);
}

void cautaMaterie(char* cmd)
{
	unsigned nr_materii_prime = numarMaterii();
	if (!nr_materii_prime)
	{
		puts("Nu exista materii prime in cofetarie!\n");
		return;
	}

	char* nume = citireStr("Introduceti numele materiei prime pe care doriti sa o eliminati din cofetarie: ");

	Materie* materie_cautata = cauta(nume);
	if (!materie_cautata)
		printf("Nu exista nicio materie prima cu numele %s in cofetarie!\n\n", nume);
	else {
		printf("Materia prima cu numele %s este:\n", nume);
		tiparireMaterie(*materie_cautata);
	}

	dezalocare(nume);
}

void afisareLista(const Materie* lista, const unsigned nr_elemente)
{
	for (unsigned i = 0; i < nr_elemente; ++i)
	{
		Materie materie = lista[i];
		printf("Materia prima #%u\n", i + 1);
		tiparireMaterie(materie);
	}
}

void afisareMateriiPrime(char* cmd)
{
	unsigned nr_materii_prime = numarMaterii();
	if (!nr_materii_prime)
	{
		puts("Nu exista materii prime in cofetarie!\n");
		return;
	}
	if (nr_materii_prime == 1)
		printf("Exista o singura materie prima in magazin, ci anume:\n\n");
	else printf("Exista %u materii prime in magazin, ci anume:\n\n", nr_materii_prime);
	Materie* lista_materii = materiiPrime();
	afisareLista(lista_materii, nr_materii_prime);
}

void vizualizareCriteriu(char* cmd)
{
	unsigned nr_materii_prime = numarMaterii();
	if (!nr_materii_prime)
	{
		puts("Nu exista materii prime in cofetarie!\n");
		return;
	}
	char* filtru;
	back:
	printf("Introduceti filtrul dorit [nume/cantitate]: ");
	filtru = citireStr("");
	_strlwr(filtru);
	unsigned char id_filtru;
	if (!strcmp(filtru, "nume"))
	{
		printf("Introduceti litera cu care sa inceapa numele materiilor prime din cofetarie: ");
		id_filtru = 0;
	}
	else if (!strcmp(filtru, "cantitate"))
	{
		printf("Introduceti numarul fata de care cantitatea materiilor prime sa fie mai mica: ");
		id_filtru = 1;
	}
	else {
		puts("Filtrul selectat este invalid!\n");
		dezalocare(filtru);
		goto back;
	}
	char* criteriu = citireStr("");
	unsigned char criteriu_valid = evaluareCriteriu(criteriu, id_filtru);
	if (!criteriu_valid)
	{
		printf("Criteriu inexistent: ");
		if (!id_filtru)
			puts("litera introdusa nu este valida!");
		else puts("cantitatea introdusa nu este valida!");
		putchar('\n');
		goto sf;
	}
	if (!id_filtru)
		printf("Materiile prime din cofetarie care incep cu litera %s sunt: ", criteriu);
	else printf("Materiile prime din cofetarie care au cantitatea mai mica decat %s sunt: ", criteriu);
	unsigned dim;
	Materie* lista_filtrata = filtrareMateriiPrime(&dim, criteriu, id_filtru);
	if (!dim)
		puts("-\n");
	else {
		puts("\n");
		afisareLista(lista_filtrata, dim);
	}
	dezalocare(lista_filtrata);
	sf:
	dezalocare(criteriu), dezalocare(filtru);
}

void vizualizareSortate(char* cmd)
{
	unsigned nr_materii_prime = numarMaterii();
	if (!nr_materii_prime)
	{
		puts("Nu exista materii prime in cofetarie!\n");
		return;
	}
	back:
	;
	char* criteriu = citireStr("Introduceti criteriul de sortare [nume/cantitate]: ");
	_strlwr(criteriu);
	unsigned char crt;
	if (!strcmp(criteriu, "nume"))
		crt = 0;
	else if (!strcmp(criteriu, "cantitate"))
		crt = 1;
	else {
		puts("Criteriu invalid!\n");
		dezalocare(criteriu);
		goto back;
	}
	char* ordine = citireStr("Introduceti ordinea de sortare: [crescator/descrescator]: ");
	_strlwr(ordine);
	unsigned char ord;
	if (!strcmp(ordine, "crescator"))
		ord = 0;
	else if (!strcmp(ordine, "descrescator"))
		ord = 1;
	else {
		puts("Ordine de sortare invalida!");
		goto end;
	}
	Materie* lista_ordonata = sortareMateriiPrime(crt, ord);
	printf("Materiile prime din cofetarie sortate/ordonate %s dupa %s sunt:\n\n", ordine, criteriu);
	afisareLista(lista_ordonata, nr_materii_prime);
	free(lista_ordonata);
	goto dezalocare;
	end:
	putchar('\n');
	dezalocare:
	dezalocare(ordine), dezalocare(criteriu);
}

void refreshTerminal(char* cmd)
{
	#define DIM 3e+1
	char* op = alocareStr((unsigned)DIM);
	#undef DIM
	back:
	printf("Sunteti sigur ca doriti sa dati refresh la ecran? [Y/N]: ");
	scanf_s("\n");
	gets(op);
	if (compareStr(_strupr(op), "Y"))
		system("CLS");
	else if (compareStr(_strupr(op), "N"))
		putchar('\n');
	else {
		puts("Optiune invalida!\n");
		goto back;
	}
	dezalocare(op);
}

void inchidereAplicatie(char* cmd)
{
	#define DIM 3e+1
	char* op = alocareStr((unsigned)DIM);
	#undef DIM
	back:
	printf("Sunteti sigur ca doriti sa iesiti din aplicatie? [Y/N]: ");
	scanf_s("\n");
	gets(op);
	if (compareStr(_strupr(op), "Y"))
	{
		dezalocare(cmd), dezalocare(op);
		finish = 1;
		return;
	}
	else if (compareStr(_strupr(op), "N"))
		putchar('\n');
	else {
		puts("Optiune invalida!\n");
		goto back;
	}
	dezalocare(op);
}

void adaugareMateriiPrime()
{
	adauga("Heidi", "Producator 1", "150");
	adauga("Milka de padure", "Producator 2", "130");
	adauga("Primola cu visine", "Producator 3", "175");
	adauga("Halva", "Producator 4", "120");
	adauga("Milka cu lapte", "Producator 5", "155");
	adauga("Milka cu biscuiti oreo", "Producator 6", "125");
	adauga("Primola cu iaurt de zmeura", "Producator 7", "130");
	adauga("Spuma de ciocolata", "Producator 8", "90");
	adauga("Pernite VIVA", "Producator 9", "105");
	adauga("Mere caramelizate", "Producator 10", "135");
}

void runApplication()
{
	adaugareMateriiPrime();
	#define DIM 3e+1
	char* cmd = alocareStr((unsigned)DIM);
	#undef DIM
	while (!finish)
	{
		afisareMeniu();
		printf("\n>>>");
		//scanf_s("\n");
		gets(cmd);
		if (compareStr(cmd, "1"))
			adaugareMaterie(cmd);
		else if (compareStr(cmd, "2"))
			modificareMaterie(cmd);
		else if (compareStr(cmd, "3"))
			stergereMaterie(cmd);
		else if (compareStr(cmd, "4"))
			cautaMaterie(cmd);
		else if (compareStr(cmd, "5"))
			afisareMateriiPrime(cmd);
		else if (compareStr(cmd, "6"))
			vizualizareCriteriu(cmd);
		else if (compareStr(cmd, "7"))
			vizualizareSortate(cmd);
		else if (compareStr(cmd, "8"))
			refreshTerminal(cmd);
		else if (compareStr(cmd, "9"))
			inchidereAplicatie(cmd);
		else puts("Comanda invalida!\n");
	}
}