#include "executar.h"

#define INTEIRO 1
#define CARACTER 2
#define LITERAL 3
#define REAL 4
#define BOOLEANO 5
#define VAZIO 6




Variavel* executaArvore(MasterNode *m)
{
	if(!m) return NULL;
	
	//printf("Executando %s|%s\n",getStringMasterNode(m,0),getStringMasterNode(m,1));
	
	if(!strcmp(getStringMasterNode(m,0),"exp"))
	{
		if	(!strcmp(getStringMasterNode(m,1),"var"))
		{
			return getLoadedVar(m);
		}
		else if(!strcmp(getStringMasterNode(m,1),"int"))
		{
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, INTEIRO);
			setEscopoVar (temp, "temp");
			
			setDataVar(temp, getData(m));
			
			return temp;
		}
		else if(!strcmp(getStringMasterNode(m,1),"literal"))
		{
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, LITERAL);
			setEscopoVar (temp, "temp");
			
			setDataVar(temp, getData(m));
			return temp;
		}
		else if(!strcmp(getStringMasterNode(m,1),"real"))
		{
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, REAL);
			setEscopoVar (temp, "temp");
			setDataVar(temp, getData(m));
			return temp;
		}
		else if (!strcmp(getStringMasterNode(m,1),"bool"))
		{
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, BOOLEANO);
			setEscopoVar (temp, "temp");
			setDataVar(temp, getData(m));
			return temp;
		}
		
		
		
		
		else if(!strcmp(getStringMasterNode(m,1),"+"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			if(getTipoVar(temp1) == INTEIRO)
			{
				*(int*)data1 += *(int*)data2;
			}
			else if(getTipoVar(temp1) == REAL)
			{
				*(double*)data1 += *(double*)data2;
			}
			else if(getTipoVar(temp1) == LITERAL)
			{
				strcat((char*)data1,(char*)data2);
			}
			else if(getTipoVar(temp1) == BOOLEANO)
			{
				*(int*)data1 += *(int*)data2;
			}
			else
			{
				// TODO chamar erro
			}
			//liberaVariavel((void*)temp2);
			return temp1;
		}
		
		
		
		else if(!strcmp(getStringMasterNode(m,1),"-"))
		{
			if(getFolha(m,'m'))
			{
				Variavel *temp1 = executaArvore(getFolha(m,'e'));
				Variavel *temp2 = executaArvore(getFolha(m,'m'));
			
				void *data1 = getDataVar(temp1);
				void *data2 = getDataVar(temp2);
	
				if(getTipoVar(temp1) == INTEIRO)
				{
					*(int*)data1 -= *(int*)data2;
				}
				else if(getTipoVar(temp1) == REAL)
				{
					*(double*)data1 -= *(double*)data2;
				}
				else
				{
					// TODO chamar erro
				}
				//liberaVariavel((void*)temp2);
				return temp1;
			}
			else
			{
				Variavel *temp1 = executaArvore(getFolha(m,'e'));
			
				void *data1 = getDataVar(temp1);
	
				if(getTipoVar(temp1) == INTEIRO)
				{
					*(int*)data1 *= -1;
				}
				else if(getTipoVar(temp1) == REAL)
				{
					*(double*)data1 *= -1;
				}
				else
				{
					// TODO chamar erro
				}
				return temp1;
			}
		}
		
		else if(!strcmp(getStringMasterNode(m,1),"*"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			if(getTipoVar(temp1) == INTEIRO)
			{
				*(int*)data1 *= *(int*)data2;
			}
			else if(getTipoVar(temp1) == REAL)
			{
				*(double*)data1 *= *(double*)data2;
			}
			else
			{
				// TODO chamar erro
			}
			//liberaVariavel((void*)temp2);
			return temp1;
		}
		
		
		else if(!strcmp(getStringMasterNode(m,1),"/"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			if(getTipoVar(temp1) == INTEIRO)
			{
				*(int*)data1 /= *(int*)data2;
			}
			else if(getTipoVar(temp1) == REAL)
			{
				*(double*)data1 /= *(double*)data2;
			}
			else
			{
				// TODO chamar erro
			}
			
			//liberaVariavel((void*)temp2);
			return temp1;
		}
		
		else if(!strcmp(getStringMasterNode(m,1),"%"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			if(getTipoVar(temp1) == INTEIRO)
			{
				*(int*)data1 = *(int*)data1 % ( *(int*)data2 );
			}
			else
			{
				// TODO chamar erro
			}
			//liberaVariavel((void*)temp2);
			return temp1;
		}
		
		else if(!strcmp(getStringMasterNode(m,1),"s"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
				
			if(getTipoVar(temp1) == INTEIRO)
			{
				*(int*)data1 = *(int*)data2;
			}
			else if(getTipoVar(temp1) == REAL)
			{
				*(double*)data1 = *(double*)data2;
			}
			else if(getTipoVar(temp1) == LITERAL)
			{
				strcpy((char*)data1,(char*)data2);
			}
			else if(getTipoVar(temp1) == BOOLEANO)
			{
				*(int*)data1 = *(int*)data2;
			}
			
			
			//liberaVariavel((void*)temp2);
			return temp1;
		}
		
				
		else if(!strcmp(getStringMasterNode(m,1),"!"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			void *data1 = getDataVar(temp1);
	
			if(getTipoVar(temp1) == INTEIRO)
			{	
				
				*(int*)data1 = !*(int*)data1;
			}
			else if(getTipoVar(temp1) == BOOLEANO)
			{
				*(int*)data1 = !*(int*)data1;
			}

			return temp1;
		}
		
		
		else if(!strcmp(getStringMasterNode(m,1),"="))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, BOOLEANO);
			setEscopoVar (temp, "temp");
			int *aux = (int*) malloc (sizeof(int));
			setDataVar(temp, aux);
			
			int avaliacao;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				avaliacao = (*(int*)data1 == *(int*)data2);
			}
			else if(getTipoVar(temp1) == REAL)
			{
				avaliacao = (*(double*)data1 == *(double*)data2);
			}
			else if(getTipoVar(temp1) == LITERAL)
			{
				avaliacao = !strcmp((char*)data1,(char*)data2);
			}
			else if(getTipoVar(temp1) == BOOLEANO)
			{
				avaliacao = (*(int*)data1 == *(int*)data2);
			}
			else
			{
				// TODO chamar erro
			}
			*aux = avaliacao;
			//liberaVariavel((void*)temp1);
			//liberaVariavel((void*)temp2);
			return temp;
		}
		
		
		else if(!strcmp(getStringMasterNode(m,1),"d"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, BOOLEANO);
			setEscopoVar (temp, "temp");
			int *aux = (int*) malloc (sizeof(int));
			setDataVar(temp, aux);
			
			int avaliacao;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				avaliacao = (*(int*)data1 == *(int*)data2);
			}
			else if(getTipoVar(temp1) == REAL)
			{
				avaliacao = (*(double*)data1 == *(double*)data2);
			}
			else if(getTipoVar(temp1) == LITERAL)
			{
				avaliacao = !strcmp((char*)data1,(char*)data2);
			}
			else if(getTipoVar(temp1) == BOOLEANO)
			{
				avaliacao = (*(int*)data1 == *(int*)data2);
			}
			else
			{
				// TODO chamar erro
			}
			*aux = !avaliacao;
			//liberaVariavel((void*)temp1);
			//liberaVariavel((void*)temp2);
			return temp;
		}
		
		
		else if(!strcmp(getStringMasterNode(m,1),"<"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, BOOLEANO);
			setEscopoVar (temp, "temp");
			int *aux = (int*) malloc (sizeof(int));
			setDataVar(temp, aux);
			
			int avaliacao;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				avaliacao = (*(int*)data1 < *(int*)data2);
			}
			else if(getTipoVar(temp1) == REAL)
			{
				avaliacao = (*(double*)data1 < *(double*)data2);
			}
			else
			{
				// TODO chamar erro
			}
			*aux = avaliacao;
		//	liberaVariavel((void*)temp1);
		//	liberaVariavel((void*)temp2);
			return temp;
		}
		
		else if(!strcmp(getStringMasterNode(m,1),">"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, BOOLEANO);
			setEscopoVar (temp, "temp");
			int *aux = (int*) malloc (sizeof(int));
			setDataVar(temp, aux);
			
			int avaliacao;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				avaliacao = (*(int*)data1 > *(int*)data2);
			}
			else if(getTipoVar(temp1) == REAL)
			{
				avaliacao = (*(double*)data1 > *(double*)data2);
			}
			else
			{
				// TODO chamar erro
			}
			*aux = avaliacao;
		//	liberaVariavel((void*)temp1);
		//	liberaVariavel((void*)temp2);
			return temp;
		}		
		
		else if(!strcmp(getStringMasterNode(m,1),"g"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, BOOLEANO);
			setEscopoVar (temp, "temp");
			int *aux = (int*) malloc (sizeof(int));
			setDataVar(temp, aux);
			
			int avaliacao;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				avaliacao = (*(int*)data1 >= *(int*)data2);
			}
			else if(getTipoVar(temp1) == REAL)
			{
				avaliacao = (*(double*)data1 >= *(double*)data2);
			}
			else
			{
				// TODO chamar erro
			}
			*aux = avaliacao;
		//	liberaVariavel((void*)temp1);
		//	liberaVariavel((void*)temp2);
			return temp;
		}		



		else if(!strcmp(getStringMasterNode(m,1),"l"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, BOOLEANO);
			setEscopoVar (temp, "temp");
			int *aux = (int*) malloc (sizeof(int));
			setDataVar(temp, aux);
			
			int avaliacao;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				avaliacao = (*(int*)data1 <= *(int*)data2);
			}
			else if(getTipoVar(temp1) == REAL)
			{
				avaliacao = (*(double*)data1 <= *(double*)data2);
			}
			else
			{
				// TODO chamar erro
			}
			*aux = avaliacao;
		//	liberaVariavel((void*)temp1);
		//	liberaVariavel((void*)temp2);
			return temp;
		}	
	
	
		else if(!strcmp(getStringMasterNode(m,1),"a"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, BOOLEANO);
			setEscopoVar (temp, "temp");
			int *aux = (int*) malloc (sizeof(int));
			setDataVar(temp, aux);
			
			int avaliacao;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				avaliacao = (*(int*)data1 && *(int*)data2);
			}
			else if(getTipoVar(temp1) == BOOLEANO)
			{
				avaliacao = (*(int*)data1 && *(int*)data2);
			}
			else
			{
				// TODO chamar erro
			}
			*aux = avaliacao;
		//	liberaVariavel((void*)temp1);
		//	liberaVariavel((void*)temp2);
			return temp;
		}	
	
		else if(!strcmp(getStringMasterNode(m,1),"o"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			void *data1 = getDataVar(temp1);
			void *data2 = getDataVar(temp2);
	
			Variavel *temp = criaVariavel();
			setNameVar(temp,"temp");
			setDimVar(temp,0);
			setTipoVar(temp, BOOLEANO);
			setEscopoVar (temp, "temp");
			int *aux = (int*) malloc (sizeof(int));
			setDataVar(temp, aux);
			
			int avaliacao;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				avaliacao = (*(int*)data1 || *(int*)data2);
			}
			else if(getTipoVar(temp1) == BOOLEANO)
			{
				avaliacao = (*(int*)data1 || *(int*)data2);
			}
			else
			{
				// TODO chamar erro
			}
			*aux = avaliacao;
		//	liberaVariavel((void*)temp1);
		//	liberaVariavel((void*)temp2);
			return temp;
		}	
		
	}
	else if(!strcmp(getStringMasterNode(m,0),"cmd"))
	{
		if (!strcmp(getStringMasterNode(m,1),"n_ass"))
		{
			Variavel *var = executaArvore(getFolha(m,'e'));
			if(!isNullorFalse(var)){
				executaArvore(getFolha(m,'m'));
			}
		}
		
		else if (!strcmp(getStringMasterNode(m,1),"se"))
		{
			Variavel *var = executaArvore(getFolha(m,'e'));
			if(!isNullorFalse(var)){
				executaArvore(getFolha(m,'m'));
			}
			else{
				executaArvore(getFolha(m,'d'));
			}
		}
		
		else if (!strcmp(getStringMasterNode(m,1),"exp"))
		{
			executaArvore(getFolha(m,'e'));
		}
		
		
		else if (!strcmp(getStringMasterNode(m,1),"enquanto"))
		{
			Variavel *var = executaArvore(getFolha(m,'e'));
			while(!isNullorFalse(var)){
				executaArvore(getFolha(m,'m'));
				var = executaArvore(getFolha(m,'e'));
			} 
			executaArvore(getFolha(m,'p'));                       
		}
		else if (!strcmp(getStringMasterNode(m,1),"brec")) //TODO rever aqui
		{
			//Variavel *b = criaVariavel();
			//setNameVar(b,"break");
			//return b; // Agora o enquanto e o para devem ficar olhando se foi retornada uma variavel break ;)
			
			
		}
		else if (!strcmp(getStringMasterNode(m,1),"para"))
		{
			Variavel *var = executaArvore(getFolha(m,'i'));
			
			int i;
			int min = *(int*)getDataVar(executaArvore(getFolha(m,'e')));
			int max = *(int*)getDataVar(executaArvore(getFolha(m,'m')));
			for ( i = min; i <= max; i++)
			{
				int *aux = getDataVar(var);
				*aux = i;
				executaArvore(getFolha(m,'d'));

			}
		}
		
		executaArvore(getFolha(m,'p'));
	}

	else if(!strcmp(getStringMasterNode(m,0),"call"))
	{
		//printf("ENTROU AKI call\n");
		MasterNode *argumentos = getFolha(m,'e');
		if(!strcmp(getStringMasterNode(m,1),"escreva")) // Chamei a função primitiva de exibição
		{
			exibeVar(executaArvore(getFolha(m,'e')));
		}
		else if(!strcmp(getStringMasterNode(m,1),"escreva_ln")) // Chamei a função primitiva de exibição
		{
			exibeVar(executaArvore(getFolha(m,'e')));
			printf("\n");
		}
		else if(!strcmp(getStringMasterNode(m,1),"leia")) // Chamei a função primitiva de leitura
		{
			Variavel *varAux = executaArvore(getFolha(m,'e'));
			char buffer[300]; buffer[0] = '\0';

			scanf("%s",buffer);
			
			switch(getTipoVar(varAux))
			{
				case INTEIRO:
				{
					int *i = (int*) malloc(sizeof(int));
					*i = atoi(buffer);
					setDataVar(varAux,(void*)i);
					break;
				}
				case REAL:
				{
					double *i = (double*) malloc(sizeof(double));
					*i = atof(buffer);
					setDataVar(varAux,(void*)i);
					break;
				}
	
				case LITERAL:
				{
					char *i = (char*) malloc((strlen(buffer)+1)*sizeof(char));
					strcpy(i,buffer);
					setDataVar(varAux,(void*)i);
					break;
				}
	
				case BOOLEANO:
				{
					int *i = (int*) malloc(sizeof(int));
					*i = (atoi(buffer) == 0);
					setDataVar(varAux,(void*)i);
					break;
				}
	
				case CARACTER:
				{
					char *i = (char*) malloc(sizeof(char));
					*i = buffer[0];
					setDataVar(varAux,(void*)i);
					break;
				}
				
			}
		}
		else if(!strcmp(getStringMasterNode(m,1),"maximo"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			
			double a,b;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				a = *(int*)getDataVar(temp1);
			}
			else if(getTipoVar(temp1) == REAL)
			{
				a = *(double*)getDataVar(temp1);
			}
			else
			{
				printf("Run-time Error when calling 1st arg of maximo\n");
				exit(0);
			}
			
			
			if(getTipoVar(temp2) == INTEIRO)
			{
				b = *(int*)getDataVar(temp2);
			}
			else if(getTipoVar(temp2) == REAL)
			{
				b = *(double*)getDataVar(temp2);
			}
			else
			{
				printf("Run-time Error when calling 2nd arg of maximo\n");
				exit(0);
			}
			
			if(a > b) 
			{
			
				double *r = (double*) malloc (sizeof(double));
				*r = a;
				free(getDataVar(temp1));
				setTipoVar(temp1,REAL);
				
				setDataVar(temp1, r);
			
				return temp1;
			
			}
			else 
			{
				double *r = (double*) malloc (sizeof(double));
				*r = b;
				free(getDataVar(temp2));
				setTipoVar(temp2,REAL);
				
				setDataVar(temp2, r);
			
				return temp2;
			}
			
			
		}
		else if(!strcmp(getStringMasterNode(m,1),"minimo"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			
			double a,b;
			
			if(getTipoVar(temp1) == INTEIRO)
			{
				a = *(int*)getDataVar(temp1);
			}
			else if(getTipoVar(temp1) == REAL)
			{
				a = *(double*)getDataVar(temp1);
			}
			else
			{
				printf("Run-time Error when calling 1st arg of maximo\n");
				exit(0);
			}
			
			
			if(getTipoVar(temp2) == INTEIRO)
			{
				b = *(int*)getDataVar(temp2);
			}
			else if(getTipoVar(temp2) == REAL)
			{
				b = *(double*)getDataVar(temp2);
			}
			else
			{
				printf("Run-time Error when calling 2nd arg of maximo\n");
				exit(0);
			}
			
			
			if(a < b) 
			{
			
				double *r = (double*) malloc (sizeof(double));
				*r = a;
				free(getDataVar(temp1));
				setTipoVar(temp1,REAL);
				
				setDataVar(temp1, r);
			
				return temp1;
			
			}
			else 
			{
				double *r = (double*) malloc (sizeof(double));
				*r = b;
				free(getDataVar(temp2));
				setTipoVar(temp2,REAL);
				
				setDataVar(temp2, r);
			
				return temp2;
			}
		}
		else if(!strcmp(getStringMasterNode(m,1),"media"))
		{
			Variavel *temp1 = executaArvore(getFolha(m,'e'));
			Variavel *temp2 = executaArvore(getFolha(m,'m'));
			
			double a,b;
			if(getTipoVar(temp1) == INTEIRO)
			{
				a = *(int*)getDataVar(temp1);
			}
			else if(getTipoVar(temp1) == REAL)
			{
				a = *(double*)getDataVar(temp1);
			}
			else
			{
				printf("Run-time Error when calling 1st arg of maximo\n");
				exit(0);
			}
			
			
			if(getTipoVar(temp2) == INTEIRO)
			{
				b = *(int*)getDataVar(temp2);
			}
			else if(getTipoVar(temp2) == REAL)
			{
				b = *(double*)getDataVar(temp2);
			}
			else
			{
				printf("Run-time Error when calling 2nd arg of maximo\n");
				exit(0);
			}
			
			// Aqui converto temp1 para real e retorno a media (aceito inteiros também como args).
			free(getDataVar(temp1));
			setTipoVar(temp1,REAL);
			double *r = (double*) malloc (sizeof(double));
			*r = (a+b)/2.0;
			setDataVar(temp1, r);
			return temp1;
		}
	
		return NULL;
	}
	else
	{
		printf("%s\n",getStringMasterNode(m,0));
		return executaArvore(getFolha(m,'p'));
	}

	
}


