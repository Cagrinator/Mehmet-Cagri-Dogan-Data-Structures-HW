#include <stdio.h>

#define MAX 100

int main(void) {
    int n, start;
    int g[MAX][MAX];
    int visited[MAX] = {0};

    printf("n (<=100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) return 1;

    printf("Adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    printf("Start node (0..%d): ", n - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) return 1;

    printf("DFS: ");
    int stack[MAX], top = -1;
    stack[++top] = start;

    for (int i = 0; i < n; i++) visited[i] = 0;

    while (top >= 0) {
        int v = stack[top--];
        if (visited[v]) continue;
        visited[v] = 1;
        printf("%d ", v);

        for (int i = n - 1; i >= 0; i--)
            if (g[v][i] && !visited[i])
                stack[++top] = i;
    }
    printf("\n");

    printf("BFS: ");
    int q[MAX], front = 0, rear = 0;
    for (int i = 0; i < n; i++) visited[i] = 0;

    q[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int v = q[front++];
        printf("%d ", v);
        for (int i = 0; i < n; i++) {
            if (g[v][i] && !visited[i]) {
                visited[i] = 1;
                q[rear++] = i;
            }
        }
    }
    printf("\n");

    return 0;
}