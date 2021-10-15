#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Memory/Memory_Controller.h"

bool gb_background_tile_map_select(MemoryBankController* mc);
bool gb_sprite_size(MemoryBankController* mc);

bool gb_tile_data_signed(MemoryBankController* mc);
uint16_t gb_tile_data_start_address(MemoryBankController* mc);

uint16_t gb_background_tile_map_start_address(MemoryBankController* mc);
uint16_t gb_window_tile_map_start_address(MemoryBankController* mc);

bool gb_lcd_display_enabled(MemoryBankController* mc);
bool gb_window_display_enabled(MemoryBankController* mc);
bool gb_background_display_enabled(MemoryBankController* mc);
bool gb_sprite_display_enabled(MemoryBankController* mc);