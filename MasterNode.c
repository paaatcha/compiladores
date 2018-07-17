#include "MasterNode.h"

int id_unico;

struct MasterNode
{
	// Strings de controle/identificação

	int id_unico;
	char str1[50];
	char str2[50];

	// Dados armazenados para terminais

	void *data; // Para constantes ou expressões agregadas
	int dataType; // Para dizer o tipo da constnate

	Variavel *var; // Para variáveis

	Funcao *func; // Para funcoes
	
	// Ponteiros para parentess

	struct MasterNode *prox;
	struct MasterNode *filhos[3];

};

MasterNode *criaNode(char *str1, char *str2)
{
	MasterNode *m = (MasterNode *) malloc (sizeof(MasterNode));
	m->id_unico = id_unico;
	
	id_unico++; // Para ser unico, ninguem mais tera o mesmo, duh...
	
	strcpy(m->str1,str1);
	strcpy(m->str2,str2);
	m->prox = NULL;
	int i;
	for(i = 0; i < 3; i++)
	{
		m->filhos[i] = NULL;
	}
	
	return m;
}


void *getData(MasterNode *m)
{
	return m->data;
}

void setData(MasterNode *m, void *d)
{
	m->data = d;
}

void setLoadedVar(MasterNode *m, void *v)
{
	m->var = v;
}

Variavel *getLoadedVar(MasterNode *m)
{
	return m->var;
}

int getIdUnico(MasterNode *m)
{
	return m->id_unico;
}

int getDataType(MasterNode *m)
{
	return m->dataType;
}

void setDataType(MasterNode *m, int t)
{
	m->dataType = t;
}

char *getStringMasterNode(MasterNode *m, int index)
{
	if(!index)
	{
		return m->str1;
	}
	else
	{
		return m->str2;
	}
}

MasterNode *getFolha(MasterNode *m, char pos)
{
	switch (pos)
	{
		case 'i':
		{
			return getData(m);
			break;
		}
		case 'p': // Próximo
		{
			return m->prox;		
			break;

		}
		case 'e': // Esquerda
		{
			return m->filhos[0];		
			break;
		}
		case 'm': // Meio
		{
			return m->filhos[1];
			break;
		}
		
		case 'd': // Direita
		{
			return m->filhos[2];
			break;
		}
	}
}

void insereNode(MasterNode* m, MasterNode *p, char pos)
{
	switch (pos)
	{
		case 'i':
		{
			m->data = p;
			break;
		}
		case 'p': // Próximo
		{
			m->prox = p;		
			break;

		}
		case 'e': // Esquerda
		{
			m->filhos[0] = p;		
			break;
		}
		case 'm': // Meio
		{
			m->filhos[1] = p;
			break;
		}
		
		case 'd': // Direita
		{
			m->filhos[2] = p;
			break;
		}
	}
}

void exibeMasterNode(MasterNode *m)
{
	if(!m) printf("nuul\n");
	else printf("%s|%s\n", m->str1,m->str2);
}

void exibeMasterNodeComProfundidade(MasterNode *m,int i)
{
	if(!m) printf("nuul\n");
	
	else
	{	int j;
		for(j = 0; j < i; j++)
		{
			printf("-");
		}
		printf("%s|%s\n", m->str1,m->str2);
	}
	
	
}

int serPara(MasterNode *m)
{
	return !strcmp(m->str2,"para");
}

void imprime_arvore(MasterNode *a, int profundidade)
{
	int i;
	if(!a) return;

	for (i = 0; i < profundidade; i++)
	{
		printf("-");
	}
	
	
	exibeMasterNode(a); // imprime a raiz
	
	if(serPara(a))
	{
		exibeMasterNodeComProfundidade(getData(a),profundidade + 1);
	}
	imprime_arvore(a->filhos[0], profundidade + 1);//imprime a sad
	
	
	
	imprime_arvore(a->filhos[1], profundidade + 1); //imprime a sae
	imprime_arvore(a->filhos[2], profundidade + 1); //imprime a sae
	if(a->prox)
	{
		printf("\n");
		for (i = 0; i < profundidade; i++)
		{
			printf("-");
		}
		printf("Proxima Arvore:\n");
		imprime_arvore(a->prox,profundidade);
	}
}

