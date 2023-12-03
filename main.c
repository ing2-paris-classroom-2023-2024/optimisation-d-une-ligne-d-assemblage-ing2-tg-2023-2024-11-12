#include "precedences.h"
#include "cycles.h"


int main() {
    char nom_fichier[100];

    printf("Veuillez saisir le nom du fichier : ");
    scanf("%s", nom_fichier);

    FILE *test_fichier = fopen(nom_fichier, "r");
    if (test_fichier == NULL) {
        printf("Le fichier %s n'a pas pu etre ouvert.\n", nom_fichier);
        return EXIT_FAILURE;
    }
    fclose(test_fichier);

    precedences();
    temps_cycle(nom_fichier);

    return 0;
}
