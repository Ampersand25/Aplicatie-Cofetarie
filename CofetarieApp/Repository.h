#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Entitati.h"

typedef struct {
	/// Atributele (campurile/componentele) structurii
	Materie* lista_materii; /// tablou unidimensional (sir/vector) alocat dinamic pe heap (pointer la prima structura de tipul Materie din lista) care contine toate materiile prime din magazin
	unsigned nr_materii, capacitate; /// nr_materii - (dimensiunea fizica a repo-ului) intreg fara semn (unsigned pe 4 bytes/octeti) reprezentand numarul curent de materii prime (entitati) din cofetarie (repository)
									 /// capacitate - (dimensiunea logica a repo-ului) intreg fara semn (unsigned pe 4 bytes/octeti) reprezentand numarul maxim de materii prime (entitati) care incap in cofetarie (repository)
} Repo; /// tip de data structurat (definit de catre utilizator) cu doua campuri/componente/atribute si cu structura fixa (inregistrare/structura)

Repo repo;

/**
* Procedura care instantiaza ("creeaza") variabila repo avand tipul de data structurat Repo (ii initializeaza campurile)
* Date de intrare: -
* Date de iesire: -
**/
void constructorRepository();

/**
* Procedura care "distruge" variabila repo avand tipul de data structurat Repo
* (face dezalocarea spatiului de memorare de pe heap pentru toate campurile nume si producator al inregistrarilor din repository)
* Date de intrare: -
* Date de iesire: -
**/
void destructorRepository();

/**
* Functie operand care returneaza toate materiile prime (inregistrarile) din repository
* Date de intrare: -
* Date de iesire: un tablou unidimensional (vector/sir) de inregistrari de tipul Materie (pointer la prima inregistrare din lista)
* Postconditii: fiecare element din vectorul returnat de functie este o materie prima avand tipul de data Materie
**/
Materie* getAll();

/**
* Functie care returneaza numarul de materii prime (inregistrari) din cofetarie (repo)
* Date de intrare: -
* Date de iesire: intreg fara semn (unsigned) pe 4 bytes/octeti (32 de biti)
* Postconditii: rezultatul functiei este egal cu numarul de elemente din lista repo (adica cu numarul de materii prime disponibile)
**/
unsigned len();

/**
* Functie care returneaza capacitatea maxima a repository-ului (numarul maxim de materii prime care pot fi adaugate)
* Date de intrare: -
* Date de iesire: intreg fara semn (unsigned) pe 4 bytes/octeti (32 de biti)
* Postconditii: rezultatul functiei este egal cu numarul maxim de materii prime (inregistrari) pentru care s-a alocat memorie/spatiu pe heap
**/
unsigned capacity();

/**
* Functie care cauta o materie prima cu numele nume in repository (cofetarie)
* Date de intrare: nume - string (sir de caractere) constant
* Preconditii: nume trebuie sa fie un string nevid (cu lungimea (numarul de elemente/caractere) > 0, adica <> 0 (nunul = diferit de 0))
* Date de iesire: pointer la Materie (rezultatul este de tipul Materie*)
* Postconditii: rezultatul intors de functie este  = NULL - daca nu exista nicio materie prima cu numele nume in repo
*                                                 <> NULL - in caz contrar (se returneaza adresa materiei prime gasite cu numele indicat)
**/
Materie* cautaDupaNume(const char* nume);

/**
* Functie care incearca sa adauge o materie prima (inregistrare/structura) in lista repository
* Date de intrare: materie - constanta de tipul Materie
* Preconditii: parametrul/argumentul materie trebuie sa fie valid (adica sa aiba campurile validate)
* Date de iesire: intreg fara semn pe 2 bytes/octeti (unsigned short) din multimea {0, 1, 2}
* Postconditii: 0 - exista deja o materie prima cu numele materiei prime pe care dorim sa o adaugam (materie) si producator diferit fata de aceasta
*               1 - adaugarea a avut loc (nu mai exista alta inregistrare in repo cu acelasi nume ca si cel al materiei prime materie)
*               2 - s-a actualizat/modificat cantitatea materiei prime cu acelasi nume si producator ca si argumentul/parametrul functiei (inregistrarea materie)
**/
unsigned short adaugaMaterie(const Materie materie);

/**
* Functie operand (de tip rezultat) care incearca sa modifice/actualizeze campurile unei materii prime din repository
* care are acelasi camp nume ca si parametrul simbolic/formal materie
* Date de intrare: materie - constanta de tipul Materie (valoarea ei nu se altereaza/modifica in corpul functiei)
* Date de iesire: intreg de tipul unsigned char (cu domeniul de valori in intervalul [0, 255]) care poate sa fie 0 sau 1
* Postconditii: 0 - modificarea nu a avut loc <=> nu exista nicio structura in lista din repository care sa aiba acelasi nume ca si structura materie parsata ca parametru subrutinei
*               1 - modificarea a fost un succes <=> exista o inregistrare (materie prima) in repo cu acelasi nume ca si entitatea materie
**/
unsigned char modificaMaterie(const Materie materie);

/**
* Functie care incearca sa stearga o materie prima cu numele nume din cofetarie
* Date de intrare: nume - str (string = sir de caractere) constant (pointer la primul caracter dintr-un string constant)
* Preconditii: nume trebuie sa fie un string nevid (<> "")
* Date de iesire: un intreg fara semn pe 1 byte/octet (8 biti) din multimea {0, 1}
* Postconditii: 0 - stergerea nu a avut loc (nu s-a realizat), adica nu exista materie prima cu numele nume in repo
*               1 - stergerea a avut loc, ceea ce inseamna ca a existat o inregistrare cu campul nume identic cu stringul constant nume
**/
unsigned char stergeMaterie(const char* nume);

#endif