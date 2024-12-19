/**
 * @file hash_table.c
 * @author Gabriel Paludeto
 * @brief 
 
    A entrega está condicionada a presença nos dias 18/12 e 20/12.

    OBS: Para implementação utilize a vídeo aula acima:

        função hash
        tratamento da colisão

 * @version 0.1
 * @date 2024-12-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define M 7
#define TAM_STRING 31

typedef struct Item {
    int chave;
    char info[TAM_STRING];
} Item;

typedef struct HashTable {
    Item *vetor[M];
    int contador;
} HashTable;

void inicializarTabela(HashTable *tabela) {

    tabela->contador = 0;

    for (int i = 0; i < M; i++) {
        tabela->vetor[i] = NULL;
    }

}

bool estaCheia(HashTable *tabela) {
    return tabela->contador == M;
}

bool estaVazia(HashTable *tabela) {
    return tabela->contador == 0;
}

void imprimeTabela(HashTable *tabela) {

    for (int i = 0; i < M; i++) {

        if (tabela->vetor[i] == NULL) {
            printf("[%d] = NULL\n", i);
        } else {
            printf("[%d] = %s\n", i, tabela->vetor[i]->info);
        }

    }

} 

int hash(int chave) {
    return chave % M;
}

void insereTabela(HashTable *tabela, Item *novoElemento) {

    if (estaCheia(tabela)) {
        printf("Tabela cheia!\n");
        return;
    
    }

    int indice = hash(novoElemento->chave);

    while (tabela->vetor[indice] != NULL) {

        // Circularidade se for maior que indice max do array
        if (indice > M - 1) {
            indice = (indice % M) - 1;
        }

        // Sondagem linear
        indice++;

    }

    tabela->vetor[indice] = novoElemento;
    tabela->contador++;

}

void removeTabela(HashTable *tabela, int chave) {

    int indice = hash(chave);

    if (estaVazia(tabela)) {
        printf("Sem elementos para remoção\n");
        return;
    }

    tabela->vetor[indice] = NULL;
    tabela->contador--;

}

int main() {

    HashTable tabela;
    Item item1 = {1, "A"};
    Item item2 = {2, "B"};
    Item item3 = {3, "C"};
    Item item4 = {4, "D"};
    Item item5 = {5, "E"};
    Item item6 = {6, "F"};
    Item item7 = {7, "G"};
    Item item8 = {8, "H"};

    inicializarTabela(&tabela);

    // Teste estaVazia()
    if (estaVazia(&tabela)) {
        printf("Tabela vazia\n");
    }

    // Teste de inserção
    insereTabela(&tabela, &item1);
    insereTabela(&tabela, &item2);
    insereTabela(&tabela, &item3);
    insereTabela(&tabela, &item4);
    insereTabela(&tabela, &item5);
    insereTabela(&tabela, &item6);
    insereTabela(&tabela, &item7);
    insereTabela(&tabela, &item8);  // Tabela cheia

    imprimeTabela(&tabela);

    // Teste de remoção
    printf("=============================\n");
    removeTabela(&tabela, 1);
    removeTabela(&tabela, 2);
    removeTabela(&tabela, 3);
    removeTabela(&tabela, 4);
    removeTabela(&tabela, 5);
    removeTabela(&tabela, 6);
    removeTabela(&tabela, 7);
    removeTabela(&tabela, 8);   // Tabela vazia

    imprimeTabela(&tabela);

    return 0;

}