/* Victor Meira Pinto 1420626 3WB */
/* José Paulo Diniz   1510910 3WB */

#include <stdio.h>
#include "decode.h"

int decode (FILE *f);
/* decodifica estruturas guardados no arquivo f*/

unsigned char get_next(FILE *f);
/* retorna prox 8 bits - 1 byte - do arquivo f */

void one_field(FILE *f, unsigned char byte);
/* print na tela um campo da estrutura */

void one_struct(FILE *f);
/* print na tela uma estrutura */

long one_num(FILE *f);
/* retorna o numero guardado no par chave-valor */

unsigned long one_num_byte(unsigned char byte, int n);
/* retorna a porcao varint de um byte */


int decode (FILE *f)
{
    int i=1;

	if(f == NULL)
	{
		printf("Erro na leitura do arquivo. \n");       /* retorna -1 caso n‹o leia arquivo */
		return -1;
	}

	while(get_next(f) == 0xFF)							/*	enquanto ainda h‡ marca FF no arquivo*/
	{
		printf("----------------------\nEstrutura %d\n",i);
		one_struct(f);
		i++;
	}							

	return 0;
}

void one_struct(FILE *f)
{
    unsigned char c;
    
    c = get_next(f);
    
    while(c & 0x80)                             /* confere se é o ultimo campo */
    {
        one_field(f,c);
        c = get_next(f);
    }
    
    one_field(f,c);								/* processa ultimo campo */
}

void one_field(FILE *f, unsigned char byte)
{

    if(byte & 0x02)                             /*confere se penultimo bit e' 1 */
        printf("<long>");
    else
        printf("<int>");
	
	printf(" %ld\n",one_num(f));

	return;
}

long one_num(FILE *f)
{
    unsigned char byte;
    unsigned long numu = 0;
    long nums;
    int i;
    
    
    for(i=0,byte = get_next(f); byte & 0x80 ; i++,byte = get_next(f)) /* vai de byte a byte do valor conferindo se 'e o ultimo*/
        numu = numu + one_num_byte(byte, i);
    
    numu = numu + one_num_byte(byte, i);                /* adiciona o valor do ultimo */
    
    nums = numu >>  1;
    if (numu & 0x01)                                     /* dado como dica no enunciado */
        nums = ~nums;
    
    return nums;
}

unsigned long one_num_byte(unsigned char byte, int n)
{
    unsigned long num;
    
    num = byte & 0x7F;                                  /* seta o bit mais a esquerda a 0 */
    
    num = num << 7*n;                                   /* da shift para a esquerda o num de significancia do byte */
    
    return num;
}


unsigned char get_next(FILE *f)
{
    unsigned char c;
    
    fread(&c,1,1,f);
    
    return c;
}
