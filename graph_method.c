#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Node structure for adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph structure for adjacency list
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Function to create a new node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph for adjacency list
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// Function to add an edge to adjacency matrix
void addEdgeMatrix(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;  // Remove this line for a directed graph
}

// Function to print adjacency matrix
void printAdjMatrix(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to add an edge to adjacency list
void addEdgeList(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to print adjacency list
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("Adjacency list of vertex %d\n", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int vertices = 5;
    int choice;

    // Initialize adjacency matrix with zeros
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};

    // Create graph for adjacency list
    Graph* graph = createGraph(vertices);

    printf("Choose graph representation:\n");
    printf("1. Adjacency Matrix\n");
    printf("2. Adjacency List\n");
    scanf("%d", &choice);

    // Adding edges
    int edges[7][2] = {
        {0, 1}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}
    };
    int numEdges = 7;

    if (choice == 1) {
        // Adjacency Matrix
        for (int i = 0; i < numEdges; i++) {
            addEdgeMatrix(adjMatrix, edges[i][0], edges[i][1]);
        }
        printAdjMatrix(adjMatrix, vertices);
    } else if (choice == 2) {
        // Adjacency List
        for (int i = 0; i < numEdges; i++) {
            addEdgeList(graph, edges[i][0], edges[i][1]);
        }
        printGraph(graph);
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}
