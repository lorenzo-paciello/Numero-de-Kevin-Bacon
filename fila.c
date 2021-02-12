#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"


Fila *cria() {
    Fila *f = malloc(sizeof(Fila)); /*instancia a fila*/
    /*define fila vazia*/
    f->ini = NULL;
    f->fim = NULL;

    return f;
}

void esvazia(Fila *f) {
    /*apaga os elementos*/
    No *aux = NULL;
    while (f->ini != NULL) {
        aux = f->ini;
        f->ini = f->ini->prox;
        free(aux);
    }
    /*desaloca a fila*/
    f = NULL;
    free(f);
}

void push(Fila *f, elem x[]) {
    No *aux;
    aux = malloc(sizeof(No)); /*cria novo no*/
    strcpy(aux->info, x);
    aux->prox = NULL;
    if (f->ini == NULL){ /*atualiza os ponteiros*/
        f->ini = aux;
    }
    else{
        f->fim->prox = aux;
    }
    f->fim = aux;
}

void pop(Fila *f)
{
    if(f->ini != NULL) /*verifica se a fila nao esta vazia*/
    {
        No *atual = f->ini;
        f->ini = f->ini->prox; /*ajusta o ponteiro*/
        free(atual); /*desaloca o no anterior*/
    }
}