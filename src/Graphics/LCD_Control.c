#include "Graphics/LCD_Control.h"

#include "Memory/Memory_Controller.h"

static const uint16_t g_lcd_control_address = 0xFF40;

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

bool gb_lcd_display_enabled(MemoryBankController* mc) {
    return mc->memory[g_lcd_control_address] & LCD_ENABLED;
}

bool gb_background_display_enabled(MemoryBankController* mc) {
    return mc->memory[g_lcd_control_address] & BACKGROUND_DISPLAY;
}

bool gb_sprite_display_enabled(MemoryBankController* mc) {
    return mc->memory[g_lcd_control_address] & SPRITE_DISPLAY;
}

bool gb_window_display_enabled(MemoryBankController* mc) {
    return mc->memory[g_lcd_control_address] & WINDOW_DISPLAY_ENABLE;
}

bool gb_background_tile_map_select(MemoryBankController* mc) {
    return mc->memory[g_lcd_control_address] & BACKGROUND_TILE_MAP;
}

bool gb_tile_data_signed(MemoryBankController* mc) {
    return !(mc->memory[g_lcd_control_address] & TILE_DATA_SELECT);
}

uint16_t gb_tile_data_start_address(MemoryBankController* mc) {
    return mc->memory[g_lcd_control_address] & TILE_DATA_SELECT ?  0x8000 : 0x9000;
}

uint16_t gb_background_tile_map_start_address(MemoryBankController* mc) {
    return mc->memory[g_lcd_control_address] & BACKGROUND_TILE_MAP ? 0x9C00 : 0x9800;
}

uint16_t gb_window_tile_map_start_address(MemoryBankController* mc) {
    return mc->memory[g_lcd_control_address] & WINDOW_TILEMAP_SELECT ?  0x9C00 : 0x9800;
}

bool gb_sprite_size(MemoryBankController* mc) {
    return mc->memory[g_lcd_control_address] & SPRITE_SIZE;
}