#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "Utilities/File.h"

typedef enum Catridge_Type {
    MB_ROM_ONLY,
    MB_MBC_1,
    MB_MBC_2,
    MB_MBC_3,
    MB_MBC_5,
    MB_MBC_6,
    MB_MBC_7,
    MB_MM01,
    MB_HUC1,
    MB_HUC3,
    MB_POCKET_CAMERA,
    MB_UNKNOWN,
    MB_BANDAI_TAMA5
} Cartridge_Type;

typedef enum DestinationCode {
    DST_JAPAN,
    DST_WORLD
} DestinationCode;

#define TITLE_SIZE 16
#define LOGO_SIZE 48

typedef struct CartridgeHeader {
    char title[TITLE_SIZE + 1];
    uint8_t logo[LOGO_SIZE];
    bool color_gameboy_only;
    bool super_gameboy_support;
    Cartridge_Type type;
    int rom_size;
    int ram_size;
    DestinationCode destination;
    uint8_t version;
    uint8_t header_checksum;
    uint16_t global_checksum;
} CartridgeHeader;

void gb_parse_header(gb_Rom* rom, CartridgeHeader* header);
void gb_print_header(CartridgeHeader* header);