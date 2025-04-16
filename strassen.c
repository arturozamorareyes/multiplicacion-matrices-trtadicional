#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Crear matriz
int** crearMatriz(int n) {
    int** matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matriz[i] = (int*)malloc(n * sizeof(int));
    return matriz;
}

// Liberar matriz
void liberarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

// Llenar matriz con números aleatorios
void llenarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matriz[i][j] = rand() % 10;
}

// Sumar matrices
void sumar(int** A, int** B, int** R, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R[i][j] = A[i][j] + B[i][j];
}

// Restar matrices
void restar(int** A, int** B, int** R, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R[i][j] = A[i][j] - B[i][j];
}

// Strassen recursivo
void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int** A11 = crearMatriz(newSize);
    int** A12 = crearMatriz(newSize);
    int** A21 = crearMatriz(newSize);
    int** A22 = crearMatriz(newSize);
    int** B11 = crearMatriz(newSize);
    int** B12 = crearMatriz(newSize);
    int** B21 = crearMatriz(newSize);
    int** B22 = crearMatriz(newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    int** P1 = crearMatriz(newSize);
    int** P2 = crearMatriz(newSize);
    int** P3 = crearMatriz(newSize);
    int** P4 = crearMatriz(newSize);
    int** P5 = crearMatriz(newSize);
    int** P6 = crearMatriz(newSize);
    int** P7 = crearMatriz(newSize);

    int** temp1 = crearMatriz(newSize);
    int** temp2 = crearMatriz(newSize);

    restar(B12, B22, temp1, newSize);     // B12 - B22
    strassen(A11, temp1, P1, newSize);

    sumar(A11, A12, temp1, newSize);      // A11 + A12
    strassen(temp1, B22, P2, newSize);

    sumar(A21, A22, temp1, newSize);      // A21 + A22
    strassen(temp1, B11, P3, newSize);

    restar(B21, B11, temp1, newSize);     // B21 - B11
    strassen(A22, temp1, P4, newSize);

    sumar(A11, A22, temp1, newSize);      // A11 + A22
    sumar(B11, B22, temp2, newSize);      // B11 + B22
    strassen(temp1, temp2, P5, newSize);

    restar(A12, A22, temp1, newSize);     // A12 - A22
    sumar(B21, B22, temp2, newSize);      // B21 + B22
    strassen(temp1, temp2, P6, newSize);

    restar(A11, A21, temp1, newSize);     // A11 - A21
    sumar(B11, B12, temp2, newSize);      // B11 + B12
    strassen(temp1, temp2, P7, newSize);

    int** C11 = crearMatriz(newSize);
    int** C12 = crearMatriz(newSize);
    int** C21 = crearMatriz(newSize);
    int** C22 = crearMatriz(newSize);

    // C11 = P5 + P4 - P2 + P6
    sumar(P5, P4, temp1, newSize);
    restar(temp1, P2, temp2, newSize);
    sumar(temp2, P6, C11, newSize);

    // C12 = P1 + P2
    sumar(P1, P2, C12, newSize);

    // C21 = P3 + P4
    sumar(P3, P4, C21, newSize);

    // C22 = P1 + P5 - P3 - P7
    sumar(P1, P5, temp1, newSize);
    restar(temp1, P3, temp2, newSize);
    restar(temp2, P7, C22, newSize);

    // Combinar en C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Liberar memoria (omitimos para mantener claro el ejemplo)
}

int main() {
    int n;
    printf("Introduce tamaño de matriz (potencia de 2): ");
    scanf("%d", &n);

    int** A = crearMatriz(n);
    int** B = crearMatriz(n);
    int** C = crearMatriz(n);

    srand(time(NULL));
    llenarMatriz(A, n);
    llenarMatriz(B, n);

    clock_t inicio = clock();
    strassen(A, B, C, n);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion (Strassen): %.6f segundos\n", tiempo);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}
