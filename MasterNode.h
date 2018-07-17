#ifndef MASTERNODE
#define MASTERNODE

#include "Variavel.h"
#include "Funcao.h"

#define dataTypeVariable 0
#define dataTypeInteger 1
#define dataTypeReal 2
#define dataTypeBoolean 3
#define dataTypeLiteral 4
#define dataTypeChar 5
#define dataTypeMasterNode 6

// MasterNode é uma árvore-lista.

typedef struct MasterNode MasterNode;

/* INSTRUÇÕES DE USO

	Nodes iniciados por "cmd" são comandos.
	Nodes iniciados por "exp" são expressões AVALIÁVEIS.
	Nodes iniciados por "call" indicam chamadas de funções (construção de novas árvores).

*/

MasterNode *criaNode(char *str1, char *str2);

void insereNode(MasterNode* m, MasterNode *p, char pos);

void *getData(MasterNode *m);

void setData(MasterNode *m, void *d);


void setLoadedVar(MasterNode *m, void *v);

Variavel *getLoadedVar(MasterNode *m);

int getIdUnico(MasterNode *m);

int getDataType(MasterNode *m);

void setDataType(MasterNode *m, int t);

char *getStringMasterNode(MasterNode *m, int index);

MasterNode *getFolha(MasterNode *m, char pos);

void exibeMasterNode(MasterNode *m);

int serPara(MasterNode *m);

void imprime_arvore(MasterNode *a, int profundidade);

#endif /* masterNode.h */
