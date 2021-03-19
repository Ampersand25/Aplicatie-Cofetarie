#include "Validatori.h"

#include <string.h>

unsigned char validareString(const char* string)
{
	return strlen(string) != 0; /// return strlen(string) > 0;
}

unsigned short validareMaterie(const Materie materie_rea)
{
	unsigned short erori = 0;
	if (!validareString(getNume(materie_rea)))
		erori |= (1 << 2); // erori |= 4;
	if (!validareString(getProducator(materie_rea)))
		erori |= (1 << 1); // erori |= 2;
	if (!getCantitate(materie_rea))
		erori |= (1 << 0); // erori |= 1;
	return erori;
}