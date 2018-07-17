#include "Funcao.h"

#define INTEIRO 1
#define CARACTER 2
#define LITERAL 3
#define REAL 4
#define BOOLEANO 5
#define VAZIO 6

#define MAX_FUNC_NAME_SIZE 32

struct Funcao{
	char nome[MAX_FUNC_NAME_SIZE];
	int tipo_retorno;
	int aridade;
	void *callFunc;
	Lista *tiposArgs;

};

Funcao *criaFunc()
{
	Funcao *f = (Funcao *) malloc(sizeof(Funcao));
	f->tiposArgs = criaLista();
	return f;
}

void setCall(Funcao *f, void *x)
{
	f->callFunc = x;
}

void *getCall(Funcao *f)
{
	return f->callFunc;
}

void liberaFunc (void *x)
{
	Funcao *f = (Funcao *) x;
	desalocaLista(f->tiposArgs,free);
		
	free(f);
}

int passaTudo(void *v)
{
	return 1;
}

void setTiposArgsFunc(Funcao *f, Lista *l)
{
	f->tiposArgs = filtraLista1(l,passaTudo,copiaFunc);
}

Lista *getTiposArgs (Funcao *f)
{
	return f->tiposArgs;
}

void *copiaFunc(void *f)
{
	Funcao *fcpy = criaFunc();
	*fcpy = *(Funcao*)f;
	return f;
}

void setNameFunc(Funcao *f,char *nome)
{
	if(strlen(nome) > MAX_FUNC_NAME_SIZE)
	{
		printf("Erro, nome \"%s\" muito grande\n", nome);
		exit(0);
	}
	strcpy(f->nome,nome);
}

void setTipoRetornoFunc (Funcao *f, int t)
{
	if (t >= 1 && t <= 6){
		f->tipo_retorno = t;
	}else{
		printf("Tipo de retorno inválido\n");
		exit(0);
	}
}

void setAridadeFunc (Funcao *f, int t)
{
	if (t >= 0){
		f->aridade = t;
	}else{
		printf("Aridade negativa nao eh permitida\n");
		exit(0);
	}
}

// Retorna sem cópia
char* getNameFunc(Funcao *f)
{
	return f->nome;
}

int getTipoRetornoFunc(Funcao *f)
{
	return f->tipo_retorno;
}

int getAridadeFunc(Funcao *f)
{
	return f->aridade;
}

void exibeFunc(void *f2)
{
	Funcao *f = (Funcao *) f2;
	printf("Funcao %s, retorna tipo %d, possui aridade %d",f->nome,f->tipo_retorno,f->aridade);
}

int funcaoHashFunc (void *info,int sizeHash)
{
	Funcao *f = (Funcao *) info;
	int c = 0;
	int i;
	int tam = strlen(f->nome);
	for(i = 0; i < tam; i++)
	{
		c+= f->nome[i];
	}
	return abs(c*c) % sizeHash;
}

int funcaoComparacaoFunc(void* info1,void *info2) // 0 significa diferente.
{
	Funcao *f1, *f2;
	f1 = (Funcao*) info1;
	f2 = (Funcao*) info2;
	
	return !strcmp(f1->nome,f2->nome);
}
