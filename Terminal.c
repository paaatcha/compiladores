#include "Terminal.h"

#include "PilhaArv.h"
extern PilhaArv *pArv;

void criaTerminal(char *tipo)
{
	int aux = 0;
	
	if(!strcmp(tipo,"var"))
	{
		MasterNode *m = criaNode("term","var");
			
	}
	else if(!strcmp(tipo,"const"))
	{
		MasterNode *m = criaNode("term","const");
				
	}
}
