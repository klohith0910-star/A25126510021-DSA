#include <stdio.h>

#define MAX 100
#define INF 999999

int main() {
    int n, source;
    int graph[MAX][MAX];
    int dist[MAX], visited[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
        return 1;

    printf("Enter weighted adjacency matrix (0 means no edge):\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);

            if (graph[i][j] < 0) {
                printf("Negative weights are not allowed.\n");
                return 1;
            }
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &source);

    if (source < 0 || source >= n)
        return 1;

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = INF;
        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] > 0 &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nShortest distances from source vertex %d:\n", source);
    printf("Destination\tDistance\n");

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF)
            printf("%d\t\tUnreachable\n", i);
        else
            printf("%d\t\t%d\n", i, dist[i]);
    }

    return 0;
}
