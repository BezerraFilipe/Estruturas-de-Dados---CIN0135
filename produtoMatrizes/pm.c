#include <stdio.h>
#include <stdlib.h>

int **criaMatriz(int m, int n){

    int **matriz;
    matriz = calloc(m, sizeof(int*));
    for (int i = 0; i < m; i++){
        matriz[i] = calloc(n, sizeof(int));
        for (int j = 0; j < n; j++){
             matriz[i][j] = i+j;
            // matriz[i][j] = (rand() % 201) -100;
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
        
    }
    return matriz;
}

int **multiplicaMatriz(int **matrizA, int **matrizB, int M, int N, int P){
    
    int **matrizC = calloc(M, sizeof(int *));
    for (int i = 0; i < M; i++) {
        matrizC[i] = calloc(P, sizeof(int));
    }

    for (int i = 0; i < M; i++){
        for (int j = 0; j < P; j++){
            for (int k = 0; k < N; k++){
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j]; 
            }            
            printf("%4d", matrizC[i][j]);
        }
        printf("\n");

        
    }
    return matrizC;

}

void liberaMatriz(int **matriz, int m) {
    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main(){

    int M, N, P = 0;

    while (M < 2 || M > 10 || N < 2 || N > 10 || P < 2 || P > 10){
        printf("\nEscreva 3 valores entre 2 e 10 separados por espaco: ");
        scanf("%d %d %d", &M, &N, &P);        
        printf("Criando matrizes: A %dx%d e B %dx%d\n", M, N, N, P);
    }
    
    printf("\nMatriz A:\n");
    int **matrizA = criaMatriz(M,N);
    printf("\nMatriz B:\n");
    int **matrizB = criaMatriz(N,P);

    printf("\n Matriz C (multiplicacao A*B)\n");
    int **matrizC = multiplicaMatriz(matrizA, matrizB, M,N,P);

    liberaMatriz(matrizA, M);
    liberaMatriz(matrizB, N);
    liberaMatriz(matrizC, M);

    return 0;
}
/*
Atividade: Calcular o produto de duas matrizes

Lê três inteiros positivos M N P no intervalo (2, 10);

Cria duas matrizes aleatórias A e B de dimensões MxN e NxP com valores no intervalo (-100, +100);

Calcula a matriz produto C = A*B de dimensões MxP

Imprime a matrizes A, B, C

*/