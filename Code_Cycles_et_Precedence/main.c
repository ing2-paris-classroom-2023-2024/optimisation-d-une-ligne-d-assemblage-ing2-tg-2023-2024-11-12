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

void precedenceSort(Graph* graph, int order[]) {
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

    for (int i = 0; i < graph->size; ++i) {
        order[i] = stack[stackIndex - 1 - i];
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

void readOperationTimesFromFile(float operationTimes[], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    int operation;
    float time;
    while (fscanf(file, "%d %f", &operation, &time) == 2) {
        operationTimes[operation - 1] = time;
    }

    fclose(file);
}

void organizeOperationsInStations(Graph* graph, int order[], float operationTimes[]) {
    float* stationTimes = (float*)malloc(graph->size * sizeof(float));
    int* stationIndices = (int*)malloc(graph->size * sizeof(int));
    for (int i = 0; i < graph->size; ++i) {
        stationTimes[i] = 0;
        stationIndices[i] = 1;
    }

    printf("Stations:\n");

    for (int i = 0; i < graph->size; ++i) {
        int operation = order[i];
        float operationTime = operationTimes[operation - 1];

        int stationIndex = stationIndices[i];
        if (stationTimes[stationIndex - 1] + operationTime <= 10.0) {
            stationTimes[stationIndex - 1] += operationTime;
            printf("Station %d: Operation %d (%.2f s)\n", stationIndex, operation, operationTime);
        } else {
            stationIndices[i]++;
            stationTimes[stationIndex] = operationTime;
            printf("Station %d: Operation %d (%.2f s)\n", stationIndex + 1, operation, operationTime);
        }
    }

    free(stationTimes);
    free(stationIndices);
}

void precedences() {
    Graph* graph = createGraph(36);
    int order[36];  // Array to store the order of operations
    float operationTimes[36];  // Array to store the time for each operation

    // Read edges from the text file
    readEdgesFromFile(graph, "precedences.txt");

    // Perform topological sort
    precedenceSort(graph, order);

    // Read operation times from the text file
    readOperationTimesFromFile(operationTimes, "cycles.txt");

    // Organize operations in stations
    organizeOperationsInStations(graph, order, operationTimes);
}

int main() {
    // Call the precedences function
    precedences();

    return 0;
}
 