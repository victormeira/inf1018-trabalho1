/* Victor Meira Pinto 1420626 3WB */
/* José Paulo Diniz   1510910 3WB */

#include <stdio.h>
#include <math.h>
#include "decode.h"
#define BYTE 8


int get_next(FILE *f);
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

	while(get_next(f))							/*	enquanto ainda é puxado bit valor 1 do arquivo		*/
	{
		printf("----------------------\nEstrutura %d\n",i);
		one_struct(f);
		i++;
	}							

	return 0;
}

void one_field(FILE *f)
{
	int i, c, numss=0, exp=0, numcs;

	for(i=0;i<5;i++)
		c=get_next(f);							/*passa os 5 bits 0 da chave */

	if(get_next(f))							/*confere se é long ou int e imprime */
		printf("<long>");
	else
		printf("<int>");
    
    c=get_next(f);

	while(get_next(f))						/*confere se é ultimo byte */
	{
		for(i=0;i<BYTE-1;i++,exp++)
			numss = numss + get_next(f)*pow(2,exp); /* como contar o exponencial de tras pra frente? */
	}

	for(i=0;i<BYTE-1;i++,exp++) 			/* Processa ultimo byte */
		numss = numss + get_next(f)*pow(2,exp);


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
		c=get_next(f);								/* acaba de ler a marca FF da estrutura */

	while(get_next(f))							/* confere se é o ultimo campo */
		one_field(f);

	one_field(f);								/* processa ultimo campo */
}

int get_next(FILE *f)
{
    return fgetc(f)-'0';
}