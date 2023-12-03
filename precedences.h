// header file for precedence

// type pour une contraite de precedence
typedef struct pairepref {
    int avant;
    int apres;
} pairepref;

// nombre des contraites et tableau de toutes les contraintes
int nbcontraintes;
pairepref *contraintes;

// lit les contraintes depuis le fichier
// résultat nbcontraintes et contraintes
// si il y a une erreur, quitte le programme
void lireprecedences(const char *nomfic);


typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node** array;
    int size;
} Graph;

Node* createNode(int value);

Graph* createGraph(int size);

void addEdge(Graph* graph, int src, int dest);

void topologicalSortUtil(Graph* graph, int v, int visited[], int stack[], int* stackIndex);

void precedenceSort(Graph* graph);

void readEdgesFromFile(Graph* graph, const char* filename);

void precedences();
