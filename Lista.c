#include "Lista.h"

struct NoLista
{
	void *info;
	NoLista *prox;
};

struct Lista
{
	NoLista *inicio;
	NoLista *fim;
	NoLista *cursor;
};

NoLista *criaNoLista(void *info)
{
	NoLista *noLista = (NoLista*) malloc (sizeof(NoLista));
	noLista->info = info;
	noLista->prox = NULL;
	return noLista;
}

Lista *criaLista()
{
	Lista *lista = (Lista*) malloc (sizeof(Lista));
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->cursor = NULL;
	return lista;
}

int avancaCursor(Lista *lista)
{
	if(!lista) 
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	if(!lista->cursor) return 0;
	else
	{
		lista->cursor = lista->cursor->prox;
		return 1;
	}
}

void resetaCursor(Lista *lista)
{
	if(!lista) 
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	lista->cursor = lista->inicio;
	return;
}

// Restaurar é importante pois as inserções podem desvirtuar isso.
void restauraUltimo(Lista *lista)
{
	if(!lista) 
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	NoLista *aux = lista->inicio;
	if(!aux) return;
	
	while(aux->prox)
	{
		aux = aux->prox;
	}
	lista->fim = aux;
	return;
}

void insereLista(Lista *lista, void *info)
{
	if(!lista) 
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	if(!lista->inicio)
	{
		lista->inicio = lista->fim = lista->cursor = criaNoLista(info);
	}
	else
	{
		lista->fim->prox = criaNoLista(info); 
		lista->fim = lista->fim->prox;
	}
	return;
}

NoLista *retiraNoLista(NoLista *noLista, int pos, void (*deleta)(void*), int *flag)
{
	
	if(!noLista) return noLista;
	if(pos <= 0 || !noLista->prox)
	{
		if(!noLista->prox) *flag = 1;
		NoLista *aux = noLista->prox;
		deleta(noLista->info);
		free(noLista);
		return aux;
	}
	else
	{
		noLista->prox = retiraNoLista(noLista->prox, pos-1, deleta,flag);
		return noLista;
	}
}

void retiraLista(Lista *lista, int pos, void (*deleta)(void*))
{
	if(!lista) 
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	int flag = 0;
	lista->inicio = retiraNoLista(lista->inicio,pos,deleta,&flag);
	if(flag) restauraUltimo(lista);
	resetaCursor(lista);
}

void swap(void **a, void **b)
{
	void *aux = *a;
	*a = *b;
	*b = aux;
}

NoLista *desalocaNoLista(NoLista *noLista)
{
	NoLista *aux = noLista;
	NoLista *aux2;
	while(aux)
	{
		aux2 = aux->prox;
		free(aux);
		aux = aux2;
	}
	return NULL;
}

void desalocaLista(Lista *lista, void (*funcaoExclusao)(void*))
{
	if(!lista) 
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	NoLista *aux = lista->inicio;
	NoLista *aux2;
	while(aux)
	{
		aux2 = aux->prox;
		funcaoExclusao(aux->info);
		free(aux);
		aux = aux2;
	}
	free(lista);
}

void desalocaApenasLista(Lista *lista)
{
	if(!lista)
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	NoLista *aux = lista->inicio;
	NoLista *aux2;
	while(aux)
	{
		aux2 = aux->prox;
		free(aux);
		aux = aux2;
	}
	free(lista);
}

void boubleSort(void **vector, int (*cmp)(void*,void*), int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			if(!cmp(vector[i],vector[j]))
			{
				swap(&(vector[i]),&(vector[j]));
			}
		}
	}
}

void ordenaLista(Lista *lista, int (*funcaoComparacao)(void*,void*))
{
	if(!lista)
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	int tam = tamanhoLista(lista);
	void **vector = (void **) malloc (tam * sizeof(void*));
	int i = 0;
	void *info = NULL;
	resetaCursor(lista);
	while ((info = acessaInfo(lista)))
	{
		vector[i++] = info;
		avancaCursor(lista);
	}
	resetaCursor(lista);
	i = 0;
	boubleSort(vector,funcaoComparacao,tam);
	NoLista *aux;
	for (aux = lista->inicio; aux; aux = aux->prox)
	{
		aux->info = vector[i++];
	}
	free(vector);
}

void *acessaInfo(Lista* lista)
{
	if(!lista)
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	if(!lista->cursor) return NULL;
	return lista->cursor->info;
}

void *acessaEnesimaInfo(Lista* lista, int pos)
{
	int contador = 1; // Conforme especificado, a primeira posição é 1.

	if(pos < 1) return NULL;
	resetaCursor(lista);
	while(contador != pos)
	{
		avancaCursor(lista);
		contador++;
	}
	return acessaInfo(lista);
}

void exibeLista(Lista *lista, void (*funcaoImprimir)(void *))
{
	if(!lista) 
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	void *info = NULL;
	int primeiro = 1;
	resetaCursor(lista);
	do
	{
		info = acessaInfo(lista);
		if(info)
		{
			if(primeiro) primeiro = 0;
			else printf(", ");
			funcaoImprimir(info);
		}
		avancaCursor(lista);	
	} while (info);
	resetaCursor(lista);
}

void salvaLista(Lista *lista, FILE *p, void (*funcaoImprimir)(FILE *p,void *))
{
	if(!lista)
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	void *info = NULL;
	resetaCursor(lista);
	do
	{
		info = acessaInfo(lista);
		if(info)
		funcaoImprimir(p,info);
		avancaCursor(lista);
	} while (info);
	resetaCursor(lista);
}



int tamanhoLista(Lista *lista)
{
	void *info = NULL;
	int cont = 0;
	resetaCursor(lista);
	do
	{
		info = acessaInfo(lista);
		if(info)
		{
			cont++;
		}
		avancaCursor(lista);
	} while (info);
	return cont;
}

int ultimoLista(Lista *lista)
{
	if(!lista)
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	if(!lista->inicio)
	{
		return 0;
	}
	return(!lista->cursor->prox);
}

Lista *filtraLista1(Lista *base, int(*criterio)(void*), void* (*funcaoCopia)(void*))
{
	if(!base)
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	Lista *new = criaLista();
	resetaCursor(base);
	void *info = NULL;
	while ((info = acessaInfo(base)))
	{
		if(criterio(info))
		{
			insereLista(new,funcaoCopia(info));
		}
		avancaCursor(base);
	}
	return new;
}

Lista *filtraLista2(Lista *base, int(*criterio)(void*,int), int n)
{
	if(!base)
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	Lista *new = criaLista();
	resetaCursor(base);
	void *info = NULL;
	while ((info = acessaInfo(base)))
	{
		if(criterio(info,n))
		{
			insereLista(new,info);
		}
		avancaCursor(base);
	}
	return new;
}

void *primeiraOcorrencia(Lista *base, char *str, int (*checa)(void *prog,char *str))
{
	if(!base)
	{
		printf("Lista nao inicializada. Encerrando\n");
		exit(0);
	}
	
	resetaCursor(base);
	void *info = NULL;
	while ((info = acessaInfo(base)))
	{
		if(checa(info,str))
		{
			return info;
		}
		avancaCursor(base);
	}
	return NULL;
}

int vazio(void *info)
{
	return (info == NULL);
}






