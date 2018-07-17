#include "Comando.h"
#include "PilhaArv.h"

#define cmd_n_ass 0
#define cmd_se 1
#define cmd_exp 2
#define cmd_ret 3
#define cmd_ret_vazio 9
#define cmd_enquanto 4
#define cmd_para 5
#define cmd_chavear 6
#define cmd_brec 7
#define cmd_fazer 8

#define caso_chavear 10
#define caso_chavear_padrao 11

extern PilhaArv *pArv;

void criaComando(char *cmdstr)
{
	//printf("Comando %s detectado\n",cmdstr);
	int cmd;
	if(!strcmp(cmdstr,"cmd_n_ass")) cmd = 0;
	else if (!strcmp(cmdstr,"cmd_se")) cmd = 1;
	else if (!strcmp(cmdstr,"cmd_exp")) cmd = 2;
	else if (!strcmp(cmdstr,"cmd_ret")) cmd = 3;
	else if (!strcmp(cmdstr,"cmd_enquanto")) cmd = 4;
	else if (!strcmp(cmdstr,"cmd_para")) cmd = 5;
	else if (!strcmp(cmdstr,"cmd_chavear")) cmd = 6;
	else if (!strcmp(cmdstr,"cmd_brec")) cmd = 7;
	else if (!strcmp(cmdstr,"cmd_fazer")) cmd = 8;
	else if (!strcmp(cmdstr,"cmd_ret_vazio")) cmd = 9;
	else if (!strcmp(cmdstr,"caso_chavear")) cmd = 10;
	else if (!strcmp(cmdstr,"caso_chavear_padrao")) cmd = 11;
	
	
	else {printf("Comando invalido\n"); exit(0);}

	switch (cmd)
	{
		case cmd_n_ass: // Ok mas não testado
		{
			MasterNode *m = criaNode("cmd", "n_ass");

			insereNode(m,desempilhaNode(pArv),'m'); // Ao desempilhar, inverte-se a ordem :P
			insereNode(m,desempilhaNode(pArv),'e');
			empilhaNode(pArv,m);
			
			break;
		}
		
		case cmd_se: // Ok mas não testado
		{
			
			MasterNode *m = criaNode("cmd", "se");
			
			insereNode(m,desempilhaNode(pArv),'d');	// ELSE
			insereNode(m,desempilhaNode(pArv),'m'); // THEN
			insereNode(m,desempilhaNode(pArv),'e'); // EXP
			empilhaNode(pArv,m);
			
			break;
		}
		
		
		case cmd_exp:        // Ok mas não testado          
		{
			MasterNode *m = criaNode("cmd", "exp");
			
			/* Aqui pego a arvore de expressões que serão AVALIADAS futuramente */
			insereNode(m,desempilhaNode(pArv),'e'); 
			empilhaNode(pArv,m);
			
			break;
		}
		
		case cmd_ret:
		{
			MasterNode *m = criaNode("cmd", "ret");
			insereNode(m,desempilhaNode(pArv),'e'); // Retornarei uma expressão AVALIÁVEL
			empilhaNode(pArv,m);
			
			break;
		}

		case cmd_ret_vazio:
		{
			MasterNode *m = criaNode("cmd", "ret"); // Aqui os das folhas ficarão nulos.
			empilhaNode(pArv,m);
			
			break;
		}		
		
		
		case cmd_enquanto: // ENQUANTO exp FACA cmd_ass { vocêestáaqui(); }
		{
			// Note que cmd_ass pode ser várias coisas, e todas elas já se empilharam!
			// Portanto pode-se tranquilamente pegar dois nós da pilha.
			
			MasterNode *m = criaNode("cmd", "enquanto");
			insereNode(m,desempilhaNode(pArv),'m'); // Peguei a expressão
			insereNode(m,desempilhaNode(pArv),'e'); // Peguei um comando qualquer.
			empilhaNode(pArv,m);
			break;

		}
		
		case cmd_para: // PARA IDENT DE exp ATE exp FACA cmd_ass  { vocêestáaqui(); }
		{
			MasterNode *m = criaNode("cmd", "para");
			insereNode(m,desempilhaNode(pArv),'d'); // Peguei um comando associado qualquer.
			insereNode(m,desempilhaNode(pArv),'m'); // Peguei a expressão de limite
			insereNode(m,desempilhaNode(pArv),'e'); // Peguei a expressão de inicio
			insereNode(m,desempilhaNode(pArv),'i'); // Peguei o iterador
			
			//setData(m, desempilhaNode(pArv)); // Pequei "exp ident" que é um inteiro eu espero.
			setDataType(m,dataTypeMasterNode); // Avisando ao comando que o dado é um masternode!!!
			
			
			
			empilhaNode(pArv,m);
			break;
		}
		
		case cmd_chavear: // Chavear ta meio complexo pra fazer na estrutura MasterNode atual...
						  // Só vou empilhar pra não bugar a lógica da pilha...
		{
			MasterNode *m = criaNode("cmd", "chavear");
			
			empilhaNode(pArv,m);
			
			break;
		}
		
		case cmd_brec: // Ok mas não testado.
		{
			MasterNode *m = criaNode("cmd", "brec");
			empilhaNode(pArv,m);
			
			
			break;
		}
		
		case cmd_fazer: // FAZER cmd ENQUANTO exp PTO_E_VIRG { vocêestáaqui(); } Ok mas sem teste
		{
			MasterNode *m = criaNode("cmd", "fazer");
			insereNode(m,desempilhaNode(pArv),'m'); // Peguei um comando
			insereNode(m,desempilhaNode(pArv),'e'); // Peguei a expressão de controle
			empilhaNode(pArv,m);
			
			break;
		}
		
		default:
		{
			printf("Tu ta fazendo merda neste trab4...\n");
			exit(0);
		}
	}
}

