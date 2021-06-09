#include "Graphics/LCD_Control.hpp"

#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.hpp"

LCD_Control::LCD_Control(MemoryBankController* memory_controller)
    : m_memory_controller(memory_controller)
{
}

bool LCD_Control::lcd_display_enabled() const
{
    const auto status = read(m_memory_controller, control_address);
    return test_bit_8bit(status, lcd_enabled_bit);
}

bool LCD_Control::background_display_enabled() const
{
    const auto status = read(m_memory_controller, control_address);
    return test_bit_8bit(status, background_display_bit);
}

bool LCD_Control::sprite_display_eanbled() const
{
    const auto status = read(m_memory_controller, control_address);
    return test_bit_8bit(status, sprite_enable_bit);
}

bool LCD_Control::background_tile_map_select() const
{
    const auto status = read(m_memory_controller, control_address);
    return test_bit_8bit(status, background_tile_map_select_bit);
}

bool LCD_Control::tile_data_signed() const 
{
    const auto status = read(m_memory_controller, control_address);
    return !test_bit_8bit(status, background_tile_data_select_bit);
}

uint16_t LCD_Control::tile_data_start_address() const {
    const auto status = read(m_memory_controller, control_address);
    return test_bit_8bit(status, background_tile_data_select_bit) ? 0x8000 : 0x8800;
}

uint16_t LCD_Control::background_tile_map_start_address() const {
    const auto status = read(m_memory_controller, control_address);
    return test_bit_8bit(status, background_tile_map_select_bit) ? 0x9C00 : 0x9800;
}

uint16_t LCD_Control::window_tile_map_start_address() const {
    const auto status = read(m_memory_controller, control_address);
    return test_bit_8bit(status, window_tile_map_select_bit) ? 0x9C00 : 0x9800;
}

bool LCD_Control::window_display_enabled() const {
    const auto status = read(m_memory_controller, control_address);
    return test_bit_8bit(status, window_display_enable_bit);
}

bool LCD_Control::sprite_size() const {
    const auto status = read(m_memory_controller, control_address);
    return test_bit_8bit(status, sprite_size_bit);
}