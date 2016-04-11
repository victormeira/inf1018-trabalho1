#include <string.h>
#include "code.h"

int code (char* desc, void* v, FILE* f)
{
	int num_fields = strlen(desc),
		i=0; /* i <= fields coded */

	char key;

	if (f == NULL) {
		printf("Erro ao escrever no arquivo.\n");
		return -1;
	}

	fprintf(f, "%x ", 0xFF); /*first byte is always FF*/

	for (; i != num_fields; i++) {
		key = 0;

		if (i < (num_fields - 1))
			key = key | 0x80;	/* first key bit indicates if it is the last field (Y=0, N=1) */

		if (desc[i] = 'i')
			key = key | 0x01;
		else if (desc[i] = 'l')
			key = key | 0x10;

		/* code to value will be here */

		fprintf(f, "%x ", key);

		if (i = num_fields - 1)
			fprintf(f, "\n");
	}

	return 0;
}
