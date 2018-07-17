#include "Variavel.h"


#define INTEIRO 1
#define CARACTER 2
#define LITERAL 3
#define REAL 4
#define BOOLEANO 5
#define VAZIO 6

#define NORMAL 0
#define VETOR 1
#define MATRIZ 2


#define MAX_VAR_NAME_SIZE 32
#define MAX_SCOPE_NAME_SIZE 64

struct Variavel {
	char nome[MAX_VAR_NAME_SIZE];
	int tipo;
	char escopo[MAX_SCOPE_NAME_SIZE];
	int usada;
	int dim; // 0 para variavis normais, 1 pra vetor e 2 pra matriz.
	
	void *data;

};

Variavel *criaVariavel()
{
	Variavel *v = (Variavel *) malloc(sizeof(Variavel));
	v->usada = 0;
	v->dim = 0;
	strcpy(v->nome,"");
	v->tipo = 7; // Começa sem tipo válido
	v->data = malloc(300*sizeof(char)); // Começa sem dados alocados, mas quando necessário, será feito um malloc.
}

void liberaVariavel (void *x){
	Variavel *v = (Variavel *) x;
	free(v->data);
	free(v);
}

void setUsadaVar(Variavel *v)
{
	v->usada = 1;
}

int getUsadaVar(Variavel *v)
{
	return v->usada;
}

int getTipoVar(Variavel *v)
{
	return v->tipo;
}

void setNameVar(Variavel *v,char *nome)
{
	if(strlen(nome) > MAX_VAR_NAME_SIZE)
	{
		printf("Erro, nome \"%s\" muito grande\n",nome);
		exit(0);
	}
	strcpy(v->nome,nome);
}

char* getNameVar(Variavel *v)
{
	return v->nome;
}

void setDimVar(Variavel *v,int m)
{
	if(m > 2 || m < 0)
	{
		printf("Erro, matriz \"%d\" desconhecido\n",m);
		exit(0);
	}
	v->dim = m;
}

void setTipoVar(Variavel *v, int tipo)
{
	if(tipo > 5 || tipo <= 0)
	{
		printf("Erro, tipo \"%d\" desconhecido\n",tipo);
		exit(0);
	}
	v->tipo = tipo;
}

void setEscopoVar (Variavel *v, char* es)
{
	if(strlen(es) > MAX_SCOPE_NAME_SIZE)
	{
		printf("Erro, escopo \"%s\" muito grande\n",es);
		exit(0);
	}	
	strcpy(v->escopo,es);
}


char *getEscopoVar(Variavel *v)
{
	return v->escopo;
}

void exibeTipoVar(Variavel *v)
{
	switch(v->tipo)
	{
		case INTEIRO:
			printf("inteiro ");
		break;
		
		case REAL:
			printf("real ");
		break;
		
		case LITERAL:
			printf("literal ");
		break;
		
		case BOOLEANO:
			printf("booleano ");
		break;
		
		case CARACTER:
			printf("caracter ");
		break;
	}
}

// Função editada para exibir apenas o necessário.
void exibeVar (Variavel *v)
{
	if(!v) return;
		
	//printf ("Nome = %s | Tipo = ",v->nome);
	//exibeTipoVar(v);
	//printf ("| escopo = %s | dim = %d | usada = %d |",v->escopo,v->dim,v->usada);
	//printf("conteudo = ");
	switch(v->tipo)
	{
		case INTEIRO:
			printf("%d",*((int*)v->data));
		break;
		
		case REAL:
			printf("%lf",*((double*)v->data));
		break;
		
		case LITERAL:
			printf("%s",(char*)v->data);
		break;
		
		case BOOLEANO:
			if(*((int*)v->data)) printf("VERDADEIRO"); else printf("FALSO");
		break;
		
		case CARACTER:
			printf("%c",*((char*)v->data));
		break;
	}
	//printf("\n");
}

void funcaoImprimir (void *info)
{
	if(!info) return;
	
	Variavel *v = (Variavel*)info;
	
	printf ("Nome = %s | Tipo = ",v->nome);
	exibeTipoVar(v);
	printf ("| escopo = %s | dim = %d | usada = %d |",v->escopo,v->dim,v->usada);
	printf("conteudo = ");
	switch(v->tipo)
	{
		case INTEIRO:
			printf("%d",*((int*)v->data));
		break;
		
		case REAL:
			printf("%lf",*((double*)v->data));
		break;
		
		case LITERAL:
			printf("%s",(char*)v->data);
		break;
		
		case BOOLEANO:
			if(*((int*)v->data)) printf("VERDADEIRO"); else printf("FALSO");
		break;
		
		case CARACTER:
			printf("%c",*((char*)v->data));
		break;
	}
	printf("\n");
}

int funcaoHashVar (void *info,int sizeHash)
{
	int c = 0;
	Variavel *var = (Variavel *) info;
	char concat[128];
	concat[0] = '\0';
	strcat(concat,var->nome);
	strcat(concat,var->escopo);
	int tam = strlen(concat);
	int i;
	for(i = 0; i < tam; i++)
	{
		c += (int) concat[i];
	}
	c += var->tipo;
	
	return (abs(c*c)) % sizeHash;
}

int funcaoComparacaoVar(void* info1,void *info2) // 0 significa diferente.
{
	Variavel *v1,*v2;
	v1 = (Variavel *) info1;
	v2 = (Variavel *) info2;
	
	if(!strcmp(v1->nome,v2->nome))
	{
		if(!strcmp(v1->escopo,v2->escopo))
		{
			return 1;
		}
	}
	return 0;
}

void setDataVar(Variavel *var, void *data)
{
	var->data = data;
}

int isNullorFalse(Variavel *v)
{
	switch(v->tipo)
	{
		case INTEIRO:
			return ((*((int*)v->data)) == 0);
		break;
		
		case REAL:
			return ((*((double*)v->data)) == 0.0);
		break;
		
		case LITERAL:
			return !strcmp (((char*)v->data) , "");
		break;
		
		case BOOLEANO:
			return ((*((int*)v->data)) == 0);
		break;
		
		case CARACTER:
			return ((*((char*)v->data)) == '\0');
		break;
	}
}

void *getDataVar(Variavel *var)
{
	return var->data;
}


