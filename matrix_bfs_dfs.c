#include <stdio.h>
#define MAX 100

int visited[MAX];
int stack[MAX];
int queue[MAX];
int top = -1;
int front = -1;
int rear = -1;

void dfs(int adjMatrix[][MAX], int vCount, int start) {
    for (int i = 0; i < vCount; i++) {
        visited[i] = 0;
    }
    stack[++top] = start;
    visited[start] = 1;

    while (top != -1) {
        int s = stack[top--];
        printf("%d ", s);

        for (int i = 0; i < vCount; i++) {
            if (adjMatrix[s][i] == 1 && !visited[i]) {
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }
}

void bfs(int adjMatrix[MAX][MAX],int vCount, int start){
    for (int i = 0; i < vCount; i++) {
        visited[i] = 0;
    }
   queue[++rear] = start;
   visited[start] = 1;
   
   while(front != rear){
   int s = queue[++front];
   printf("%d ",s);
   
   for(int i = 0;i<vCount;i++)
   {
       if(adjMatrix[s][i] == 1 && !visited[i])
       {
           queue[++rear] = i;
           visited[i] =1;
       }
   }
  }
}

int main() {
    int vCount = 5; // Number of vertices
    int adjMatrix[MAX][MAX] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };

    int startVertex;
    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);

    printf("BFS Traversal starting from vertex %d:\n", startVertex);
    bfs(adjMatrix, vCount, startVertex);

    printf("\nDFS Traversal starting from vertex %d:\n", startVertex);
    dfs(adjMatrix, vCount, startVertex);

    return 0;
}