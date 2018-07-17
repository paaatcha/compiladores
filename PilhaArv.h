#ifndef PILHAARV
#define PILHAARV

#include "MasterNode.h"

typedef struct PilhaArv PilhaArv;

PilhaArv *criaPilhaArv();

void preenchePilha(PilhaArv *p, MasterNode **v,int quant);

void empilhaNode(PilhaArv* p, MasterNode *n);

MasterNode* desempilhaNode(PilhaArv* p);

void desempilhaTudo(PilhaArv* p);

int stackSize(PilhaArv *p);

void exibePilha (PilhaArv *p);

MasterNode *getFirst(PilhaArv *p);

MasterNode *converteParaArvore(PilhaArv *p);

void desalocaPilhaArv(PilhaArv *a);

#endif
