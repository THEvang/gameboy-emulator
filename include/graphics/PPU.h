#pragma once
#include "graphics/LCD_Status.h"
#include "cpu/Interrupt_Handler.h"
#include "memory_controllers/MBC1.h"

class PPU {
public:
    PPU(MemoryBankController* memory_controller);

    void step(int cycles);

    auto screen() {
        return m_screen;
    }

private:

    void draw_scanline();
    void draw_background();
    void draw_sprites();

    const static int scanline_address = 0xFF44;

    MemoryBankController* m_memory_controller;

    Interrupt_Handler m_interrupt_handler;
    LCD_Control m_lcd_control;
    LCD_Status m_lcd_status;
    
    int m_scanline_counter = 0;

    int m_screen[160][144];
};