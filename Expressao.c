#include "Expressao.h"

#include "PilhaArv.h"
#include "Hash.h"
#include "Funcao.h"


extern PilhaArv *pArv;
extern Hash *variaveis;
extern Hash *funcoes;



void criaExpPrimaria(char *tipo, void* data)
{
	int aux = 0;
	
	if(!strcmp(tipo,"ident")) // Se encontrei um identificador, posso empilhar.
	{
		MasterNode *m = criaNode("exp","var");
		
		setLoadedVar(m,data);
		setDataType(m,dataTypeVariable);
		
		empilhaNode(pArv,m);
	}
	else if(!strcmp(tipo,"constInt")) // Se encontrei uma constante inteira, posso empilhar tb.
	{
		MasterNode *m = criaNode("exp","int");
		setData(m,data);
		setDataType(m,dataTypeInteger);
		empilhaNode(pArv,m);
	}
	else if(!strcmp(tipo,"constReal"))
	{
		MasterNode *m = criaNode("exp","real");
		setData(m,data);
		setDataType(m,dataTypeReal);
		empilhaNode(pArv,m);
	}
	else if(!strcmp(tipo,"constLiteral"))
	{
		MasterNode *m = criaNode("exp","literal");
		setData(m,data);
		setDataType(m,dataTypeLiteral);
		empilhaNode(pArv,m);
	}
	else if(!strcmp(tipo,"constChar"))
	{
		MasterNode *m = criaNode("exp","char");
		setData(m,data);
		setDataType(m,dataTypeChar);
		empilhaNode(pArv,m);
	}
	else if(!strcmp(tipo,"constBoolean"))
	{
		MasterNode *m = criaNode("exp","bool");
		setData(m,data);
		setDataType(m,dataTypeBoolean);
		empilhaNode(pArv,m);
	}
	else
	{
		MasterNode *m = criaNode("call",tipo);
		
		
		if(!strcmp("escreva",tipo) || !strcmp("escreva_ln",tipo) || !strcmp("leia",tipo))  // Primitiva unária
		{
			insereNode(m,desempilhaNode(pArv),'e') ;
			empilhaNode(pArv,m);
			return;
		}				
		
		if(!strcmp("maximo",tipo) || !strcmp("minimo",tipo) || !strcmp("media",tipo))  // Primitiva binária
		{
			insereNode(m,desempilhaNode(pArv),'m') ;
			insereNode(m,desempilhaNode(pArv),'e') ;
			empilhaNode(pArv,m);
			return;
		}	
		
		
		int aridade;
		
		Funcao *f = criaFunc();
		setNameFunc(f,tipo);
		Funcao *faux = (Funcao *) buscaNaHash(funcoes,f,funcaoComparacaoFunc);
		liberaFunc(f);

		aridade = getAridadeFunc(faux);
		MasterNode *aux[aridade];
		
			
		if(aridade <= 0)
		{
			empilhaNode(pArv,m);
		}
		else
		{
			// TODO Passar os parâmetros de função!!! mas já não foi passado no todo abaixo?
			int i;
			for(i = 0; i < aridade; i++)
			{
				aux[i] = desempilhaNode(pArv);
			}
	
			PilhaArv *paux = criaPilhaArv();
			preenchePilha(paux, aux,aridade);
			MasterNode *mAux = converteParaArvore(paux);
	
			insereNode(m,mAux,'e'); // TODO já passei!!!
	
			empilhaNode(pArv,m);
		}
		
	}
			
}

void criaExpUnaria(char op)
{
	char op_str[2];
	op_str[0] = op;
	op_str[1] = '\0';
	MasterNode *m = criaNode("exp",op_str);
	insereNode(m,desempilhaNode(pArv),'e'); // Capturei a expressão primária previamente empilhada.
	empilhaNode(pArv,m);
}

void criaExpBinaria(char op)
{
	char op_str[2];
	op_str[0] = op;
	op_str[1] = '\0';
	MasterNode *m = criaNode("exp",op_str);
	insereNode(m,desempilhaNode(pArv),'m'); // Capturei a primeira expressão.
	insereNode(m,desempilhaNode(pArv),'e'); // Capturei a segunda expressão.
	empilhaNode(pArv,m); // Empilhei a expressão multiplicativa.
}













