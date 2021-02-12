typedef char elem;

struct no {
    elem info[40];
    struct no *prox;
};

typedef struct no No;

struct fila {
    No *ini, *fim;
};

typedef struct fila Fila;

Fila *cria();
void esvazia(Fila *f);
void push(Fila *f, elem x[]);
void pop(Fila *f);