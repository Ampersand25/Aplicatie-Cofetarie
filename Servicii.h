#ifndef SERVICII_H
#define SERVICII_H

#include "Entitati.h"

/**
* Functie care face conversia unui sir de caractere (string) dat ca si parametru la numarul pe care acesta il reprezinta
* Date de intrare: str - sir constant de caractere (pointer la primul caracter dintr-un string constant)
* Preconditii: stringul str trbuie sa contina doar caractere cifra
* Date de iesire (rezultate): int (integer) = intreg (cu semn = signed) pe 4 bytes/octeti
* Postconditii: conversieDeLaStringLaIntreg(str) = -1 - daca stringul nu contine reprezentarea unui numar natural (adica contine si alte caractere inafara de cifre)
*                                               <> -1 - o valoare intreaga pozitiva (fara semn, >= 0) reprezentand valoarea numerica din string-ul str dat ca si parametru de intrare
**/
int conversieDeLaStringLaIntreg(const char* str);

/**
* Functie operand care compara doua stringuri (siruri de caractere)
* Date de intrare: str_1 - const char* = pointer la primul caracter dintr-un string (sir de caractere) constant
*                  str_2 - const char* = pointer la primul caracter dintr-un string (sir de caractere) constant
* Preconditii: -
* Date de iesire (rezultate): unsigned char = intreg fara semn (unsigned, adica pozitiv sau nul (0)) reprezentat pe 1 byte/octet (8 biti)
* Postconditii: 0 - cele doua stringuri sunt diferite/distincte
*               1 - cele doua stringuri coincid (au acelasi numar de caractere si aceleasi elemente/caractere pe aceleasi pozitii)
**/
unsigned char compareStr(const char* str_1, const char* str_2);

/**
* Subrutina (subprogram) care aloca pe heap (in mod dinamic) o zona continua de memorie (un bloc de memorie) de dim elemente de tipul char (caractere)
* Date de intrare: dim - o constanta pe 4 bytes/octeti (de tipul unsigned)
* Preconditii: dim >= 0
* Date de iesire (rezultate): char* - un pointer la char (character = caracter)
* Postconditii: functia returnaza o valoare  = NULL, daca dim este nul (egal cu 0) sau alocarea nu a avut loc (Heap Overflow)
*                                           <> NULL, daca alocarea memoriei a avut loc (pointerul returnat de functie in acest caz reprezinta inceputul zonei de memorie de dim elemente de tipul caracter alocate pe heap)
**/
char* alocareStr(const unsigned dim);

/**
* Functie operand care realoca memorie pe heap pentru un string (sir de caractere) pentru a acomoda doar elementele citite (fara surplusuri de memorie)
* Date de intrare: str - pointer la primul caracter dintr-un sir de caractere (C string)
* Preconditii: str trebuie sa fie un pointer la o zona valida de memorie de pe heap (obtinut in urma apelului uneia din functiile malloc/calloc/realloc) care sa contina caractere (elemente de tip char = character)
* Date de iesire: char* = pointer la primul caracter dintr-un string
* Postconditii: rezultatul intors de functie este un pointer la noua zona de memorie alocata in mod dinamic pe heap
**/
char* realocareStr(char* str);

/**
* Subrutina (subprogram) care dezaloca un bloc de memorie memory_block alocat anterior pe heap (cu malloc/calloc/realloc)
* Date de intrare: void* - pointer la void (vid), reprezentand inceputul zonei de memorie pe care vrem sa o dezalocam de pe heap (aceasta zona poate sa contina elemente avand orice tip de data)
* Preconditii: memory_block trebuie sa fie un pointer returnat de un apel al uneia din functiile malloc, calloc sau realloc
* Date de iesire (rezultate): -
**/
void dezalocare(void* memory_block);

/**
* Functie operand (rezultat) care returneaza numarul de materii prime din cofetarie (adica numarul de entitati (structuri/inregistrari) din repo)
* Date de intare: -
* Date de iesire (rezultate): unsigned = intreg fara semn (>= 0)
* Postconditii: rezultatul intors de functie este numarul de materii prime disponibile in magazin si stocate in repository
**/
unsigned numarMaterii();

/**
* Functie care intoarce prin numele ei un pointer (de tipul Materie) la prima inregistrare din repository
* Date de intrare: -
* Date de iesire (rezultate): Materie* - pointer la primul element dintr-un sir/vector de elemente de tipul Materie
* Postconditii: rezultatul functiei reprezinta un pointer la prima materie prima din lista de materii prime din repository (acesta este pointerul NULL daca nu exista materii prime in repo)
**/
Materie* materiiPrime();

/**
* Subrutina care incearca sa adauge o noua materie prima (inregistrare) cu numele: nume, producatorul: producator si cantitatea: cantitate in cofetarie (repo)
* Date de intrare: nume       - const char* = pointer la primul caracter dintr-un string (sir de caractere) constant
*                  producator - const char* = pointer la primul caracter dintr-un string (sir de caractere) constant
*                  cantitate  - const char* = pointer la primul caracter dintr-un string (sir de caractere) constant
* Preconditii: nume trebuie sa fie un string nevid
*              producator trebuie sa fie un string nevid
*              cantitate trebuie sa fie un string nevid si care sa contina doar cifre, iar reprezentarea lui numerica trebuie sa fie un numar nenul (<> 0)
* Date de iesire (rezultate): intreg fara semn (unsigned), reprezentand o valoare numerica pozitiva (>= 0) din intervalul [0, 10]
* Postconditii:   0 - adaugarea nu a avut loc, exista o materie prima cu numele nume in cofetarie (si producatorul diferit de producator)
*                 1 - adaugarea a avut loc (s-a introdus o noua materie prima cu numele nume, producatorul producator si cantitatea cantitate in cofetarie)
*                 2 - adaugarea nu a avut loc (exista o materie prima cu numele nume si producatorul producator in cofetarie), dar s-a modificat cantitatea materiei prime gasite cu noua cantitate
*                 3 - cantitate nu reprezinta un numar nenul in reprezentarea ca si intreg (conversia de la string la intreg)
*                 4 - cantitate invalida (nula, = 0)
*                 5 - producator invalid (string vid, = "")
*                 6 - producator invalid si cantitate invalida
*                 7 - nume invalid (string vid, = "")
*                 8 - nume invalid si cantitate invalida
*                 9 - nume invalid si producator invalid
*                10 - nume invalid, producator invalid si cantitate invalida
* Adaugarea s-a realizat doar daca rezultatul intors/returnat de functie este 1
* In cazul in care functia returneaza valoarea 2 (exista o materie prima in cofetarie cu numele nume si producatorul producator) inseamna ca atributul cantitatea s-a actualizat cu valoarea parametrului cantitate
**/
unsigned short adauga(const char* nume, const char* producator, const char* cantitate);

/**
* Subrutina care incearca sa modifice o materie prima existenta (care are acelasi atribut nume ca si parametrul nume).
* Daca aceasta exista atunci se vor updata campurile/componentele producator si cantitate ale inregistrarii cu parametrii formali/simbolici producator si cantitate
* Date de intrare: nume       - const char* = pointer la primul caracter dintr-un string (sir de caractere) constant
*                  producator - const char* = pointer la primul caracter dintr-un string (sir de caractere) constant
*                  cantitate  - const char* = pointer la primul caracter dintr-un string (sir de caractere) constant
* Preconditii: nume trebuie sa fie un string nevid
*              producator trebuie sa fie un string nevid
*              cantitate trebuie sa fie un string nevid si care sa contina doar cifre, iar reprezentarea lui numerica trebuie sa fie un numar nenul (<> 0)
* Date de iesire (rezultate): intreg fara semn (unsigned), reprezentand o valoare numerica pozitiva (>= 0) din intervalul [0, 9]
* Postconditii:  0 - modificarea nu a avut loc, nu exista materie prima cu numele nume in cofetarie
*                1 - modificarea a avut loc (s-au actualizat/modificat campurile/componentele producator si cantitate a materiei prime cu numele nume cu valorile parametrilor formali/simbolici producator si cantitate)
*                2 - cantitate nu reprezinta un numar nenul in reprezentarea ca si intreg (conversia de la string la intreg)
*                3 - cantitate invalida (nula, = 0)
*                4 - producator invalid (string vid, = "")
*                5 - producator invalid si cantitate invalida
*                6 - nume invalid (string vid, = "")
*                7 - nume invalid si cantitate invalida
*                8 - nume invalid si producator invalid
*                9 - nume invalid, producator invalid si cantitate invalida
* Modificarea s-a realizat doar daca rezultatul intors/returnat de functie este 1
**/
unsigned short modifica(const char* nume, const char* producator, const char* cantitate);

/**
* Subrutina care incearca stergerea unei materii prime (inregistari/structuri) cu numele nume din cofetarie (repository)
* Date de intrare: nume - const char* (pointer la primul caracter dintr-un string constant), reprezentand numele materiei prime pe care dorim sa o stergem/eliminam din cofetarie
* Preconditii: nume trebuie sa fie un string valid (adica sa fie nevid, <> "")
* Date de iesire (rezultate): unsigned short = intreg fara semn (valoare numerica naturala) pe 2 bytes/octeti (16 biti) care poate sa fie 0, 1 sau 2
* Postconditii: 0 - stergerea nu a avut loc (nu exista materii prime cu numele nume in cofetarie/repo)
*               1 - stergerea s-a realizat cu succes (a existat o structura/inregistrare avand campul nume identic cu stringul nume dat ca si parametru functiei)
*               2 - sirul de caractere nume nu este valid (este invalid <=> nume.lenght = 0, adica este un string vid = are lungimea 0)
**/
unsigned short sterge(const char* nume);

/**
* Subrutina (subprogram) care cauta o materie prima (inregistrare) cu numele (atributul/campul nume) nume in cofetarie (repository)
* Date de intrare: nume - pointer la primul caracter dintr-un sir de caractere (string) constant
* Preconditii: nume trebuie sa pointeze/puncteze/refere la un string nevid (adica sa contina cel putin un caracter)
* Date de iesire (rezultate): Materie* - pointer la o structura (variabila de tip de data structurat cu structura fixa) avand tipul Materie
* Postconditii: cauta(nume) =  NULL, daca nu exista materie prima cu numele nume in cofetarie (repo)
*                           <> NULL, daca exista o materie prima cu numele nume in cofetarie (repo), in acest caz se returneaza pointer la materia gasita
**/
Materie* cauta(const char* nume);

/**
* Subrutina care verifica daca un criteriu de filtrare este sau nu valid in functie de filtrul ales (filtrul poate fi numele sau cantitatea)
* Date de intrare: criteriu  - sir de caractere (C string) constant care reprezinta criteriul de filtrare (o singura litera daca id_filtru este 0 sau un numar natural daca id_filtru este 1)
*                  id_filtru - constanta intreaga fara semn de tipul unsigned char (character) reprezentat pe 1 byte/octet
* Preconditii: id_filtru trebuie sa fie 0 (filtrare dupa nume) sau 1 (filtrare dupa cantitate)
*              id_filtru = 0 - filtrare dupa nume (criteriul criteriu trebuie sa contina o singura litera)
*              id_filtru = 1 - filtrare dupa cantitate (criteriul criteriu trebuie sa contina doar cifre, adica sa fie un numar intreg fara semn)
* Date de iesire (rezultate): unsigned char (intreg fara semn (unsigned) pe 1 byte/octet) care poate sa fie 0 sau 1
* Postconditii: 0 - criteriul criteriu nu este valid pentru filtrul id_filtru (indisponibil in meniul aplicatiei)
*               1 - criteriul criteriu este valid pentru filtrul id_filtru (disponibil in meniul aplicatiei)
**/
unsigned char evaluareCriteriu(const char* criteriu, const unsigned char id_filtru);

/**
* Subprogram care filtreaza materiile prime (inregistrarile) din cofetarie (repository) dupa un filtru cu un id dat (codificat binar) si un criteriu dat ca si parametru
* Date de intrare: criteriu  - const char* (pointer la primul caracter dintr-un string constant)
*                  id_filtru - const unsigned char (constanta intreaga fara semn pe 1 byte/octet)
* Preconditii: id_filtru poate sa fie 0 sau 1
*              id_filtru = 0 - filtrare dupa nume (se filtreaza toate materiile prime din cofetarie care incep cu litera din sirul de caractere criteriu dat ca si parametru)
*              id_filtru = 1 - filtrare dupa cantitate (se filtreaza toate materiile prime care au cantitatea mai mica decat cantitatea din criteriu din sirul de caractere criteriu dat ca si parametru)
*              daca id_filtru = 0 atunci criteriu trebuie sa fie un string format dintr-un singur caracter care este litera (mica = minuscula sau mare = majuscula)
*                   id_filtru = 1 atunci criteriu trebuie sa fie un string format doar din caractere cifra (de la 0 la 9)
* Date de iesire (rezultate): Materie* - pointer de tipul Materie (lista de materii prime (inregistrari avand tipul de data Materie))
* Postconditii: rezultatul functiei este o lista care contine materiile prime din cofetarie (copiate prin adresa) care respecta criteriul din filtrul ales
* (incep cu o litera din stringul criteriu daca filtrul are id-ul 0 sau au cantitatea mai mica decat intregul fara semn din stringul criteriu in cazul in care id-ul filtrului este 1)
**/
Materie* filtrareMateriiPrime(unsigned* dim, const char* criteriu, const unsigned char id_filtru);

/**
* Functie care compara doua stringuri (siruri de caractere) constante, ci anume nume_1 si nume_2 din punct de vedere alfabetic (lexicografic)
* Date de intrare: nume_1   - pointer la primul caracter (element) dintr-un C string constant
*                  nume_2   - pointer la primul caracter (element) dintr-un C string constant
*                  reversed - intreg fara semn (unsigned) pe 1 byte/octet (8 biti)
* Preconditii: reversed trebuie sa fie 0 sau 1
* Date de iesire: rezultatul functiei este un intreg cu semn (signed)
* Postconditii: comparareCantitate(nume_1, nume_2, reversed) = 0, daca nume_1 = nume_2 (reversed = 0 sau reversed = 1)
*                                                            < 0, daca nume_1 < nume_2 (cand reversed = 0) sau nume_1 > nume_2 (cand reversed = 1)
*                                                            > 0, daca nume_1 > nume_2 (cand reversed = 0) sau nume_1 < nume_2 (cand reversed = 1)
* cu conventia ca '=' reprezinta egalitate lexicografica
*                 '<' reprezinta faptul ca primul string este mai mic din punct de vedere lexicografic decat al doilea
*                 '>' reprezinta faptul ca primul string este mai mare din punct de vedere lexicografic decat al doilea
**/
int comparareNume(const char* nume_1, const char* nume_2, const unsigned char reversed);

/**
* Functie care compara doua numere intregi fara semn (unsigned) cantitate_1 si cantitate_2
* Date de intrare: cantitate_1 - intreg fara semn (unsigned), adica numar natural
*                  cantitate_2 - intreg fara semn (unsigned), adica numar natural
*                  reversed    - intreg fara semn (unsigned) pe 1 byte/octet (8 biti)
* Preconditii: reversed trebuie sa fie 0 sau 1
* Date de iesire: rezultatul functiei este un intreg cu semn (signed)
* Postconditii: comparareCantitate(cantitate_1, cantitate_2, reversed) = 0, daca cantitate_1 = cantitate_2 (reversed = 0 sau reversed = 1)
*                                                                      < 0, daca cantitate_1 < cantitate_2 (cand reversed = 0) sau cantitate_1 > cantitate_2 (cand reversed = 1)
*                                                                      > 0, daca cantitate_1 > cantitate_2 (cand reversed = 0) sau cantitate_1 < cantitate_2 (cand reversed = 1)
**/
int comparareCantitate(const unsigned cantitate_1, const unsigned cantitate_2, const unsigned char reversed);

/**
* Functie generica de comparare a doua inregistrari de tipul Materie (materii prime) dupa fieldul (campul) nume
* Date de intrare: materie_1 - constanta avand tipul de data structurat Materie
*                  materie_2 - constanta avand tipul de data structurat Materie
*                  reversed  - intreg fara semn (unsigned = natural) pe 1 byte/octet (8 biti)
* Preconditii: 0 <= reversed <= 1 (reversed apartine lui N - multimii numerelor naturale)
*              materie_1 si materie_2 trebuie sa fie valide (sa aiba campurile valide)
* Date de iesire (rezultate): unsigned char - intreg fara semn pe 1 byte/octet care poate sa fie 0 sau 1
* Postconditii: functia intoarce 0, daca ordinea nu este buna (materie_1 are campul nume mai mare din punct de vedere lexicografic/alfabetic decat materie_2 daca reversed este 0, sau invers (mai mic) in cazul in care reversed este 1)
*                                1, daca ordinea este buna (materie_1 are campul nume mai mic din punct de vedere lexicografic/alfabetic decat materie_2 daca reversed este 0, sau invers (mai mare) in cazul in care reversed este 1)
**/
unsigned char comparareNumeGen(const Materie materie_1, const Materie materie_2, const unsigned char reversed);

/**
* Functie generica de comparare a doua inregistrari de tipul Materie (materii prime) dupa fieldul (campul) cantitate
* Date de intrare: materie_1 - constanta avand tipul de data structurat Materie
*                  materie_2 - constanta avand tipul de data structurat Materie
*                  reversed  - intreg fara semn (unsigned = natural) pe 1 byte/octet (8 biti)
* Preconditii: 0 <= reversed <= 1 (reversed apartine lui N - multimii numerelor naturale)
*              materie_1 si materie_2 trebuie sa fie valide (sa aiba campurile valide)
* Date de iesire (rezultate): unsigned char - intreg fara semn pe 1 byte/octet care poate sa fie 0 sau 1
* Postconditii: functia intoarce 0, daca ordinea nu este buna (materie_1 are campul cantitate mai mare din punct de vedere numeric (al valorii) decat materie_2 daca reversed este 0, sau invers (mai mic) in cazul in care reversed este 1)
*                                1, daca ordinea este buna (materie_1 are campul cantitate mai mic din punct de vedere numeric (al valorii) decat materie_2 daca reversed este 0, sau invers (mai mare) in cazul in care reversed este 1)
**/
unsigned char comparareCantitateGen(const Materie materie_1, const Materie materie_2, const unsigned char reversed);

/**
* Subprogram care sorteaza/ordoneaza materiile prime (inregistrarile) din cofetarie (repository) dupa un o functie de comparare (cmp = compare) data ca si parametru de intrare
* Date de intrare: reversed  - constanta intreaga fara semn (unsigned) pe 1 byte/octet (8 biti)
*                  comparare - pointer la o functie operand (rezultat) care intoarce/returneaza un unsigned char si are exact 3 parametri (primul de tipul const Materie, al doilea de tipul const Materie si al treilea de tipul const unsigned char)
* Preconditii: reversed trebuie sa apartina intervalului [0, 1]
*              reversed = 0 - ordine crescatoare
*              reversed = 1 - ordine descrescatoare
*              comparare trebuie sa fie un pointer la o functie existenta care returneaza un unsigned char (intreg fara semn pe 1 byte/octet) si are exact 3 parametrii de intrare (primul si al doilea de tipul const Materie, iar al treilea de tipul const unsigned char)
* Date de iesire (rezultate): Materie* - pointer la primul element dintr-o lista de materii prime (inregistrari de tipul Materie)
* Postconditii: Materie* este o copie a listei de materii din repo ordonata/sortata crescator (reversed = 0) sau descrescator (reversed = 1) dupa un criteriu dat ca si o functie de comparare care poate sa returneze 0 (ordinea nu e buna => interschimbare) sau 1 (ordiea elementelor e buna => se pastreaza)
**/
Materie* sortareMateriiPrime(const unsigned char reversed, unsigned char (*comparare)(const Materie, const Materie, const unsigned char));

#endif