#include <stdio.h>

#define MAX 1000

int n;
int T[MAX];

//* Forms A Tree Taking The Inputs From User And Also Sorts -> Prints The Postorder, Inorder And Preorder Form In Main *//  

void preorder(int i) {
    if (i >= n || T[i] == -1) return;
    printf("%d ", T[i]);
    preorder(2*i + 1);
    preorder(2*i + 2);
}

void inorder(int i) {
    if (i >= n || T[i] == -1) return;
    inorder(2*i + 1);
    printf("%d ", T[i]);
    inorder(2*i + 2);
}

void postorder(int i) {
    if (i >= n || T[i] == -1) return;
    postorder(2*i + 1);
    postorder(2*i + 2);
    printf("%d ", T[i]);
}

int main(void) {
    printf("Array size (n <= %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) return 1;

    printf("Enter %d values (-1 for empty):\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &T[i]);

    printf("Preorder : ");
    preorder(0);
    printf("\n");

    printf("Inorder  : ");
    inorder(0);
    printf("\n");

    printf("Postorder: ");
    postorder(0);
    printf("\n");

    return 0;
}