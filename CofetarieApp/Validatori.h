#ifndef VALIDATORI_H
#define VALIDATORI_H

#include "Entitati.h"

/**
* Functie operand care verifica daca un sir de caractere (C string) este nevid
* Date de intrare: string - C string (sir de caractere)
* Preconditii: -
* Date de iesire: intreg fara semn (unsigned) pe 1 byte/octet (8 biti) din multimea {0, 1}
* Postconditii: 0 - daca parametrul formal/simbolic string are lungimea nula (0), adica este vid (stringul "")
*               1 - daca parametrul formal/simbolic string are lungime nenula (diferita de 0), adica nu este vid (este nevid)
**/
unsigned char validareString(const char* string);

/**
* Functie operand pentru validarea campurilor (componentelor) unei varibile de tipul Materie (tip de data structurat cu structura fixa)
* Date de intrare: materie_rea - constanta avand tipul de data definit (de catre utilizator) Materie
* Preconditii: -
* Date de iesire: intreg fara semn (unsigned) pe 2 byte/octeti (16 biti) din intervalul [0, 7]
* Postconditii: 0 (000b) - materie_rea are toate campurile valide
*               1 (001b) - campul cantitate este invalid
*               2 (010b) - campul producator este invalid
*               3 (011b) - campurile producator si cantitate sunt invalide
*               4 (100b) - campul nume este invalid
*               5 (101b) - campul nume si cantitate sunt invalide 
*               6 (110b) - campul nume si producator sunt invalide
*               7 (111b) - toate campurile sunt invalide
* Fie res rezultatul returnat de functie, considerand cei mai putini semnificativi biti (bitii low = inferiori)
* din reprezentarea binara (in baza 2) a numarului si ii indexam de la dreapta la stanga cu indici de la 0 la 2
* vom avea ca bitul de pe pozitia 0 este setat (1) daca componenta cantitate a structurii materie_rea nu e valida,
* bitul de pe pozitia 1 este setat (1) daca componenta producator a structurii nu este valida,
* iar bitul de pe pozitia 2 este setat (1) daca componenta nume a structurii nu este valida
**/
unsigned short validareMaterie(const Materie materie_rea);

#endif