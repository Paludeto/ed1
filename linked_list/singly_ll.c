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
        printf("%s\n", obj->nome);
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
        lista->inicio =  novoObj;
    } else {

        // Ordem crescente de idade
        if (novoObj->idade < lista->inicio->idade) {
            novoObj->prox = lista->inicio;
            lista->inicio = novoObj;
            lista->tamanho++;
        } else {

            Objeto *auxiliar = lista->inicio;

            while (auxiliar->prox != NULL && novoObj->idade > auxiliar->prox->idade) {
                auxiliar = auxiliar->prox;
            }

            novoObj->prox = auxiliar->prox;
            auxiliar->prox = novoObj;  

        }

        lista->tamanho++;   
        
    }   
    
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

    // Terminar!

} 

void destroiLista(LinkedList *lista) {

    Objeto *aux = lista->inicio;
    Objeto *aux2;    

    while (aux->prox != NULL) {
        aux2 = aux;        
        aux = aux->prox;
        free(aux2);
    }

}   

// Fazer pesquisa, mínimo, máximo, próximo e anterior
int main() {
    
    LinkedList lista;

    insereElemento(&lista, 12345, 38, "Pietra");
    insereElemento(&lista, 54321, 60, "Pietr");
    insereElemento(&lista, 87654, 70, "Piet");
    insereElemento(&lista, 34567, 62, "Pie");
    
    imprimeLista(&lista);
    destroiLista(&lista);

    return 0;

}