#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif
#include "code.h"


typedef struct teste1 {
	int i1;
	int i2;
	long l1;
	long l2;
} tpteste1;

typedef struct teste2 {
	int i1;
	long l1;
	int i2;
	int i3;
	long l2;
	long l3;
} tpteste2;

typedef struct teste3 {
    int i1;
    long l1;
    int i2;
    long l2;
    int  i3;
    long l3;
} tpteste3;

int main (void){

	FILE *input;
	FILE *output;
	int i, j, k;
	tpteste1 t1 = {1, -1, 256, -256};
	tpteste2 t2 = {-1, -1, 0, 397, 0, 429};
    tpteste3 t3 = {-2147483648, -9223372036854775808, 2147483647, 9223372036854775807, -46387, 498569};

	output = fopen("arquivoteste.bin","wb");
	if (output == NULL) {
		printf("Erro ao criar arquivo\n");
		return -1;
	}

	i = code("iill", &t1, output);
	j = code("iliill", &t2, output);
    k = code("ililil",&t3, output);
    
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