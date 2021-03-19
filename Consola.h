#pragma once

unsigned char finish; /// variabila (semafor) care indica daca ciclul de viata al aplicatiei s-a terminat sau nu
                      /// finish = 0 (inseamna ca aplicatia inca ruleaza)
                      /// finish = 1 (executia aplicatiei s-a incheiat, utilizatorul a iesit din ea)

/// Procedura care porneste aplicatia
void runApplication();