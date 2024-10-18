#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define M 5

typedef struct Objeto {   
    int cpf;
    char nome[30];
    int idade;
} Objeto;

typedef struct Fila {
    int inicio;
    int fim;
    int quantidadeElementos;
    Objeto vetor[M];
} Fila;

void inicializaFila(Fila *fila) {

    fila->inicio = fila->fim = fila->quantidadeElementos = 0;

}

bool estaVazia(Fila *fila) {

    return fila->quantidadeElementos == 0;

}

bool estaCheia(Fila *fila) {

    return fila->quantidadeElementos == M;
    
}

void adicionaObjeto(Fila *fila, Objeto novoObjeto) {

    if (!estaCheia(fila)) {
        
        fila->vetor[fila->fim] = novoObjeto; 
        fila->quantidadeElementos++;
        fila->fim++;

        printf("Objeto %s adicionado\n", novoObjeto.nome);

    } else {

        fila->fim = 0;
        fila->vetor[fila->fim] = novoObjeto; 
        fila->quantidadeElementos++;
        fila->fim++;

        printf("Objeto adicionado ao primeiro índice, deu a volta\n");
        
    }

}

void removeObjeto(Fila *fila) {

    if (estaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }

    printf("%s removido\n", fila->vetor[fila->inicio].nome);

    fila->inicio = (fila->inicio + 1) % M; 
    fila->quantidadeElementos--;

}


int main() {

    Fila fila;

    Objeto obj = {0, "Primeiro", 0};
    Objeto obj2 = {0, "Segundo", 0};
    Objeto obj3 = {0, "Terceiro", 0};
    Objeto obj4 = {0, "Quarto", 0};
    Objeto obj5 = {0, "Quinto", 0};
    Objeto obj6 = {0, "Sexto", 0};

    inicializaFila(&fila);

    adicionaObjeto(&fila, obj);
    adicionaObjeto(&fila, obj2);
    adicionaObjeto(&fila, obj3);
    adicionaObjeto(&fila, obj4);
    adicionaObjeto(&fila, obj5);
    adicionaObjeto(&fila, obj6);

    printf("%s\n", fila.vetor[fila.inicio].nome);
    printf("%s\n", fila.vetor[fila.fim].nome);

    return 0;

}


