// ProjetoEd.cpp : Defines the entry point for the console application.
//
/*
Nomes:
Fernando Barbosa Gomes Ra 12194122
Gabriela Ferreira Jorge Ra 12228441
Opcionais funcionando: 4 , 5 e 2
Valor total do Projeto:          pontos

OBS: RODAR O PROGRAMA DIRETO DO DIRETORIO ONDE ELE EH CRIADO.NÃO EXECUTAR PELA IDE!! A EXECUÇAO PELA IDE FAZ VARIAS CHECAGENS DE TUDO O QUE ACONTECE NO PROGRAMA
TORNANDO O PROGRAMA EXTREMAMENTE LENTO, POR EXEMPLO UMA PESQUISA QUE DEMORARIA 1 MINUTO SE RODADO APARTIR DO DIRETORIO, DEMORA 4 HORAS SE EXECUTADA PELA IDE


OBS2: SE COMPILAR O PROGRAMA PELO VISUAL STUDIO 2012 ACESSE: PROPERTIES >C/C++>PREPROCESSOR DEFINITIONS> ESCREVA :_CRT_SECURE_NO_WARNINGS EM UMA DAS LINHAS

OB3: COMPILE O PROGRAMA EM MODO DE RELEASE-> UMA PESQUISA QUE DEMORA 1 MINUTO EM RELEASE, DEMORA 8 EM DEBUG.
*/


#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int menorcustototal;
int totalcities;
char destinome[17];

struct destino
{
struct cidade *local;
int distancia; 
};

struct cidade
{
	char nome[17];
	struct destino *destino[10];
	struct cidade *next;
	int lastdestino;
	int cidid;
	void setNome(char nomearg[17])
	{
		for (int i = 0; i < 10; i++)
		{
			destino[i]=NULL;
		}
	strcpy(nome,nomearg);
	}

};


struct pilha
{
struct pilha *ant;
struct pilha *prox;
struct cidade *cid;
struct cidade *dadcid;
int custo;
int cidtil;
int caminhoid[200];
};

pilha nullpilha;

void inserePilha(struct cidade *cidarg,struct cidade *dadcidade,int antcaminho[], int custo,int cidtil, struct pilha **raiz, struct pilha **end)
{
	struct pilha *aux;
	if (*raiz==NULL)
	{
	*raiz=(struct pilha *)malloc(sizeof(struct pilha));
	aux=(*raiz);
	aux->ant=NULL;
	aux->prox=NULL;
	aux->cid=cidarg;
	aux->custo=custo;
	aux->dadcid=dadcidade;
	aux->cidtil=cidtil;
	for(int i=0;i<200;i++)
	{
		if (antcaminho[i]==-1){aux->caminhoid[i]=cidarg->cidid; aux->caminhoid[i+1]=-1; break;}
		aux->caminhoid[i]=antcaminho[i];
	}
	(*end)=(*raiz);
	}else
	{
		aux=(*end);
		//while(aux->prox!=NULL){aux=aux->prox;}
		aux->prox=(struct pilha *)malloc(sizeof(struct pilha));
		aux->prox->ant=aux;
		aux=aux->prox;
		aux->cid=cidarg;
		aux->custo=custo;
		aux->dadcid=dadcidade;
		aux->cidtil=cidtil;
		for(int i=0;i<200;i++)
		{
			if (antcaminho[i]==-1){aux->caminhoid[i]=cidarg->cidid; aux->caminhoid[i+1]=-1; break;}
			aux->caminhoid[i]=antcaminho[i];
		}
		aux->prox=NULL;
		(*end)=aux;
	}
}

struct cidade *findCidade(char nome[17],struct cidade *raiz)
{
	struct cidade *aux;
	aux=raiz;
	int achou=false;
	while(aux!=NULL)
	{
		if (strcmp(aux->nome,nome)==0){achou=true; break;}
		aux=aux->next;
	}	
	if (achou==true)
	{
		return aux;
	}else{return NULL;}
}

void buble(struct destino *v[])
	{   int n = 7;
		int x=0,y=0;
		struct destino aux;

		for( x = 0; x < n; x++ )
  {
    for( y = x + 1; y < n; y++ )
    {
		if (v[x]!=NULL && v[y]!=NULL)
		{
			if ( v[x]->distancia < v[y]->distancia )
			 {	 
			 aux.distancia = v[x]->distancia;
			 aux.local = v[x]->local;
			 v[x]->distancia = v[y]->distancia;
			 v[x]->local = v[y]->local;
			 v[y]->distancia = aux.distancia;
			 v[y]->local = aux.local;
			 }
		}
    }
  } 

}


bool pertenceCaminho(int cidid, int caminhoid[200])
{
	for (int i = 0; i < 200; i++)
	{
		if (caminhoid[i]==-1)return false;
		if (caminhoid[i]==cidid)return true;
	}
	return false;
}

bool pertenceCaminhoDuplo(int cidid,int cidid2, int caminhoid[200])
{
	for (int i = 0; i < 199; i++)
	{
		if (caminhoid[i+1]==-1)return false;
		if (caminhoid[i]==cidid && caminhoid[i+1]==cidid2)return true;
	}
	return false;
}

struct pilha removePilha(struct pilha **raiz,struct pilha **end)
	{
		struct pilha *aux;
		struct pilha aux2;
		aux=(*raiz);
		if (*raiz!=NULL){
		if (aux->prox==NULL)
		{
			aux2=(*aux);
			free(aux);
			*raiz=NULL;
			*end-NULL;
			return aux2;
		}
		//while(aux->prox!=NULL){aux=aux->prox;}
		aux=(*end);
		aux2=(*aux);
		aux->ant->prox=NULL;
		(*end)=aux->ant;
		free(aux);
		return aux2;
		}else{return nullpilha;}
	}




void esvaziaPilha(struct pilha **raiz)
	{
		struct pilha *aux;
		aux=(*raiz);
		int pos=0;
		if (*raiz!=NULL){pos=1;}
		while(pos>0)
		{
		while(aux->prox!=NULL)
		{
			aux=aux->prox;
			pos++;	
		}
		if (aux->ant!=NULL)
		{
		aux->ant->prox=NULL;
		}
		free(aux);
		if (pos==1){(*raiz)=NULL;pos=0;break;}
		aux=(*raiz);
		pos=1;
		}	
	}

bool pilhaVazia(struct pilha **raiz)
{
	if (*raiz==NULL){return true;}else{return false;}
}

void createCidade(char nomearg[17],struct cidade *raiz)
{
	struct cidade *aux;

		aux=raiz;
		while(aux->next!=NULL){aux=aux->next;}
		aux->next=(struct cidade *)malloc(sizeof(struct cidade));
		aux->next->setNome(nomearg);
		aux->next->next=NULL;
		aux->next->cidid=totalcities;
		totalcities++;
}



void printAllConnections(struct cidade *raiz)
{
	struct cidade *aux;
	aux=raiz;
	int ncidade=0;
	while(aux!=NULL)
	{
		printf("%d.%s \n",ncidade,aux->nome); 
		
		for (int i = 0; i < 10; i++)
		{
			if (aux->destino[i]!=NULL){printf("para %s distancia %d \n",aux->destino[i]->local->nome,aux->destino[i]->distancia*10);}
		}
		aux=aux->next;
		ncidade++;
	}
}

void printAllCidades(struct cidade *raiz)
{
	struct cidade *aux;
	aux=raiz;
	int ncidade=0;
	while(aux!=NULL)
	{
		printf("%d.%s \n",ncidade,aux->nome); 
		aux=aux->next;
		ncidade++;
	}
}


void setDestino(char nome[17],char nome2[17],int custo,struct cidade *raiz)
{
	struct cidade *aux;
	aux=raiz;
	struct cidade *aux2;
	aux2=raiz;
	int achou=false,achou2=false;
	while(aux!=NULL)
	{
		if (strcmp(aux->nome,nome)==0){achou=true; break;}
		aux=aux->next;
	}
	
	if (achou==true)
	{
	while(aux2!=NULL)
	{
		if (strcmp(aux2->nome,nome2)==0){achou2=true; break;}
		aux2=aux2->next;
	}

	if (achou2==true)
	{
		for (int i = 0; i < 10; i++)
		{
			if (aux->destino[i]==NULL){break;}
			if (i==9){return;}
		}
		for (int i = 0; i < 10; i++)
		{
			if (aux2->destino[i]==NULL){break;}
			if (i==9){return;}
		}
		for (int i = 0; i < 10; i++)
		{
			if (aux->destino[i]==NULL)
			{
				aux->destino[i]=(struct destino *)malloc(sizeof(struct destino));
				aux->destino[i]->local=aux2;
				aux->destino[i]->distancia=custo;
				aux->lastdestino=i;
				menorcustototal+=custo;
				break;
			}
		}
		buble(aux->destino);	
		for (int i = 0; i < 10; i++)
		{
			if (aux2->destino[i]==NULL)
			{
				aux2->destino[i]=(struct destino *)malloc(sizeof(struct destino));
				aux2->destino[i]->local=aux;
				aux2->destino[i]->distancia=custo;  
				aux2->lastdestino=i;
				break;
			}
		}
		buble(aux2->destino);
	
	}
	}

}


bool pegouTodos(struct cidade *raiz,int caminhoid[200])
{
	struct cidade *aux;
	aux=raiz;
	int ok=false;

	while(aux!=NULL)
	{
		ok=false;
		for (int i = 0; i < 200; i++)
		{
			if (caminhoid[i]==-1)return false;
			if (caminhoid[i]==aux->cidid){ok=true; break;}
		}
		if (ok==false){return false;}
		aux=aux->next;
	}
	return true;
}

void printCaminho(int caminho[200],struct cidade *raiz)
{
	struct cidade *aux;
	for (int i = 0; i < 200; i++)
	{
		if (caminho[i]==-1){break;}
	aux=raiz;
	while(aux!=NULL)
	{
		if (aux->cidid==caminho[i])
		{
		printf("%s,",aux->nome); break;
		}
		aux=aux->next;
	}
	}
}


int main()
{
	totalcities=0;
	time_t timer;
	double seconds;
	time_t now;
	menorcustototal=0;
	struct pilha *firstp=NULL;
	struct pilha *endp=NULL;
	struct pilha checkresult;
	nullpilha.custo=-1;

	struct cidade *first=NULL;
	first = (struct cidade *)malloc(sizeof(struct cidade));
	first->setNome("Seattle");
	first->next=NULL;
	first->cidid=0;
	totalcities++;

	createCidade("Portland",first);
	createCidade("Boise",first);
	createCidade("San Francisco",first);
	createCidade("Lake Tahde",first);
	createCidade("Los Angeles",first);
	createCidade("San Diego",first);
	createCidade("Palm Springs",first);
	createCidade("Las Vegas",first);
	createCidade("Grand Canyon",first);
	createCidade("Phoenix",first);
	createCidade("Salt Lake City",first);
	createCidade("YellowStone",first);
	createCidade("Vail",first);
	createCidade("Aspen",first);
	createCidade("Denver",first);
	createCidade("Colorado Springs",first);
	createCidade("Omaha",first);
	createCidade("Kansas City",first);
	createCidade("St Louis",first);
	createCidade("Dallas",first);
	createCidade("Little Rock",first);
	createCidade("San Antonio",first);
	createCidade("Houston",first);
	createCidade("Nova Orleans",first);
	createCidade("Orlando",first);
	createCidade("Fort Lauderdale",first);
	createCidade("Miami",first);
	createCidade("Atlanta",first);
	createCidade("Memphis",first);
	createCidade("Nashville",first);
	createCidade("Richmond",first);
	createCidade("Washington",first);
	createCidade("Nova York",first);
	createCidade("Boston",first);
	createCidade("Albany",first);
	createCidade("Indianopolis",first);
	createCidade("Detroit",first);
	createCidade("Chicago",first);
	createCidade("Milwaukee",first);
	createCidade("Minneapolis",first);


	setDestino("Seattle","Portland",17,first);
	setDestino("Seattle","Boise",50,first);
	setDestino("Portland","Boise",42,first);
	setDestino("Portland","San Francisco",69,first);
	setDestino("Portland","Lake Tahde",58,first);
	setDestino("Boise","YellowStone",67,first);
	setDestino("Boise","Lake Tahde",42,first);
	setDestino("San Francisco","Lake Tahde",30,first);
	setDestino("San Francisco","Los Angeles",38,first);
	setDestino("Lake Tahde","Salt Lake City",52,first);
	setDestino("Lake Tahde","Palm Springs",78,first);
	setDestino("Los Angeles","Palm Springs",16,first);
	setDestino("Los Angeles","San Diego",12,first);
	setDestino("Los Angeles","Las Vegas",27,first);
	setDestino("Palm Springs","Las Vegas",29,first);
	setDestino("Palm Springs","Grand Canyon",47,first);
	setDestino("Palm Springs","San Diego",14,first);
	setDestino("San Diego","Phoenix",35,first);
	setDestino("Las Vegas","Salt Lake City",42,first);
	setDestino("Las Vegas","Grand Canyon",47,first);
	setDestino("Phoenix","Grand Canyon",36,first);
	setDestino("Phoenix","San Antonio",99,first);
	setDestino("Phoenix","Dallas",107,first);
	setDestino("Phoenix","Salt Lake City",66,first);
	setDestino("San Antonio","Houston",31,first);
	setDestino("San Antonio","Dallas",28,first);
	setDestino("Houston","Nova Orleans",53,first);
	setDestino("Houston","Dallas",25,first);
	setDestino("Nova Orleans","Miami",86,first);
	setDestino("Nova Orleans","Orlando",64,first);
	setDestino("Nova Orleans","Atlanta",47,first);
	setDestino("Miami","Fort Lauderdale",3,first);
	setDestino("Miami","Orlando",23,first);
	setDestino("Fort Lauderdale","Orlando",18,first);
	setDestino("Orlando","Atlanta",44,first);
	setDestino("Atlanta","Richmond",56,first);
	setDestino("Atlanta","Nashville",24,first);
	setDestino("Atlanta","Memphis",39,first);
	setDestino("Atlanta","Dallas",79,first);
	setDestino("Richmond","Washington",20,first);
	setDestino("Nashville","Richmond",71,first);
	setDestino("Nashville","Memphis",21,first);
	setDestino("Nashville","Indianopolis",29,first);
	setDestino("Washington","Nova York",24,first);
	setDestino("Washington","Detroit",53,first);
	setDestino("Washington","Chicago",70,first);
	setDestino("Washington","Indianopolis",59,first);
	setDestino("Nova York","Detroit",64,first);
	setDestino("Nova York","Boston",21,first);
	setDestino("Nova York","Albany",15,first);
	setDestino("Boston","Albany",17,first);
	setDestino("Albany","Detroit",65,first);
	setDestino("Detroit","Chicago",28,first);
	setDestino("Indianopolis","Chicago",18,first);
	setDestino("Milwaukee","Chicago",9,first);
	setDestino("Milwaukee","Minneapolis",34,first);
	setDestino("Minneapolis","Chicago",41,first);
	setDestino("St Louis","Chicago",30,first);
	setDestino("St Louis","Kansas City",25,first);
	setDestino("Omaha","Chicago",47,first);
	setDestino("Indianopolis","St Louis",25,first);
	setDestino("Memphis","Little Rock",14,first);
	setDestino("Memphis","St louis",29,first);
	setDestino("Little Rock","St Louis",46,first);
	setDestino("Little Rock","Dallas",32,first);
	setDestino("Kansas City","Dallas",55,first);
	setDestino("Kansas City","Omaha",19,first);
	setDestino("Minneapolis","Omaha",38,first);
	setDestino("Minneapolis","YellowStone",134,first);
	setDestino("Denver","Omaha",54,first);
	setDestino("Denver","Colorado Springs",12,first);
	setDestino("Denver","Aspen",17,first);
	setDestino("Denver","Vail",16,first);
	setDestino("Denver","Salt Lake City",53,first);
	setDestino("Denver","YellowStone",93,first);
	setDestino("Vail","Aspen",8,first);
	setDestino("Colorado Springs","Aspen",18,first);
	setDestino("Colorado Springs","Dallas",73,first);
	


	int nextcusto=0;
	int vet[200];
	int tamanhopilha=0;
	int maxrepete=totalcities*0.88;
	int checagens=0,checagens2=0,qtdcaminhos=0;
	int destinos2=0;
	int menorcaminho[200],smenorcaminho[200],tmenorcaminho[200];
	int menorcusto=menorcustototal-50,smenorcusto=menorcusto,tmenorcusto=menorcusto;
	char nextcaminho[1000]="";
	char mixcaminho[1000]="";
	char novacidade[17]="",novodestino[17]="";
	int opcao=1,opcao2=1;

	while(opcao!=0)
	{
	printf("O que você deseja fazer?(Digite o numero da opcao) \n0.Sair\n1.Listar todas as cidades \n2.Listar todas as cidade e suas conexoes\n3.Inserir nova cidade \n4.Achar caminho entre duas cidades\n5.Achar caminho de ida e volta a uma cidade(Passando por todas cidades)\n>");
	scanf("%d",&opcao);
	if (opcao==1)
	{
	printAllCidades(first);
	}
	if (opcao==2)
	{
	printAllConnections(first);
	}
	if (opcao==3)
	{
		printf("\nDigite o nome da nova cidade:\n");
		fflush(stdin);
		gets(novacidade);
		createCidade(novacidade,first);	
		opcao2=1;
		printf("\nAdicione conexoes para essa cidade.\n");
		while(opcao2!=0)
		{
		printf("\nDigite o nome da cidade que voce quer conectar a esta:\n");
		fflush(stdin);
		gets(novodestino);
		printf("\nQual a distancia em KMs dessas cidades?\n");
		scanf("%d",&nextcusto);
		setDestino(novacidade,novodestino,nextcusto/10,first);
		printf("\nContinuar Adicionando Conexoes?(0=Nao,1=Sim)\n");
		scanf("%d",&opcao2);
		if (opcao2==0 && findCidade(novacidade,first)->destino[0]==NULL)
		{
		printf("\nA ultima insercao foi invalida.Cada cidade precisa ter ao menos uma conexao.\n");
		opcao2=1;
		}else{
		printf("\nCidade Inserida com Sucesso\n");
		}
		
		}
	}

	//VAI======================================================================================================================================

	
		if (opcao==4)
	{
	strcpy(destinome,"zir56i345g43id72un");
	strcpy(novodestino,"zir56i345g43id72un");
	while(findCidade(novodestino,first)==NULL)
	{
	printf("Digite o nome da cidade de saida:");
	fflush(stdin);
	gets(novodestino);
	}
	while(findCidade(destinome,first)==NULL)
	{
	printf("Digite o nome da cidade destino:");
	fflush(stdin);
	gets(destinome);
	}
	nextcusto=0;
	menorcusto=menorcustototal;
	smenorcusto=menorcusto;
	tmenorcusto=menorcusto;
	tamanhopilha=0;
	tamanhopilha++;
	
	vet[0]=-1;
	struct cidade *destinocidade=findCidade(novodestino,first);
	inserePilha(destinocidade,NULL,vet,0,0,&firstp,&endp);
	destinocidade=findCidade(destinome,first);

	timer = time(NULL);
	printf("\nCalculando. Isso pode levar alguns minutos.\n");
	while(!pilhaVazia(&firstp))
	{	
	checkresult=removePilha(&firstp,&endp);
	tamanhopilha--;
	//printf("%d\n",tamanhopilha);
	
	//printf("%s \n \n \n checagens %d",checkresult.caminho,checagens);
	//system("Pause");
		if (checkresult.custo!=-1)
		{
			if (checkresult.cid->cidid==destinocidade->cidid && checkresult.custo<=menorcusto)
				{
					for (int i = 0; i < 200; i++)
						{
							tmenorcaminho[i]=smenorcaminho[i];
							smenorcaminho[i]=menorcaminho[i];
							menorcaminho[i]=checkresult.caminhoid[i];
						}

					tmenorcusto=smenorcusto;
					smenorcusto=menorcusto;
					menorcusto=checkresult.custo;	
					printf("-");
					//printf("\n\n\n Caminho Encontrado! Custo %d Checagens %d Tempo: %g s \n\n\n\n %s \n \n\ \n",menorcusto,checagens,seconds,menorcaminho);	
					checagens=0;
					checagens2=0;
					qtdcaminhos++;
					//}
				}
			if (tamanhopilha<120)
			{
			for (int i = 0; i < 10; i++)
			{
				if(checkresult.cid->destino[i]!=NULL)
				{
						if (!pertenceCaminho(checkresult.cid->destino[i]->local->cidid,checkresult.caminhoid))
						{
						destinos2++;
						nextcusto=checkresult.cid->destino[i]->distancia + checkresult.custo;
						if (nextcusto<menorcusto)
						{
						checagens2++;
						checagens=0;
						tamanhopilha++;
						inserePilha(checkresult.cid->destino[i]->local,checkresult.cid,checkresult.caminhoid,nextcusto,checkresult.cidtil+1,&firstp,&endp);
						}
					}	
				}else{break;}
			}		
			if (destinos2==0 && checagens<50000)
			{ 
			for (int i = 0; i < 10; i++)
			{
				if(checkresult.cid->destino[i]!=NULL)
				{
					if (!pertenceCaminhoDuplo(checkresult.cid->cidid,checkresult.cid->destino[i]->local->cidid,checkresult.caminhoid))
					{
						nextcusto=checkresult.cid->destino[i]->distancia + checkresult.custo;
						if (nextcusto<menorcusto)
						{
						checagens2++;
						checagens++;
						tamanhopilha++;
						inserePilha(checkresult.cid->destino[i]->local,checkresult.cid,checkresult.caminhoid,nextcusto,checkresult.cidtil,&firstp,&endp);
							 
						}
					}
				}else{break;}
			}	
			}
			destinos2=0;
		}
		}
	}
	now =time(NULL);
	seconds = difftime(now,timer);
	printf("\n\n\n Terceiro Melhor Caminho: "); printCaminho(tmenorcaminho,first); printf("Distancia Total %d kilometros \n\n\n",tmenorcusto*10);
	printf("\n\n\n Segundo Melhor Caminho: "); printCaminho(smenorcaminho,first); printf("Distancia Total %d kilometros \n\n\n",smenorcusto*10);
	printf("\n\n\n Melhor Caminho: "); printCaminho(menorcaminho,first); printf("Distancia Total %d kilometros \n\n\n",menorcusto*10);
	printf("Tempo Total de Busca: %g segundo(s) \n",seconds);
	checagens2=0;
	checagens=0;
	qtdcaminhos=0;
	destinos2=0;
	esvaziaPilha(&firstp);
	}//END OPCAO 4 IF

	

	//VAI E VOLTA=======================================================================================================


	if (opcao==5)
	{
	strcpy(destinome,"zir56i345g43id72un");
	while(findCidade(destinome,first)==NULL)
	{
	printf("Digite o nome da cidade de saida:");
	fflush(stdin);
	gets(destinome);
	}
	maxrepete=totalcities*0.88;
	//printf("%d",maxrepete);
	nextcusto=0;
	menorcusto=menorcustototal;
	smenorcusto=menorcusto;
	tmenorcusto=menorcusto;
	tamanhopilha=0;
	tamanhopilha++;
	vet[0]=-1;
	struct cidade *destinocidade=findCidade(destinome,first);
	inserePilha(destinocidade,NULL,vet,0,0,&firstp,&endp);
	
	timer = time(NULL);
	printf("\nCalculando. Isso pode levar alguns minutos.\n");
	while(!pilhaVazia(&firstp))
	{	
	checkresult=removePilha(&firstp,&endp);
	tamanhopilha--;
	//printf("%d\n",tamanhopilha);
	if (checagens2>150950000 && qtdcaminhos>3){break;}
	//for (int i = 0; i < 200; i++)
	//{
	//	if (checkresult.caminhoid[i]==-1){break;}
	//	printf("%d,",checkresult.caminhoid[i]);
	//}
	//printf("\n \n \n cidades ateh %d",checkresult.cidtil);
	//printf("%s \n \n \n cidades ateh %d",checkresult.caminho,checkresult.cidtil);
	//system("Pause"); //19700 3.71 
		if (checkresult.custo!=-1)
		{
			if (checkresult.cid->cidid==destinocidade->cidid && checkresult.custo<=menorcusto)
				{
					if (pegouTodos(first,checkresult.caminhoid))
					{
						for (int i = 0; i < 200; i++)
						{
							tmenorcaminho[i]=smenorcaminho[i];
							smenorcaminho[i]=menorcaminho[i];
							menorcaminho[i]=checkresult.caminhoid[i];
						}
					tmenorcusto=smenorcusto;
					smenorcusto=menorcusto;
					menorcusto=checkresult.custo;	
					printf("-");	
					checagens=0;
					checagens2=0;
					qtdcaminhos++;
					}
				}
			if (tamanhopilha<125)
			{
			for (int i = 0; i < 10; i++)
			{
				if(checkresult.cid->destino[i]!=NULL)
				{
					nextcusto=checkresult.cid->destino[i]->distancia + checkresult.custo;
					if (nextcusto<menorcusto)
					{
						if (!pertenceCaminho(checkresult.cid->destino[i]->local->cidid,checkresult.caminhoid))
						{
						destinos2++;
						checagens2++;
						checagens=0;
						tamanhopilha++;
						inserePilha(checkresult.cid->destino[i]->local,checkresult.cid,checkresult.caminhoid,nextcusto,checkresult.cidtil+1,&firstp,&endp);
						}
					}	
				}else{break;}
			}		
			if (destinos2==0 && checagens<50000 && checkresult.cidtil>36)
			{ 
			for (int i = 0; i < 10; i++)
			{
				if(checkresult.cid->destino[i]!=NULL)
				{
						nextcusto=checkresult.cid->destino[i]->distancia + checkresult.custo;
						if (nextcusto<menorcusto)
						{
						if (!pertenceCaminhoDuplo(checkresult.cid->cidid,checkresult.cid->destino[i]->local->cidid,checkresult.caminhoid))
					{
						checagens2++;
						checagens++;
						tamanhopilha++;
						inserePilha(checkresult.cid->destino[i]->local,checkresult.cid,checkresult.caminhoid,nextcusto,checkresult.cidtil,&firstp,&endp);
							 
						}
					}
				}else{break;}
			}	
			}
			destinos2=0;
		}
		}
	}
	now =time(NULL);
	seconds = difftime(now,timer);
	printf("\n\n\n Terceiro Melhor Caminho: "); printCaminho(tmenorcaminho,first); printf("Distancia Total %d kilometros \n\n\n",tmenorcusto*10);
	printf("\n\n\n Segundo Melhor Caminho: "); printCaminho(smenorcaminho,first); printf("Distancia Total %d kilometros \n\n\n",smenorcusto*10);
	printf("\n\n\n Melhor Caminho: "); printCaminho(menorcaminho,first); printf("Distancia Total %d kilometros \n\n\n",menorcusto*10);
	printf("Tempo Total de Busca: %g minuto(s) \n",seconds/60);
	checagens2=0;
	checagens=0;
	qtdcaminhos=0;
	destinos2=0;
	esvaziaPilha(&firstp);
	}//END OPCAO 4 IF


	}//END OPCAO WHILE

	system("Pause");
	return 0;
}

