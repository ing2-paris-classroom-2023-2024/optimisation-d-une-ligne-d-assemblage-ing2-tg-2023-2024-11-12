
#include "Exclusion.h"


void lire_donnees(char* nom_fichier, int* nb_contraintes, int contraintes[][2]) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Lire les contraintes du fichier
    *nb_contraintes = 0;
    while (fscanf(fichier, "%d %d", &contraintes[*nb_contraintes][0], &contraintes[*nb_contraintes][1]) == 2) {
        (*nb_contraintes)++;
    }

    fclose(fichier);
}

void affecter_stations(int nb_contraintes, int contraintes[][2], int nb_stations) {
    int station_assignee[MAX_OPERATIONS];

    for (int i = 0; i < MAX_OPERATIONS; i++) {
        station_assignee[i] = 0;
    }

    for (int i = 0; i < nb_contraintes; i++) {
        int operation1 = contraintes[i][0];
        int operation2 = contraintes[i][1];

        if (station_assignee[operation1 - 1] == 0 && station_assignee[operation2 - 1] == 0) {
            // Affecter les opérations à une station
            station_assignee[operation1 - 1] = station_assignee[operation2 - 1] = 1;
        }
    }

    // Affichage de l'affectation des opérations aux stations
    for (int k = 1; k <= nb_stations; k++) {
        printf("Station %d: Opérations ", k);
        for (int i = 0; i < MAX_OPERATIONS; i++) {
            if (station_assignee[i] == 1) {
                printf("%d ", i + 1);
            }
        }
        printf("\n");
    }
}

