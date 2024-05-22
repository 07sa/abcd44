// #include <stdio.h>
// #include <limits.h>
// #include <stdbool.h>

// #define V 6 // Number of vertices

// int minKey(int key[], bool mstSet[]) {
//     int min = INT_MAX, min_index;

//     for (int v = 0; v < V; v++) {
//         if (!mstSet[v] && key[v] < min) {
//             min = key[v];
//             min_index = v;
//         }
//     }

//     return min_index;
// }

// void printMST(int parent[], int graph[V][V]) {
//     printf("Edge   Weight\n");
//     for (int i = 1; i < V; i++) {
//         printf("%d - %d    %d\n", parent[i], i, graph[i][parent[i]]);
//     }
// }

// void primMST(int graph[V][V]) {
//     int parent[V]; // Array to store constructed MST
//     int key[V];    // Key values used to pick the minimum weight edge
//     bool mstSet[V]; // To represent set of vertices included in MST

//     // Initialize all keys as INFINITE and mstSet[] as false
//     for (int i = 0; i < V; i++) {
//         key[i] = INT_MAX;
//         mstSet[i] = false;
//     }

//     // Always include the first vertex in MST
//     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
//     parent[0] = -1; // First node is always root of MST

//     // The MST will have V vertices
//     for (int count = 0; count < V - 1; count++) {
//         int u = minKey(key, mstSet);

//         // Add the picked vertex to the MST
//         mstSet[u] = true;

//         // Update key value and parent index of adjacent vertices
//         for (int v = 0; v < V; v++) {
//             if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
//                 parent[v] = u;
//                 key[v] = graph[u][v];
//             }
//         }
//     }

//     // Print the constructed MST
//     printMST(parent, graph);
// }

// int main() {
//     int graph[V][V] = {
//         {0, 3, 1, 6, 0, 0},
//         {3, 0, 5, 0, 3, 0},
//         {1, 5, 0, 5, 6, 4},
//         {6, 0, 5, 0, 0, 2},
//         {0, 3, 6, 0, 0, 6},
//         {0, 0, 4, 2, 6, 0}
//     };

//     primMST(graph);

//     return 0;
// }



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Structure to represent the adjacency list
struct AdjList {
    struct Node* head;
};

// Structure to represent the graph
struct Graph {
    int V;
    struct AdjList* array;
};

struct Node* createNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void primMST(struct Graph* graph) {
    int V = graph->V;
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u;
        int min = INT_MAX;

        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

        struct Node* currentNode = graph->array[u].head;
        while (currentNode != NULL) {
            int v = currentNode->vertex;
            int weight = currentNode->weight;
            if (!mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
            currentNode = currentNode->next;
        }
    }

    printf("Edge   Weight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d    %d\n", parent[i], i, key[i]);
    }
}

int main() {
    int V = 6; // Number of vertices in the graph

    struct Graph* graph = createGraph(V);

    // Add edges to the graph
    addEdge(graph, 0, 1, 3);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 1, 2, 5);
    addEdge(graph, 1, 4, 3);
    addEdge(graph, 2, 3, 5);
    addEdge(graph, 2, 4, 6);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 5, 2);
    addEdge(graph, 4, 5, 6);

    primMST(graph);

    return 0;
}
