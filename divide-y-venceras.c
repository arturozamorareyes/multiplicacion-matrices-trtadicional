#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para crear matriz
int** crearMatriz(int n) {
    int** matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matriz[i] = (int*)malloc(n * sizeof(int));
    return matriz;
}

// Llena matriz con números aleatorios
void llenarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matriz[i][j] = rand() % 10;
}

// Suma matrices
void sumar(int** A, int** B, int** resultado, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            resultado[i][j] = A[i][j] + B[i][j];
}

// Resta matrices
void restar(int** A, int** B, int** resultado, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            resultado[i][j] = A[i][j] - B[i][j];
}

// Multiplicación por divide y vencerás
void multiplicarDaC(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int nuevoTam = n / 2;

    // Crear submatrices temporales
    int** A11 = crearMatriz(nuevoTam);
    int** A12 = crearMatriz(nuevoTam);
    int** A21 = crearMatriz(nuevoTam);
    int** A22 = crearMatriz(nuevoTam);
    int** B11 = crearMatriz(nuevoTam);
    int** B12 = crearMatriz(nuevoTam);
    int** B21 = crearMatriz(nuevoTam);
    int** B22 = crearMatriz(nuevoTam);

    // Llenar submatrices
    for (int i = 0; i < nuevoTam; i++) {
        for (int j = 0; j < nuevoTam; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + nuevoTam];
            A21[i][j] = A[i + nuevoTam][j];
            A22[i][j] = A[i + nuevoTam][j + nuevoTam];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + nuevoTam];
            B21[i][j] = B[i + nuevoTam][j];
            B22[i][j] = B[i + nuevoTam][j + nuevoTam];
        }
    }

    // Crear matrices para resultados intermedios
    int** C11 = crearMatriz(nuevoTam);
    int** C12 = crearMatriz(nuevoTam);
    int** C21 = crearMatriz(nuevoTam);
    int** C22 = crearMatriz(nuevoTam);

    int** P1 = crearMatriz(nuevoTam);
    int** P2 = crearMatriz(nuevoTam);

    // C11 = A11*B11 + A12*B21
    multiplicarDaC(A11, B11, P1, nuevoTam);
    multiplicarDaC(A12, B21, P2, nuevoTam);
    sumar(P1, P2, C11, nuevoTam);

    // C12 = A11*B12 + A12*B22
    multiplicarDaC(A11, B12, P1, nuevoTam);
    multiplicarDaC(A12, B22, P2, nuevoTam);
    sumar(P1, P2, C12, nuevoTam);

    // C21 = A21*B11 + A22*B21
    multiplicarDaC(A21, B11, P1, nuevoTam);
    multiplicarDaC(A22, B21, P2, nuevoTam);
    sumar(P1, P2, C21, nuevoTam);

    // C22 = A21*B12 + A22*B22
    multiplicarDaC(A21, B12, P1, nuevoTam);
    multiplicarDaC(A22, B22, P2, nuevoTam);
    sumar(P1, P2, C22, nuevoTam);

    // Combinar submatrices en C
    for (int i = 0; i < nuevoTam; i++) {
        for (int j = 0; j < nuevoTam; j++) {
            C[i][j] = C11[i][j];
            C[i][j + nuevoTam] = C12[i][j];
            C[i + nuevoTam][j] = C21[i][j];
            C[i + nuevoTam][j + nuevoTam] = C22[i][j];
        }
    }

    // Liberar memoria
    // (Puedes hacerlo después para no saturar ahora el código con muchas líneas)
}

// Liberar una matriz
void liberarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
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
    multiplicarDaC(A, B, C, n);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion (DaC): %.6f segundos\n", tiempo);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}
