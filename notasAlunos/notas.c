#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct Aluno
typedef struct {
    char nome[15];
    char matricula[10];
    float nota;
} Aluno;

int main() {
    FILE *file; // Ponteiro para o arquivo
    char buffer[256];
    const char *filename = "notas.txt"; // Nome do arquivo a ser lido
    int maxAlunos = 101; // Quantidade máxima de alunos
    int countAlunos = 0; // Contador para alunos lidos
    float somaNotas = 0; // Soma das notas

    // Alocação dinâmica do array de structs
    Aluno *alunos = malloc(maxAlunos * sizeof(Aluno));
    if (alunos == NULL) {
        perror("Erro ao alocar memória");
        return EXIT_FAILURE;
    }

    // Abrindo o arquivo para leitura
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        free(alunos); // Liberar memória antes de sair
        return EXIT_FAILURE;
    }

    // Lendo os registros do arquivo
    while (fscanf(file, "%s %s %f", alunos[countAlunos].nome,
                  alunos[countAlunos].matricula, 
                  &alunos[countAlunos].nota) == 3) {
        somaNotas += alunos[countAlunos].nota; // Soma as notas
        countAlunos++; // Incrementa o número de alunos lidos

        // Verifica se o limite do array foi atingido
        if (countAlunos >= maxAlunos) {
            printf("Número máximo de alunos excedido!\n");
            break;
        }
    }

    fclose(file); // Fecha o arquivo

    // Calcula a média da turma
    float mediaTurma = somaNotas / countAlunos;

    // Exibe a lista de alunos com nota >= média
    printf("Média da turma: %.2f\n", mediaTurma);
    printf("Alunos com nota maior ou igual à média:\n");
    for (int i = 0; i < countAlunos; i++) {
        if (alunos[i].nota >= mediaTurma) {
            printf("%s (%s): %.2f\n", alunos[i].nome, alunos[i].matricula, alunos[i].nota);
        }
        else{
            printf("%s (%s): %.2f REPROVADO\n", alunos[i].nome, alunos[i].matricula, alunos[i].nota);
        }
        
    }

    // Libera a memória alocada
    free(alunos);
    return 0;
}
