

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_11_12_EXCLUSION_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_11_12_EXCLUSION_H

#include "stdlib.h"
#include "stdio.h"

#define MAX_OPERATIONS 35
#define MAX_STATIONS 5

void lire_donnees(char* nom_fichier, int* nb_contraintes, int contraintes[][2]);

void affecter_stations(int nb_contraintes, int contraintes[][2], int nb_stations);



#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_11_12_EXCLUSION_H
