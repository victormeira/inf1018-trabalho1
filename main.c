#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif
#include "code.h"
#include <limits.h>


typedef struct teste1 {
	int i1;
} tpteste1;

typedef struct teste2 {
	long l1;
} tpteste2;

typedef struct teste3 {
    int i1;
    long l1;
    int i2;
    long l2;
} tpteste3;

int main (void){

	FILE *input;
	FILE *output;
	int i, j, k;
	tpteste1 t1 = {0};
	tpteste2 t2 = {0};
    tpteste3 t3 = {INT_MIN,LONG_MIN, INT_MAX, LONG_MAX};

	output = fopen("arquivoteste.bin","wb");
	if (output == NULL) {
		printf("Erro ao criar arquivo\n");
		return -1;
	}

	i = code("i", &t1, output);
	j = code("l", &t2, output);
    k = code("ilil",&t3, output);
    
	if (i != 0)
		return i;
	if (j != 0)
		return j;
    if (k != 0)
        return k;

	fclose(output);
    
	input = fopen("arquivoteste.bin", "rb");
	if (input == NULL) {
		printf("Erro ao abrir arquivo\n");
		return -1;
	}
    
	i=decode(input);

	if (i != 0)
		return i;

    fclose(input);
    
	return 0;
}