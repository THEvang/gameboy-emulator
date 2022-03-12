#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Memory/Memory_Controller.h"

enum {
    BACKGROUND_DISPLAY = 1 << 0,
    SPRITE_DISPLAY = 1 << 1,
    SPRITE_SIZE = 1 << 2,
    BACKGROUND_TILE_MAP = 1 << 3,
    TILE_DATA_SELECT = 1 << 4,
    WINDOW_DISPLAY_ENABLE = 1 << 5,
    WINDOW_TILEMAP_SELECT = 1 << 6,
    LCD_ENABLED = 1 << 7
};

bool gb_sprite_size(MemoryBankController* mc);
bool gb_tile_data_signed(MemoryBankController* mc);
uint16_t gb_tile_data_start_address(MemoryBankController* mc);

uint16_t gb_background_tile_map_start_address(MemoryBankController* mc);
uint16_t gb_window_tile_map_start_address(MemoryBankController* mc);