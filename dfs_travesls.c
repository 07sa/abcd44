// #include <stdio.h>

// #define SIZE 7

// struct Stack {
//     int size;
//     int top;
//     int arr[SIZE];
// };

// void initializeStack(struct Stack *s) {
//     s->size = SIZE;
//     s->top = -1;
// }

// int isStackEmpty(struct Stack *s) {
//     return s->top == -1;
// }

// int isStackFull(struct Stack *s) {
//     return s->top == s->size - 1;
// }

// void push(struct Stack *s, int data) {
//     if (!isStackFull(s)) {
//         s->arr[++(s->top)] = data;
//     } else {
//         printf("Stack is full\n");
//     }
// }

// int pop(struct Stack *s) {
//     if (!isStackEmpty(s)) {
//         return s->arr[(s->top)--];
//     } else {
//         printf("Stack is empty\n");
       
//     }
// }

// void DFS(int start, int a[SIZE][SIZE], int visited[SIZE]) {
//     struct Stack s;
//     initializeStack(&s);

//     printf("Depth First Search traversal order is\n");
//     printf("%d ", start);
//     visited[start] = 1;
//     push(&s, start);

//     while (!isStackEmpty(&s)) {
//         int node = s.arr[s.top];
//         int found = 0;

//         for (int j = 0; j < SIZE; j++) {
//             if (a[node][j] == 1 && visited[j] == 0) {
//                 printf("%d ", j);
//                 visited[j] = 1;
//                 push(&s, j);
//                 found = 1;
//                 break;
//             }
//         }

//         if (!found) {
//             // If no unvisited neighbor is found, pop the current node
//             pop(&s);
//         }
//     }
// }

// int main() {
//     int i;
//     printf("Enter the node from where you want to find DFS order\n");
//     scanf("%d", &i);

//     int visited[SIZE];
//     for (int k = 0; k < SIZE; k++) {
//         visited[k] = 0;
//     }

//     int a[SIZE][SIZE] = {
//         {0, 1, 1, 1, 0, 0, 0},
//         {1, 0, 0, 1, 0, 0, 0},
//         {1, 1, 0, 1, 1, 0, 0},
//         {1, 0, 1, 0, 1, 0, 0},
//         {0, 0, 1, 1, 0, 1, 1},
//         {0, 0, 0, 0, 1, 0, 0},
//         {0, 0, 0, 0, 1, 0, 0}
//     };

//     DFS(i, a, visited);
//     return 0;
// }

// /*
//    0-----1
//    | \   |
//    |   \ |
//    2-----3
//     \   /
//       4
//     /   \
//    5     6
// */




#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a graph using an adjacency matrix
struct GraphMatrix {
    int vertices;
    int matrix[MAX_VERTICES][MAX_VERTICES];
};

// Structure to represent a graph using adjacency lists
struct Node {
    int data;
    struct Node* next;
};

struct GraphList {
    int vertices;
    struct Node* adjLists[MAX_VERTICES];
};

// Function to create a new node for adjacency list
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new graph using an adjacency matrix
struct GraphMatrix* createGraphMatrix(int vertices) {
    struct GraphMatrix* graph = (struct GraphMatrix*)malloc(sizeof(struct GraphMatrix));
    graph->vertices = vertices;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge to the graph using adjacency matrix
void addEdgeMatrix(struct GraphMatrix* graph, int src, int dest) {
    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1; // For an undirected graph
}

// Function to print the adjacency list for a graph using adjacency matrix
void printAdjacencyList(struct GraphMatrix* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->vertices; i++) {
        printf("Vertex %d:", i);
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->matrix[i][j] == 1) {
                printf(" %d", j);
            }
        }
        printf("\n");
    }
}

// Function to perform DFS traversal on a graph using adjacency matrix
void DFSMatrix(struct GraphMatrix* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->matrix[vertex][i] == 1 && !visited[i]) {
            DFSMatrix(graph, i, visited);
        }
    }
}

int main() {
    int vertices = 6;
    struct GraphMatrix* graphMatrix = createGraphMatrix(vertices);

    // Adding edges to the graph using adjacency matrix
    addEdgeMatrix(graphMatrix, 0, 1);
    addEdgeMatrix(graphMatrix, 0, 2);
    addEdgeMatrix(graphMatrix, 1, 3);
    addEdgeMatrix(graphMatrix, 2, 4);
    addEdgeMatrix(graphMatrix, 3, 5);

    int visited[MAX_VERTICES] = {0};

    printAdjacencyList(graphMatrix);
    printf("\n");
    printf("DFS traversal using adjacency matrix: ");
    DFSMatrix(graphMatrix, 0, visited);
    printf("\n");

    return 0;
}
