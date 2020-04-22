#include "graphics/LCD_Control.h"
#include "BitOperations.h"

LCD_Control::LCD_Control(MemoryBankController* memory_controller)
    : m_memory_controller(memory_controller)
{
}

bool LCD_Control::lcd_display_enabled() const
{
    const auto status = m_memory_controller->read(control_address);
    return is_set(status, 7);
}

bool LCD_Control::background_display_enabled() const
{
    const auto status = m_memory_controller->read(control_address);
    return is_set(status, 0);
}

bool LCD_Control::sprite_display_eanbled() const
{
    const auto status = m_memory_controller->read(control_address);
    return is_set(status, 1);
}

bool LCD_Control::background_tile_map_select() const
{
    const auto status = m_memory_controller->read(control_address);
    return is_set(status, 3);
}

bool LCD_Control::tile_data_signed() const 
{
    const auto status = m_memory_controller->read(control_address);
    return is_set(status, 4);
}

uint16_t LCD_Control::tile_data_start_address() const {
    const auto status = m_memory_controller->read(control_address);
    return is_set(status, 4) ? 0x8000 : 0x8800;
}

uint16_t LCD_Control::tile_map_start_address() const {
    const auto status = m_memory_controller->read(control_address);
    return is_set(status, 3) ? 0x9C00 : 0x9800;
}

uint16_t LCD_Control::window_tile_map_start_address() const {
    const auto status = m_memory_controller->read(control_address);
    return is_set(status, 6) ? 0x9C00 : 0x9800;
}