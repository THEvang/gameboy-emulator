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

    void request(Interrupts interrupt);

    bool should_exit_halt();
    bool timer_interrupt_enabled() const;

private:

    void clear(Interrupts interrupt);
    bool is_requested(Interrupts interrupt) const;
    bool is_enabled(Interrupts interrupt) const;
    uint16_t get_vector(Interrupts interrupt) const;

    void call(Cpu& cpu, uint8_t interrupt_vector);  
    
    const uint16_t interrupt_request_address = 0xFF0F;
    const uint16_t interrupt_enabled_address = 0xFFFF;

    MemoryBankController* m_memory_bank_controller;
};