#include "Lista.h"
#include "primos.h"


typedef struct Hash Hash;

Hash *criaHash(int tam);
void exibeHash(Hash *h, void (*funcaoImprimir)(void *));
void insereHash(Hash *h, void *info, int (*funcaoHash)(void *,int));
int getHashSize(Hash *h);
void *buscaNaHash(Hash *h, void *info, int (*funcaoComparacao)(void*,void*));
Lista *seleciona(Hash *h, int (*filter)(void*));
void desalocaHash(Hash *h,void (*funcaoExclusao)(void*));
