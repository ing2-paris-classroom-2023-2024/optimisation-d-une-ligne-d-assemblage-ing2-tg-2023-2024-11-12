#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 35
#define TAILLE_NOM 100

void void_templs_cycle(char* nom_fichier) {
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
            printf("Station %d: Operation %d (%.2f s)\n", current_station, operation, temps);
            current_station_time += temps;
        } else {
            printf("\n");
            current_station++;
            current_station_time = temps;
            printf("Station %d: Operation %d (%.2f s)\n", current_station, operation, temps);
        }
    }

    // Ajouter un retour à la ligne après la dernière opération de la dernière station
    printf("\n");

    fclose(fichier);
}

void afficher_temps_total(char* nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int operation;
    float temps;
    int current_station = 1;
    float current_station_time = 0;

    printf("Temps total par station:\n");

    while (fscanf(fichier, "%d %f", &operation, &temps) == 2) {
        if (current_station_time + temps <= 10.0) {
            current_station_time += temps;
        } else {
            printf("Station %d: %.2f s\n", current_station, current_station_time);
            current_station++;
            current_station_time = temps;
        }
    }

    // Ajouter l'affichage du temps total de la dernière station
    printf("Station %d: %.2f s\n", current_station, current_station_time);

    fclose(fichier);
}

int main() {
    char nom_fichier[TAILLE_NOM];

    // Demander à l'utilisateur de saisir le nom du fichier
    printf("Veuillez saisir le nom du fichier : ");
    scanf("%s", nom_fichier);

    void_templs_cycle(nom_fichier);

    afficher_temps_total(nom_fichier);

    return 0;
}
