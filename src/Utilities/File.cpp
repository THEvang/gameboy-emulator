#include "Utilities/File.hpp"

#include <stdio.h>
#include <stdlib.h>

void load_rom(gb_Rom* rom, const char* path) {

    FILE* rom_file;
    rom_file = fopen(path, "r");
    if(!rom_file) {
        rom->data = nullptr;
        return;
    }

    fseek(rom_file, 0, SEEK_END);
    rom->size = ftell(rom_file);
    fseek(rom_file, 0, SEEK_SET);

    rom->data = (uint8_t*) malloc(rom->size);
    fread(rom->data, 1, rom->size, rom_file);

    fclose(rom_file);
}