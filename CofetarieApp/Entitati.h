#ifndef ENTITATI_H
#define ENTITATI_H

typedef struct {
	/// Atributele (campurile/componentele) structurii
	char* nume, * producator; /// nume - C string (sir de caractere) alocat dinamic (pe heap), reprezinta numele materiei prime (string nevid)
							  /// producator - C string (sir de caractere) alocat dinamic (pe heap), reprezinta producatorul materiei prime (string nevid)
	unsigned cantitate; /// intreg fara semn (unsigned) pentru a memora cantitatea unei materii prime (numar natural > 0)
} Materie; /// tip de data structurat pentru a reprezenta o entitate de tipul materie prima

/**
* Functie care instantiaza (init) o structura/inregistrare de tip Materie
* Date de intrare: nume       -
*                  producator -
*                  cantitate  -
* Preconditii: nume       <> "" (nume.lenght != 0)
*              producator <> "" (producator.lenght != 0)
*              cantitate  <> 0  (> 0)
* Rezultate: variabila avand tipul Materie (tip de data structurat cu structura fixa)
* Postconditii: constructorEnitate(nume, producator, cantitate) = res => res.nume = nume, res.producator = producator, res.cantitate = cantitate
**/
Materie constructorEntitate(const char* nume, const char* producator, const unsigned cantitate);

/**
* Procedura (subrutina procedurala) care "distruge" o inregistrare de tipul Masina, dezalocand campurile alocate dinamic ale acesteia (nume si producator)
* Date de intrare: materie - pointer la structura pe care vrem sa o "eradicam"
* Preconditii: materie trebuie sa pointeze/puncteze la o materie deja existenta (materie <> NULL)
* Rezultate: -
* Postconditii: -
**/
void destructorEntitate(Materie* materie);

/**
* Functie care returneaza campul nume al unei structuri date ca si parametru de intrare (argument)
* Date de intrare: materie - constanta de tipul Materie
* Preconditii: materie trebuie sa aiba campurile valide
* Date de iesire: char* (pointer la primul element dintr-un sir de caractere, adica un C string alocat dinamic pe heap)
* Postconditii: rezultatul intors de subrutina (fie el notat simbolic res) este chiar campul (atributul) structurii materie parsata ca si argument in antetul functiei (res = materie.nume)
**/
char* getNume(const Materie materie);

/**
* Functie getter pentru a obine campul producator (string) al unei entitati de tipul Materie (al unei materii prime)
* Date de intrare: materie - inregistrare constanta avand tipul de data structurat Materie
* Preconditii: materie trebuie sa fie valida
* Date de iesire: str (string = sir de caractere), adica pointer la primul caracter (element) dintr-un C string (avand tipul char*)
* Postconditii: rezultatul furnizat de functia operand (fie res acesta) este campul producator al materiei materie (res = materie.producator)
**/
char* getProducator(const Materie materie);

/**
* Functie getter pentru a obtine/accesa campul cantitate al unei materii prime
* Date de intrare: materie - de tipul const Materie (constanta avand tipul de data structurat Materie cu structura fixa)
* Preconditii: materie trebuie sa fie o materie valida (avand campurile corecte)
* Date de iesire: unsigned (intreg fara semn pe 4 bytes/octeti)
* Postconditii: rezultatul intors de subprogram este componenta/campul cantitate din entitatea (inregistrarea materie)
* Fie res rezultatul intors (returnat) de functie prin numele ei. Avem res = materie.cantitate
**/
unsigned getCantitate(const Materie materie);

/**
*Procedura(setter) care seteaza/modifica/actualizeaza campul(componenta) producator a unei variabile te tipul Materie (tip definit de utilizator)
*Date de intrare: materie       - pointer la o structura de tipul Materie
*                 new_cantitate - constanta reprezentata pe 4 bytes / octeti(32 de biti)
*Preconditii : materie trebuie sa fie un pointer nenul (materie <> NULL)
*              new_cantitate <> 0 (> 0), cantitatea noua trebuie sa fie nenula (diferita de 0)
*Date de iesire: -
*Postconditii: -
**/
void setProducator(Materie* materie, const char* new_producator);

/**
* Procedura (setter) care seteaza/modifica/actualizeaza campul (componenta) cantitate a unei variabile te tipul Materie (tip definit de utilizator)
* Date de intrare: materie       - pointer la o structura de tipul Materie
*                  new_cantitate - constanta reprezentata pe 4 bytes/octeti (32 de biti)
* Preconditii: inregistrarea la care pointeaza/puncteaza parametrul materie trebuie sa existe (materie <> NULL)
*              new_cantitate <> 0 (> 0), cantitatea noua trebuie sa fie nenula (diferita de 0)
* Date de iesire: -
* Postconditii: -
**/
void setCantitate(Materie* materie, const unsigned new_cantitate);

/**
* Functie care verifica daca doua inregistrari (structuri) de tipul Materie coincid
* Date de intrare: materie_1 - constanta de tip structurat Materie
*                  materie_2 - constanta de tip structurat Materie
* Preconditii: materie_1 si materie_2 trebuie sa aiba campurile valide (nume - string nevid, producator - string nevid si cantitate - numar natural nenul)
* Date de iesire: intreg fara semn din multimea {0, 1}
* Postconditii: 0 - cele doua structuri sunt distincte (campul nume este diferit)
*               1 - cele doua structuri coincid (au acelasi camp nume)
**/
unsigned char equals(const Materie materie_1, const Materie materie_2);

#endif
