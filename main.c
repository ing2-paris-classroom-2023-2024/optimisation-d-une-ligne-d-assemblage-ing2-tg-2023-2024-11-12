#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 35
#define MAX_STATIONS 5
#define TAILLE_NOM 100

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
        printf("Station %d: Operations ", k);
        for (int i = 0; i < MAX_OPERATIONS; i++) {
            if (station_assignee[i] == 1) {
                printf("%d ", i + 1);
            }
        }
        printf("\n");
    }
}

void void_templs_cycle(char* nom_fichier, int nb_stations) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int operation;
    float temps;
    int current_station = 1;
    float current_station_time = 0;

    printf("Stations:\n");

    while (fscanf(fichier, "%d %f", &operation, &temps) == 2) {
        if (current_station_time + temps <= 10.0) {
            printf("Station %d: Operation %d (%.2f s) ", current_station, operation, temps);
            current_station_time += temps;
        } else {
            printf("\n");
            current_station++;
            current_station_time = temps;
            printf("Station %d: Operation %d (%.2f s) ", current_station, operation, temps);
        }
    }

    fclose(fichier);
}

int main() {
    char nom_fichier[TAILLE_NOM];

    //Demander à l'utilisateur de saisir le nom du fichier
    printf("Veuillez saisir le nom du fichier : ");
    scanf("%s", nom_fichier);

    int nb_contraintes;
    int contraintes[MAX_OPERATIONS][2];

    lire_donnees(nom_fichier, &nb_contraintes, contraintes);

    int nb_stations = 5;

    affecter_stations(nb_contraintes, contraintes, nb_stations);

    void_templs_cycle(nom_fichier, MAX_STATIONS);


    return 0;
}
