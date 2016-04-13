#include <stdio.h>
#include "code.h"
#include "decode.h"

int main (void){

	FILE *input, *output;
    int i;
    unsigned char vet[11] = {0xFF,0x81,0x02,0x81,0x01,0x82,0x80,0x04,0x02,0xff,0x03};
    
    output = fopen("/Users/victorpinto/Desktop/inf1018-trabalho1/arquivoteste.bin","wb");
    fwrite(vet,1,11,output);
    fclose(output);

	input = fopen("/Users/victorpinto/Desktop/inf1018-trabalho1/arquivoteste.bin","rb");

	i=decode(input);

    fclose(input);
    
	return 0;
}