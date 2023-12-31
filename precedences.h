#include <stdio.h>
#include <stdlib.h>

// Définition d'une structure de nœud pour représenter un sommet dans le graphe
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Définition d'une structure de graphe contenant un tableau d'adjacence
typedef struct {
    Node** array;
    int size;
} Graph;

// Fonction pour créer un nouveau nœud avec une valeur donnée
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}


// Fonction pour créer un nouveau graphe avec une taille donnée
Graph* createGraph(int size) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = size;
    graph->array = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; ++i) {
        graph->array[i] = NULL;
    }
    return graph;
}

// Fonction pour ajouter une arête dirigée entre deux sommets (src et dest) dans le graphe
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;
}

// Fonction utilitaire récursive pour le tri topologique
void topologicalSortUtil(Graph* graph, int v, int visited[], int stack[], int* stackIndex) {
    visited[v] = 1;

    Node* current = graph->array[v];
    while (current != NULL) {
        int adj = current->value;
        if (!visited[adj]) {
            topologicalSortUtil(graph, adj, visited, stack, stackIndex);
        }
        current = current->next;
    }

    stack[(*stackIndex)++] = v;
}

// Fonction principale pour effectuer le tri topologique du graphe
void precedenceSort(Graph* graph) {
    int* visited = (int*)malloc(graph->size * sizeof(int));
    int* stack = (int*)malloc(graph->size * sizeof(int));
    int stackIndex = 0;

    // Initialiser le tableau de visite à 0 (non visité)
    for (int i = 0; i < graph->size; ++i) {
        visited[i] = 0;
    }
// Parcourir tous les sommets et effectuer le tri topologique
    for (int i = 0; i < graph->size; ++i) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &stackIndex);
        }
    }

    // Afficher l'ordre de précédence résultant
    printf("Ordre de précédence : ");
    for (int i = stackIndex - 1; i >= 0; --i) {
        printf("%d ", stack[i]);
    }

// Libérer la mémoire allouée
    free(visited);
    free(stack);
}

// Fonction pour lire les arêtes du graphe depuis un fichier texte
void readEdgesFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    int src, dest;
    // Lire les paires de sommets à partir du fichier et ajouter des arêtes
    while (fscanf(file, "%d %d", &src, &dest) == 2) {
        addEdge(graph, src, dest);
    }

    // Fermer le fichier
    fclose(file);
}
// Fonction principale pour effectuer le tri topologique en utilisant un fichier d'entrée
void precedences() {
    // Créer un graphe avec une taille fixe de 36 sommets
    Graph* graph = createGraph(36);


    // Lire les arêtes depuis le fichier texte
    readEdgesFromFile(graph, "precedences.txt");

    // Effectuer le tri topologique
    precedenceSort(graph);
}