#include "Hash.h"

struct Hash
{
	Lista **data;
	int size;
};

Hash *criaHash(int tam)
{
	tam = gera_primo_maior_que(tam);
	Hash *h = (Hash*) malloc (sizeof(Hash));
	h->size = tam;
	h->data = (Lista**) malloc(tam*sizeof(Lista*));
	int i;
	for(i = 0; i < tam; i++)
	{
		h->data[i] = criaLista();
	}
	return h;
}

void exibeHash(Hash *h, void (*funcaoImprimir)(void *))
{
	int i;
	printf("|||Exibindo Hash de tamanho %d|||\n",getHashSize(h));
	for(i = 0; i < h->size; i++)
	{
		if(tamanhoLista(h->data[i]) >= 1)
		{
			printf("[ ");
			exibeLista(h->data[i],funcaoImprimir);
			printf(" ]\n");
		}
		else
		{
			printf("[]\n");
		}
	}
	printf("|||Fim da Hash|||\n");
}

void insereHash(Hash *h, void *info, int (*funcaoHash)(void *,int))
{
	insereLista(h->data[funcaoHash(info,h->size)],info);
}

int getHashSize(Hash *h)
{
	return h->size;
}

void *buscaNaHash(Hash *h, void *info, int (*funcaoComparacao)(void*,void*))
{
	int i,j;
	int tam;
	for(i = 0; i < h->size; i++)
	{
		tam = tamanhoLista(h->data[i]);
		for(j = 1; j <= tam; j++)
		{
			//printf("i,j = %d,%d\n",i,j);
			if(funcaoComparacao(info,acessaEnesimaInfo(h->data[i],j)) == 1)
			{
				return acessaEnesimaInfo(h->data[i],j);
			}
		}
	}
	return NULL;
}

Lista *seleciona(Hash *h, int (*filter)(void*))
{
	Lista *l = criaLista();
	int i,j;
	int tam;
	for(i = 0; i < h->size; i++)
	{
		tam = tamanhoLista(h->data[i]);
		for(j = 1; j <= tam; j++)
		{
			void *aux = acessaEnesimaInfo(h->data[i],j);
			if(filter(aux))
			{
				insereLista(l,aux);
			}
		}
	}
	return l;
}

void desalocaHash(Hash *h,void (*funcaoExclusao)(void*))
{
	int i;
	for (i = 0; i < h->size; i++)
	{
		desalocaLista(h->data[i],funcaoExclusao);
	}
}





















