#include <stdio.h>

#define MAX 100

int g[MAX][MAX];
int visited[MAX];
int n;

void dfs(int v) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < n; i++) {
        if (g[v][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main(void) {
    printf("Number of nodes (<=100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) return 1;

    printf("Adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    for (int i = 0; i < n; i++) visited[i] = 0;

    int cluster = 1;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Cluster %d: ", cluster++);
            dfs(i);
            printf("\n");
        }
    }

    return 0;
}