%{

#include <stdio.h>
#include <math.h>
#include "Hash.h"
#include "Variavel.h"
#include "Funcao.h"
#include "Lista.h"
#include <string.h>
#include "erros.h"
#include "Programa.h"
#include "Comando.h"
#include "PilhaArv.h"
#include "executar.h"
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void printCabecalho();
void opcoesMenu();
int trataExtensao (char *str);
void listarProgramasNoDiretorio();

#define D_INTEIRO 1
#define D_CARACTER 2
#define D_LITERAL 3
#define D_REAL 4
#define D_BOOLEANO 5
#define D_VAZIO 6


extern int tipo;

// Isso vai ajudar na exibicao da arvore. Na main vou inicializar com 0.
extern int id_unico;

// Variaveis auxiliares que vem do .l
extern char id[50];
extern int constInt;
extern char constChar;
extern double constReal;
extern int constBoolean;
extern char constLiteral[300];



char nomeEscopo[64];
char nomeFunc[64];
int aridade=0,N = 0;
extern char tret[32];

char carry_ret[32];
char carry_ret_func[32];
char carry_ret_old[32];
int avaliando_func = 0;


char operador_unario_corrente;


Hash *variaveis;
Hash *funcoes;
Lista *vars_ids;
Lista *tipos_args;
Lista *args_func;
Lista *programasCompilados;

PilhaArv *pArv;
Programa *programa;
MasterNode *noRaiz;
extern MasterNode *currentNode;

int filtro(void *var)
{
	Variavel *aux = (Variavel *) var;
	return !getUsadaVar(aux);
}

void exibeString(void *str)
{
	printf("%s ",(char*)str);
}

void exibeInt(void *i)
{
	printf("%d ",*(int*)i);
}

Variavel* buscaNaHashPeloNomeEEscopo(char *var,char *escopo)
{
	Variavel *v = criaVariavel();
	setNameVar(v,var);
	setEscopoVar(v,escopo);
	Variavel *aux = (Variavel *) buscaNaHash(variaveis,v,funcaoComparacaoVar);
	return aux;
}

void varJaDeclarada(char *var,char *escopo)
{
	Variavel *v = criaVariavel();
	setNameVar(v,var);
	setEscopoVar(v,escopo);
	Variavel *aux = (Variavel *) buscaNaHash(variaveis,v,funcaoComparacaoVar);

	if(aux==NULL)
	{
		erro(2);
	}
	else
	{
		setUsadaVar (aux);
	}


	int tipo = getTipoVar(aux);
	switch (tipo)
	{
		case D_INTEIRO:
			strcpy(tret,"inteiro");
		break;
		
		case D_CARACTER:
			strcpy(tret,"caracter");
		break;
		
		case D_LITERAL:
			strcpy(tret,"literal");
		break;
		
		case D_REAL:
			strcpy(tret,"real");
		break;
		
		case D_BOOLEANO:
			strcpy(tret,"booleano");
		break;
	}
	
	liberaVariavel(v);	
}

void verificaUsadas (){
	Lista *lu;
	lu = seleciona (variaveis,filtro);
	int tam = tamanhoLista (lu);

	if (tam==0){
		return;
	}else if (tam==1){	
		printf ("A variavel: ");
		exibeLista(lu,exibeString);		 
		printf(" nao foi utilizada. \n");
	}else{
		printf ("As variaveis: ");
		exibeLista(lu,exibeString);		 
		printf(" nao foram utilizadas. \n");
	}	
}

void verificaTiposAtrib (int tipo1, int tipo2)
{
	if (tipo1 != tipo2){
		erro(3);
	}	
}

void insereVar (Lista **lista, int tipo, char *escopo, int dimensao)
{

	void *info = NULL;
	char *aux = NULL;
	resetaCursor(*lista);
	while(	info = acessaInfo(*lista) )
	{
		Variavel *v = criaVariavel();
		aux = (char *) info;
		setNameVar(v,aux);
		setDimVar(v,dimensao);
		setTipoVar(v,tipo);
		setEscopoVar (v,escopo);
	
		if(buscaNaHash(variaveis,v,funcaoComparacaoVar))
		{
			erro(1);
		}
		else
		{
			insereHash(variaveis,v,funcaoHashVar);
		}
		avancaCursor(*lista);
	}
	
	desalocaLista(*lista,free);
	*lista = criaLista();
}

void insereFunc (char *nome, int tiporet, int aridade, Lista** tipos_args){
	
	//printf("Aridade setada = %d\n",aridade);
	Funcao *f = criaFunc ();
	setNameFunc (f,nome);
	setTipoRetornoFunc (f,tiporet);
	setAridadeFunc (f,aridade);
	
	if(tipos_args) // As funções primitivas	leia, escreva, maximo, minimo e media não tem tipos definidos.
	{
		setTiposArgsFunc (f,*tipos_args);
	}
	else
	{
		setTiposArgsFunc (f,NULL);
	}
	
	if(buscaNaHash(funcoes,f,funcaoComparacaoFunc))
	{
		erro(4);
	}
	else
	{
		insereHash(funcoes,f,funcaoHashFunc);
	}
	
	if(tipos_args)
	{
		desalocaApenasLista(*tipos_args);
		*tipos_args = criaLista();
	}
}

void obterTipoRetorno (char *nomeFunc, char *tiporet)
{
	Funcao *f = criaFunc();
	setNameFunc(f,nomeFunc);
	Funcao *aux = (Funcao *) buscaNaHash(funcoes,f,funcaoComparacaoFunc);
	int tipo;
	
	if (aux == NULL)
	{
		erro(5);
	}
	else
	{
		tipo = getTipoRetornoFunc(aux);

		switch (tipo)
		{
			case D_INTEIRO:
				strcpy(tiporet,"inteiro");
			break;
		
			case D_CARACTER:
				strcpy(tiporet,"caracter");
			break;
		
			case D_LITERAL:
				strcpy(tiporet,"literal");
			break;
		
			case D_REAL:
				strcpy(tiporet,"real");
			break;
		
			case D_BOOLEANO:
				strcpy(tiporet,"booleano");
			break;
			
			case D_VAZIO:
				strcpy(tiporet,"vazio");
			break;
		}
	}
}

void verificaTipoRetorno (char *nomeFunc, char *tiporet)
{
	Funcao *f = criaFunc();
	setNameFunc(f,nomeFunc);
	Funcao *aux = (Funcao *) buscaNaHash(funcoes,f,funcaoComparacaoFunc);
	int tipo;
	
	if (aux == NULL)
	{
		erro(5);
	}else{
		tipo = getTipoRetornoFunc(aux);
		
		if (!strcmp (tiporet,"inteiro")){
			if (tipo!=D_INTEIRO) erro(7);
		}else if (!strcmp (tiporet,"caracter")){
			if (tipo!=D_CARACTER) erro(7);
		}else if (!strcmp (tiporet,"literal")){
			if (tipo!=D_LITERAL) erro(7);
		}else if (!strcmp (tiporet,"real")){
			if (tipo!=D_REAL) erro(7);
		}else if (!strcmp (tiporet,"booleano")){
			if (tipo!=D_BOOLEANO) erro(7);
		}else if (!strcmp (tiporet,"vazio")){
			if (tipo!=D_VAZIO) erro(7);
		}else{
		
			int tipovar;
			Variavel *v = criaVariavel();
			setNameVar(v,tiporet);
			setEscopoVar(v,nomeFunc);
			Variavel *auxvar = (Variavel *) buscaNaHash(variaveis,v,funcaoComparacaoVar);

			if(auxvar==NULL){
				erro(2);
			}else{
				tipovar = getTipoVar(auxvar);
				if (tipo != tipovar) erro(7);							
			}		
		}		
	}
}

int filtraTipos (char *tipo, char *escopo)
{	

		if (!strcmp (tipo,"inteiro")){
			return D_INTEIRO;
		}else if (!strcmp (tipo,"caracter")){
			return D_CARACTER;
		}else if (!strcmp (tipo,"literal")){
			return D_LITERAL;
		}else if (!strcmp (tipo,"real")){
			return D_REAL;
		}else if (!strcmp (tipo,"booleano")){
			return D_BOOLEANO;
		}else if (!strcmp (tipo,"vazio")){
			return D_VAZIO;
		}else{
			int tipovar;
			Variavel *v = criaVariavel();
			setNameVar(v,tipo);
			setEscopoVar(v,escopo);
			
			Variavel *auxvar = (Variavel *) buscaNaHash(variaveis,v,funcaoComparacaoVar);				
			if(auxvar==NULL){
				erro(2);
			}else{
				tipovar = getTipoVar(auxvar);
			}
			liberaVariavel (v);			
			return tipovar;
		}
}

void verificaArgumentos (char *nomeFunc, Lista *lcha, char *escopo)
{
	Funcao *f = criaFunc();
	setNameFunc(f,nomeFunc);
	Funcao *aux = (Funcao *) buscaNaHash(funcoes,f,funcaoComparacaoFunc);
	if (aux == NULL){
		erro(5);
	}
	else
	{
		int i;
		int tipoChamadaFiltrado;
		void *info;
		char *tipoChamada;
		int *tipoDec = (int*) malloc (sizeof(int));
		int tamDec,tamChamada;
		
		// Como as funções primitivas não possuem uma Estrutura de dados completa na Hash,
		// O algoritmo abaixo falha no caso delas, portanto um ajuste em tamDec será feito.
		Lista *ldec = getTiposArgs (aux); // lista declarada
		tamDec = tamanhoLista(ldec);	
		tamChamada = tamanhoLista(lcha);
		
		if(!strcmp(nomeFunc,"leia") ||
		!strcmp(nomeFunc,"escreva") || 
		!strcmp(nomeFunc,"escreva_ln")
		)
		{
			tamDec = 1;
			return;
		}
		
		if(
		!strcmp(nomeFunc,"maximo") ||
		!strcmp(nomeFunc,"minimo") || 
		!strcmp(nomeFunc,"media") 
		)
		{
			tamDec = 2;
			return;
		}
		
		
	//	printf("tamDec = %d e tamChamada = %d\n",tamDec, tamChamada);
		if (tamDec != tamChamada) 
			erro(6);

		resetaCursor (ldec);
		resetaCursor (lcha);
		for (i=0; i<tamDec; i++)
		{
			info = acessaInfo(ldec);
			tipoDec = (int*) info;
				
			info = acessaInfo (lcha);
			tipoChamada = (char*) info;
			tipoChamadaFiltrado = filtraTipos (tipoChamada,escopo);
			
			
			if (*tipoDec != tipoChamadaFiltrado) 
				erro (8);
			
			avancaCursor(ldec);
			avancaCursor(lcha);

		}		
		desalocaLista(lcha,free);
		lcha = criaLista();		
	}
}

// Esta função encadeia todos os MasterNodes remanescentes da pilha e armazena o ponteiro
// do primeiro elemento desta nova lista, no campo "void *callFunc" da função na hash.
void dump()
{

	
	MasterNode *aux = converteParaArvore(pArv);
	
	Funcao *f = criaFunc();
	setNameFunc(f,nomeEscopo);

	Funcao *faux = (Funcao *) buscaNaHash(funcoes,f,funcaoComparacaoFunc);
	liberaFunc(f);
	
	
	setCall(faux, aux);

	//printf("Vou exibir um treco\n");
	//exibePilha(pArv);
}

void execute(MasterNode *m)
{
	//exibeMasterNode(m);
	executaArvore(m);
}

void dumpMain()
{
	/*int tamanhoPilha = stackSize(pArv);
	
	//printf("Tamanho Pilha da Main = %d\n",tamanhoPilha);
	
	int i = 0;
	
	
	for(i = 0; i < tamanhoPilha; i++)
	{
		//execute(desempilhaNode(pArv));
		//printf("\n");
	}*/
}

%}


%token FIM_VARIAVEIS
%token CARACTERE
%token SE
%token FACA
%token FIM_PARA
%token LITERAIS
%token ALGORITMO
%token LITERAL
%token FIM
%token SENAO
%token FIM_ENQUANTO
%token MATRIZ
%token LOGICOS
%token VARIAVEIS
%token LOGICO
%token ENTAO
%token PARA
%token INTEIROS
%token FUNCAO 
%token INTEIRO
%token INICIO
%token FIM_SE
%token DE
%token REAIS
%token RETORNE
%token REAL
%token ENQUANTO
%token ATE
%token CARACTERES
%token PASSO
%token VAZIO
%token VERDADEIRO
%token FALSO
%token CONST_INTEIRO
%token CONST_REAL
%token CONST_LITERAL
%token CONST_CARACTERE

// Operador de atribuição
%token ATRIB_OP

//Operadores aritiméticos
%token MENOS_OP
%token MAIS_OP
%token MULTI_OP
%token DIV_OP
%token MOD_OP

// Operadores relacionais
%token LE_OP
%token GE_OP
%token IGUAL_OP
%token DIF_OP
%token MENOR_OP
%token MAIOR_OP

// Operadores lógicos bit a bit
%token XOR_BIT_OP
%token NOT_BIT_OP
%token AND_BIT_OP
%token OR_BIT_OP

// Operador lógico normal
%token NAO_OP
%token OU_OP
%token E_OP 

%token PTO_E_VIRG
%token ABRE_BLOCO
%token FECHA_BLOCO
%token VIRGULA
%token DOIS_PONTOS
%token ABRE_PARENT
%token FECHA_PARENT
%token ABRE_COLCHE
%token FECHA_COLCHE
%token PONTO

%token IDENT


%token CHAVEAR
%token CASO
%token BRECAR
%token PADRAO
%token FAZER

%start programa
%%

programa: 
		ALGORITMO IDENT 
		{ 
			setNomeProg(programa,id); 
		} PTO_E_VIRG
		bloco_dec_func
		bloco_dec_var INICIO bloco_cmd FIM { dumpMain(); }
		;

bloco_dec_var: 
		|VARIAVEIS { strcpy(nomeEscopo,"variaveis"); } list_dec_var FIM_VARIAVEIS
		;
		
list_dec_var_locais:
					|list_dec_var 
					;		
		
list_dec_var:
			dec_var 
			| dec_var list_dec_var
			;

dec_var:
		list_ident DOIS_PONTOS tipo_dado PTO_E_VIRG 
		{
			insereVar(&vars_ids, tipo,nomeEscopo,0);
		}
		|list_ident DOIS_PONTOS MATRIZ ABRE_COLCHE CONST_INTEIRO FECHA_COLCHE DE tipo_dado_mat PTO_E_VIRG 
		{
			insereVar (&vars_ids, tipo,nomeEscopo,1);
		}
		|list_ident DOIS_PONTOS MATRIZ ABRE_COLCHE CONST_INTEIRO FECHA_COLCHE ABRE_COLCHE CONST_INTEIRO FECHA_COLCHE DE tipo_dado_mat PTO_E_VIRG 			{
			insereVar (&vars_ids, tipo,nomeEscopo,2);
		}
		;

// *******************************		

bloco_dec_func:
			|list_dec_func
			;			
			
list_dec_func:
			dec_func
			| dec_func list_dec_func		
			;		
			
dec_func:
		FUNCAO IDENT {strcpy(nomeEscopo,id); aridade=0;} ABRE_PARENT list_arg_dec_func FECHA_PARENT DOIS_PONTOS tipo_ret {insereFunc (nomeEscopo,tipo,aridade,&tipos_args);}
		list_dec_var_locais
		INICIO bloco_cmd FIM { dump(); }
		;

list_arg_dec_func:
				arg_dec_func
				|arg_dec_func VIRGULA list_arg_dec_func
				;

arg_dec_func:
			|IDENT DOIS_PONTOS tipo_dado
			{
				int *aux = (int*) malloc (sizeof(int));
				*aux = tipo;
				insereLista (tipos_args,aux);
				aridade++;
			}
			;
			
//*************************************************			

list_ident:
		  IDENT
		  { 
		  	char *aux = (char*) malloc((strlen(id)+1)*sizeof(char));
		  	strcpy(aux,id);
		  	insereLista(vars_ids,(void*) aux);
		  }
		  |IDENT
		  { 
		  	char *aux = (char*) malloc((strlen(id)+1)*sizeof(char));
		  	strcpy(aux,id);
		  	insereLista(vars_ids,(void*) aux);
		  }
		   VIRGULA list_ident 
		  ;
			

// *******************************
		
tipo_dado:
		 	INTEIRO
		 	| REAL
		 	| CARACTERE
		 	| LITERAL
		 	| LOGICO
		 	;
		 	
tipo_dado_mat:
		 	INTEIROS
		 	| REAIS
		 	| CARACTERES
		 	| LITERAIS
		 	| LOGICOS
		 	;		 	




tipo_ret:
		VAZIO
		|tipo_dado
		;		 				

//*******************************************
bloco_cmd:
		|list_cmd
		;

list_cmd:
		cmd 
		|cmd list_cmd 
		;
		
exp:
	exp_atrib
	| exp VIRGULA exp_atrib
	;

exp_atrib:       
		exp_or
		| exp_atrib {strcpy(carry_ret_old,carry_ret);} ATRIB_OP exp_or
		// 's' significa "store" pois := exigiria dois caracteres...
		{
			criaExpBinaria('s');
			
			if(avaliando_func == 0)
			{
				if(!strcmp(carry_ret_old,carry_ret))
				{
					// ok
				}
				else
				{
					erro(9);
				}
			}
			else
			{
				if(!strcmp(carry_ret_old,carry_ret_func))
				{
				
					// ok
				}
				else
				{
					erro(9);
				}
			}
			
		}
		;	
		
exp_or:
		exp_and
		| exp_or OU_OP exp_and {criaExpBinaria('o'); strcpy(carry_ret,"booleano");} // 'o' significa or
		;
		
exp_and:
		exp_igual
		| exp_and E_OP exp_igual {criaExpBinaria('a'); strcpy(carry_ret,"booleano");} // 'a' significa and
		;

exp_igual:
		exp_rel
		| exp_igual IGUAL_OP exp_rel {criaExpBinaria('='); strcpy(carry_ret,"booleano");}
		| exp_igual DIF_OP exp_rel {criaExpBinaria('d'); strcpy(carry_ret,"booleano"); } // 'd' significa diferente
		;

exp_rel:
		exp_adit
		| exp_rel MAIOR_OP exp_adit {criaExpBinaria('>'); strcpy(carry_ret,"booleano"); }
		| exp_rel MENOR_OP exp_adit {criaExpBinaria('<'); strcpy(carry_ret,"booleano"); }
		| exp_rel GE_OP exp_adit {criaExpBinaria('g'); strcpy(carry_ret,"booleano"); } // 'g' não significa greater mas sim ge
		| exp_rel LE_OP exp_adit {criaExpBinaria('l'); strcpy(carry_ret,"booleano"); } // Vide GE_OP
		;
		
exp_adit:
		exp_mult
		| exp_adit MAIS_OP exp_mult {criaExpBinaria('+');}
		| exp_adit MENOS_OP exp_mult {criaExpBinaria('-');}
		;
		
exp_mult:
		exp_un
		| exp_mult MULTI_OP exp_un {criaExpBinaria('*');}
		| exp_mult DIV_OP exp_un {criaExpBinaria('/');}
		| exp_mult MOD_OP exp_un {criaExpBinaria('%');}
		;				
		
exp_un:
		oper_unario exp_prim { criaExpUnaria(operador_unario_corrente); }
		| exp_prim
		;

oper_unario:
			MENOS_OP { operador_unario_corrente = '-'; }
			| NAO_OP { operador_unario_corrente = '!'; }
			| XOR_BIT_OP { operador_unario_corrente = '^'; }
			| AND_BIT_OP { operador_unario_corrente = '&'; }
			| OR_BIT_OP { operador_unario_corrente = '|'; }
			| NOT_BIT_OP { operador_unario_corrente = '~'; }
			; 

exp_prim:
	exp_prim_pura { avaliando_func = 0;} // Resolvido
	| func {verificaArgumentos (nomeFunc,args_func,nomeEscopo);  avaliando_func = 1;  criaExpPrimaria(nomeFunc,NULL);}
	;

exp_prim_pura:
		IDENT 
		{
			varJaDeclarada(id,nomeEscopo);
			
			strcpy(carry_ret,tret);
			Variavel *var = buscaNaHashPeloNomeEEscopo(id,nomeEscopo);
			criaExpPrimaria("ident",var);
			
		}
		
		| CONST_INTEIRO 
		{ 
			strcpy(carry_ret,tret);
			int *i = (int*) malloc (sizeof(int));
			*i = constInt;
			criaExpPrimaria("constInt",i);
		}
		
		| CONST_REAL  
		{
			strcpy(carry_ret,tret);
			double *d = (double*) malloc (sizeof(double));
			*d = constReal;
			criaExpPrimaria("constReal",d);
		}
		
		| LITERAL  
		{
			strcpy(carry_ret,tret);
			char *lit = (char*) malloc((1+strlen(constLiteral))*sizeof(char));
			strcpy(lit,constLiteral);
			criaExpPrimaria("constLiteral",lit);
		}
		
		| CONST_CARACTERE  
		{
			strcpy(carry_ret,tret);
			char *c = (char*) malloc(sizeof(char));
			*c = constChar;
			criaExpPrimaria("constChar",c);
		}
		
		| ABRE_PARENT exp FECHA_PARENT  
		{
			strcpy(carry_ret,tret);
			//  Nada a ser feito aqui, acredito eu (Thaylo) que essa regra recairá em outra que fará o 
			// trabalho necessário. Acredito fortemente nisso e não vou implementar nada aqui :s
			// E eu estava certo! hahaha :D
		}
		
		| VERDADEIRO  
		{
			strcpy(carry_ret,tret);
			int *b = (int*) malloc (sizeof(char));
			*b = constBoolean; // *b = 1; ?
			criaExpPrimaria("constBoolean",b);
		}
		
		| FALSO  
		{
			strcpy(carry_ret,tret);
			int *b = (int*) malloc (sizeof(char));
			*b = constBoolean; // *b = 0; ?
			criaExpPrimaria("constBoolean",b);
		}
		;
		
list_arg_chama_func:
					exp_prim_pura
					{
					  	char *aux = (char*) malloc((strlen(tret)+1)*sizeof(char));
					  	strcpy(aux,tret);
		  				insereLista(args_func,(void*) aux);					
					 
					}
					| exp_prim_pura VIRGULA 
					{
		  				char *aux = (char*) malloc((strlen(tret)+1)*sizeof(char));
		  				strcpy(aux,tret);
					  	insereLista(args_func,(void*) aux);						
						
						
					} list_arg_chama_func 
					;	

func:
	IDENT 
	{	
		avaliando_func = 1;
		strcpy(nomeFunc,id);  
		obterTipoRetorno (nomeFunc, carry_ret_func); 		
	} chamada_func
	;

chamada_func: 
		 ABRE_PARENT list_arg_chama_func FECHA_PARENT
		|ABRE_PARENT FECHA_PARENT
		;

cmd_ret:
		 RETORNE PTO_E_VIRG {verificaTipoRetorno (nomeEscopo,"vazio"); criaComando("cmd_ret_vazio");}	 		
		| RETORNE exp {verificaTipoRetorno (nomeEscopo,tret);} PTO_E_VIRG {criaComando("cmd_ret");}
		;
		
cmd_brec:
        BRECAR PTO_E_VIRG {criaComando("cmd_brec");}
        ;

cmd_exp:
    exp PTO_E_VIRG {criaComando("cmd_exp");}
    ;    


cmd:
	cmd_ass
	| cmd_n_ass
	
;

cmd_n_ass:
	SE exp ENTAO cmd_ass {criaComando("cmd_n_ass");}
;

cmd_se:
	SE exp ENTAO cmd_ass SENAO cmd_ass  {criaComando("cmd_se");}
;

cmd_enquanto:
    ENQUANTO exp FACA cmd_ass  {criaComando("cmd_enquanto");}
;

cmd_para:
    	PARA exp DE exp ATE exp FACA cmd_ass {criaComando("cmd_para");}
  //  |	PARA IDENT DE exp ATE exp PASSO exp FACA cmd_ass 
    
;

cmd_fazer:
        FAZER cmd ENQUANTO exp PTO_E_VIRG {criaComando("cmd_fazer");}
    ;

cmd_chavear:
    CHAVEAR IDENT {varJaDeclarada(id,nomeEscopo); } ABRE_BLOCO
        lista_casos_chavear
        caso_padrao
    FECHA_BLOCO {criaComando("cmd_chavear");} // Criei o comando apenas para não bugar a pilha.
    ;
  
lista_casos_chavear:
    caso_chavear
    | caso_chavear lista_casos_chavear
;
  
caso_chavear:
    CASO exp_prim DOIS_PONTOS
        bloco_cmd
;

caso_padrao:
    PADRAO DOIS_PONTOS
        bloco_cmd
;

cmd_ass:
		ABRE_BLOCO bloco_cmd FECHA_BLOCO 
	|	cmd_se	
	|	cmd_exp
	|   cmd_ret
	|   cmd_enquanto
	|   cmd_para 
	|   cmd_chavear
	|   cmd_brec
	|   cmd_fazer
;

%%

#include "lex.yy.c"
#include <unistd.h>

void desalocaListasAuxiliares()
{
    desalocaApenasLista(tipos_args);
    desalocaApenasLista(args_func);
	desalocaHash(funcoes,liberaFunc);
	desalocaHash(variaveis,liberaVariavel);
}

void compila(Programa *p)
{
	
	programa = p;
	vars_ids = criaLista();  // lista para armazenar identificadores em declarações multiplas
	tipos_args = criaLista(); // lista para armazenar argumentos de função na declaração
	args_func = criaLista(); // lista para armazenar argumentos de função na chamada
	
	
	
	
	variaveis = getHashVarsProg(p);
	funcoes = getHashFuncsProg(p);
	
	
	// Criando primitivas
	Lista *temp = criaLista(); // Esta lista é "falsa", apenas para as funções se comportarem bem.
	insereFunc ("escreva",6,1,&temp); // 6 == Vazio // Estou declarando a primitiva
	insereFunc ("escreva_ln",6,1,&temp); // 6 == Vazio // Estou declarando a primitiva
	insereFunc ("leia",6,1,&temp); // 6 == Vazio // Estou declarando a primitiva
	
	insereFunc ("maximo",D_REAL,2,&temp); // Estou declarando a primitiva
	insereFunc ("minimo",D_REAL,2,&temp); // Estou declarando a primitiva
	insereFunc ("media",D_REAL,2,&temp); // Estou declarando a primitiva
	
	
	desalocaApenasLista(temp);
		
	vars_ids = criaLista();  // lista para armazenar identificadores em declarações multiplas
	tipos_args = criaLista(); // lista para armazenar argumentos de função na declaração
	args_func = criaLista(); // lista para armazenar argumentos de função na chamada
	
    yyparse(); // Aqui a mágica acontece!!!
	
	
    verificaUsadas ();
   
    MasterNode *main = converteParaArvore(pArv); // Pronto, esse cara é que deve ser executado!   	
	setArvoreExecucao(programa,main);
    	
    setProgamaCompilado(p);
    
    desalocaListasAuxiliares();
    
}

void executaPrograma(Programa *p)
{
	executaArvore(getArvoreExecucao(p));
}

void imprimeArvoreExecPrograma(Programa *p)
{
    imprime_arvore(getArvoreExecucao(p),0);
}

void pegaNomeDoArquivo (char *nome)
{
	printf ("Digite o nome do arquivo:\n",nome);
	scanf("%s",nome);
}


void printCabecalho() {
	printf("### Compilador Humildade++ ###\nObs.: Seja coerente ao nomear arquivos .gpt e algoritmos.\n");
}

void opcoesMenu() {
	char aux[30];
	int opcao;
	char nome[256];
		
	while(1) {
		printCabecalho();
		printf("Escolha uma opcao abaixo:\n");
		printf("[1] Compilar programa\n");
		printf("[2] Executar programa\n");
		printf("[3] Listar programas nao compilados no diretório corrente\n");
		printf("[4] Listar programas compilados\n");
		printf("[5] Imprimir árvore de execução\n");
		printf("[6] Sair\n");
	
		do {
			printf("\nDigite sua opcao:\nH++> ");
			scanf("%s",aux);
			aux[1] = '\0';
			opcao = atoi(aux);
		
			if(opcao < 1 || opcao > 6)
				printf("Opcao desconhecida!\n");
				
		} while(opcao < 1 || opcao > 6);
	
		switch(opcao) {
			case 1:
			{
				// Compilar
				pegaNomeDoArquivo(nome);
				
				if(!trataExtensao(nome)) // Se o cara não colocar .gpt no final do nome, eu adiciono
				{
					strcat(nome,".gpt");
				}

				char nomeAux[30]; // Tirando o .gpt do nome para evitar problemas.
				strcpy(nomeAux,nome);
				int i = 0;
				while(i < strlen(nome))
				{
					if(nomeAux[i] == '.')
						nomeAux[i] = '\0';
					i++;
				}
				
				Programa *px = (Programa*) primeiraOcorrencia(programasCompilados,nomeAux,checaNome);
				if(px)
				{
					printf("\n\n\nO arquivo %s já foi compilado!\n",nome);
					break; // O programa já foi compilado!!!
				}
				// Se cheguei até aqui, significa que tudo está ok.
				Programa *p = criaPrograma(nomeAux);
				insereLista(programasCompilados,p);

				FILE *f = fopen(nome, "r");
				if(!f) 
				{
					printf("Arquivo %s nao encontrado!!!\n\n\n",nome);
					break;
				}
				yyin = f;
				compila(p);		// compilo!!!
				YY_FLUSH_BUFFER;
				fclose(f);
				printf("\nPrograma compilado, pressione ENTER para voltar para o menu anterior...");
				getchar(); getchar();					
				break;
			}
			case 2:
			{
				pegaNomeDoArquivo(nome);

				char nomeAux[30]; // Tirando o .gpt do nome para evitar problemas.
				strcpy(nomeAux,nome);
				int i = 0;
				while(i < strlen(nome))
				{
					if(nomeAux[i] == '.')
						nomeAux[i] = '\0';
					i++;
				}
				
				Programa *p = (Programa*) primeiraOcorrencia(programasCompilados,nomeAux,checaNome);
				if(!p) 
				{
					printf("O programa %s ainda nao foi compilado, digite [1] no menu principal\n\n\n",nome);
					break;
				}
				printf("\n");
				executaPrograma(p);
				printf("\n");
				printf("\nPressione ENTER para voltar para o menu anterior...");
				getchar(); getchar();					
				break;
			}
			case 3:
				listarProgramasNoDiretorio();
				printf("Pressione ENTER para voltar ao MENU\n");
				break;
		
			case 4:
			{
				//listarProgramasCompilados ();
				printf("Programas Compilados:\n");
				exibeLista(programasCompilados,exibePrograma);
				printf("\nPressione ENTER para voltar para o menu anterior...");
				getchar(); getchar();				
			}
			break;
				
			case 5:
			{
				printf("\n");				
				pegaNomeDoArquivo(nome);
				
				char nomeAux[30]; // Tirando o .gpt do nome para evitar problemas.
				strcpy(nomeAux,nome);
				int i = 0;
				while(i < strlen(nome))
				{
					if(nomeAux[i] == '.')
						nomeAux[i] = '\0';
					i++;
				}
				
				
				Programa *p = (Programa*) primeiraOcorrencia(programasCompilados,nomeAux,checaNome);
				if(p)
				{
					imprimeArvoreExecPrograma(p);
				}
				else
				{
					printf("O programa %s ainda nao foi compilado, digite [1] no menu principal\n\n\n",nome);
				}
				
				printf("\nPressione ENTER para voltar para o menu anterior...");
				getchar(); getchar();
				break;				
			}
			case 6:
				printf("Humildade++ se despedindo...bye\n");
				exit(0);
		}
	}
}


int trataExtensao (char *str){
	char aux[5];
	strcpy(aux,".gpt");
	int tam = strlen(str);
	return !strcmp(aux,&(str[tam-4]));        
}

void listarProgramasNoDiretorio (Lista *progComp){
	char diretorio[1500];	
	getcwd(diretorio,1500);
	DIR *d = opendir(diretorio);
	struct dirent *entrada;

	printf ("\n### Lista de programas que ainda podem ser compilados ###\n");
	while((entrada = readdir(d)) != NULL) {
		if(entrada->d_type == DT_REG && trataExtensao (entrada->d_name)){
			// agora so tem que tratar se a função ja foi compilada
			
			char nomeAux[30]; // Tirando o .gpt do nome para evitar problemas.
			strcpy(nomeAux,entrada->d_name);
			int i = 0;
			
			strcpy(nomeAux,entrada->d_name);
			while(i < strlen(entrada->d_name))
			{
				if(nomeAux[i] == '.')
					nomeAux[i] = '\0';
				i++;
			}
			
			Programa *p = (Programa*) primeiraOcorrencia(programasCompilados,nomeAux,checaNome);
			
			if(!p)
			{
				printf ("- %s\n",entrada->d_name);			
			}
		}
	}
	getchar(); getchar();
	closedir(d);
}

int main()
{
	system("clear");
	pArv = criaPilhaArv(); // Auxiliar, será usada por todos. Mas a cada fim de compilação ficará vazia.
	programasCompilados = criaLista();
	
	opcoesMenu(); // Aqui o menu é chamado :D



    
   
	
    return 0;
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (char *s){
       printf("Erro detectado ao avaliar a linha %d, coluna %d\n",linha,column);
       exit(0);
}
