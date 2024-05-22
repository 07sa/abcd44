// #include <stdio.h>
// #include <stdbool.h>

// #define SIZE 7

// struct Queue {
//     int size;
//     int f;
//     int r;
//     int arr[SIZE];
// };

// int isEmpty(struct Queue q) {
//     return q.r == q.f;
// }

// int isFull(struct Queue q) {
//     return q.r == q.size - 1;
// }

// void enqueue(struct Queue *q, int val) {
//     if (isFull(*q)) {
//         printf("This Queue is full\n");
//     } else {
//         q->r++;
//         q->arr[q->r] = val;
//     }
// }

// int dequeue(struct Queue *q) {
//     int num = -1;
//     if (isEmpty(*q)) {
//         printf("queue is empty\n");
//     } else {
//         q->f++;
//         num = q->arr[q->f];
//     }
//     return num;
// }

// void initializeQueue(struct Queue *q) {
//     q->size = SIZE;
//     q->f = q->r = -1;
// }

// void bfs(int startNode, int a[SIZE][SIZE], int visited[SIZE]) {
//     struct Queue q;
//     initializeQueue(&q);

//     printf("%d ", startNode);
//     visited[startNode] = 1;
//     enqueue(&q, startNode); // Enqueue startNode for exploration

//     while (!isEmpty(q)) {
//         int node = dequeue(&q);
//         for (int j = 0; j < SIZE; j++) {
//             if (a[node][j] == 1 && visited[j] == 0) {
//                 printf("%d ", j);
//                 visited[j] = 1;
//                 enqueue(&q, j);
//             }
//         }
//     }
// }

// int main() {
//     int i;
//     printf("Enter the node from where you want to find BFS order\n");
//     scanf("%d", &i);
    
//     int visited[SIZE] = {0, 0, 0, 0, 0, 0, 0};
//     int a[SIZE][SIZE] = {
//         {0, 1, 1, 1, 0, 0, 0},
//         {1, 0, 0, 1, 0, 0, 0},
//         {1, 1, 0, 1, 1, 0, 0},
//         {1, 0, 1, 0, 1, 0, 0},
//         {0, 0, 1, 1, 0, 1, 1},
//         {0, 0, 0, 0, 1, 0, 0},
//         {0, 0, 0, 0, 1, 0, 0}
//     };

//     printf("The breadth first search traversal order is \n");
//     bfs(i, a, visited);

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

////end

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct to represent a node in the adjacency list
struct node {
    int vertex;
    struct node* next;
};

// Struct to represent the graph
struct Graph {
    int numVertices;
    struct node* adjlists[7];
};

// Function to create a node
struct node* create(int v) {
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->vertex = v;
    n->next = NULL;
    return n;
}

// Function to create a graph
// Initializing it to null as there are no adjacent vertices
struct Graph* createGraph() {
    struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
    g->numVertices = 7;

    int i;
    for (i = 0; i < 7; i++) {
        g->adjlists[i] = NULL;
    }
    return g;
}

// Function to add an edge to the graph
void addedge(struct Graph* graph, int src, int dest) {
    struct node* n1 = create(dest);
    n1->next = graph->adjlists[src];
    graph->adjlists[src] = n1;

    struct node* n2 = create(src);
    n2->next = graph->adjlists[dest];
    graph->adjlists[dest] = n2;
}

// Function to print the adjacency list
void adjacency(struct Graph* graph) {
    printf("Adjacency List:\n");
    int i;
    for (i = 0; i < 7; i++) {
        printf("%d: ", i);

        struct node* current = graph->adjlists[i];
        while (current) {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
}

// Function to perform BFS traversal
void BFS(struct Graph* graph, int startvertex) {
    int queue[7];
    bool visited[7];

    int front = -1, rear = -1;

    // Initialize visited array
    int i;
    for (i = 0; i < 7; i++) {
        visited[i] = false;
    }
    visited[startvertex] = true;

    queue[++rear] = startvertex;

    printf("BFS traversal starting from vertex %d: ", startvertex);

    while (front < rear) {
        int currentvertex = queue[++front];
        printf("%d ", currentvertex);
        struct node* temp = graph->adjlists[currentvertex];

        while (temp) {
            int adjvertex = temp->vertex;
            if (!visited[adjvertex]) {
                visited[adjvertex] = true;
                queue[++rear] = adjvertex;
            }
            temp = temp->next;
        }
    }
}

int main() {
    struct Graph* g = createGraph();

    // Add edges to the graph (for your specific graph)
    addedge(g, 0, 1);
    addedge(g, 0, 2);
    addedge(g, 1, 3);
    addedge(g, 2, 3);
    addedge(g, 2, 4);
    addedge(g, 3, 5);
    addedge(g, 4, 5);
    addedge(g, 4, 6);

    adjacency(g);

    int startvertex;
    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startvertex);

    BFS(g, startvertex);

    // Free memory
    free(g);

    return 0;
}