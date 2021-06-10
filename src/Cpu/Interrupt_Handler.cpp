#include "Cpu/Interrupt_Handler.hpp"

#include "Cpu/Cpu.hpp"
#include "Utilities/BitOperations.h"

int Interrupt_Handler::interrupts(Cpu& cpu) {

    auto handle = [this](Cpu& cpu, Interrupts interrupt) -> bool {
        if(is_enabled(interrupt) && is_requested(interrupt)) {
            const auto vector = get_vector(interrupt);
            call(cpu, vector);
            clear_interrupt(cpu.memory_controller, interrupt);
            cpu.interrupts_enabled = false;
            return true;
        }
        return false;
    };

    for(auto i = 0; i <= static_cast<int>(Interrupts_Joypad); i++) {
        if(handle(cpu, static_cast<Interrupts>(i))) {
            return 20;
        };
    }

    return  4;
}

void request_interrupt(MemoryBankController* mc, Interrupts interrupt) {
    uint8_t interrupt_request = read(mc, g_interrupt_request_address);
    set_bit(&interrupt_request, interrupt);
    write(mc, g_interrupt_request_address, interrupt_request);
}

void clear_interrupt(MemoryBankController* mc, Interrupts interrupt) {
    
    auto request_register = read(mc, g_interrupt_request_address);
    clear_bit(&request_register, static_cast<int>(interrupt));
    write(mc, g_interrupt_request_address, request_register);
}

bool Interrupt_Handler::should_exit_halt() {

    const auto interrupt_requests = read(memory_bank_controller, g_interrupt_request_address);
    const auto interrupts_enabled = read(memory_bank_controller, g_interrupt_request_address);

    return (static_cast<uint8_t>(interrupt_requests & interrupts_enabled) & 0x1FU) == 0;
}

bool Interrupt_Handler::is_requested(Interrupts interrupt) const {
    const auto request_register = read(memory_bank_controller, g_interrupt_request_address);
    return test_bit_8bit(request_register, static_cast<int>(interrupt));
}

bool Interrupt_Handler::is_enabled(Interrupts interrupt) const {
    const auto interrupt_enable_register = read(memory_bank_controller, g_interrupt_enabled_address);
    return test_bit_8bit(interrupt_enable_register, static_cast<int>(interrupt));
}

void Interrupt_Handler::call(Cpu& cpu, uint8_t interrupt_vector) {

    const auto pc_low = static_cast<uint8_t>(cpu.program_counter & 0xFFU);
    const auto pc_high = static_cast<uint8_t>(cpu.program_counter >> 8U);
    write(memory_bank_controller, static_cast<uint16_t>(cpu.stack_ptr - 1), pc_high);
    write(memory_bank_controller, static_cast<uint16_t>(cpu.stack_ptr - 2), pc_low);
    cpu.stack_ptr = static_cast<uint16_t>(cpu.stack_ptr - 2);
    cpu.program_counter = static_cast<uint16_t>(interrupt_vector);
}

uint16_t Interrupt_Handler::get_vector(Interrupts interrupt) const {
    switch(interrupt) {
        case Interrupts_V_Blank:
            return 0x40;
        case Interrupts_LCD_STAT:
            return 0x48;
        case Interrupts_Timer:
            return 0x50;
        case Interrupts_Serial:
            return 0x58;
        case Interrupts_Joypad:
            return 0x60;
    }
}