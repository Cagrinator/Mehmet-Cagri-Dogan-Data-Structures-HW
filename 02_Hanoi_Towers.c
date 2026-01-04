#include <stdio.h>

void hanoi(int n, char from, char to, char aux) {
    if (n == 0) {
        return;
    }
    hanoi(n-1, from, aux, to);

    printf("Move disk %d from %c to %c\n", n, from, to);

    hanoi(n-1, aux, to, from);
}

int main() {
    int n;

    printf("Enter number of disks:\n");
    if(scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of disks, Please run this code again");
        return 1;
    }

    printf("Steps to solve hanoi towers: \n");
    hanoi(n, 'A', 'C', 'B');

    return 0;
}