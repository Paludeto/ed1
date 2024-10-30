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
    int tamanho;
} LinkedList;

void inicializaLista(LinkedList *lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

bool estaVazia(LinkedList *lista) {
    return lista->tamanho == 0;
}

void imprimeLista(LinkedList *lista) {
    Objeto *obj = lista->inicio;

    while (obj != NULL) {
        printf("Nome: %s, Idade: %d\n", obj->nome, obj->idade);
        obj = obj->prox;
    }
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
        lista->inicio = novoObj;
    } else {
        // Ordem crescente de idade
        if (novoObj->idade < lista->inicio->idade) {
            novoObj->prox = lista->inicio;
            lista->inicio = novoObj;
        } else {
            Objeto *auxiliar = lista->inicio;

            while (auxiliar->prox != NULL && novoObj->idade > auxiliar->prox->idade) {
                auxiliar = auxiliar->prox;
            }

            novoObj->prox = auxiliar->prox;
            auxiliar->prox = novoObj;
        }
    }

    lista->tamanho++;

}

void removeElemento(LinkedList *lista, int idade) {

    if (estaVazia(lista)) {
        printf("Lista vazia!\n");
        return;
    }

    if (idade < lista->inicio->idade) {
        printf("Objeto não existe\n");
        return;
    }

    if (idade == lista->inicio->idade) {
        printf("Elemento de idade %d removido com sucesso\n", idade);
        Objeto *aux = lista->inicio;
        lista->inicio = aux->prox;
        free(aux);
        lista->tamanho--;
        return;
    }

    Objeto *aux = lista->inicio;

    while (aux->prox != NULL && aux->prox->idade < idade) {
        aux = aux->prox;
    }

    if (aux->prox == NULL || aux->prox->idade != idade) {
        printf("Idade não está na lista\n");
        return;
    }

    printf("Elemento de idade %d removido com sucesso\n", idade);
    Objeto *temp = aux->prox;
    aux->prox = temp->prox;
    free(temp);
    lista->tamanho--;

}

void destroiLista(LinkedList *lista) {

    Objeto *aux = lista->inicio;
    Objeto *aux2;    

    while (aux != NULL) {
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
    lista->inicio = NULL; // Opcional: garantir que o ponteiro `inicio` é NULL
    lista->tamanho = 0;   // Resetar o tamanho da lista

}

int main() {

    LinkedList lista;
    inicializaLista(&lista); // Inicializa a lista

    insereElemento(&lista, 12345, 38, "Pietra");
    insereElemento(&lista, 54321, 60, "Pietr");
    insereElemento(&lista, 87654, 70, "Piet");
    insereElemento(&lista, 34567, 62, "Pie");

    removeElemento(&lista, 38);
    removeElemento(&lista, 20); 
    removeElemento(&lista, 70);
    
    imprimeLista(&lista);
    destroiLista(&lista);

    return 0;

}
