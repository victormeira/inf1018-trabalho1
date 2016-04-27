/* Victor Meira Pinto 1420626 3WB */
/* José Paulo Diniz   1510910 3WB */

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "code.h"
#define MAX ((sizeof(long)*8)/7+1)

typedef union value {
	int vInt;
	long vLong;
} tpValue;

void codeValue(char *desc, int inx, void *v, FILE *f);

void printValue(char type, long value, FILE *f);

int numBits (long value);

int decode (FILE *f);
/* decodifica estruturas guardados no arquivo f*/

unsigned char get_next(FILE *f);
/* retorna prox 8 bits - 1 byte - do arquivo f */

void one_field(FILE *f, unsigned char byte);
/* print na tela um campo da estrutura */

long one_num(FILE *f);
/* retorna o numero guardado no par chave-valor */

int code (char* desc, void* v, FILE* f)
{
	int num_fields = strlen(desc),
		i=0; /* i <= fields coded */
	unsigned char key, firstByte = 0xFF;
	char *pVal;

	pVal = (char*)v; /* pointer to the first element of the struct */

	if (f == NULL) {
		printf("Erro ao escrever no arquivo.\n");
		return -1;
	}

	fwrite(&firstByte, 1, 1, f); /*first byte is always FF*/

	for (; i != num_fields; i++) {
		key = 0;

		if (i < (num_fields - 1))
			key = key | 0x80;	/* most left key bit indicates if it is the last field (Y=0, N=1) */

		if (desc[i] == 'i')
			key = key | 0x01;
		else if (desc[i] == 'l')
			key = key | 0x02;

		fwrite(&key, 1, 1, f);

		codeValue(desc, i, &pVal, f);
	}

	return 0;
}

void codeValue(char *desc, int inx, void *v, FILE *f) {
	int j, intBeforeLong = 0;
	char *pVal;
	tpValue val;

	pVal = *(char**)v;

	if (desc[inx] == 'l') {
		for (j=inx-1; j>=0 && desc[j]!='l'; j--)
			intBeforeLong++;
		if (intBeforeLong % 2 != 0){
			pVal += 4;
		}
		val.vLong = *(signed long*)pVal;
		printValue('l', val.vLong, f);
	}
	else if (desc[inx] == 'i') {
		val.vInt = *(signed int*)pVal;
		printValue('i', val.vInt, f);
	}

	if (desc[inx] == 'i')		/* deferencing v to the end of the field */
		pVal += 4;
	else if (desc[inx] == 'l')
		pVal += 8;
	*(void **)v = pVal;
}

void printValue(char type, long value, FILE *f) {
  unsigned long val;
  int i=0;
  unsigned char codedValue[MAX];

  val = value << 1;
  if (value < 0)
    val = ~val;

  do {
    codedValue[i] = val | 0x80;
    val >>= 7;
    i++;
  } while (val);

  codedValue[i-1] &= 0x7f;

  fwrite(codedValue, 1, i, f);
}

int numBits (long value) {
	int num = 64;
	long lastBit = 0x8000000000000000;
	long val = value;

	for (; (num >= 0)&&!(val & lastBit); num--)
		val <<= 1;

	return num;
}

int decode (FILE *f)
{
    int i=1;
    unsigned char c;

	if(f == NULL)
	{
		printf("Erro na leitura do arquivo. \n");       /* retorna -1 caso não leia arquivo */
		return -1;
	}

	while(get_next(f) == 0xFF)							/*	enquanto ainda há marca FF no arquivo*/
	{
		printf("----------------------\nEstrutura %d\n",i);

    	c = get_next(f);
    
   		while(c & 0x80)                             /* confere se é o ultimo campo */
    	{
        	one_field(f,c);
        	c = get_next(f);
   		}
    	one_field(f,c);		
		i++;
	}							

	return 0;
}

void one_field(FILE *f, unsigned char byte)
{

    if(byte & 0x02)                             /*confere se penultimo bit é 1 */
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
    int i = 0;

    do {
     byte = get_next(f);
     numu |= ((unsigned long)(byte & 0x7f)) << (7 * i);
     i++;
    } while (byte & 0x80);

    nums = numu >>  1;
    if (numu & 0x01)                                     /* dado como dica no enunciado */
        nums = ~nums;

    return nums;
}

unsigned char get_next(FILE *f)
{
    unsigned char c;
    
    fread(&c,1,1,f);
    //c = (unsigned char) fgetc(f);
    
    return c;
}