#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#include "code.h"
#include "decode.h"

typedef struct teste1 {
	int i1;
	int i2;
	long long l1;
	long long l2;
} tpteste1;

typedef struct teste2 {
	int i1;
	long long l1;
	int i2;
	int i3;
	long long l2;
	long long l3;
} tpteste2;

int main (void){

	FILE *input;
	FILE *output;
	int i, j;
	tpteste1 t1 = {1, -1, 256, -256};
	tpteste2 t2 = {-1, -1, 0, 397, 0, 429}; 

	output = fopen("arquivoteste.bin","wb");
	if (output == NULL) {
		printf("Erro ao criar arquivo\n");
		return -1;
	}

	i = code("iill", &t1, output);
	j = code("iliill", &t2, output);
	if (i != 0)
		return i;
	if (j != 0)
		return j;

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