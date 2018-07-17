#ifndef _FUNCAO_H
#define _FUNCAO_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Lista.h"




typedef struct Funcao Funcao;

Funcao *criaFunc();

void setCall(Funcao *f, void *x);

void *getCall(Funcao *f);

void liberaFunc (void *f);

int passaTudo(void *v);

void setTiposArgsFunc(Funcao *f, Lista *l);

void setNameFunc(Funcao *f,char *nome);

void setTipoRetornoFunc (Funcao *f, int t);

Lista *getTiposArgs (Funcao *f);

void *copiaFunc(void *f);

char* getNameFunc(Funcao *f);

int getTipoRetornoFunc(Funcao *f);

int getAridadeFunc(Funcao *f);

void exibeFunc(void *f);

int funcaoHashFunc (void *info,int sizeHash);

int funcaoComparacaoFunc(void* info1,void *info2); // 0 significa diferente.

#endif
