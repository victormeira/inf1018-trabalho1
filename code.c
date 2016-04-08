/* Victor Meira Pinto 1420626 3WB */
/* José Paulo Diniz   1510XXX 3WB */


#include "code.h"
#define BYTE 8

int code (char* desc, void* v, FILE* f)
{
	/*esta funcao codifica o blablabla*/
}

/* Funcao 
fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
escreve a string ptr no arquivo
stream com nmemb elementos de tamanho size 

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) */

void one_field(FILE *f)
{
	int i, num;

	for(i=0;i<6;i++)
		c=fgetc(f);							/*passa os 5 bits 0 da chave */

	if(fgetc(f)==0)							/*confere se é long ou int e imprime */
		printf("<int>");
	else
		printf("<long>");

	while(fgetc(f)==1)						/*confere se é ultimo byte */
	{						
		for(i=0;i<BYTE-1;i++,mult++)
		{
				/*implementar sabendo que inteiro tem que ser transformado com sinal */
		}
	}

	for(i=0;i<BYTE-1;i++,mult++) 			/* Processa ultimo byte */
	{
				/*implementar sabendo que inteiro tem que ser transformado com sinal */
	}

	printf("%d",num);
	printf("\n");

	return;
}

void one_struct(FILE *f)
{
	int i, c, exp=0, num=0;

	for(i=0;i<BYTE-1;i++)
		c=fgetc(f);								/* acaba de ler a marca FF da estrutura */

	while(fgetc(f)==1)							/*confere se é o ultimo campo */
		one_field(f);

	one_field(f);								/* processa ultimo campo */
}

int decode (FILE *f)
{
	int i, c;

	if(f == NULL)
	{
		printf("Erro na leitura do arquivo"); 	/* retorna -1 caso não leia arquivo */
		return -1;
	}

	while(fgetc(f)==1)
	{
		printf("----------------------");
		one_struct(f);							/*	enquanto ainda é puxado bit valor 1 do arquivo		*/
												/*	processa uma estrutura escrevendo linha separadora	*/
	}

	return 0;
}
