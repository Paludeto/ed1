#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int chave;

    struct Node *direita;
    struct Node *esquerda;
} Node;

void inicializarArvore(Node **raiz) {

    (*raiz) = NULL;

}

bool estaVazia(Node **raiz) {

    return (*raiz) == NULL; 

}

void insereElemento(Node **no, int key) {

    Node *novoNo = (Node *) malloc(sizeof(Node));

    if (novoNo == NULL) {
        fprintf(stderr, "Erro na alocação de memória\n");
        return;
    }
    
    novoNo->chave = key;
    novoNo->direita = NULL;
    novoNo->esquerda = NULL;

    if (estaVazia(no)) {
        (*no) = novoNo;
        return;
    }

    if ((*no)->chave == novoNo->chave) {
        fprintf(stderr, "Elemento repetido não inserido\n");
        return;
    }

    if (novoNo->chave < (*no)->chave) {
        insereElemento(&(*no)->esquerda, key);
    } else {
        insereElemento(&(*no)->direita, key);
    }

}

void preOrdem(Node **raiz) {

    if (estaVazia((raiz))) {
        return;
    } 

    printf("%d ", (*raiz)->chave);

    preOrdem(&(*raiz)->esquerda);
    preOrdem(&(*raiz)->direita);

}

void posOrdem(Node **raiz) {

    if (estaVazia((raiz))) {
        return;
    } 

    printf("%d ", (*raiz)->chave);

    preOrdem(&(*raiz)->direita);
    preOrdem(&(*raiz)->esquerda);

}

void emOrdem(Node **raiz) {

    if (estaVazia((raiz))) {
        return;
    } 

    emOrdem(&(*raiz)->esquerda);
    printf("%d ", (*raiz)->chave);
    emOrdem(&(*raiz)->direita);

}

int main() {

    Node *raiz;

    inicializarArvore(&raiz);

    // Inserções
    insereElemento(&raiz, 65);
    insereElemento(&raiz, 42);
    insereElemento(&raiz, 51);
    insereElemento(&raiz, 32);
    insereElemento(&raiz, 12);
    insereElemento(&raiz, 38);
    insereElemento(&raiz, 80);
    insereElemento(&raiz, 71);
    insereElemento(&raiz, 69);
    insereElemento(&raiz, 92);
    insereElemento(&raiz, 90);

    printf("Pré-ordem: ");
    preOrdem(&raiz);
    printf("\n");

    printf("Pós-ordem: ");
    posOrdem(&raiz);
    printf("\n");

    printf("Em ordem: ");
    emOrdem(&raiz);
    printf("\n");

    return 0;

}