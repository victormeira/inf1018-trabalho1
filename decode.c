/* Victor Meira Pinto 1420626 3WB */
/* José Paulo Diniz   1510910 3WB */

#include <stdio.h>
#include <math.h>
#include "decode.h"
#define BYTE 8


int get_next(FILE *f);
void one_field(FILE *f);
void one_struct(FILE *f);
int one_num(FILE *f);

int decode (FILE *f)
{
    int i=1;

	if(f == NULL)
	{
		printf("Erro na leitura do arquivo. \n"); 	/* retorna -1 caso n‹o leia arquivo */
		return -1;
	}

	while(get_next(f)==1)							/*	enquanto ainda h‡ marca FF no arquivo*/
	{
		printf("----------------------\nEstrutura %d\n",i);
		one_struct(f);
		i++;
	}							

	return 0;
}

void one_field(FILE *f)
{
    int i, c;
    

	for(i=0;i<5;i++)
		c=get_next(f);							/*passa os 5 bits 0 da chave */

	if(get_next(f))                             /*confere se é long ou int e imprime */
		printf("<long>");
	else
		printf("<int>");
    
    c=get_next(f);                              /*percorre o char faltando no tipo */
	
	printf("%d\n",one_num(f));

	return;
}

void one_struct(FILE *f)
{
    int i, c;

	for(i=0;i<BYTE-1;i++)
		c=get_next(f);							/* acaba de ler a marca FF da estrutura */

	while(get_next(f))							/* confere se é o ultimo campo */
		one_field(f);

	one_field(f);								/* processa ultimo campo */
}

int get_next(FILE *f)
{
    return fgetc(f)-'0';
}

int one_num(FILE *f)
{
    int numss=0, numcs, i, exp=0;
    char str[BYTE-1];

    
    while(get_next(f))
    {
        fread(str,BYTE-1,1,f);                              /*le string de 7 bits correspondendo ao valor */
        for(i=BYTE-2;i>-1;i--,exp++)
            numss = numss + ((int)(str[i]-'0'))*pow(2,exp); /*percorre o vetor de tr‡s pra frente adicionando potencias de 2*/
    }
    
    fread(str,BYTE-1,1,f);
    for(i=BYTE-2;i>-1;i--,exp++)
        numss = numss + ((int)(str[i]-'0'))*pow(2,exp);
    
    numcs = numss >>  1;
    if (numss & 0x01)                           /* zigzag dado como dica */
        numcs = ~numcs;
    
    return numcs;
}