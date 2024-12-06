#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_STRING 32

typedef struct No {
    int chave;
    struct No *filhoDir;
    struct No *filhoEsq;
    int h; // Altura do nó
} No;

void inicializaArvore(No **raiz) {
    *raiz = NULL;
}

bool estaVazia(No **raiz) {
    return (*raiz == NULL);
}

int altura(No *no) {

    if (no == NULL) {
        return -1;
    }

    return no->h;

}

int calculaFb(No *no) {

    if (no == NULL) {
        return 0;
    }

    return altura(no->filhoDir) - altura(no->filhoEsq);

}

No *rotacaoEsquerda(No *x) {

    No *y = x->filhoDir;
    x->filhoDir = y->filhoEsq;
    y->filhoEsq = x;

    x->h = 1 + (altura(x->filhoEsq) > altura(x->filhoDir) ? altura(x->filhoEsq) : altura(x->filhoDir));
    y->h = 1 + (altura(y->filhoEsq) > altura(y->filhoDir) ? altura(y->filhoEsq) : altura(y->filhoDir));

    return y;
}

No *rotacaoDireita(No *y) {

    No *x = y->filhoEsq;
    y->filhoEsq = x->filhoDir;
    x->filhoDir = y;

    y->h = 1 + (altura(y->filhoEsq) > altura(y->filhoDir) ? altura(y->filhoEsq) : altura(y->filhoDir));
    x->h = 1 + (altura(x->filhoEsq) > altura(x->filhoDir) ? altura(x->filhoEsq) : altura(x->filhoDir));

    return x;

}

No *balancear(No *raiz) {

    int fb = calculaFb(raiz);

    if (fb > 1) { // Desbalanceamento à direita

        if (calculaFb(raiz->filhoDir) < 0) { // Rotação dupla para esquerda
            raiz->filhoDir = rotacaoDireita(raiz->filhoDir);
        }

        raiz = rotacaoEsquerda(raiz);

    } else if (fb < -1) { // Desbalanceamento à esquerda

        if (calculaFb(raiz->filhoEsq) > 0) { // Rotação dupla para direita
            raiz->filhoEsq = rotacaoEsquerda(raiz->filhoEsq);
        }

        raiz = rotacaoDireita(raiz);

    }

    return raiz;

}

No *insereNoAvl(No *raiz, int chave) {

    if (raiz == NULL) {

        No *novoNo = (No *) malloc(sizeof(No));

        if (novoNo == NULL) {
            exit(EXIT_FAILURE);
        }

        novoNo->chave = chave;
        novoNo->filhoDir = NULL;
        novoNo->filhoEsq = NULL;
        novoNo->h = 0;

        return novoNo;

    }

    if (chave < raiz->chave) {
        raiz->filhoEsq = insereNoAvl(raiz->filhoEsq, chave);
    } else if (chave > raiz->chave) {
        raiz->filhoDir = insereNoAvl(raiz->filhoDir, chave);
    } else {
        return raiz; // Não permite duplicados
    }

    raiz->h = 1 + (altura(raiz->filhoEsq) > altura(raiz->filhoDir) ? altura(raiz->filhoEsq) : altura(raiz->filhoDir));
    return balancear(raiz);

}

void emOrdem(No *raiz) {

    if (raiz == NULL) {
        return;
    }

    emOrdem(raiz->filhoEsq);
    printf("%d\n", raiz->chave);
    emOrdem(raiz->filhoDir);

}

int main() {

    No *raiz;
    inicializaArvore(&raiz);

    // Inserção de nós na árvore AVL
    raiz = insereNoAvl(raiz, 10);
    raiz = insereNoAvl(raiz, 20);
    raiz = insereNoAvl(raiz, 5);
    raiz = insereNoAvl(raiz, 4);
    raiz = insereNoAvl(raiz, 8);
    raiz = insereNoAvl(raiz, 15);

    // Impressão em ordem
    printf("Árvore em ordem:\n");
    emOrdem(raiz);

    return 0;

}