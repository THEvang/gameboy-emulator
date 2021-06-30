#include "Graphics/LCD_Control.h"

#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"

static const uint16_t g_lcd_control_address = 0xFF40;

bool lcd_display_enabled(MemoryBankController* mc) {
    
    const uint8_t status = gb_read(mc, g_lcd_control_address);
    
    const int lcd_enabled_bit = 7;
    return test_bit_8bit(status, lcd_enabled_bit);
}

bool background_display_enabled(MemoryBankController* mc) {
    const uint8_t status = gb_read(mc, g_lcd_control_address);

    const int background_display_bit = 0;
    return test_bit_8bit(status, background_display_bit);
}

bool sprite_display_enabled(MemoryBankController* mc) {
    const uint8_t status = gb_read(mc, g_lcd_control_address);

    const int sprite_enable_bit = 1;
    return test_bit_8bit(status, sprite_enable_bit);
}

bool window_display_enabled(MemoryBankController* mc) {
    const uint8_t status = gb_read(mc, g_lcd_control_address);

    const int window_display_enable_bit = 5;
    return test_bit_8bit(status, window_display_enable_bit);
}

bool background_tile_map_select(MemoryBankController* mc) {
    const uint8_t status = gb_read(mc, g_lcd_control_address);

    const int background_tile_map_select_bit = 3;
    return test_bit_8bit(status, background_tile_map_select_bit);
}

bool tile_data_signed(MemoryBankController* mc) {

    const uint8_t status = gb_read(mc, g_lcd_control_address);

    const int background_tile_data_select_bit = 4;
    return !test_bit_8bit(status, background_tile_data_select_bit);
}

uint16_t tile_data_start_address(MemoryBankController* mc) {

    const uint8_t status = gb_read(mc, g_lcd_control_address);

    const int background_tile_data_select_bit = 4;
    return test_bit_8bit(status, background_tile_data_select_bit) ? 0x8000 : 0x9000;
}

uint16_t background_tile_map_start_address(MemoryBankController* mc) {
    const uint8_t status = gb_read(mc, g_lcd_control_address);

    const int background_tile_map_select_bit = 3;
    return test_bit_8bit(status, background_tile_map_select_bit) ? 0x9C00 : 0x9800;
}

uint16_t window_tile_map_start_address(MemoryBankController* mc) {
    const uint8_t status = gb_read(mc, g_lcd_control_address);

    const int window_tile_map_select_bit = 6;
    return test_bit_8bit(status, window_tile_map_select_bit) ? 0x9C00 : 0x9800;
}

bool sprite_size(MemoryBankController* mc) {
    const uint8_t status = gb_read(mc, g_lcd_control_address);

    const int sprite_size_bit = 2;
    return test_bit_8bit(status, sprite_size_bit);
}
