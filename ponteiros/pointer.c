#include <stdio.h>

int main(){

    int x = 1024;
    printf("Valor de x = %d\n", x);
    printf("Tamanho de x = %ld\n", sizeof(x)); // retorna espaço ocupado na memória em bytes
    printf("Endereco de x = %ld\n", &x); // o valor de x foi escrito nesse local da memória


    // um ponteiro é também uma variável, tem um endereço de memória e carrega consigo um valor
    int *p; // declaração de um ponteiro para um inteiro


    p = &x; // o ponteiro p está apontando para o endereço de memória de x 


    printf("Endereco de p  = %ld\n", p); 
    // ao acessar p, estamos acessando o endenreço de memória da variável x
    
    
    printf("Endereco de *p com & = %ld\n", &*p); /*
    aqui é acessado o endereço de memória do valor que o ponteiro p assume, 
    nesse caso, o endereço de memória de onde foi escrito o valor da variável x
    */
    
    
    printf("Endereco de p com  & = %ld\n", &p);
    /*
    Aqui é acessado o endereço de memória do endereço de memória do ponteiro p
    */

    
    printf("Valor de *p  = %d\n", *p); 
    // ao acessar *p, estamos acessando o VALOR do endereço de memória apontado por p
    

    return 0;
}