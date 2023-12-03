#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100

typedef struct {
    int operation;
} Operation;

typedef struct {
    Operation operations[MAX_OPERATIONS];
    int count;
} Station;

int estExclue(int operation1, int operation2, int exclusion[][2], int nb_contraintes) {
    for (int i = 0; i < nb_contraintes; i++) {
        if ((operation1 == exclusion[i][0] && operation2 == exclusion[i][1]) ||
            (operation1 == exclusion[i][1] && operation2 == exclusion[i][0])) {
            return 1; // Opérations exclues
        }
    }
    return 0; // Opérations non exclues
}

void trier_par_exclusion(char* nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    Station stations[MAX_OPERATIONS]; // Nombre maximal de stations possible
    int nb_contraintes;
    int exclusion[MAX_OPERATIONS][2];

    printf("\nStations:\n");

    // Initialiser les stations
    for (int i = 0; i < MAX_OPERATIONS; i++) {
        stations[i].count = 0;
    }

    // Lire les exclusions depuis le fichier
    FILE *exclusion_file = fopen("exclusion.txt", "r");
    if (exclusion_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'exclusions");
        exit(EXIT_FAILURE);
    }

    nb_contraintes = 0;
    while (fscanf(exclusion_file, "%d %d", &exclusion[nb_contraintes][0], &exclusion[nb_contraintes][1]) == 2) {
        nb_contraintes++;
    }

    fclose(exclusion_file);

    int operation;

    // Lire les opérations et les placer dans les stations
    while (fscanf(fichier, "%d", &operation) == 1) {
        int placed = 0;

        // Parcourir les stations
        for (int i = 0; i < MAX_OPERATIONS; i++) {
            int canPlace = 1;

            // Vérifier les contraintes d'exclusion
            for (int j = 0; j < stations[i].count; j++) {
                if (estExclue(stations[i].operations[j].operation, operation, exclusion, nb_contraintes)) {
                    canPlace = 0;
                    break;
                }
            }

            // Si la contrainte d'exclusion est respectée, placer l'opération dans la station
            if (canPlace) {
                stations[i].operations[stations[i].count].operation = operation;
                stations[i].count++;
                placed = 1;
                break;
            }
        }

        // Si aucune station ne convient, créer une nouvelle station
        if (!placed) {
            for (int i = 0; i < MAX_OPERATIONS; i++) {
                if (stations[i].count == 0) {
                    stations[i].operations[stations[i].count].operation = operation;
                    stations[i].count++;
                    break;
                }
            }
        }
    }

    // Afficher les stations
    for (int i = 0; i < MAX_OPERATIONS; i++) {
        if (stations[i].count > 0) {
            printf("Station %d:\n", i + 1);
            for (int j = 0; j < stations[i].count; j++) {
                printf("Operation %d\n", stations[i].operations[j].operation);
            }
            printf("\n");
        }
    }

    fclose(fichier);
}

int main() {
    char nom_fichier[100];

    printf("Entrez le nom du fichier : ");
    scanf("%s", nom_fichier);

    trier_par_exclusion(nom_fichier);

    return 0;
}
