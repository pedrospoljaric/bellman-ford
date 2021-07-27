#include <stdio.h>
#include <stdlib.h>
#define MAX 500

#define INFINITO 999999

typedef struct Vertice
{
    int id;
    int nArestas;
    int dist;
    struct Vertice *prox;
}Vertice;

typedef struct Grafo
{
    int M[MAX][MAX];
    Vertice *V;
    int nArestas;
    int nVertices;
}Grafo;

typedef struct Fila
{
    Vertice *inicio, *fim;
}Fila;

Vertice novoVert(int id);
void InserirAresta(Grafo *grafo, Vertice u, Vertice v, int valor);
int BellmanFord(Grafo *g, int vInicial);

void Enfileirar(Fila *f, Vertice v);
Vertice Desenfileirar(Fila *f);
int FilaVazia(Fila *f);

int main()
{
    Grafo grafo;
    int i, j;

    grafo.nArestas = 0;
    grafo.nVertices = 0;

    int vert;
    printf("Numero de vertices: ");
    scanf("%d", &vert);
    grafo.nVertices = vert;

    grafo.V = (Vertice*) malloc(grafo.nVertices * sizeof(Vertice));

    for (i = 0; i < grafo.nVertices; i++)
        grafo.V[i] = novoVert(i);


    for (i = 0; i < grafo.nVertices; i++)
        for (j = 0; j < grafo.nVertices; j++)
            grafo.M[i][j] = INFINITO;

    int edg;
    printf("Numero de arestas: ");
    scanf("%d", &edg);
    printf("Exemplo: Origem Destino Peso\n");

    for (i = 0; i < edg; i++)
    {
        int o, d, p;
        scanf("%d %d %d", &o, &d, &p);
        InserirAresta(&grafo, grafo.V[o], grafo.V[d], p);
    }

    for (i = 0; i < grafo.nVertices; i++)
    {
        grafo.V[i].dist = INFINITO;
    }

    int alteracao;

    for (i = 0; i < grafo.nVertices; i++)
    {
        alteracao = 0;
        alteracao = BellmanFord(&grafo, 0);
    }

    if (alteracao)
        printf("Ha ciclo(s) negativo(s).\n");
    else
        printf("Nao ha ciclo(s) negativo(s).\n");

    return 0;
}

int BellmanFord(Grafo *g, int vInicial)
{
    int alteracao = 0;
    int i, j;

    Fila f;
    f.inicio = NULL;
    f.fim = NULL;
    g->V[vInicial].dist = 0;
    Enfileirar(&f, g->V[vInicial]);

    for(i = 0; i < g->nVertices; i++)
    {
        for(j = 0; j < g->nVertices; j++)
        {

            if (g->M[g->V[i].id][g->V[j].id] != INFINITO)
            {
                if (g->V[i].dist + g->M[g->V[i].id][g->V[j].id] < g->V[j].dist)
                {
                    g->V[j].dist = g->V[i].dist + g->M[g->V[i].id][g->V[j].id];
                    alteracao = 1;
                }
            }
        }
    }
    return alteracao;
}

void Enfileirar(Fila *f, Vertice v)
{
    Vertice *aux = (Vertice*) malloc(sizeof(Vertice));
    *aux = v;

    aux->prox = NULL;

    if (f->inicio == NULL)
        f->inicio = aux;

    if (f->fim != NULL)
        f->fim->prox = aux;

    f->fim = aux;
}

int FilaVazia(Fila *f)
{
    if (f->inicio == NULL) return 1;
    return 0;
}

Vertice Desenfileirar(Fila *f)
{
    Vertice v = *f->inicio;

    Vertice *aux = f->inicio->prox;

    f->inicio = aux;

    return v;
}

Vertice novoVert(int id)
{
    Vertice v;
    v.id = id;
    v.nArestas = 0;

    return v;
}

void InserirAresta(Grafo *grafo, Vertice u, Vertice v, int valor)
{
    //printf("%d %d\n", u.id, v.id);
    grafo->M[u.id][v.id] = valor;
    u.nArestas++;
    v.nArestas++;
}
