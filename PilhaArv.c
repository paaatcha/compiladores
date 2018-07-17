#include "PilhaArv.h"
#define max_stack_size_t 300
struct PilhaArv
{
	MasterNode *pilha[max_stack_size_t];
	int quant;
};

PilhaArv *criaPilhaArv()
{
	PilhaArv * p = (PilhaArv *) malloc (sizeof(PilhaArv));
	p->quant = 0;
	return p;
}

void preenchePilha(PilhaArv *p, MasterNode **v,int quant)
{
	int i;
	for(i = 0; i < quant; i++)
	{
		empilhaNode(p,v[i]);
	}
}

void empilhaNode(PilhaArv* p, MasterNode *n)
{
	
	//exibeMasterNode(n);
	if(p->quant < max_stack_size_t)
	{
		p->pilha[p->quant] = n;
		int id = getIdUnico(p->pilha[p->quant]);
		//printf("\nEmpilhando  %d ...\n",id);
		p->quant++;
	}
	else
		printf("pilha cheia!!!\n");

}

MasterNode* desempilhaNode(PilhaArv* p)
{
	
	//exibeMasterNode(p->pilha[p->quant]);
	
	if(p->quant > 0)
	{
		int id = getIdUnico(p->pilha[p->quant-1]);
		//printf("\nDesempilhando %d...\n",id);
		if(p->quant == 1)
		{
			MasterNode *aux = p->pilha[--p->quant];
			p->pilha[0] = NULL;
			return aux;
		}
		else
		{
			return p->pilha[--p->quant];
		}
	}
	else
	{
		
		printf("pilha ja esta vazia!!!\n");
		return NULL;
	}
}

MasterNode *getFirst(PilhaArv *p)
{
	if(p->quant > 0)
		return p->pilha[p->quant];
	else
	{
		printf("pilha ja esta vazia!!!\n");
		return NULL;
	}
}

int stackSize(PilhaArv *p)
{
	return p->quant;
}

void exibePilha (PilhaArv *p){
	int tam = p->quant;
	int i;
    printf("Tamanho Pilha da Main = %d\n\n",tam);
	for (i=0; i<tam; i++){
		exibeMasterNode(p->pilha[i]);
	}	
}

MasterNode *converteParaArvore(PilhaArv *p)
{
	int tam = p->quant;
	if(!tam) return NULL;
	int j = p->quant-1;
	int i;
	
	MasterNode *r = p->pilha[0];
	
	for(i = 0; i < tam; i++)
	{
		if(j == 0)
			break;
		
		insereNode(p->pilha[j-1], p->pilha[j], 'p');
		j--;
	}
	p->quant = 0; // Esvaziei a pilha!!!
	return r;
}

void desempilhaTudo(PilhaArv* p)
{
	p->quant = 0;
}

void desalocaPilhaArv(PilhaArv *a)
{
	free(a);
}
