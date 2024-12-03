/**
 * @file ex1.c
 * @author Gabriel Paludeto
 * @brief Implemente um programa com duas pilhas estáticas: uma que armazenará apenas números pares e outra que armazenará apenas números ímpares. 
 * O programa deverá ler um arquivo de entrada contendo 10 números e empilhá-los corretamente. Ao final, imprima cada pilha em seu respectivo arquivo de saída.
 * @version 0.1
 * @date 2024-12-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_MAX 10


typedef struct Pilha {
    int numeros[TAM_MAX];
    int topo;
} Pilha;

bool estaCheia(Pilha *pilha) {

    return pilha->topo == TAM_MAX;

}

bool estaVazia(Pilha *pilha) {

    return pilha->topo == 0;

}

// Elementos recebem 0 a fim de evitar lixo
void inicializarPilha(Pilha *pilha) {

    pilha->topo = 0;

    for (int i = 0; i < TAM_MAX; i++) {
        pilha->numeros[i] = 0;
    }

}

void empilhar(Pilha *pilha, int num) {

    if (estaCheia(pilha)) {
        perror("Pilha cheia!\n");
        return;
    }

    pilha->numeros[pilha->topo] = num;
    pilha->topo++;

}

void desempilhar(Pilha *pilha) {

    if (estaVazia(pilha)) return;

    printf("%d desempilhado\n", pilha->numeros[--pilha->topo]);

}


int main(int argc, char **argv) {

    Pilha pilhaPares;
    Pilha pilhaImpares;

    inicializarPilha(&pilhaPares);
    inicializarPilha(&pilhaImpares);

    if (argc != 4) {
        perror("Número de argumentos inválido\n");
        exit(EXIT_FAILURE);
    }

    FILE *fpInput, *fpPar, *fpImpar;
    
    fpInput = fopen(argv[1], "r");
    fpPar = fopen(argv[2], "w");
    fpImpar = fopen(argv[3], "w");

    if (fpInput == NULL || fpPar == NULL || fpImpar == NULL) {
        fclose(fpInput);
        fclose(fpPar);
        fclose(fpImpar);

        exit(EXIT_FAILURE);
    }

    int conta = 0;
    int numero;

    while (fscanf(fpInput, "%d", &numero) == 1 && conta < TAM_MAX) {

        if (numero % 2 == 0) {
            fprintf(fpPar, "%d\n", numero);
            empilhar(&pilhaPares, numero);
        } else {
            fprintf(fpImpar, "%d\n", numero);
            empilhar(&pilhaImpares, numero);
        }

        conta++;

    }

    for (int i = 0; i < TAM_MAX; i++) {
        printf("%d\n", pilhaImpares.numeros[i]);
    }

     for (int i = 0; i < TAM_MAX; i++) {
        printf("%d\n", pilhaPares.numeros[i]);
    }

    fclose(fpInput);
    fclose(fpPar);
    fclose(fpImpar);

    return 0;

}