#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Fila
typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct Fila {
    No *inicio_fila;
    No *fim_fila;
    int qtde_fila;
} Fila;

// Grafo
typedef struct Grafo {
    int **matriz_adj;
    int num_vert;
    bool digrafo;
} Grafo;

// Fila
void inicializa_fila(Fila *fila) {

    fila->inicio_fila = fila->fim_fila = 0;
    fila->qtde_fila = 0;

}

bool fila_vazia(Fila *fila) {
    return fila->qtde_fila == 0;
}

void imprime_fila(Fila *fila) {

    No *inicio = fila->inicio_fila;

    while (inicio != NULL) {
        printf("%d ", inicio->vertice);
        inicio = inicio->prox;
    }

    printf("\n");

}

void adiciona_fila(Fila *fila, int vertice) {

    No *novo_no = (No *) malloc(sizeof(No));

    if (!novo_no) {
        perror("Erro de alocacao\n");
        exit(EXIT_FAILURE);
    }

    novo_no->vertice = vertice;
    novo_no->prox = NULL;

    if (fila_vazia(fila)) {
        fila->inicio_fila = novo_no;
        fila->fim_fila = novo_no;
    } else {
        fila->fim_fila->prox = novo_no;
        fila->fim_fila = novo_no;
    }

    fila->qtde_fila++;

}

int remove_fila(Fila *fila) {

    if (fila_vazia(fila)) {
        perror("Fila vazia\n");
        exit(EXIT_FAILURE);
    }

    No *temp = fila->inicio_fila;
    fila->inicio_fila = temp->prox;
    int vert = temp->vertice;
    free(temp);
    fila->qtde_fila--;

    return vert;

}

// Grafo
void inicializa_grafo(Grafo *grafo, int num_vert, bool digrafo) {

    grafo->num_vert = num_vert;
    grafo->digrafo = digrafo;

    grafo->matriz_adj = (int **) malloc(num_vert * sizeof(int *));

    for (int i = 0; i < num_vert; i++) {
        grafo->matriz_adj[i] = (int  *) malloc(num_vert * sizeof(int));
    }

}

void adiciona_aresta(Grafo *grafo, int src, int dest) {

    // se nao eh digrafo
    grafo->matriz_adj[src][dest] = 1;

    if (!grafo->digrafo) {
        grafo->matriz_adj[dest][src] = 1;
    }

}

void imprime_matriz(Grafo *grafo) {

    for (int i = 0; i < grafo->num_vert; i++) {
        for (int j = 0; j < grafo->num_vert; j++) {
            printf("%d ", grafo->matriz_adj[i][j]);
        }
        printf("\n");
    }

}

void bfs(Grafo *grafo, int vertice) {

    int visitados[grafo->num_vert];

    for (int i = 0; i < grafo->num_vert; i++) {
        visitados[i] = 0;
    }

    Fila fila;
    inicializa_fila(&fila);
    visitados[vertice] = 1;
    adiciona_fila(&fila, vertice);
    
    while (!fila_vazia(&fila)) {

        int vertice = remove_fila(&fila);
        printf("%d\n", vertice);

        for (int i = 0; i < grafo->num_vert; i++) {
            if (grafo->matriz_adj[vertice][i] == 1) {
                if (visitados[i] == 0) {
                    visitados[i] = 1;
                    adiciona_fila(&fila, i);
                }
            }
        }

    }

}

int main() {

    Grafo grafo;
    Fila fila;

    inicializa_fila(&fila);
    adiciona_fila(&fila, 1);
    inicializa_grafo(&grafo, 6, false);

    /*
        0 -- 2
        |    |
        3 -- 5
        |    |
        1 -- 4
    */  

    adiciona_aresta(&grafo, 0, 2);
    adiciona_aresta(&grafo, 0, 3);
    adiciona_aresta(&grafo, 1, 3);
    adiciona_aresta(&grafo, 1, 4);
    adiciona_aresta(&grafo, 2, 5);
    adiciona_aresta(&grafo, 3, 5);
    adiciona_aresta(&grafo, 4, 5);

    imprime_matriz(&grafo);

    bfs(&grafo, 0);

    return 0;

}