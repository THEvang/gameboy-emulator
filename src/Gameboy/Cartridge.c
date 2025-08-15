#include "Cartridge.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define TITLE_START 0x0134
#define LOGO_START 0x0104
#define COLOR_GAMEBOY_FLAG 0x0143
#define SUPER_GAMEBOY_SUPPORT 0x0146
#define MEMORY_BANK_ADDRESS 0x0147
#define ROM_SIZE_ADDRESS 0x0148
#define RAM_SIZE_ADDRESS 0x0149
#define DESTINATION_CODE_ADDRESS 0x14A
#define VERSION_ADDRESS 0x14C
#define HEADER_CHECKSUM_ADDRESS 0x14D
#define GLOBAL_CHECKSUM_ADDRESS

long file_size(FILE* file) {

    long size = -1L;
    if (fseek(file, 0, SEEK_END) == 0) {
        size = ftell(file);
        fseek(file, 0, SEEK_SET);
    }

    return size;
}

int gb_load_rom(GameboyRom* rom, const char* path) {

    FILE* rom_file = fopen(path, "r");
    if(!rom_file) {
        printf("ERROR\tOpening file\t%s\n", strerror(errno));
        return -1;
    }

    
    rom->size = file_size(rom_file);
    if (rom->size < 0) {
        return -1;
    }

    rom->data = malloc(rom->size * sizeof(uint8_t));
    fread(rom->data, sizeof(uint8_t), rom->size, rom_file);

    return fclose(rom_file);
}

void gb_parse_header(GameboyRom* rom, CartridgeHeader* header) {

    //Logo
    memcpy(&header->logo[0], &rom->data[LOGO_START], sizeof(uint8_t) * LOGO_SIZE);
    
    //Title
    memcpy(&header->title[0], &rom->data[TITLE_START], sizeof(uint8_t) * TITLE_SIZE);
    header->title[TITLE_SIZE] = '\0';

    //TODO: 0x80 is multi-platform 0xC0 is color gameboy only. What if
    //it contains something else?
    header->color_gameboy_only = rom->data[COLOR_GAMEBOY_FLAG] == 0xC0;

    header->super_gameboy_support = rom->data[SUPER_GAMEBOY_SUPPORT] == 0x03;

    //Cartridge Type
    switch(rom->data[MEMORY_BANK_ADDRESS]) {
        case 0x00: case 0x08: case 0x09:
            header->type = MB_ROM_ONLY;
            break;
        case 0x01: case 0x02: case 0x03:
            header->type = MB_MBC_1;
            break;
        case 0x05: case 0x06:
            header->type = MB_MBC_2;
            break;
        case 0x0B: case 0x0C: case 0x0D:
            header->type = MB_MM01;
            break;
        case 0x0F: case 0x10: case 0x11: case 0x12: case 0x13:
            header->type = MB_MBC_3;
            break;
        case 0x19: case 0x1A: case 0x1B: case 0x1C: case 0x1D: case 0x1E:
            header->type = MB_MBC_5;
            break;
        case 0x20:
            header->type = MB_MBC_6;
            break;
        case 0x22:
            header->type = MB_MBC_7;
            break;
        case 0xFC:
            header->type = MB_POCKET_CAMERA;
            break;
        case 0xFD:
            header->type = MB_BANDAI_TAMA5;
            break;
        default:
            header->type = MB_UNKNOWN;
            break;
    }
    
    //TODO: There are some sizes that are non-standard
    header->rom_size = 32 << rom->data[ROM_SIZE_ADDRESS];
    header->rom_banks = header->rom_size / 16;

    //TODO: What if we get something bigger than 0x05
    switch(rom->data[RAM_SIZE_ADDRESS]) {
        case 0x05:
            header->ram_size = 64;
            break;
        case 0x04:
            header->ram_size = 128;
            break;
        case 0x03:
            header->ram_size = 32;
            break;
        case 0x02:
            header->ram_size = 8;
            break;
        case 0x00: case 0x01:
        default:
            header->ram_size = 0;
            break;
    }
    header->ram_banks = header->ram_size / 8;
    
    header->destination = rom->data[DESTINATION_CODE_ADDRESS] == 0x00 ? DST_JAPAN : DST_WORLD;

    header->version = rom->data[VERSION_ADDRESS];

    header->header_checksum = rom->data[HEADER_CHECKSUM_ADDRESS];
    header->global_checksum = (uint16_t) (rom->data[HEADER_CHECKSUM_ADDRESS] << 8 | rom->data[HEADER_CHECKSUM_ADDRESS + 1]);
}
