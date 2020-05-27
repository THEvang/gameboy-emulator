#pragma once 

#include <cstdint>

class Cpu;
class MemoryBankController;

enum class Interrupts {
    V_Blank = 0,
    LCD_STAT,
    Timer,
    Serial,
    Joypad
};

class Interrupt_Handler {
public: 

    explicit Interrupt_Handler(MemoryBankController* memory_controller);

    int interrupts(Cpu& cpu);

    void request_v_blank_interrupt();
    void request_lcd_stat_interrupt();
    void request_timer_interrupt();
    void request_serial_interrupt();
    void request_joypad_interrupt();

    bool should_exit_halt();
    bool timer_interrupt_enabled() const;

private:

    void clear_v_blank_request();
    void clear_lcd_stat_request();
    void clear_timer_request();
    void clear_serial_request();
    void clear_joypad_request();

    bool v_blank_interrupt_requested() const;
    bool lcd_stat_interrupt_requested() const;
    bool timer_interrupt_requested() const;
    bool serial_interrupt_requested() const;
    bool joypad_interrupt_requested() const;

    bool v_blank_interrupt_enabled() const;
    bool lcd_stat_interrupt_enabled() const;
    bool serial_interrupt_enabled() const;
    bool joypad_interrupt_enabled() const;

    void call(Cpu& cpu, uint8_t interrupt_vector);  
    
    const uint16_t interrupt_request_address = 0xFF0F;
    const uint16_t interrupt_enabled_address = 0xFFFF;

    const int v_blank_interrupt_bit = 0;
    const int lcd_interrupt_bit = 1;
    const int timer_interrupt_bit = 2;
    const int joypad_interrupt_bit = 3;

    MemoryBankController* m_memory_bank_controller;
};