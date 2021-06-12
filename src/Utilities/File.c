#include "File.h"

#include <stdio.h>
#include <stdlib.h>

void load_rom(gb_Rom* rom, const char* path) {

    FILE* rom_file;
    rom_file = fopen(path, "r");
    if(!rom_file) {
        rom->data = NULL;
        return;
    }

    fseek(rom_file, 0, SEEK_END);
    rom->size = ftell(rom_file);
    fseek(rom_file, 0, SEEK_SET);

    rom->data = malloc(rom->size * sizeof(uint8_t));
    fread(rom->data, sizeof(uint8_t), rom->size, rom_file);

    fclose(rom_file);
}