
#include "Exclusion.h"

#include <stdio.h>
#include <stdlib.h>


//main exlusion

int main() {
    int nb_contraintes;
    int contraintes[MAX_OPERATIONS][2];

    lire_donnees("donnees.txt", &nb_contraintes, contraintes);

    int nb_stations = 5;

    affecter_stations(nb_contraintes, contraintes, nb_stations);

    return 0;
}
