struct aresta
{
    char ator[40];
    char filme[200];
    long pos;
    struct aresta *prox;
};

typedef struct aresta Apontador;

struct grafo
{
    char ator[40];
    long pos;
    Apontador *apontador;
    struct grafo *prox;
};

typedef struct grafo Grafo;

typedef struct
{
    char atorAtual[40];
    char atorAnterior[40];
    char filme[200];
    long indice;
}Antecessor;

Grafo *insereVertice(Grafo *grafo, char *atorV, int *pos);
Grafo *valorVertice(Grafo *grafo, char *ator);
Apontador *valorLim(Grafo *grafo, char atorV[], char atorU[]);
Apontador *insereAresta(Grafo *grafo, char atorV[], char atorU[], char filme[]);
void mudaAresta(Grafo *grafo, char atorV[], char atorU[], char filme[]);
Grafo *verticeFinal(Grafo *grafo, char ator[]);
Grafo *oposto(Grafo *grafo, char atorV[], char filme[]);
void liberaGrafo(Grafo *grafo);
int saoAdjacentes(Grafo *a, char atorV[], char atorU[]);
void separaCampos(char *aux, Grafo **grafo, int *pos);
int BFS(Grafo *grafo, int *cor, int pos, char fAtor[], Antecessor *antecessor);
int buscaKB(Grafo *grafo, int *pos, char ator[], int *auxAntecessor, Antecessor **contador);