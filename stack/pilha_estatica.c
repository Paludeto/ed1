#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_ARRAY 10

typedef struct {

    int array[TAMANHO_ARRAY];
    int topo;

} Pilha;

void inicializaPilha(Pilha *pilha) {

    pilha->topo = 0;

}

void push(Pilha *pilha, int elemento) {

    if (pilha->topo < TAMANHO_ARRAY) {
        pilha->array[pilha->topo] = elemento;
        pilha->topo++;
    } else {
        printf("Pilha cheia!\n");
    }

}

void pop(Pilha *pilha) {

    if (pilha->topo > 0) {
        pilha->topo--;
        printf("%d\n", pilha->array[pilha->topo]);
        pilha->array[pilha->topo] = 0;        
    } else {
        printf("Pilha vazia!\n");
    }
    
}

void imprimePilha(Pilha pilha) {

    printf("[ ");

    for (int i = 0; i < TAMANHO_ARRAY; i++) {

        printf("%d ", pilha.array[i]);
        
    }

    printf("]\n");

}

int main() {

    Pilha pilha;

    inicializaPilha(&pilha);

    //testa push
    for (int i = 0; i < TAMANHO_ARRAY; i++) {

        push(&pilha, i);

    }

    imprimePilha(pilha);

    //testa pop
    for (int i = TAMANHO_ARRAY; i > 0; i--) {
        pop(&pilha);
    }
    
    imprimePilha(pilha);

    return 0;

}