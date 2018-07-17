#ifndef VARIAVEL_H
#define VARIAVEL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Variavel Variavel;

Variavel *criaVariavel();

void liberaVariavel (void *v);


void setUsadaVar(Variavel *v);
void setNameVar(Variavel *v,char *nome);
void setDimVar(Variavel *v,int m);
void setTipoVar(Variavel *v, int tipo);
void setEscopoVar (Variavel *v, char* es);
void setDataVar(Variavel *var, void *data);

char* getNameVar(Variavel *v);
int getTipoVar(Variavel *v);
char *getEscopoVar(Variavel *v);
int getUsadaVar(Variavel *v);
void *getDataVar(Variavel *var);

int isNullorFalse(Variavel *var);
void exibeVar (Variavel *v);
void funcaoImprimir (void *info);
void exibeTipoVar(Variavel *v);


int funcaoHashVar (void *info,int sizeHash);
int funcaoComparacaoVar(void* info1,void *info2); // 0 significa diferente.




#endif /* Variavel.h */
