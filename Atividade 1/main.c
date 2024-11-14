#include <stdio.h>
#include "prime.h"

int main() {
    int N;
    printf("Digite um número inteiro positivo: ");
    scanf("%d", &N);

    if (is_prime(N)) {
        printf("%d is prime\n", N);
    } else {
        printf("%d is not prime\n", N);
    }

    return 0;
}