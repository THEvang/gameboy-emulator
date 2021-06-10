#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Memory/Memory_Controller.h"

#ifdef __cplusplus
extern "C" {
#endif


int window_tile_select(MemoryBankController* mc);
bool background_tile_map_select(MemoryBankController* mc);
bool sprite_size(MemoryBankController* mc);

bool tile_data_signed(MemoryBankController* mc);
uint16_t tile_data_start_address(MemoryBankController* mc);

uint16_t background_tile_map_start_address(MemoryBankController* mc);
uint16_t window_tile_map_start_address(MemoryBankController* mc);

bool lcd_display_enabled(MemoryBankController* mc);
bool window_display_enabled(MemoryBankController* mc);
bool background_display_enabled(MemoryBankController* mc);
bool sprite_display_eanbled(MemoryBankController* mc);

#ifdef __cplusplus
}
#endif