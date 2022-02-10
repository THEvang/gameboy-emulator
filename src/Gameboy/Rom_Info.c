#include "Rom_Info.h"

#include <stdio.h>
#include <string.h>

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

void gb_parse_header(gb_Rom* rom, CartridgeHeader* header) {

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
    
    header->destination = rom->data[DESTINATION_CODE_ADDRESS] == 0x00 ? DST_JAPAN : DST_WORLD;

    header->version = rom->data[VERSION_ADDRESS];

    header->header_checksum = rom->data[HEADER_CHECKSUM_ADDRESS];
    header->global_checksum = (uint16_t) (rom->data[HEADER_CHECKSUM_ADDRESS] << 8 | rom->data[HEADER_CHECKSUM_ADDRESS + 1]);
}

void gb_print_header(CartridgeHeader* header) {

    printf("%s\n", header->title);

    header->color_gameboy_only ? printf("COLOR GAMEBOY SUPPORT: Color Gameboy Only\n")
        : printf("COLOR GAMEBOY SUPPORT: Gameboy and Color Gameboy\n");

    header->super_gameboy_support ? printf("SUPER GAMEBOY SUPPORT: Yes\n")
        : printf("SUPER GAMEBOY SUPPORT: No\n");

    printf("CARTRIDGE TYPE: ");
    switch (header->type) {
        case MB_ROM_ONLY:
            printf("Rom\n");
            break;
        case MB_MBC_1:
            printf("MBC 1\n");
            break;
        case MB_MBC_2:
            printf("MBC 2\n");
            break;
        case MB_MBC_3:
            printf("MBC_3\n");
            break;
        case MB_MBC_5:
            printf("MBC 5\n");
            break;
        case MB_MBC_6:
            printf("MBC 6\n");
            break;
        case MB_MBC_7:
            printf("MBC 7\n");
            break;
        case MB_MM01:
            printf("MM01\n");
            break;
        case MB_HUC1:
            printf("HuC 1\n");
            break;
        case MB_HUC3:
            printf("HuC 3\n");
            break;
        case MB_POCKET_CAMERA:
            printf("Pocket Camera\n");
            break;
        case MB_BANDAI_TAMA5:
            printf("Bandai Tama 5\n");
            break;
        case MB_UNKNOWN:
        default:
            printf("Unknow\n");
            break;
    }

    printf("ROM SIZE: %dKByte\n", header->rom_size);
    printf("RAM SIZE: %dKByte\n", header->ram_size);
    
    printf("DESTINATION: ");
    header->destination == DST_JAPAN ? printf("Japan") : printf("World");
    printf("\n");
}