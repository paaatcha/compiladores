#ifndef LISTA_H
#define LISTA_H 1

#include <stdio.h>
#include <stdlib.h>

typedef struct NoLista NoLista;
typedef struct Lista Lista;

NoLista *criaNoLista(void *info);
Lista *criaLista();
int avancaCursor(Lista *lista);
void resetaCursor(Lista *lista);
void insereLista(Lista *lista, void *info);
void retiraLista(Lista *lista, int pos, void (*deleta)(void*));
void desalocaLista(Lista *lista, void (*funcaoExclusao)(void*));
void desalocaApenasLista(Lista *lista);
void ordenaLista(Lista *lista, int (*funcaoComparacao)(void*,void*));
void *acessaInfo(Lista* lista);
void *acessaEnesimaInfo(Lista* lista, int pos);
void exibeLista(Lista *lista, void (*funcaoImprimir)(void *));
void salvaLista(Lista *lista, FILE *p, void (*funcaoImprimir)(FILE *p,void *));
int tamanhoLista(Lista *lista);
int ultimoLista(Lista *lista);
Lista *filtraLista1(Lista *base, int(*criterio)(void*), void* (*funcaoCopia)(void*));
Lista *filtraLista2(Lista *base, int(*criterio)(void*,int), int n);
void *primeiraOcorrencia(Lista *base, char *str, int (*checa)(void *prog,char *str));

int vazio(void *info);

#endif
