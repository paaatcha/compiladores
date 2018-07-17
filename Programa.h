#ifndef PROGRAMA_H
#define PROGRAMA_H

#include "Hash.h"
#include "Lista.h"
#include "MasterNode.h"
#include "string.h"

typedef struct Programa Programa;

Programa *criaPrograma(char *nome);

int checaNome(void *prog,char *str);

Hash *getHashVarsProg(Programa *p);

Hash *getHashFuncsProg(Programa *p);

void setNomeProg(Programa *p, char *str);

void setArvoreExecucao(Programa *p, MasterNode *main);

MasterNode *getArvoreExecucao(Programa *p);

void setProgamaCompilado (Programa *p);

int getProgramaCompilado (Programa *p);

void exibePrograma(void* prog);

#endif /* Programa.h */
