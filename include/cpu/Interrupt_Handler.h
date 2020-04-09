#pragma once 

#include "memory_controllers/MemoryBankController.h"
#include "cpu/Cpu.h"

enum class Interrupts {
    V_Blank = 0,
    LCD_STAT,
    Timer,
    Serial,
    Joypad
};

class Interrupt_Handler {
public: 

    explicit Interrupt_Handler(MemoryBankController*);

    int interrupts(Cpu& cpu);

    void request_v_blank_interrupt();
    void request_lcd_stat_interrupt();
    void request_timer_interrupt();
    void request_serial_interrupt();
    void request_joypad_interrupt();

    bool should_exit_halt();

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
    bool timer_interrupt_enabled() const;
    bool serial_interrupt_enabled() const;
    bool joypad_interrupt_enabled() const;

    void call(Cpu& cpu, int interrupt_vector);

    static const uint16_t interrupt_request_address = 0xFF0F;
    static const uint16_t interrupt_enabled_address = 0xFFFF;

    static const uint8_t v_blank_vector = 0x40;
    static const uint8_t lcd_stat_vector = 0x48;
    static const uint8_t timer_vector = 0x50;
    static const uint8_t serial_vector = 0x58;
    static const uint8_t joypad_vector = 0x60;

    MemoryBankController* m_memory_bank_controller;
};