    #include <stdio.h>
    #include <stdlib.h>

    typedef struct {
        int operation1;
        int operation2;
    } Contrainte;

    void lire_donnees(char* nom_fichier, int* nb_contraintes, Contrainte contraintes[]) {
        FILE *fichier = fopen(nom_fichier, "r");
        if (fichier == NULL) {
            perror("Erreur lors de l'ouverture du fichier");
            exit(EXIT_FAILURE);
        }

        // Lire les contraintes du fichier
        *nb_contraintes = 0;
        while (fscanf(fichier, "%d %d", &contraintes[*nb_contraintes].operation1, &contraintes[*nb_contraintes].operation2) == 2) {
            (*nb_contraintes)++;
        }

        fclose(fichier);
    }

    void affecter_stations(int nb_contraintes, Contrainte contraintes[], int nb_stations, int max_operations) {
        int station_assignee[max_operations];
        int charge_station[nb_stations];

        for (int i = 0; i < max_operations; i++) {
            station_assignee[i] = 0;
        }

        // Initialiser la charge de chaque station à zéro
        for (int k = 0; k < nb_stations; k++) {
            charge_station[k] = 0;
        }

        // Affecter les opérations aux stations en équilibrant la charge
        for (int i = 0; i < nb_contraintes; i++) {
            int operation1 = contraintes[i].operation1;
            int operation2 = contraintes[i].operation2;

            // Trouver la station avec la charge minimale
            int min_charge_station = 0;
            for (int k = 1; k < nb_stations; k++) {
                if (charge_station[k] < charge_station[min_charge_station]) {
                    min_charge_station = k;
                }
            }

            if (station_assignee[operation1 - 1] == 0 && station_assignee[operation2 - 1] == 0) {
                // Affecter les opérations à la station avec la charge minimale
                station_assignee[operation1 - 1] = station_assignee[operation2 - 1] = min_charge_station + 1;
                charge_station[min_charge_station] += 2; // Deux opérations sont affectées
            }
        }

        // Affichage de l'affectation des opérations aux stations
        for (int k = 0; k < nb_stations; k++) {
            printf("Station %d: Opérations ", k + 1);
            for (int i = 0; i < max_operations; i++) {
                if (station_assignee[i] == k + 1) {
                    printf("%d ", i + 1);
                }
            }
            printf("\n");
        }
    }

    int main() {
        char nom_fichier[100];
        int nb_contraintes;

        // Demander à l'utilisateur de saisir le nom du fichier
        printf("Veuillez saisir le nom du fichier : ");
        scanf("%s", nom_fichier);

        FILE *test_fichier = fopen(nom_fichier, "r");
        if (test_fichier == NULL) {
            printf("Le fichier %s n'a pas pu être ouvert.\n", nom_fichier);
            return EXIT_FAILURE;
        }
        fclose(test_fichier);

        printf("Veuillez saisir le nombre maximal d'opérations : ");
        int max_operations;
        scanf("%d", &max_operations);

        Contrainte contraintes[max_operations];
        lire_donnees(nom_fichier, &nb_contraintes, contraintes);

        if (nb_contraintes == 0) {
            printf("Erreur : Aucune contrainte n'a été lue dans le fichier %s.\n", nom_fichier);
            return EXIT_FAILURE;
        }

        int nb_stations = 5;

        affecter_stations(nb_contraintes, contraintes, nb_stations, max_operations);

        return 0;
    }
