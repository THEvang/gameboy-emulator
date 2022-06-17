#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


#define ROM_START 0x0100

int
main(int argc, char* argv[]) {
	
	if (argc < 2) {
		printf("usage: %s rom\n", argv[0]);
		return 1;
	}

	FILE* rom = fopen(argv[1], "r");

	if (rom == NULL) {
		fprintf(stderr, "%s %s\n", argv[1], strerror(errno));
		return 1;
	}


	fseek(rom, 0L, SEEK_END);
	long int size = ftell(rom);
	fseek(rom, 0L, SEEK_SET);

	uint8_t* data = malloc(size);
	
	size_t n_read = fread(data, 1, size, rom);

	int pos = ROM_START;
	
	while (pos < size) {
		uint8_t opcode = data[pos];
		#include "generated.h"
	}


	return 0;
}
