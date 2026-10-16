#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int queue[MAX];

int main() {
    int n, start, front = 0, rear = -1;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
        return 1;

    printf("Enter adjacency matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter starting vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    if (start < 0 || start >= n)
        return 1;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    queue[++rear] = start;
    visited[start] = 1;

    printf("BFS Traversal: ");

    while (front <= rear) {
        int v = queue[front++];

        printf("%d ", v);

        for (int i = 0; i < n; i++) {
            if (graph[v][i] != 0 && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }

    printf("\n");

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Vertex %d is not reachable from starting vertex.\n", i);
        }
    }

    return 0;
}
