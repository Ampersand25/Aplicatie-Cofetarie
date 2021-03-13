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
		erori |= (1 << 2);
	if (!validareString(getProducator(materie_rea)))
		erori |= (1 << 1);
	if (!getCantitate(materie_rea))
		erori |= (1 << 0);
	return erori;
}