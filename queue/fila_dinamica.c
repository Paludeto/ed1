#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Objeto {
    int cpf, idade;
    char nome[30];
    struct Objeto *prox;
} Objeto;

typedef struct FilaDinamica {
    Objeto *inicio;
    Objeto *fim;
    int tamanho;
} FilaDinamica;

void inicializaFila(FilaDinamica *fila) {

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;

}

bool estaVazia(FilaDinamica *fila) {

    return fila->tamanho == 0;

}

int retornaTamanho(FilaDinamica *fila) {

    return fila->tamanho;

}

void adicionaObjeto(FilaDinamica *fila, int cpf, int idade, char nome[]) {

    Objeto *novoObjeto = (Objeto *) malloc(sizeof(Objeto));

    if (novoObjeto == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return;
    }

    novoObjeto->cpf = cpf;
    novoObjeto->idade = idade;
    strcpy(novoObjeto->nome, nome);
    novoObjeto->prox = NULL;

    if (estaVazia(fila)) {
        fila->inicio = novoObjeto;
    } else {
        fila->fim->prox = novoObjeto;
    }
   
    fila->fim = novoObjeto;
    fila->tamanho++;

}

void imprimePrimeiro(FilaDinamica *fila) {

    if (estaVazia(fila)) {
        fprintf(stderr, "Fila vazia!\n");
        return;
    }

    printf("%s\n", fila->inicio->nome);
    printf("%d\n", fila->inicio->cpf);
    printf("%d\n", fila->inicio->idade);
    printf("=======================================\n");

}

void removeElemento(FilaDinamica *fila) {

    if (estaVazia(fila)) {
        fprintf(stderr, "Fila vazia!\n");
        return;
    }

    Objeto *aux = fila->inicio;
    fila->inicio = fila->inicio->prox;
    free(aux);
    fila->tamanho--;

}

void destroiFila(FilaDinamica *fila) {

    if (estaVazia(fila)) {
        printf("Fila esvaziada!\n");
        return;
    } 
        
    removeElemento(fila);
    destroiFila(fila);

}
 
int main() {

    FilaDinamica fila;
    inicializaFila(&fila);

    adicionaObjeto(&fila, 123456789, 19, "Amostradinho");
    adicionaObjeto(&fila, 123456789, 20, "Casca de Bala");

    imprimePrimeiro(&fila);

    removeElemento(&fila);
    imprimePrimeiro(&fila);

    removeElemento(&fila);
    imprimePrimeiro(&fila);

    destroiFila(&fila);

    return 0;

}