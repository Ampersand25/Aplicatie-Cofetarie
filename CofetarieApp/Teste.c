#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Teste.h"
#include "Entitati.h"
#include "Servicii.h"
#include "Repository.h"
#include "Validatori.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

void functieTestEntitate(const Materie materie, const char* nume, const char* producator, const unsigned cantitate)
{
	assert(!strcmp(getNume(materie), nume));
	assert(!strcmp(getProducator(materie), producator));
	assert(getCantitate(materie) == cantitate);
}

/// Teste pentru layerul (stratul) de domeniu (reprezentarea/modelarea obiectelor din lumea reala ca si entitati matematice)
void ruleazaTesteConstructorDestructorEntitate()
{
	Materie materie = constructorEntitate("Prajitura cu visine", "Napoca Sweet World", 85);
	destructorEntitate(&materie);
}

void ruleazaTesteGetters()
{
	Materie materie;

	materie = constructorEntitate("Cheesecake", "Alpina", 150);
	assert(!strcmp(getNume(materie), "Cheesecake"));
	assert(!strcmp(getProducator(materie), "Alpina"));
	assert(getCantitate(materie) == 150);
	destructorEntitate(&materie);

	materie = constructorEntitate("Tort cu ciocolata", "Lemnul Verde", 25);
	assert(!strcmp(getNume(materie), "Tort cu ciocolata"));
	assert(!strcmp(getProducator(materie), "Lemnul Verde"));
	assert(getCantitate(materie) == 25);
	destructorEntitate(&materie);

	materie = constructorEntitate("Prajitura cu vanilie si menta", "Heidi", 55);
	assert(!strcmp(getNume(materie), "Prajitura cu vanilie si menta"));
	assert(!strcmp(getProducator(materie), "Heidi"));
	assert(getCantitate(materie) == 55);
	destructorEntitate(&materie);
}

void ruleazaTesteSetters()
{
	Materie materie = constructorEntitate("Prajitura cu vanilie si menta", "Heidi", 55);

	setCantitate(&materie, 35000);
	assert(!strcmp(getNume(materie), "Prajitura cu vanilie si menta"));
	assert(!strcmp(getProducator(materie), "Heidi"));
	assert(getCantitate(materie) == 35000);

	setProducator(&materie, "Milka US");
	assert(!strcmp(getNume(materie), "Prajitura cu vanilie si menta"));
	assert(!strcmp(getProducator(materie), "Milka US"));
	assert(getCantitate(materie) == 35000);

	setCantitate(&materie, 15), setProducator(&materie, "Primola UK");
	assert(!strcmp(getNume(materie), "Prajitura cu vanilie si menta"));
	assert(!strcmp(getProducator(materie), "Primola UK"));
	assert(getCantitate(materie) == 15);

	destructorEntitate(&materie);
}

void ruleazaTesteEquals()
{
	Materie materie = constructorEntitate("Prajitura cu vanilie si menta", "Primola", 175);
	Materie materie_noua;

	materie_noua = constructorEntitate("Tort cu ciocolata", "Heidi", 75);
	assert(!equals(materie, materie_noua));
	destructorEntitate(&materie_noua);

	materie_noua = constructorEntitate("Cheesecake", "Alpina", 55);
	assert(!equals(materie, materie_noua));
	destructorEntitate(&materie_noua);

	materie_noua = constructorEntitate("Cheesecake", "Primola", 35);
	assert(!equals(materie, materie_noua));
	destructorEntitate(&materie_noua);

	materie_noua = constructorEntitate("Cheesecake", "Napoca", 175);
	assert(!equals(materie, materie_noua));
	destructorEntitate(&materie_noua);

	materie_noua = constructorEntitate("Cheesecake", "Primola", 175);
	assert(!equals(materie, materie_noua));
	destructorEntitate(&materie_noua);

	materie_noua = constructorEntitate("Prajitura cu vanilie si menta", "Lemnul Verde", 150);
	assert(equals(materie, materie_noua));
	destructorEntitate(&materie_noua);

	destructorEntitate(&materie);
}

void ruleazaTesteDomeniu()
{
	ruleazaTesteConstructorDestructorEntitate();
	ruleazaTesteGetters();
	ruleazaTesteSetters();
	ruleazaTesteEquals();
}

/// Teste pentru layerul (stratul) de business (servicii)
void ruleazaTesteConversieDeLaStringLaIntreg()
{
	assert(conversieDeLaStringLaIntreg("") == -1);
	assert(conversieDeLaStringLaIntreg("356a") == -1);
	assert(conversieDeLaStringLaIntreg("H356") == -1);
	assert(conversieDeLaStringLaIntreg("356upUEaVa683ua3") == -1);
	assert(conversieDeLaStringLaIntreg("_*32fgd*fas*") == -1);
	assert(conversieDeLaStringLaIntreg("35g67fa3297") == -1);
	assert(conversieDeLaStringLaIntreg("fds4_32asfiu2* 1") == -1);
	assert(conversieDeLaStringLaIntreg("7823 47") == -1);
	assert(conversieDeLaStringLaIntreg("_47812") == -1);
	assert(conversieDeLaStringLaIntreg("3892|43&123") == -1);
	assert(conversieDeLaStringLaIntreg("89231 ") == -1);
	assert(conversieDeLaStringLaIntreg("7689344654.") == -1);
	
	assert(conversieDeLaStringLaIntreg("0") == 0);
	assert(conversieDeLaStringLaIntreg("6") == 6);
	assert(conversieDeLaStringLaIntreg("23") == 23);
	assert(conversieDeLaStringLaIntreg("80") == 80);
	assert(conversieDeLaStringLaIntreg("100") == 100);
	assert(conversieDeLaStringLaIntreg("923") == 923);
	assert(conversieDeLaStringLaIntreg("301") == 301);
	assert(conversieDeLaStringLaIntreg("1849") == 1849);
	assert(conversieDeLaStringLaIntreg("1000") == 1000);
	assert(conversieDeLaStringLaIntreg("78412") == 78412);
	assert(conversieDeLaStringLaIntreg("982300") == 982300);
	assert(conversieDeLaStringLaIntreg("30031040") == 30031040);
}

void ruleazaTesteAlocareStr()
{
	char* string;
	
	string = alocareStr(0);
	assert(string == NULL);

	string = alocareStr(1);
	assert(string != NULL);
	dezalocare(string);

	string = alocareStr(5);
	assert(string != NULL);
	dezalocare(string);

	string = alocareStr((unsigned)10);
	assert(string != NULL);
	dezalocare(string);

	string = alocareStr((unsigned)15);
	assert(string != NULL);
	dezalocare(string);

	string = alocareStr((unsigned)20);
	assert(string != NULL);
	dezalocare(string);

	string = alocareStr((unsigned)25);
	assert(string != NULL);
	dezalocare(string);

	string = alocareStr((unsigned)30);
	assert(string != NULL);
	dezalocare(string);
}

void ruleazaTesteRealocareStr()
{
	char* string;
	
	string = alocareStr(10);
	assert(string != NULL);
	
	strcpy(string, "12345");
	string = realocareStr(string);
	assert(string != NULL);

	strcpy(string, "12345678");
	string = realocareStr(string);
	assert(string != NULL);

	strcpy(string, "123");
	string = realocareStr(string);
	assert(string != NULL);

	strcpy(string, "1234");
	string = realocareStr(string);
	assert(string != NULL);

	dezalocare(string);

	string = alocareStr(10);
	assert(string != NULL);

	dezalocare(string);
}

void ruleazaTesteCompareStr()
{
	assert(compareStr("a", "a"));
	assert(compareStr("", ""));
	assert(compareStr("abc", "abc"));
	assert(compareStr("a bc defgh", "a bc defgh"));
	assert(compareStr("Ana are 15 mere si 54 de pere!", "Ana are 15 mere si 54 de pere!"));

	assert(!compareStr("a", "ab"));
	assert(!compareStr("ab", "a"));
	assert(!compareStr(" ", ""));
	assert(!compareStr("", " "));
	assert(!compareStr("abc", "cbc"));
	assert(!compareStr("cba", "abc"));
	assert(!compareStr("a bc degfh", "a bc defgh"));
	assert(!compareStr("a bc defgh", "a bc degfh"));
	assert(!compareStr("Ana are 15 mere si 54 de pere!", "Ana are 15 mere si 54 de pere."));
	assert(!compareStr("Ana are 15 mere si 54 de pere.", "Ana are 15 mere si 54 de pere!"));

	assert(compareStr("", ""));
	assert(compareStr("abc", "abc"));
	assert(compareStr("Ana are multe mere!", "Ana are multe mere!"));
	assert(compareStr("381afr82FiOP902_328IF", "381afr82FiOP902_328IF"));
	assert(compareStr(".", "."));
}

void ruleazaTesteNumarMaterii()
{
	constructorRepository();

	Materie materie;

	assert(!numarMaterii());

	adauga("Materie prima 1", "producator 1", "1");

	assert(numarMaterii() == 1);

	adauga("Materie prima 2", "producator 2", "2");

	assert(numarMaterii() == 2);

	adauga("Materie prima 3", "producator 3", "3");

	assert(numarMaterii() == 3);

	adauga("Materie prima 3", "producator 3", "300");

	assert(numarMaterii() == 3);

	adauga("Materie prima 2", "producator nou 2", "2");

	assert(numarMaterii() == 3);

	adauga("Materie prima 1", "producator nou 1", "100");

	assert(numarMaterii() == 3);

	destructorRepository();
}

void ruleazaTesteMateriiPrime()
{
	constructorRepository();

	Materie materie;

	assert(materiiPrime() == NULL);

	adauga("Materie prima 1", "producator 1", "1");

	Materie* materii;

	adauga("Materie prima 1", "producator 1", "1");
	materii = materiiPrime();
	assert(materii != NULL);
	functieTestEntitate(materii[0], "Materie prima 1", "producator 1", 1);

	adauga("Materie prima 2", "producator 2", "2");
	materii = materiiPrime();
	assert(materii != NULL);
	functieTestEntitate(materii[0], "Materie prima 1", "producator 1", 1);
	functieTestEntitate(materii[1], "Materie prima 2", "producator 2", 2);

	adauga("Materie prima 3", "producator 3", "3");
	materii = materiiPrime();
	assert(materii != NULL);
	functieTestEntitate(materii[0], "Materie prima 1", "producator 1", 1);
	functieTestEntitate(materii[1], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(materii[2], "Materie prima 3", "producator 3", 3);

	adauga("Materie prima 3", "producator 3", "300");
	materii = materiiPrime();
	assert(materii != NULL);
	functieTestEntitate(materii[0], "Materie prima 1", "producator 1", 1);
	functieTestEntitate(materii[1], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(materii[2], "Materie prima 3", "producator 3", 300);

	adauga("Materie prima 2", "producator nou 2", "2");
	materii = materiiPrime();
	assert(materii != NULL);
	functieTestEntitate(materii[0], "Materie prima 1", "producator 1", 1);
	functieTestEntitate(materii[1], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(materii[2], "Materie prima 3", "producator 3", 300);

	adauga("Materie prima 1", "producator nou 1", "100");
	materii = materiiPrime();
	assert(materii != NULL);
	functieTestEntitate(materii[0], "Materie prima 1", "producator 1", 1);
	functieTestEntitate(materii[1], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(materii[2], "Materie prima 3", "producator 3", 300);

	destructorRepository();
}

void ruleazaTesteAdauga()
{
	constructorRepository();

	assert(!repo.nr_materii);
	assert(repo.lista_materii == NULL);

	assert(adauga("Materie prima", "producator", "") == 3);
	assert(adauga("Materie prima", "", "abc") == 3);
	assert(adauga("", "producator", "-10") == 3);
	assert(adauga("", "", "3510 ") == 3);
	assert(!repo.nr_materii);
	assert(repo.lista_materii == NULL);

	assert(adauga("Materie prima", "producator", "0") == 4);
	assert(adauga("Materie prima", "", "1") == 5);
	assert(adauga("Materie prima", "", "0") == 6);
	assert(adauga("", "producator", "1") == 7);
	assert(adauga("", "producator", "0") == 8);
	assert(adauga("", "", "1") == 9);
	assert(adauga("", "", "0") == 10);
	assert(!repo.nr_materii);
	assert(repo.lista_materii == NULL);

	assert(adauga("Materie prima", "producator", "1") == 1);
	assert(repo.nr_materii == 1);
	assert(repo.lista_materii != NULL);

	assert(!adauga("Materie prima", "producator nou", "10"));
	assert(repo.nr_materii == 1);
	assert(repo.lista_materii != NULL);

	assert(!adauga("Materie prima", "producator nou", "1"));
	assert(repo.nr_materii == 1);
	assert(repo.lista_materii != NULL);

	assert(adauga("Materie prima", "producator", "15") == 2);
	assert(repo.nr_materii == 1);
	assert(repo.lista_materii != NULL);

	destructorRepository();
}

void ruleazaTesteModifica()
{
	constructorRepository();

	assert(!numarMaterii());
	assert(materiiPrime() == NULL);

	assert(modifica("", "", "-1") == 2);
	assert(modifica("Materie prima", "", "") == 2);
	assert(modifica("", "producator", "aBCdeF") == 2);
	assert(modifica("Materie prima", "producator", "1ag39f101byi0") == 2);

	assert(!numarMaterii());
	assert(materiiPrime() == NULL);

	assert(modifica("Materie prima", "producator", "0") == 3);
	assert(modifica("Materie prima", "", "1") == 4);
	assert(modifica("Materie prima", "", "0") == 5);
	assert(modifica("", "producator", "1") == 6);
	assert(modifica("", "producator", "0") == 7);
	assert(modifica("", "", "1") == 8);
	assert(modifica("", "", "0") == 9);

	assert(!numarMaterii());
	assert(materiiPrime() == NULL);

	adauga("Materie prima 1", "producator 1", "1");
	assert(numarMaterii() == 1);
	assert(materiiPrime() != NULL);

	assert(modifica("Materie prima 1", "producator nou 1", "2") == 1);
	assert(numarMaterii() == 1);
	assert(materiiPrime() != NULL);

	assert(!modifica("Materie prima 2", "producator 1", "1"));
	assert(numarMaterii() == 1);
	assert(materiiPrime() != NULL);

	destructorRepository();
}

void ruleazaTesteSterge()
{
	constructorRepository();

	assert(!numarMaterii());

	assert(sterge("") == 2);

	assert(!sterge("Heidi"));

	adauga("Heidi", "producator Heidi", "50");
	assert(numarMaterii() == 1);

	assert(sterge("Heidi") == 1);
	assert(!numarMaterii());

	adauga("Primola cu visine", "producator Primola", "25");
	assert(numarMaterii() == 1);

	adauga("Napolitane", "producator napolitane", "105");
	assert(numarMaterii() == 2);

	adauga("Corn cu ciocolata", "producator corn", "85");
	assert(numarMaterii() == 3);

	assert(sterge("Napolitane") == 1);
	assert(numarMaterii() == 2);

	assert(!sterge("Napolitane"));
	assert(numarMaterii() == 2);

	assert(sterge("Primola cu visine") == 1);
	assert(numarMaterii() == 1);

	assert(!sterge("Primola cu visine"));
	assert(numarMaterii() == 1);

	assert(!sterge("Napolitane"));
	assert(numarMaterii() == 1);

	assert(sterge("Corn cu ciocolata") == 1);
	assert(!numarMaterii());

	assert(!sterge("Primola cu visine"));
	assert(!numarMaterii());

	assert(!sterge("Napolitane"));
	assert(!numarMaterii());

	assert(!sterge("Corn cu ciocolata"));
	assert(!numarMaterii());

	destructorRepository();
}

void ruleazaTestCauta()
{
	constructorRepository();

	Materie* materie_cautata;

	materie_cautata = cauta("Halva");
	assert(materie_cautata == NULL);

	adauga("Halva", "producator", "1");

	materie_cautata = cauta("Halva");
	assert(materie_cautata != NULL);
	functieTestEntitate(*materie_cautata, "Halva", "producator", 1);

	materie_cautata = cauta("halva");
	assert(materie_cautata == NULL);

	sterge("Halva");

	materie_cautata = cauta("Halva");
	assert(materie_cautata == NULL);

	adauga("Perne VIVA", "producator 1", "1");
	adauga("Biscuiti cu lapte", "producator 2", "2");
	adauga("Oreo cu crema", "producator 3", "3");

	materie_cautata = cauta("Perne VIVA");
	assert(materie_cautata != NULL);
	functieTestEntitate(*materie_cautata, "Perne VIVA", "producator 1", 1);

	materie_cautata = cauta("Biscuiti cu lapte");
	assert(materie_cautata != NULL);
	functieTestEntitate(*materie_cautata, "Biscuiti cu lapte", "producator 2", 2);

	materie_cautata = cauta("Oreo cu crema");
	assert(materie_cautata != NULL);
	functieTestEntitate(*materie_cautata, "Oreo cu crema", "producator 3", 3);

	sterge("Biscuiti cu lapte");

	materie_cautata = cauta("Biscuiti cu lapte");
	assert(materie_cautata == NULL);

	sterge("Oreo cu crema");

	materie_cautata = cauta("Oreo cu crema");
	assert(materie_cautata == NULL);

	sterge("Perne VIVA");

	materie_cautata = cauta("Perne VIVA");
	assert(materie_cautata == NULL);

	destructorRepository();
}

void ruleazaTesteEvaluareCriteriu()
{
	// Testare criteriu 0 (nume)
	assert(!evaluareCriteriu("", 0));
	assert(!evaluareCriteriu("ab", 0));
	assert(!evaluareCriteriu("123", 0));

	assert(!evaluareCriteriu("4", 0));
	assert(!evaluareCriteriu(".", 0));
	assert(!evaluareCriteriu("-", 0));

	assert(evaluareCriteriu("A", 0));
	assert(evaluareCriteriu("b", 0));
	assert(evaluareCriteriu("z", 0));

	// Testare criteriu 1 (cantitate)
	assert(!evaluareCriteriu("49f14", 1));
	assert(!evaluareCriteriu("948b", 1));
	assert(!evaluareCriteriu("8avx", 1));

	assert(evaluareCriteriu("59", 1));
	assert(evaluareCriteriu("3164", 1));
	assert(evaluareCriteriu("1", 1));
}

void ruleazaTesteFiltrareMateriiPrimeCriteriuNume()
{
	constructorRepository();

	adauga("Milka cu visine", "producator materie prima 1", "50");
	adauga("Heidi", "producator materie prima 2", "75");
	adauga("Primola", "producator materie prima 3", "65");
	adauga("Milka cu caise", "producator materie prima 4", "25");
	adauga("Primola cu capsuni", "producator materie prima 5", "40");
	adauga("Primola Premium", "producator materie prima 6", "30");

	unsigned dim = 0;

	Materie* lista_filtrata;

	lista_filtrata = filtrareMateriiPrime(&dim, "m", 0);
	assert(dim == 2);
	functieTestEntitate(lista_filtrata[0], "Milka cu visine", "producator materie prima 1", 50);
	functieTestEntitate(lista_filtrata[1], "Milka cu caise", "producator materie prima 4", 25);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "P", 0);
	assert(dim == 3);
	functieTestEntitate(lista_filtrata[0], "Primola", "producator materie prima 3", 65);
	functieTestEntitate(lista_filtrata[1], "Primola cu capsuni", "producator materie prima 5", 40);
	functieTestEntitate(lista_filtrata[2], "Primola Premium", "producator materie prima 6", 30);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "h", 0);
	assert(dim == 1);
	functieTestEntitate(lista_filtrata[0], "Heidi", "producator materie prima 2", 75);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "l", 0);
	assert(!dim);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "Z", 0);
	assert(!dim);
	free(lista_filtrata);

	destructorRepository();
}

void ruleazaTesteFiltrareMateriiPrimeCriteriuCantitate()
{
	constructorRepository();

	adauga("Milka cu visine", "producator materie prima 1", "50");
	adauga("Heidi", "producator materie prima 2", "75");
	adauga("Primola", "producator materie prima 3", "65");
	adauga("Milka cu caise", "producator materie prima 4", "25");
	adauga("Primola cu capsuni", "producator materie prima 5", "40");
	adauga("Primola Premium", "producator materie prima 6", "30");

	unsigned dim = 0;

	Materie* lista_filtrata;

	lista_filtrata = filtrareMateriiPrime(&dim, "0", 1);
	assert(!dim);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "10", 1);
	assert(!dim);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "25", 1);
	assert(!dim);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "30", 1);
	assert(dim == 1);
	functieTestEntitate(lista_filtrata[0], "Milka cu caise", "producator materie prima 4", 25);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "40", 1);
	assert(dim == 2);
	functieTestEntitate(lista_filtrata[0], "Milka cu caise", "producator materie prima 4", 25);
	functieTestEntitate(lista_filtrata[1], "Primola Premium", "producator materie prima 6", 30);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "50", 1);
	assert(dim == 3);
	functieTestEntitate(lista_filtrata[0], "Milka cu caise", "producator materie prima 4", 25);
	functieTestEntitate(lista_filtrata[1], "Primola cu capsuni", "producator materie prima 5", 40);
	functieTestEntitate(lista_filtrata[2], "Primola Premium", "producator materie prima 6", 30);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "65", 1);
	assert(dim == 4);
	functieTestEntitate(lista_filtrata[0], "Milka cu visine", "producator materie prima 1", 50);
	functieTestEntitate(lista_filtrata[1], "Milka cu caise", "producator materie prima 4", 25);
	functieTestEntitate(lista_filtrata[2], "Primola cu capsuni", "producator materie prima 5", 40);
	functieTestEntitate(lista_filtrata[3], "Primola Premium", "producator materie prima 6", 30);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "70", 1);
	assert(dim == 5);
	functieTestEntitate(lista_filtrata[0], "Milka cu visine", "producator materie prima 1", 50);
	functieTestEntitate(lista_filtrata[1], "Primola", "producator materie prima 3", 65);
	functieTestEntitate(lista_filtrata[2], "Milka cu caise", "producator materie prima 4", 25);
	functieTestEntitate(lista_filtrata[3], "Primola cu capsuni", "producator materie prima 5", 40);
	functieTestEntitate(lista_filtrata[4], "Primola Premium", "producator materie prima 6", 30);
	free(lista_filtrata);

	lista_filtrata = filtrareMateriiPrime(&dim, "80", 1);
	assert(dim == 6);
	functieTestEntitate(lista_filtrata[0], "Milka cu visine", "producator materie prima 1", 50);
	functieTestEntitate(lista_filtrata[1], "Heidi", "producator materie prima 2", 75);
	functieTestEntitate(lista_filtrata[2], "Primola", "producator materie prima 3", 65);
	functieTestEntitate(lista_filtrata[3], "Milka cu caise", "producator materie prima 4", 25);
	functieTestEntitate(lista_filtrata[4], "Primola cu capsuni", "producator materie prima 5", 40);
	functieTestEntitate(lista_filtrata[5], "Primola Premium", "producator materie prima 6", 30);
	free(lista_filtrata);

	destructorRepository();
}

void ruleazaTesteFiltrareMateriiPrime()
{
	ruleazaTesteFiltrareMateriiPrimeCriteriuNume();
	ruleazaTesteFiltrareMateriiPrimeCriteriuCantitate();
}

void ruleazaTesteSortareMateriiPrimeCriteriuNumeCrescator()
{
	constructorRepository();

	adauga("Milka cu visine", "producator materie prima 1", "50");
	adauga("Heidi", "producator materie prima 2", "75");
	adauga("Primola", "producator materie prima 3", "65");
	adauga("Milka cu caise", "producator materie prima 4", "25");
	adauga("Primola cu capsuni", "producator materie prima 5", "40");
	adauga("Primola Premium", "producator materie prima 6", "30");

	Materie* lista_sortata = sortareMateriiPrime(0, 0);

	functieTestEntitate(lista_sortata[0], "Heidi", "producator materie prima 2", 75);
	functieTestEntitate(lista_sortata[1], "Milka cu caise", "producator materie prima 4", 25);
	functieTestEntitate(lista_sortata[2], "Milka cu visine", "producator materie prima 1", 50);
	functieTestEntitate(lista_sortata[3], "Primola", "producator materie prima 3", 65);
	functieTestEntitate(lista_sortata[4], "Primola cu capsuni", "producator materie prima 5", 40);
	functieTestEntitate(lista_sortata[5], "Primola Premium", "producator materie prima 6", 30);

	free(lista_sortata);

	destructorRepository();
}

void ruleazaTesteSortareMateriiPrimeCriteriuNumeDescrescator()
{
	constructorRepository();

	adauga("Milka cu visine", "producator materie prima 1", "50");
	adauga("Heidi", "producator materie prima 2", "75");
	adauga("Primola", "producator materie prima 3", "65");
	adauga("Milka cu caise", "producator materie prima 4", "25");
	adauga("Primola cu capsuni", "producator materie prima 5", "40");
	adauga("Primola Premium", "producator materie prima 6", "30");

	Materie* lista_sortata = sortareMateriiPrime(0, 1);

	functieTestEntitate(lista_sortata[0], "Primola Premium", "producator materie prima 6", 30);
	functieTestEntitate(lista_sortata[1], "Primola cu capsuni", "producator materie prima 5", 40);
	functieTestEntitate(lista_sortata[2], "Primola", "producator materie prima 3", 65);
	functieTestEntitate(lista_sortata[3], "Milka cu visine", "producator materie prima 1", 50);
	functieTestEntitate(lista_sortata[4], "Milka cu caise", "producator materie prima 4", 25);
	functieTestEntitate(lista_sortata[5], "Heidi", "producator materie prima 2", 75);

	free(lista_sortata);

	destructorRepository();
}

void ruleazaTesteSortareMateriiPrimeCriteriuNume()
{
	ruleazaTesteSortareMateriiPrimeCriteriuNumeCrescator();
	ruleazaTesteSortareMateriiPrimeCriteriuNumeDescrescator();
}

void ruleazaTesteSortareMateriiPrimeCriteriuCantitateCrescator()
{
	constructorRepository();

	adauga("Milka cu visine", "producator materie prima 1", "50");
	adauga("Heidi", "producator materie prima 2", "75");
	adauga("Primola", "producator materie prima 3", "65");
	adauga("Milka cu caise", "producator materie prima 4", "25");
	adauga("Primola cu capsuni", "producator materie prima 5", "40");
	adauga("Primola Premium", "producator materie prima 6", "30");

	Materie* lista_sortata = sortareMateriiPrime(1, 0);

	functieTestEntitate(lista_sortata[0], "Milka cu caise", "producator materie prima 4", 25);
	functieTestEntitate(lista_sortata[1], "Primola Premium", "producator materie prima 6", 30);
	functieTestEntitate(lista_sortata[2], "Primola cu capsuni", "producator materie prima 5", 40);
	functieTestEntitate(lista_sortata[3], "Milka cu visine", "producator materie prima 1", 50);
	functieTestEntitate(lista_sortata[4], "Primola", "producator materie prima 3", 65);
	functieTestEntitate(lista_sortata[5], "Heidi", "producator materie prima 2", 75);

	free(lista_sortata);

	destructorRepository();
}

void ruleazaTesteSortareMateriiPrimeCriteriuCantitateDescrescator()
{
	constructorRepository();

	adauga("Milka cu visine", "producator materie prima 1", "50");
	adauga("Heidi", "producator materie prima 2", "75");
	adauga("Primola", "producator materie prima 3", "65");
	adauga("Milka cu caise", "producator materie prima 4", "25");
	adauga("Primola cu capsuni", "producator materie prima 5", "40");
	adauga("Primola Premium", "producator materie prima 6", "30");

	Materie* lista_sortata = sortareMateriiPrime(1, 1);

	functieTestEntitate(lista_sortata[0], "Heidi", "producator materie prima 2", 75);
	functieTestEntitate(lista_sortata[1], "Primola", "producator materie prima 3", 65);
	functieTestEntitate(lista_sortata[2], "Milka cu visine", "producator materie prima 1", 50);
	functieTestEntitate(lista_sortata[3], "Primola cu capsuni", "producator materie prima 5", 40);
	functieTestEntitate(lista_sortata[4], "Primola Premium", "producator materie prima 6", 30);
	functieTestEntitate(lista_sortata[5], "Milka cu caise", "producator materie prima 4", 25);

	free(lista_sortata);

	destructorRepository();
}

void ruleazaTesteSortareMateriiPrimeCriteriuCantitate()
{
	ruleazaTesteSortareMateriiPrimeCriteriuCantitateCrescator();
	ruleazaTesteSortareMateriiPrimeCriteriuCantitateDescrescator();
}

void ruleazaTesteSortareMateriiPrime()
{
	ruleazaTesteSortareMateriiPrimeCriteriuNume();
	ruleazaTesteSortareMateriiPrimeCriteriuCantitate();
}

void ruleazaTesteBusiness()
{
	ruleazaTesteConversieDeLaStringLaIntreg();
	ruleazaTesteAlocareStr();
	ruleazaTesteRealocareStr();
	ruleazaTesteCompareStr();
	ruleazaTesteNumarMaterii();
	ruleazaTesteMateriiPrime();
	ruleazaTesteAdauga();
	ruleazaTesteModifica();
	ruleazaTesteSterge();
	ruleazaTestCauta();
	ruleazaTesteEvaluareCriteriu();
	ruleazaTesteFiltrareMateriiPrime();
	ruleazaTesteSortareMateriiPrime();
}

/// Teste pentru layerul (stratul) de infrastructura (persistenta datelor, adica repository)
void ruleazaTesteConstructorDestructorRepo()
{
	constructorRepository();
	
	assert(repo.nr_materii == NULL);
	assert(!repo.nr_materii);
	assert(!repo.capacitate);

	destructorRepository();
}

void ruleazaTesteAdaugaMaterie()
{
	constructorRepository();
	assert(repo.lista_materii == NULL);
	assert(!repo.nr_materii);
	assert(!repo.capacitate);
	
	Materie materie;
	
	// Adaugare 1
	materie = constructorEntitate("Materie prima 1", "producator 1", 1);
	assert(adaugaMaterie(materie) == 1);
	destructorEntitate(&materie);

	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 1);
	assert(repo.capacitate == 1);
	
	// Adaugare 2
	materie = constructorEntitate("Materie prima 2", "producator 2", 2);
	assert(adaugaMaterie(materie) == 1);
	destructorEntitate(&materie);

	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 2);
	assert(repo.capacitate == 2);
	
	// Adaugare 3
	materie = constructorEntitate("Materie prima 3", "producator 3", 3);
	assert(adaugaMaterie(materie) == 1);
	destructorEntitate(&materie);
	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 3);
	assert(repo.capacitate == 4);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator 1", 1);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(repo.lista_materii[2], "Materie prima 3", "producator 3", 3);

	// Incercare adaugare 1
	materie = constructorEntitate("Materie prima 1", "producator 4", 4);
	assert(!adaugaMaterie(materie));
	destructorEntitate(&materie);
	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 3);
	assert(repo.capacitate == 4);

	// Incercare adaugare 2
	materie = constructorEntitate("Materie prima 2", "producator 4", 4);
	assert(!adaugaMaterie(materie));
	destructorEntitate(&materie);
	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 3);
	assert(repo.capacitate == 4);

	// Incercare adaugare 3
	materie = constructorEntitate("Materie prima 3", "producator 4", 4);
	assert(!adaugaMaterie(materie));
	destructorEntitate(&materie);
	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 3);
	assert(repo.capacitate == 4);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator 1", 1);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(repo.lista_materii[2], "Materie prima 3", "producator 3", 3);

	// Adaugare 4
	materie = constructorEntitate("Materie prima 4", "producator 4", 4);
	assert(adaugaMaterie(materie) == 1);
	destructorEntitate(&materie);
	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 4);
	assert(repo.capacitate == 4);
	
	functieTestEntitate(repo.lista_materii[3], "Materie prima 4", "producator 4", 4);

	// Adaugare modificare cantitate 1
	materie = constructorEntitate("Materie prima 1", "producator 1", 11);
	assert(adaugaMaterie(materie) == 2);
	destructorEntitate(&materie);
	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 4);
	assert(repo.capacitate == 4);

	// Adaugare modificare cantitate 2
	materie = constructorEntitate("Materie prima 2", "producator 2", 12);
	assert(adaugaMaterie(materie) == 2);
	destructorEntitate(&materie);
	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 4);
	assert(repo.capacitate == 4);

	// Adaugare modificare cantitate 3
	materie = constructorEntitate("Materie prima 3", "producator 3", 13);
	assert(adaugaMaterie(materie) == 2);
	destructorEntitate(&materie);
	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 4);
	assert(repo.capacitate == 4);

	// Adaugare modificare cantitate 4
	materie = constructorEntitate("Materie prima 4", "producator 4", 14);
	assert(adaugaMaterie(materie) == 2);
	destructorEntitate(&materie);
	assert(repo.lista_materii != NULL);
	assert(repo.nr_materii == 4);
	assert(repo.capacitate == 4);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator 1", 11);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator 2", 12);
	functieTestEntitate(repo.lista_materii[2], "Materie prima 3", "producator 3", 13);
	functieTestEntitate(repo.lista_materii[3], "Materie prima 4", "producator 4", 14);

	destructorRepository();
}

void ruleazaTesteLen()
{
	constructorRepository();

	assert(!len());

	Materie materie;

	materie = constructorEntitate("Materie prima 1", "producator 1", 1);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(len() == 1);

	materie = constructorEntitate("Materie prima 2", "producator 2", 2);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(len() == 2);

	materie = constructorEntitate("Materie prima 1", "producator nou 1", 101);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(len() == 2);

	materie = constructorEntitate("Materie prima 2", "producator nou 2", 102);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(len() == 2);

	materie = constructorEntitate("Materie prima 3", "producator 3", 3);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(len() == 3);

	materie = constructorEntitate("Materie prima 3", "producator nou 3", 103);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(len() == 3);

	materie = constructorEntitate("Materie prima 1", "producator 1", 101);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(len() == 3);

	materie = constructorEntitate("Materie prima 2", "producator 2", 102);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(len() == 3);

	materie = constructorEntitate("Materie prima 3", "producator 3", 103);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(len() == 3);

	destructorRepository();
}

void ruleazaTesteCapacity()
{
	constructorRepository();

	assert(!capacity());

	Materie materie;

	materie = constructorEntitate("Materie prima 1", "producator 1", 1);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(capacity() == 1);

	materie = constructorEntitate("Materie prima 2", "producator 2", 2);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(capacity() == 2);

	materie = constructorEntitate("Materie prima 3", "producator 3", 3);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(capacity() == 4);

	materie = constructorEntitate("Materie prima 4", "producator 4", 4);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(capacity() == 4);

	materie = constructorEntitate("Materie prima 5", "producator 5", 5);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(capacity() == 8);

	materie = constructorEntitate("Materie prima 6", "producator 6", 6);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(capacity() == 8);

	materie = constructorEntitate("Materie prima 7", "producator 7", 7);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(capacity() == 8);

	materie = constructorEntitate("Materie prima 8", "producator 8", 8);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(capacity() == 8);

	materie = constructorEntitate("Materie prima 9", "producator 9", 9);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	assert(capacity() == 16);

	destructorRepository();
}

void ruleazaTesteGetAll()
{
	constructorRepository();

	assert(getAll() == NULL);

	Materie materie;

	materie = constructorEntitate("Materie prima 1", "producator 1", 1);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	assert(getAll() != NULL);

	materie = constructorEntitate("Materie prima 2", "producator 2", 2);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	assert(getAll() != NULL);

	materie = constructorEntitate("Materie prima 3", "producator 3", 3);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	assert(getAll() != NULL);

	Materie* materii = getAll();
	functieTestEntitate(materii[0], "Materie prima 1", "producator 1", 1);
	functieTestEntitate(materii[1], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(materii[2], "Materie prima 3", "producator 3", 3);

	destructorRepository();
}

void ruleazaTesteCautaDupaNume()
{
	constructorRepository();

	assert(cautaDupaNume("Materie prima 1") == NULL);

	Materie materie;
	
	materie = constructorEntitate("Materie prima 1", "producator 1", 1);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	assert(cautaDupaNume("Materie prima 1") != NULL);
	assert(cautaDupaNume("Materie prima 2") == NULL);

	materie = constructorEntitate("Materie prima 2", "producator 2", 2);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	//assert(cautaDupaNume("Materie prima 1") != NULL);
	//assert(cautaDupaNume("Materie prima 2") != NULL);
	//assert(cautaDupaNume("Materie prima 3") == NULL);

	Materie* materie1, *materie2, *materie3;

	materie1 = cautaDupaNume("Materie prima 1");
	materie2 = cautaDupaNume("Materie prima 2");
	materie3 = cautaDupaNume("Materie prima 3");

	assert(materie1 != NULL);
	assert(materie2 != NULL);
	assert(materie3 == NULL);

	functieTestEntitate(*materie1, "Materie prima 1", "producator 1", 1);
	functieTestEntitate(*materie2, "Materie prima 2", "producator 2", 2);

	destructorRepository();
}

void ruleazaTesteModificaMaterie()
{
	constructorRepository();

	Materie materie, materie_noua;

	materie_noua = constructorEntitate("Materie prima 1", "producator 1", 1);
	assert(!modificaMaterie(materie_noua));
	destructorEntitate(&materie_noua);

	materie = constructorEntitate("Materie prima 1", "producator 1", 1);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator 1", 1);

	materie_noua = constructorEntitate("Materie prima 1", "producator nou 1", 11);
	assert(modificaMaterie(materie_noua) == 1);
	destructorEntitate(&materie_noua);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator nou 1", 11);

	materie_noua = constructorEntitate("Materie prima 2", "producator 1", 1);
	assert(!modificaMaterie(materie_noua));
	destructorEntitate(&materie_noua);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator nou 1", 11);

	materie = constructorEntitate("Materie prima 2", "producator 2", 2);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator nou 1", 11);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator 2", 2);

	materie_noua = constructorEntitate("Materie prima 2", "producator nou 2", 2);
	assert(modificaMaterie(materie_noua) == 1);
	destructorEntitate(&materie_noua);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator nou 1", 11);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator nou 2", 2);

	materie_noua = constructorEntitate("Materie prima 3", "producator 2", 3);
	assert(!modificaMaterie(materie_noua));
	destructorEntitate(&materie_noua);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator nou 1", 11);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator nou 2", 2);

	materie = constructorEntitate("Materie prima 3", "producator 3", 3);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator nou 1", 11);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator nou 2", 2);
	functieTestEntitate(repo.lista_materii[2], "Materie prima 3", "producator 3", 3);

	materie_noua = constructorEntitate("Materie prima 3", "producator 3", 33);
	assert(modificaMaterie(materie_noua) == 1);
	destructorEntitate(&materie_noua);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator nou 1", 11);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator nou 2", 2);
	functieTestEntitate(repo.lista_materii[2], "Materie prima 3", "producator 3", 33);

	materie_noua = constructorEntitate("Materie prima 4", "producator 4", 3);
	assert(!modificaMaterie(materie_noua));
	destructorEntitate(&materie_noua);

	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator nou 1", 11);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator nou 2", 2);
	functieTestEntitate(repo.lista_materii[2], "Materie prima 3", "producator 3", 33);

	destructorRepository();
}

void ruleazaTesteStergeMaterie()
{
	constructorRepository();

	assert(!len());
	assert(getAll() == NULL);
	assert(!capacity());

	Materie materie;

	materie = constructorEntitate("Materie prima 1", "producator 1", 1);
	adaugaMaterie(materie);
	destructorEntitate(&materie);
	
	assert(len() == 1);
	assert(getAll() != NULL);
	assert(capacity() == 1);

	assert(!stergeMaterie("Materie prima 2"));

	assert(len() == 1);
	assert(getAll() != NULL);
	assert(capacity() == 1);

	assert(stergeMaterie("Materie prima 1") == 1);

	assert(!len());

	materie = constructorEntitate("Materie prima 1", "producator 1", 1);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	assert(len() == 1);
	assert(getAll() != NULL);
	assert(capacity() == 1);

	materie = constructorEntitate("Materie prima 2", "producator 2", 2);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	assert(len() == 2);
	assert(getAll() != NULL);
	assert(capacity() == 2);

	materie = constructorEntitate("Materie prima 3", "producator 3", 3);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	assert(len() == 3);
	assert(getAll() != NULL);
	assert(capacity() == 4);

	materie = constructorEntitate("Materie prima 4", "producator 4", 4);
	adaugaMaterie(materie);
	destructorEntitate(&materie);

	assert(len() == 4);
	assert(getAll() != NULL);
	assert(capacity() == 4);

	assert(!stergeMaterie("Materie prima 5"));

	assert(len() == 4);
	assert(getAll() != NULL);
	assert(capacity() == 4);
	functieTestEntitate(repo.lista_materii[0], "Materie prima 1", "producator 1", 1);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(repo.lista_materii[2], "Materie prima 3", "producator 3", 3);
	functieTestEntitate(repo.lista_materii[3], "Materie prima 4", "producator 4", 4);

	assert(stergeMaterie("Materie prima 1") == 1);

	assert(len() == 3);
	assert(getAll() != NULL);
	assert(capacity() == 4);
	functieTestEntitate(repo.lista_materii[0], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 3", "producator 3", 3);
	functieTestEntitate(repo.lista_materii[2], "Materie prima 4", "producator 4", 4);

	assert(stergeMaterie("Materie prima 3") == 1);

	assert(len() == 2);
	assert(getAll() != NULL);
	assert(capacity() == 4);
	functieTestEntitate(repo.lista_materii[0], "Materie prima 2", "producator 2", 2);
	functieTestEntitate(repo.lista_materii[1], "Materie prima 4", "producator 4", 4);

	assert(stergeMaterie("Materie prima 4") == 1);

	assert(len() == 1);
	assert(getAll() != NULL);
	assert(capacity() == 4);
	functieTestEntitate(repo.lista_materii[0], "Materie prima 2", "producator 2", 2);

	assert(stergeMaterie("Materie prima 2") == 1);

	assert(!len());
	assert(capacity() == 4);

	destructorRepository();
}

void ruleazaTesteInfrastructura()
{
	ruleazaTesteConstructorDestructorRepo();
	ruleazaTesteAdaugaMaterie();
	ruleazaTesteLen();
	ruleazaTesteCapacity();
	ruleazaTesteGetAll();
	ruleazaTesteCautaDupaNume();
	ruleazaTesteModificaMaterie();
	ruleazaTesteStergeMaterie();
}

/// Teste pentru layerul (stratul) de validare (validarea datelor cu validatori)
void ruleazaTesteValidareString()
{
	assert(!validareString(""));
	assert(validareString(" "));
	assert(validareString("abc"));
	assert(validareString("a4831 b41 c543632"));
	assert(validareString("3894afsa350"));
	assert(validareString("0"));
}

void ruleazaTesteValidareMaterie()
{
	Materie materie;

	materie = constructorEntitate("nume", "producator", 1);
	assert(!validareMaterie(materie));
	destructorEntitate(&materie);

	materie = constructorEntitate("nume", "producator", 0);
	assert(validareMaterie(materie) == 1);
	destructorEntitate(&materie);

	materie = constructorEntitate("nume", "", 2);
	assert(validareMaterie(materie) == 2);
	destructorEntitate(&materie);

	materie = constructorEntitate("nume", "", 0);
	assert(validareMaterie(materie) == 3);
	destructorEntitate(&materie);

	materie = constructorEntitate("", "producator", 3);
	assert(validareMaterie(materie) == 4);
	destructorEntitate(&materie);

	materie = constructorEntitate("", "producator", 0);
	assert(validareMaterie(materie) == 5);
	destructorEntitate(&materie);

	materie = constructorEntitate("", "", 4);
	assert(validareMaterie(materie) == 6);
	destructorEntitate(&materie);

	materie = constructorEntitate("", "", 0);
	assert(validareMaterie(materie) == 7);
	destructorEntitate(&materie);
}

void ruleazaTesteValidare()
{
	ruleazaTesteValidareString();
	ruleazaTesteValidareMaterie();
}

/// Teste pentru intreaga aplicatie (pentru toate layerele mai putin cel de UI/Prezentare)
void ruleazaTeste()
{
	ruleazaTesteDomeniu();
	ruleazaTesteBusiness();
	ruleazaTesteInfrastructura();
	ruleazaTesteValidare();
}