#pragma once
#include "memory_controllers/MemoryBankController.h"

class LCD_Control {
public:

    explicit LCD_Control(MemoryBankController* memory_controller);

    bool lcd_display_enabled() const;
    bool window_display_enabled() const;
    bool background_display_enabled() const;
    bool sprite_display_eanbled() const;

    int window_tile_select() const;
    bool background_tile_map_select() const;
    bool sprite_size() const;

    bool tile_data_signed() const;
    uint16_t tile_data_start_address() const;
    
    uint16_t background_tile_map_start_address() const;
    uint16_t window_tile_map_start_address() const;

private:

    static const int lcd_enabled_bit = 7;
    static const int window_tile_map_select_bit = 6;
    static const int window_display_enable_bit = 5;
    static const int background_tile_data_select_bit = 4;
    static const int background_tile_map_select_bit = 3;
    static const int sprite_size_bit = 2;
    static const int sprite_enable_bit = 1;
    static const int background_display_bit = 0;


    const uint16_t control_address = 0xFF40;
    MemoryBankController* m_memory_controller;
};