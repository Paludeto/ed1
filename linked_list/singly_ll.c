#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Objeto {
    int cpf;
    int idade;
    char nome[30];
    struct Objeto *prox;
} Objeto;

typedef struct LinkedList {
    Objeto *inicio;
    Objeto *fim;
    int tamanho;
} LinkedList;

void inicializaLista(LinkedList *lista) {

    lista->inicio = NULL;
    lista->tamanho = 0;

}

bool estaVazia(LinkedList *lista) {

    return lista->tamanho == 0;

}

void insereElemento(LinkedList *lista, int cpf, int idade, char nome[]) {

    Objeto *novoObj = (Objeto *) malloc(sizeof(Objeto));

    if (novoObj == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return;
    }

    novoObj->cpf = cpf;
    novoObj->idade = idade;
    strcpy(novoObj->nome, nome);
    novoObj->prox = NULL;

    if (estaVazia(lista)) {
        lista->inicio = lista->fim = novoObj;
    } else {

        // Ordem crescente de idade
        if (novoObj->idade < lista->inicio->idade) {
            novoObj->prox = lista->inicio;
            lista->inicio = novoObj;
            lista->tamanho++;
        } else {

            Objeto *auxiliar = lista->inicio;

            while (novoObj->idade < auxiliar->prox->idade && auxiliar->prox != NULL) {
                auxiliar = auxiliar->prox;
            }

            

        }

        
    }

    
    
}