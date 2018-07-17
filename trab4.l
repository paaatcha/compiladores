%{
#include <stdio.h>
#include <string.h>

#define D_INTEIRO 1
#define D_CARACTER 2
#define D_LITERAL 3
#define D_REAL 4
#define D_BOOLEANO 5
#define D_VAZIO 6

int column = 0;
int linha = 1;

void count();

int tipo;
char id[50];

int constInt;
char constChar;
double constReal;
int constBoolean;
char constLiteral[300];

char tret[32];

%}


comentario_linha		"//"(.*)[\n]

digito			[0-9]
letra			[a-zA-Z_]
inteiro 		{digito}+
real			{digito}+.{digito}+

literal 		\"(\\.|[^\\"])*\"
caractere		'[^']'

identificador {letra}({letra}|{digito})*

%%

"/*"     {
         	int c;
			int estado = 1;
     		for(;;)
     		{
     			if(estado == 1)
 				{
 					c = input();
 					if(c == '\n') {linha++; column = 0;}
 					if(c == EOF) 
 					{
 						printf("Erro: EOF no final do bloco de comentarios\n");
 						exit(1);
 					}
 					if(c == '*') estado = 2;
 				}
 				else if(estado == 2)
 				{
 					c = input();
 					if(c == '\n') {linha++; column = 0;}
 					if(c == '*') estado = 2;
 					else if(c == '/') break;
 					else estado = 1;
 				}
 			}
 		}
 		
{comentario_linha}	; {linha++; column = 0;}/* Ignora blocos e linhas de comentarios */


chavear             { count(); return CHAVEAR;}
caso                { count(); return CASO;}
brecar              { count(); return BRECAR;}
padrão              { count(); return PADRAO;}
fazer               { count(); return FAZER;}                


fim-variáveis 		{ count(); return FIM_VARIAVEIS;}
caractere			{ count(); tipo = D_CARACTER; return CARACTERE;}
se					{ count(); return SE;}
faça				{ count(); return FACA;}
fim-para			{ count(); return FIM_PARA;}
literais			{ count(); tipo = D_LITERAL; return LITERAIS;}
algoritmo			{ count(); return ALGORITMO;}
literal				{ count(); tipo = D_LITERAL; return LITERAL;}
fim					{ count(); return FIM;}
senão				{ count(); return SENAO;}
fim-enquanto		{ count(); return FIM_ENQUANTO;}
matriz				{ count(); return MATRIZ;}
lógicos				{ count(); tipo = D_BOOLEANO; return LOGICOS;}
variáveis			{ count(); return VARIAVEIS;}
lógico				{ count(); tipo = D_BOOLEANO; return LOGICO;}
então				{ count(); return ENTAO;}
para				{ count(); return PARA;}
inteiros			{ count(); tipo = D_INTEIRO; return INTEIROS;}
função				{ count(); return FUNCAO;}
inteiro				{ count(); tipo = D_INTEIRO; return INTEIRO;}
início				{ count(); return INICIO;}
fim-se				{ count(); return FIM_SE;}
de					{ count(); return DE;}
reais				{ count(); tipo = D_REAL; return REAIS;}
retorne				{ count(); return RETORNE;}
real				{ count(); tipo = D_REAL;return REAL;}
enquanto			{ count(); return ENQUANTO;}
até					{ count(); return ATE;}
caracteres			{ count(); tipo = D_CARACTER; return CARACTERES;}
passo				{ count(); return PASSO;}
vazio				{ count(); tipo = D_VAZIO; return VAZIO;}



verdadeiro			{ count(); strcpy (tret,"booleano"); constBoolean = 1; tipo = D_BOOLEANO; return VERDADEIRO;} 
falso				{ count(); strcpy (tret,"booleano"); constBoolean = 0; tipo = D_BOOLEANO; return FALSO;} 
{inteiro}			{ count(); strcpy (tret,"inteiro"); constInt = atoi(yytext); tipo = D_INTEIRO; return CONST_INTEIRO;} 
{real}				{ count(); strcpy (tret,"real"); constReal = atof(yytext); tipo = D_REAL; return CONST_REAL;}  
{literal}			{ count(); strcpy (tret,"literal"); strcpy(constLiteral,yytext); tipo = D_LITERAL; return LITERAL;} 
{caractere}			{ count(); strcpy (tret,"caracter"); constChar = yytext[0]; tipo = D_CARACTER; return CONST_CARACTERE;} 

":="				{ count(); return ATRIB_OP;}

"-"					{ count(); return MENOS_OP;}
"+"					{ count(); return MAIS_OP;}
"*"					{ count(); return MULTI_OP;}
"/"					{ count(); return DIV_OP;}
"%"					{ count(); return MOD_OP;}

"<="				{ count(); return LE_OP;}
">="				{ count(); return GE_OP;}
"="					{ count(); return IGUAL_OP;}
"<>"				{ count(); return DIF_OP;}
"<"					{ count(); return MENOR_OP;}
">"					{ count(); return MAIOR_OP;}

"^"					{ count(); return XOR_BIT_OP;}
"~"					{ count(); return NOT_BIT_OP;}
"&"					{ count(); return AND_BIT_OP;}
"|"					{ count(); return OR_BIT_OP;}
não					{ count(); return NAO_OP;}
e					{ count(); return E_OP;}
ou					{ count(); return OU_OP;}

";"					{ count(); return PTO_E_VIRG;}
("{")	 			{ count(); return ABRE_BLOCO;}
("}")				{ count(); return FECHA_BLOCO;}
","					{ count(); return VIRGULA;} 
":"					{ count(); return DOIS_PONTOS;} 
"("					{ count(); return ABRE_PARENT;}
")"					{ count(); return FECHA_PARENT;}
("[")				{ count(); return ABRE_COLCHE;}
("]")				{ count(); return FECHA_COLCHE;}
"."					{ count(); return PONTO;}

{identificador}		{ count(); strcpy (tret,yytext); strcpy (id,yytext); return IDENT;} 

[ \t\v\n\f]			{ count(); }
.					{ /* Ignorar */ }
<<EOF>>				{return 0;}

%%

int yywrap()
{
	return(1);
}

void count()
{
	int i;
	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
		{	
			column = 0;
			linha++;
		}
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;
}
