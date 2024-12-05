#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Implemente uma função que receba um vetor de valores inteiros com n elementos e construa uma lista encadeada armazenando os elementos do vetor nos nós da lista. 
 * Se o vetor tiver zero elementos, a função deve ter como valor de retorno uma lista vazia. 
 * O protótipo da função é dado por: 

    Lista* constroi(int n, int* v);

    Obs: elabore sua função e a testa em um arquivo único contendo a main. Realize o upload deste arquivo aqui, depois de realizar os testes na sua máquina.
 * 
*/

typedef struct No {
    int elemento;
    struct No *prox;
} No;

typedef struct Lista {
    No *inicio, *fim;
} Lista;

bool estaVazia(Lista *lista) {
    return lista->inicio == NULL;
}

void inicializar(Lista *lista) {
    lista->inicio = lista->fim = NULL;
}

void append(Lista *lista, int n) {

    No *novoNo = (No *) malloc(sizeof(No));

    if (novoNo == NULL) {
        return;
    }

    novoNo->elemento = n;
    novoNo->prox = NULL; 

    if (estaVazia(lista)) {
        lista->inicio = lista->fim = novoNo; 
    } else {
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
    }

}

void imprimeLista(No *inicio) {

    if (inicio == NULL) {
        return;
    }

    printf("%d ", inicio->elemento);

    imprimeLista(inicio->prox);

}

Lista* constroi(int n, int* v) {

    Lista *novaLista = (Lista *) malloc(sizeof(Lista));

    if (novaLista == NULL) {
        return NULL;
    }

    if (n == 0) {
        inicializar(novaLista);
        return novaLista;
    }

    for (int i = 0; i < n; i++) {
        append(novaLista, v[i]);
    }

    return novaLista; 

}

int main() {

    int *v = malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }

    Lista *lista = constroi(5, v);

    imprimeLista(lista->inicio);
    printf("\n");

    return 0;

}