#include "Graphics/LCD_Control.h"
#include "Memory/Memory_Controller.h"
#include "Registers.h"

bool gb_tile_data_signed(MemoryBankController* mc) {
    return !(mc->memory[LCDC] & TILE_DATA_SELECT);
}

uint16_t gb_tile_data_start_address(MemoryBankController* mc) {
    return mc->memory[LCDC] & TILE_DATA_SELECT ?  0x8000 : 0x9000;
}

uint16_t gb_background_tile_map_start_address(MemoryBankController* mc) {
    return mc->memory[LCDC] & BACKGROUND_TILE_MAP ? 0x9C00 : 0x9800;
}

uint16_t gb_window_tile_map_start_address(MemoryBankController* mc) {
    return mc->memory[LCDC] & WINDOW_TILEMAP_SELECT ?  0x9C00 : 0x9800;
}

bool gb_sprite_size(MemoryBankController* mc) {
    return mc->memory[LCDC] & SPRITE_SIZE;
}