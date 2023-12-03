#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node** array;
    int size;
} Graph;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int size) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = size;
    graph->array = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; ++i) {
        graph->array[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;
}

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

void precedenceSort(Graph* graph) {
    int* visited = (int*)malloc(graph->size * sizeof(int));
    int* stack = (int*)malloc(graph->size * sizeof(int));
    int stackIndex = 0;

    for (int i = 0; i < graph->size; ++i) {
        visited[i] = 0;
    }

    for (int i = 0; i < graph->size; ++i) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &stackIndex);
        }
    }

    printf("Ordre de precedence : ");
    for (int i = stackIndex - 1; i >= 0; --i) {
        printf("%d ", stack[i]);
    }

    free(visited);
    free(stack);
}

void readEdgesFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    int src, dest;
    while (fscanf(file, "%d %d", &src, &dest) == 2) {
        addEdge(graph, src, dest);
    }

    fclose(file);
}

void precedences() {
    Graph* graph = createGraph(36);

    // Lire les arêtes depuis le fichier texte
    readEdgesFromFile(graph, "precedences.txt");

    // Effectuer le tri topologique
    precedenceSort(graph);
}