#include "graphics/LCD_Control.h"
#include "BitOperations.h"

LCD_Control::LCD_Control(MemoryBankController* memory_controller) 
    : m_memory_controller(memory_controller)
{

}

bool LCD_Control::lcd_display_enabled() {
    const auto status = m_memory_controller->read(control_address);
    return is_set(status, 7);
}