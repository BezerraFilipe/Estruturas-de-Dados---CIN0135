#include <stdio.h>
#include <stdlib.h>

int *rand_array(int n){ //
    int delta = 1000/n; 
    int *arr = calloc(n, sizeof(n)); 
    /*
    - *arr é um ponteiro que aponta para a primeira posição do array na heap;
    - calloc reserva n espaços na memória de tamanho n, nesse caso, de tamanho inteiro;
    */

    arr[0] = rand() % delta; // arr[0] é no máximo 1000
    
    for (int i = 1; i < n; i++){
        arr[i] = arr[i-1] + (rand() % delta);
    }
    
    return arr;
}

void printArray(int *arr, int n){

    for (int i = 0; i < n; i++){
        printf("%d", arr[i]);
        printf(" ");
        
    }
    printf("\n");
}

int invertArray(int *arr, int n){

    for (int i = 0, j = n-1; i < n/2; i++, j--){
        
        int temp = arr[j];
        arr[j] = arr[i]; 
        arr[i] = temp;
    }
    return *arr;
}



int main(){

    int limit = 1000;
    int randLimit = rand() %limit;

    int N = 0;    
    while (N<1 || N>100)
    {
        printf("\nEnter a array size (max 100):");
        scanf("%d", &N );
    }
    

    int *arr = rand_array(N);

    printf("\nArray Crescente (em ordem): \n");
    printArray(arr, N);
    invertArray(arr, N);
    printf("\nArray Decrescente (invertido): \n");
    printArray(arr, N);
    

    return 0;
}

/*
Atividade: Reverter um vetor de inteiros

Lê do teclado o tamanho do array (N <= 100)

Cria um array aleatório em ordem crescente com valores entre 0 e 1000 (usar função rand())

Imprime o array original

Inverte o array

Imprime o array invertido

*/