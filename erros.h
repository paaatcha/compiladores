#include <stdio.h>
#include <stdlib.h>

extern int linha;

void erro(int codigo)
{
	printf("Erro semantico na linha %d.", linha);
	switch(codigo)
	{
		case 1:
		{
			printf(" Variavel redeclarada.\n");
			break;
		}
		case 2:
		{
			printf(" variavel nao declarada.\n");
			break;
		}
		case 3:
		{
			printf (" Atribuição inválida.\n");
			break;
		}
		case 4:
		{
			printf (" Funcao redeclarada.\n");
			break;
		}
		case 5:
		{
			printf (" Funcao nao declarada.\n");
			break;
		}
		case 6:
		{
			printf (" Aridade nao correspondente.\n");
			break;
		}
		case 7:
		{
			printf (" Tipo de retorno da funcao incompativel.\n");
			break;
		}	
		case 8:
		{	
			printf (" Argumento de funcao incompativel.\n");
			break;
		}
		case 9:
		{
			printf(" Atribuicao de tipos incompativeis.\n");
			break;
		}
	}
	
	exit(0);
}
