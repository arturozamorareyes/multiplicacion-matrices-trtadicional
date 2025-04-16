#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Llena una matriz con números aleatorios
void llenarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matriz[i][j] = rand() % 10; // números del 0 al 9
}

// Multiplicación tradicional
void multiplicarTradicional(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main() {
    int n;
    printf("Introduce el tamaño n de la matriz (n x n): ");
    scanf("%d", &n);

    // Reservar memoria
    int** A = (int**)malloc(n * sizeof(int*));
    int** B = (int**)malloc(n * sizeof(int*));
    int** C = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        A[i] = (int*)malloc(n * sizeof(int));
        B[i] = (int*)malloc(n * sizeof(int));
        C[i] = (int*)malloc(n * sizeof(int));
    }

    srand(time(NULL));
    llenarMatriz(A, n);
    llenarMatriz(B, n);

    clock_t inicio = clock();
    multiplicarTradicional(A, B, C, n);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %.6f segundos\n", tiempo);

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
