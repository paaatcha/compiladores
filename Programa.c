#include "Programa.h"

struct Programa
{
	char nome[64];
	Hash *variaveis;
	Hash *funcoes;
	
	int compilado; // 0 para nao. 1 para sim.
	MasterNode *aExec;
};

Programa *criaPrograma(char *nome)
{
	Programa *p = (Programa*) malloc (sizeof(Programa));
	strcpy(p->nome,nome);
	p->compilado = 0;
	p->variaveis = criaHash(400);
	p->funcoes = criaHash(400);
	p->aExec = NULL;
	
	return p;	
}

int checaNome(void *prog,char *str)
{
	Programa *p = (Programa*) prog;
	return !strcmp(str,p->nome);
}

void setNomeProg(Programa *p, char *str)
{
	strcpy(p->nome,str);
}

Hash *getHashVarsProg(Programa *p)
{
	return p->variaveis;
}

Hash *getHashFuncsProg(Programa *p)
{
	return p->funcoes;
}

void setArvoreExecucao(Programa *p, MasterNode *main)
{
	p->aExec = main;
}

MasterNode *getArvoreExecucao(Programa *p)
{
	return p->aExec;
}

void setProgamaCompilado (Programa *p)
{
	p->compilado = 1;
}

int getProgramaCompilado (Programa *p)
{
	return p->compilado;
}

void exibePrograma(void*prog)
{
	Programa *p = (Programa*) prog;
	printf("%s ",p->nome);
}

