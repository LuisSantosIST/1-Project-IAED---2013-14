/*
TG012:

Luis Nunes      77940
Luis Henriques  77919    
Ricardo Rei     78047

*/
#include <stdio.h>

#define DIM1 12				/*Numero de partidos*/
#define DIM2 28				/*Numero de paises*/

const int max[28] = {96, 18, 21, 17, 6, 11, 13, 13, 8, 54, 6, 13, 74, 21, 21,        
					 11, 73, 8, 11, 6, 6, 26, 51, 21, 73, 21, 32, 20};	 
					 /*numero maximos de mandatos de cada pais*/

const char countries[][3] = {"DE","AT","BE","BG","CY","HR","DK","SK","SI","ES","EE","FI","FR","GR","HU","IE","IT",
							"LV","LT","LU","MT","NL","PL","PT","GB","CZ","RO","SE"};  
							 /*Strings correspondentes a cada pais*/

const char parties[][4] = {"EPP","PES","LDE","EGP","ECR","ELP","ELD","EDP","EAF","EMN","ECP","AED"}; 
							/*Strings correspondentes a cada partido*/


typedef struct{				/*estrutura utilizada para guardar dentro de dois vectores
							 os votos e os mandatos correspondentes a cada partido de cada pais*/
    						
	int mandatos[12];
	int votos[12];
} Pais;

/*declaracao das funcoes*/
void inicializa_partis(Pais v[]);
void soma_votos(Pais vec[], int, int, int);
void atribui_mandatos(int k, Pais vec[]);
int soma_mandatos(Pais p);
int maxvec(float v[], Pais p);
int total_votos(Pais p);
void e_out(Pais v[]);
void m_out(Pais v[], int pais);

int main()
{
    char command;  

    Pais vec[DIM2];							/*criacao de um vector do tipo Pais com espaco reservado para
   											todos os paises*/			
    inicializa_partis(vec);		

    while ((command = getchar()) != 'x') {  /* le o comando */
        switch (command) 
        {
        int pais, partido, votos, i;
        case '+':
            scanf("%d %d %d", &pais, &partido, &votos);	/*le os dados introduzidos pelo utilizador, sendo o primeiro o indice
             correspondente ao pais, o segundo o indice correspondente ao partido e o terceiro ao numero de votos atribuidos*/
            soma_votos(vec, pais ,partido ,votos );
            for (i = 0; i < DIM2; i++)		/*percorre cada um dos 28 paises*/
            	atribui_mandatos(i, vec);
            break;
        case 'm':
        	scanf("%d",&pais);				/*le os dados introduzidos pelo utilizador referentes ao indice do
        									 pais acerca do qual se quer obter os mandatos*/
            m_out(vec, pais);
            break;
        case 'e':
            e_out(vec);
            break;
        default:
            printf("ERRO: Comando desconhecido\n");
        }
        getchar(); 							/* le o '\n' introduzido pelo utilizador */
    }
    return 0;
}


void inicializa_partis(Pais vec[])
/*inicializa_partis: Pais vector --> void

Percorre todos os partidos de todos os paises e inicializa os correspondentes votos e mandatos a 0*/

{
	int i, j;

	for (i = 0; i < DIM2; i++)			/*Percorre todos os paises*/
		for (j = 0; j < DIM1; j++)		/*Percorre todos os partidos dentro de cada pais*/
		{
			vec[i].mandatos[j] = 0;
			vec[i].votos[j] = 0;
		}
}

void soma_votos(Pais vec[], int country, int parti, int vote)
/*soma_votos: Pais vector x inteiro x inteiro x inteiro --> void

Soma os votos introduzidos pelo utilizador no partido do pais desejado*/
{
    vec[country-1].votos[parti-1]+=vote;	/*decrementamos um indice pois no nosso codigo
    										 trabalhamos com os indices de 0-27 e de 0-11*/
}

void atribui_mandatos(int k, Pais vec[])
/*atribui_mandatos: inteiro x Pais vector --> void

recebe um inteiro correspondente ao indice do pais e o vetor com todos os paises
e actualiza todos os mandatos para esse determinado pais, tendo em conta os votos*/

{
	float v[DIM1];
	int i, total, votos, indice;

	for (i = 0; i < DIM1; i++) /*cria vetor auxiliar com os votos em float */
	{
		v[i] = vec[k].votos[i];
		vec[k].mandatos[i] = 0;
	} 

	total = soma_mandatos(vec[k]); 
	votos = total_votos(vec[k]); 
	
	if (votos != 0) 
		while (total < max[k]) /* so acaba quando tiverem sido atribuidos todos os mandatos*/
		{
			indice = maxvec(v, vec[k]); 
			vec[k].mandatos[indice] += 1; 
			/*tranformacao para float de forma a nao dar zero quando o dividendo for menor que o divisor */
			v[indice] = (float)vec[k].votos[indice] / (vec[k].mandatos[indice]+1);
			total = soma_mandatos(vec[k]);
		}
}


int total_votos(Pais p)
/* total_votos: Pais p --> votos 

recebe um pais e devolve o total de votos */
{
	int i, votos = 0;

	for (i = 0; i < DIM1; i++)
		votos += p.votos[i];

	return votos;
}

int soma_mandatos(Pais p)
/* soma_mandatos: Pais p --> total de mandatos

recebe um pais e devolve o total de mandatos atribuidos nesse pais */
{
	int total = 0, i;

	for (i = 0; i < DIM1; i++)
		total += p.mandatos[i];

	return total;
}

int maxvec(float v[], Pais p)
/* maxvec : vetor x Pais p --> indice

recebe um vetor e devolve o indice correspondente ao numero mais elevado do vetor */
{
	int i, indice = 0;
	float maior = 0;

	for( i = 0; i < DIM1; i++)
	{
		if (v[i] > maior)
		{
			maior = v[i];
			indice = i;
		}
        /*em caso de igualdade guarda o indice correspondente ao partido com menos mandatos atribuidos,
        no caso de os mandatos serem iguais mantem o indice menor */
		else if (v[i] == maior)
			if (p.mandatos[i] < p.mandatos[indice]) indice = i;	 
	}
	return indice;
}

void m_out(Pais v[], int pais)
/*m_out: Pais vector x inteiro --> void

Imprime para o ecra o numero de mandatos de cada partido referente ao indice do pais introduzido*/
{
	int i;

	printf("   %s", parties[0]);	/*Imprime o primeiro partido antecedente de três espaços*/
	for (i = 1; i < DIM1; i++)		/*Percorre os partidos e começa em um porque ja imprimimos o primeiro partido*/
		printf(" %s", parties[i]);	/*Imprime os restantes partidos antecedentes de um espaço*/
	puts("");						/*para continuar a imprimir na linha seguinte*/

	for (i = -1; i < DIM1; i++)		/*Percorre cada partido e começa em -1 para imprimir o pais correspondente*/
	{
		if(i == -1)
			printf("%s", countries[pais-1]);
		else
			printf(" %3d", v[pais-1].mandatos[i]);
	}
	puts("");
}

void e_out(Pais v[])
/*e_out: Pais vector --> void

Imprime para o ecra os mandatos de cada partido de todos os paises e ainda a soma de mandatos de cada partido*/
{
	int i, j, soma;

	printf("   %s", parties[0]);
	for (i = 1; i < DIM1; i++)
		printf(" %s", parties[i]);
	puts("");

	for(i = 0; i < DIM2; i++)
	{
		for (j = -1; j < DIM1; j++)
		{
			if(j == -1)
				printf("%s", countries[i]);
			else
				printf(" %3d", v[i].mandatos[j]);
		}
		puts("");
	}

	printf("TE");				
	for(i = 0; i < DIM1; i++)				/*Percorre todos os partidos*/
	{	
		soma = 0;
		for(j = 0; j < DIM2; j++)			/*Percorre o mesmo partido de cada pais*/
			soma += v[j].mandatos[i];		/*Soma os mandatos de cada partido de cada pais*/
		printf(" %3d", soma);
	}
	puts("");
}
