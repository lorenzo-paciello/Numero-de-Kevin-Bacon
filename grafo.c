#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "grafo.h"
#include "fila.h"

#define BRANCO 0
#define CINZA 1
#define PRETO 2

/*funcao que busca o vertice e avalia se eh possivel inseri-lo*/
Grafo *valorVertice(Grafo *grafo, char *ator)
{
    while(grafo != NULL && strcmp(grafo->ator, ator) != 0) /*percorre o grafo enquanto nao encontrar o vertice*/
    {
        grafo = grafo->prox;
    }

    return grafo;
}

/*funcao que insere o vertice no grafo*/
Grafo *mudaVertice(Grafo *grafo, Grafo *aux, char *ator, int *pos)
{
    strcpy(aux->ator, ator);
    aux->prox = grafo;
    aux->apontador = NULL;
    aux->pos = (*pos); /*insere a posicao do vertice na variavel*/
    grafo = aux;
    (*pos) += 1; /*incrementa a posicao para a possivel proxima insercao. Essa variavel eh usada tambem para determinar o numero total*/
                 /*de vertices ao final da leitura de todo o arquivo para alocar o vetor de cor*/

    return grafo;
}

/*funcao que insere um vertice na lista*/
Grafo *insereVertice(Grafo *grafo, char *ator, int *pos)
{
    Grafo *aux = valorVertice(grafo, ator); /*verifica se o vertice ja existe*/

    if(aux == NULL) /*vertice nao existe, entao eh possivel inseri-lo*/
    {
        aux = malloc(sizeof(Grafo)); /*aloca memoria do novo vertice*/
        grafo = mudaVertice(grafo, aux, ator, pos);
    }
        return grafo;
    
}

/*funcao auxiliar que verifica a existencia dos vertices para entao inserir a aresta*/
Apontador *valorLim(Grafo *grafo, char atorV[], char atorU[])
{
    /*verifica se os vertices existem*/
    Grafo *v1 = valorVertice(grafo, atorV);
    Grafo *v2 = valorVertice(grafo, atorU);
    Apontador *aux = NULL;

    if(v1 != NULL && v2 != NULL)
    {   
        /*percorre a lista de v1 enquanto o valor do vertice eh diferente de u*/
        aux = v1->apontador;
        while(aux != NULL && strcmp(aux->ator, atorU) != 0)
        {
            aux = aux->prox;
        }
    }

    return aux;
}

/*funcao que insere a aresta nos respectivos vertices*/
void mudaAresta(Grafo *grafo, char atorV[], char atorU[], char filme[])
{
    /*verifica se os dois vertices existem*/
    Grafo *g = valorVertice(grafo, atorV);
    Grafo *g1 = valorVertice(grafo, atorU);
    if(g != NULL && g1 != NULL){ /*se ambos os vertices existem*/
        Apontador *novo = malloc(sizeof(Apontador)); /*aloca e insere no comeco da lista*/
        strcpy(novo->ator, atorU);
        strcpy(novo->filme, filme);
        novo->pos = g->pos;
        novo->prox = g->apontador;
        g->apontador = novo;
    }
}

/*funcao principal que eh usada para inserir a aresta nos respectivo vertices*/
Apontador *insereAresta(Grafo *grafo, char atorV[], char atorU[], char filme[])
{
    Apontador *aux = valorLim(grafo, atorV, atorU); /*verifica se a aresta e os vertices existem*/

    if(aux == NULL) /*aresta nao existe, portanto eh possivel inseri-la*/
    {
        mudaAresta(grafo, atorV, atorU, filme); /*insere a aresta em (v, u)*/
        mudaAresta(grafo, atorU, atorV, filme); /*insere a aresta em (u, v)*/
    }

    return aux;
}

/*funcao que verifica se dois vertices sao adjacentes*/
int saoAdjacentes(Grafo *grafo, char atorV[], char atorU[])
{
    return (grafo->ator == atorV && grafo->apontador->ator == atorU) ? 1 : 0;
}

/*funcao que retorna o vertice oposto a v na aresta e*/
Grafo *oposto(Grafo *grafo, char atorV[], char filme[])
{
    Grafo *aux = grafo;

    while(aux != NULL && strcmp(aux->ator, atorV) != 0)
    {
        aux = aux->prox;
    }
    if(saoAdjacentes(aux, atorV, aux->apontador->ator))
    {
        return aux;
    }
}

/*funcao que separa os campos atraves dos delimitadores*/
void separaCampos(char *aux, Grafo **grafo, int *pos)
{
    char *token = strtok(aux, "/\n"), auxToken[200]; /*auxToken eh uma variavel auxiliar para armazenar o filme*/
    Fila *f = cria(); /*criacao da fila que auxiliara na insercao dos vertices e arestas*/

    strcpy(auxToken, token); /*armazenamento do primeiro campo*/
    token = strtok(NULL, "/\n");

    while (token != NULL) /*leitura dos campos ate encontrar "\n"*/
    {
        char auxActor[40]; /*variavel auxiliar que armazena os atores/atrizes*/
        strcpy(auxActor, token);
        *grafo = insereVertice(*grafo, auxActor, pos); /*insere o vertice no grafo e incrementa a variavel de posicao*/
        push(f, auxActor); /*insere o vertice na fila*/
        token = strtok(NULL, "/\n"); /*continua a leitura dos campos ate encontrar "\n"*/
    }

    /*variaveis auxiliares para percorrer a fila de vertices*/
    No *auxNo = f->ini;
    No *auxInsert = f->ini;
    while (auxNo != NULL)
    {
        char auxActor[40]; /*variavel auxiliar que armazena o vertice em questao*/
        strcpy(auxActor, auxNo->info);
        auxInsert = f->ini;
        while (auxInsert != NULL) /*o intuito desta parte eh realizar dois loops, como se fosse 2 for's, para inserir as arestas em todos os vertices armazenados*/
        {
            if (strcmp(auxNo->info, auxInsert->info) != 0)
            {
                insereAresta(*grafo, auxActor, auxInsert->info, auxToken);
            }
            auxInsert = auxInsert->prox;
        }
        auxNo = auxNo->prox;
    }

    esvazia(f); /*esvazia a fila e desaloca a memoria alocada*/
}

/*funcao que retorna a referencia para o vertice final da aresta
/*como a estrutura possui um ponteiro "apontador", o seguinte vertice seria aux->apontador*/
Grafo *verticeFinal(Grafo *grafo, char ator[])
{
    Grafo *aux = grafo;
    while(aux != NULL && strcmp(aux->ator, ator) != 0)
    {
        aux = aux->prox;
    }
    return aux;
}

/*funcao que realiza a busca em largura*/
int BFS(Grafo *grafo, int *cor, int pos, char fAtor[], Antecessor *antecessor)
{
    Fila *f = cria(); /*fila auxiliar*/
    char filme[200], ator[40]; /*variaveis auxiliares para o armazenamento de dados*/
    int posicaoAnterior = pos; /*variavel que armazena a posicao anterior ao vertice atual*/
    char auxAtor[40]; /*variavel que armazena o vertice armazenado no inicio da fila*/

    int result = -1; /*representa a posicao final no vetor de antecessores*/

    cor[pos] = CINZA; /*vertice em questao eh colorido de cinza*/
    antecessor[pos].indice = -1; /*simbolizando a posicao final do vetor de antecessores*/

    push(f, fAtor); /*insere o vertice na fila*/

    while (f->ini != NULL)
    {
        strcpy(auxAtor, f->ini->info); /*armazena o vetor do inicio da fila*/
        pop(f); /*retira o elemento do comeco da fila*/
        Grafo *aux = verticeFinal(grafo, auxAtor); /*recebe a posicao do vertice na aresta*/
        posicaoAnterior = aux->pos; /*armazena a posicao do vertice que vira a ser o anterior ao proximo*/
        Apontador *adj = aux->apontador; /*auxiliar que armazena o vertice seguinte*/
        if (saoAdjacentes(aux, aux->ator, adj->ator)) /*verifica se sao adjacentes*/
        {
            while (adj != NULL) /*enquanto a lista do conjunto de vertices nao for nula*/
            {
                strcpy(ator, adj->ator); /*armazena o vertice*/
                strcpy(filme, adj->filme); /*armazena a aresta*/
                Grafo *auxIn = grafo; /*variavel auxiliar que percorre a lista principal para encontrar o seguinte vertice*/
                while (auxIn != NULL && strcmp(auxIn->ator, adj->ator) != 0)
                {
                    auxIn = auxIn->prox;
                }
                if (cor[auxIn->pos] == BRANCO) /*verifica se o vertice ainda nao foi visitado*/
                {
                    /*armazena as informacoes no vetor de antecessores*/
                    antecessor[(auxIn)->pos].indice = posicaoAnterior;
                    strcpy(antecessor[(auxIn)->pos].atorAtual, auxAtor);
                    strcpy(antecessor[(auxIn)->pos].atorAnterior, ator);
                    strcpy(antecessor[(auxIn)->pos].filme, filme);
                    cor[(auxIn)->pos] = CINZA; /*marca o vertice como visitado*/
                    push(f, auxIn->ator); /*insere o vertice na fila*/
                }
                if (strcmp(auxIn->ator, "Bacon, Kevin") == 0) /*verifica se o vertice eh o procurado*/
                {
                    result = auxIn->pos; /*variavel armazena a posicao final do vertice*/
                    esvazia(f); /*a fila auxiliar eh esvaziada e desalocada*/
                    return result; /*eh retornado o valor da posicao do vertice*/
                }

                adj = adj->prox;
            }
        }
        cor[aux->pos] = PRETO; /*todos os vertices adjacentes foram visitados*/
    }
    esvazia(f); /*esvazia e desaloca a fila auxiliar*/
    return result; /*se a funcao chegar ate aqui, retorna -1, que eh o valor inicial da variavel*/
}

/*funcao que calcula o KB do ator em questao*/
int buscaKB(Grafo *grafo, int *pos, char ator[], int *auxAntecessor, Antecessor **contador)
{
    int cor[(*pos)], resultado, i; /*variaveis auxiliares*/
    Antecessor *antecessor = malloc((*pos) * sizeof(Antecessor)); /*variavel que armazena o caminho percorrido dentro da funcao BFS*/
    Grafo *aux = grafo; /*auxiliar usada para percorrer o grafo*/
    int auxResult; /*auxiliar que armazena o resultado para percorres o vetor de antecessores*/

    (*auxAntecessor) = 0; /*variavel que armazena o KB*/

    while (aux != NULL && strcmp(aux->ator, ator) != 0) /*percorre o grafo para encontrar o vertice*/
    {
        aux = aux->prox;
    }

    if (aux == NULL) /*vertice inexistente*/
    {
        return 0;
    }

    for (i = 0; i < (*pos); i++) /*inicia o vetor de cor com branco, e as posicoes do vetor de antecessor com -1*/
    {
        cor[i] = BRANCO;
        antecessor[i].indice = -1;
    }

    resultado = BFS(grafo, cor, aux->pos, aux->ator, antecessor); /*recebe a posicao do vertice final*/
    if (resultado != -1) /*se existir um caminho até "Bacon, Kevin"*/
    {
        auxResult = resultado; /*armazena o resultado para realizar mudancas*/
        while (auxResult != -1) /*-1 simboliza o inicio do caminho, pois no vetor de antecessores foram armazenadas as posicoes de tras pra frente*/
        {
            /*"contador" e a variavel que armazena o caminho de forma linear, ainda de tras pra frente*/
            (*contador) = realloc((*contador), ((*auxAntecessor) + 1) * sizeof(Antecessor));
            assert(contador);
            /*armazena os dados do vetor de antecessores no outro vetor para representar de forma linear*/
            strcpy((*contador)[(*auxAntecessor)].atorAtual, antecessor[auxResult].atorAtual);
            strcpy((*contador)[(*auxAntecessor)].atorAnterior, antecessor[auxResult].atorAnterior);
            strcpy((*contador)[(*auxAntecessor)].filme, antecessor[auxResult].filme);
            (*auxAntecessor) += 1; /*incrementa o KB*/
            auxResult = antecessor[auxResult].indice; /*indice recebe a posicao armazenada na variavel "antecessor" para percorrer a mesma*/
        }
        return 1; /*sucesso*/
    }
    else
    {
        return 2; /*retorno que simboliza a nao existencia de um caminho até "Bacon, Kevin", sendo o KB = infinito*/
    }
}

/*desaloca a memoria*/
void liberaGrafo(Grafo *grafo)
{
    while(grafo != NULL)
    {
        while(grafo->apontador != NULL)
        {
            Apontador *aux = grafo->apontador;
            grafo->apontador = grafo->apontador->prox;
            free(aux); /*desaloca o vertice junto da aresta*/
        }
        grafo = grafo->prox;
    }
    grafo = NULL;
    free(grafo); /*desaloca o grafo*/
}