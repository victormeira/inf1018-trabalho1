#include <stdio.h>
#include <stdlib.h>
#include "code.h"
#include "decode.h"

int main (void){

	FILE *input;
	int i;

	input = fopen("arquivoteste.txt","rb");

	i=decode(input);

    fclose(input);
    
	return 0;
}