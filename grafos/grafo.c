#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct No {
    int vertice;
    struct No *prox;
} No;

// Pilha
typedef struct Pilha {
    No *topo;
    int qtde_pilha;
} Pilha;

// Fila
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

void inicializa_pilha(Pilha *pilha) {

    pilha->topo = NULL;
    pilha->qtde_pilha = 0;

}

bool pilha_vazia(Pilha *pilha) {

    return pilha->qtde_pilha == 0;

}

void empilha(Pilha *pilha, int vertice) {

    No *novo_no = (No *) malloc(sizeof(No));

    novo_no->vertice = vertice;

    if (!novo_no) {
        perror("Erro de alocacao\n");
        exit(EXIT_FAILURE);
    }

    novo_no->prox = pilha->topo;
    
    pilha->topo = novo_no;
    pilha->qtde_pilha++;

}

int desempilha(Pilha *pilha) {

    No *aux = pilha->topo;

    pilha->topo = aux->prox;
    int vert = aux->vertice;
    free(aux);
    pilha->qtde_pilha--;

    return vert;

}

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

void bfs(Grafo *grafo, int src) {

    int visitados[grafo->num_vert];

    for (int i = 0; i < grafo->num_vert; i++) {
        visitados[i] = 0;
    }

    Fila fila;
    inicializa_fila(&fila);
    visitados[src] = 1;
    adiciona_fila(&fila, src);
    
    while (!fila_vazia(&fila)) {

        int vertice = remove_fila(&fila);
        printf("%d ", vertice);

        for (int i = 0; i < grafo->num_vert; i++) {
            if (grafo->matriz_adj[vertice][i] == 1) {
                if (visitados[i] == 0) {
                    visitados[i] = 1;
                    adiciona_fila(&fila, i);
                }
            }
        }

        if (fila_vazia(&fila)) {

            for (int i = 0; i < grafo->num_vert; i++) {
                if (visitados[i] == 0) {
                    visitados[i] = 1;
                    adiciona_fila(&fila, i);
                }
            }

        }

    }

    printf("\n");

}

void dfs(Grafo *grafo, int src) {

    Pilha pilha;
    inicializa_pilha(&pilha);

    int visitados[grafo->num_vert];

    for (int i = 0; i < grafo->num_vert; i++) {
        visitados[i] = 0;
    }

    empilha(&pilha, src);
    visitados[src] = 1;

    while (!pilha_vazia(&pilha)) {

        int vertice = desempilha(&pilha);
        printf("%d ", vertice);

        for (int i = 0; i < grafo->num_vert; i++) {
            if (grafo->matriz_adj[vertice][i] == 1) {
                if (visitados[i] == 0) {
                    empilha(&pilha, i);
                    visitados[i] = 1;
                }
            }
        }

    }

    // vertices desconexos
    for (int i = 0; i < grafo->num_vert; i++) {
        if (!visitados[i]) {
            empilha(&pilha, i);
            visitados[i] = 1;
            while (!pilha_vazia(&pilha)) {
                int vert = desempilha(&pilha);
                printf("%d ", vert);
                for (int j = grafo->num_vert - 1; j >= 0; j--) {
                    if (grafo->matriz_adj[vert][j] == 1 && !visitados[j]) {
                        empilha(&pilha, j);
                        visitados[j] = 1;
                    }
                }
            }
        }
    }

    printf("\n");

}

int main() {

    Grafo grafo;

    inicializa_grafo(&grafo, 7, false);

  /*
         Graph Structure:
         
               0
              / \
             1   2
             |    \
             3     4
              \   /
                5
                |
                6

         Edges:
         0-1, 0-2, 1-3, 2-4, 3-5, 4-5, 5-6
    */
    adiciona_aresta(&grafo, 0, 1);
    adiciona_aresta(&grafo, 0, 2);
    adiciona_aresta(&grafo, 1, 3);
    adiciona_aresta(&grafo, 2, 4);
    adiciona_aresta(&grafo, 3, 5);
    adiciona_aresta(&grafo, 4, 5);
    adiciona_aresta(&grafo, 5, 6);

    printf("Matriz de adjacência: \n");
    imprime_matriz(&grafo);
    printf("====================\n");

    printf("BFS: ");
    bfs(&grafo, 0);
    printf("DFS: ");
    dfs(&grafo, 0);

    return 0;

}