    //* This program converts dense matrices into sparse matrix, with the best of my ability of course *//
    //* I made it so that the rows and columns start from 0 and not 1 like its usually is for the sake of c language purposes *//
#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
} Triplet;

static int idx(int r, int c, int val) {
    return r * val + c;
}

void printfDense(int *A, int rows, int val) {
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < val; c++)
        {
            printf("%d\n", A[idx(r, c, val)]);   
        }
        
    }
    
}

int main(void) {
    int rows, val;

    printf("Enter matrice space; row then column:");
    if (scanf("%d %d", &rows, &val) != 2 || rows <= 0 || val <= 0) {
        printf("The rows and columns shouldn't be negative in value.");
        return 1;
    }
    
    int total = rows * val;
    int *A = (int*)malloc((size_t)total * sizeof(int));
    if (!A) {
        //* I have no idea what this does but AI said i need this and the memory allocation *//
        printf("Memory Allocation failed");
        return 1;
    }
        //* User needs to set the matrice up *//
    printf("Enter matrix elements (%d integers):", total); //* I had no idea you could do this in c but AI wanted me to use this one *//
    for(int i = 0; i < total; i++) {
        if (scanf("%d", &A[i]) != 1) {
        printf("Invalid Input");
        free(A);
        return 1;
        }
    }

    printf("Dense Matric:\n");
    printfDense(A, rows, val);
}