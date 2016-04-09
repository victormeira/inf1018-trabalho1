/* Victor Meira Pinto 1420626 3WB */
/* José Paulo Diniz   1510XXX 3WB */


#include "code.h"
#include <stdio.h>
#include <math.h>
#define BYTE 8

int code (char* desc, void* v, FILE* f)
{
	/*esta funcao codifica o blablabla*/
    return 0;
}

void one_field(FILE *f);
void one_struct(FILE *c);

int decode (FILE *f)
{
    int i=1;

	if(f == NULL)
	{
		printf("Erro na leitura do arquivo. \n"); 	/* retorna -1 caso não leia arquivo */
		return -1;
	}

	while(fgetc(f))							/*	enquanto ainda é puxado bit valor 1 do arquivo		*/
	{
		printf("----------------------\nEstrutura %d\n",i);
		one_struct(f);
		i++;
	}							

	printf("----------------------\nEstrutura %d\n",i);	/*  processa a ultima struct do arquivo */
	one_struct(f);	

	return 0;
}
/* Funcao 
int fgetc(FILE *arq) retorna como int do primeiro byte do arquivo*/

void one_field(FILE *f)
{
	int i, c, numss=0, exp=0, numcs;

	for(i=0;i<6;i++)
		c=fgetc(f);							/*passa os 5 bits 0 da chave */

	if(fgetc(f))							/*confere se é long ou int e imprime */
		printf("<long>");
	else
		printf("<int>");

	while(fgetc(f))						/*confere se é ultimo byte */
	{
		for(i=0;i<BYTE-1;i++,exp++)
		{
			numss = numss + fgetc(f)*pow(2,exp);	/*implementar sabendo que inteiro tem que ser transformado com sinal */
		}
	}

	for(i=0;i<BYTE-1;i++,exp++) 			/* Processa ultimo byte */
	{
		numss = numss + fgetc(f)*pow(2,exp);		/*implementar sabendo que inteiro tem que ser transformado com sinal */
	}


	numcs = numss >> 1;
	if(numss & 0x01)
		numcs = ~numcs;
	
	printf("%d\n",numcs);

	return;
}

void one_struct(FILE *f)
{
    int i, c;

	for(i=0;i<BYTE-1;i++)
		c=fgetc(f);								/* acaba de ler a marca FF da estrutura */

	while(fgetc(f))							/* confere se é o ultimo campo */
		one_field(f);

	one_field(f);								/* processa ultimo campo */
}

