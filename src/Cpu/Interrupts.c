#include "Cpu/Interrupts.h"

#include "Cpu/Cpu.h"
#include "Utilities/BitOperations.h"

int handle_interrupts(Cpu* cpu) {

    for(int i = 0; i <= Interrupts_Joypad; i++) {
        if(is_enabled(cpu->memory_controller, (Interrupts) i) && is_requested(cpu->memory_controller, (Interrupts) i)) {
            const uint16_t vector = to_vector((Interrupts) i);
            call_interrupt_vector(cpu, vector);
            clear_interrupt(cpu->memory_controller, (Interrupts) i);
            cpu->interrupts_enabled = false;
            return 20;
        }
    }

    return  4;
}

void request_interrupt(MemoryBankController* mc, Interrupts interrupt) {
    uint8_t interrupt_request = gb_read(mc, g_interrupt_request_address);
    set_bit(&interrupt_request, interrupt);
    gb_write(mc, g_interrupt_request_address, interrupt_request);
}

void clear_interrupt(MemoryBankController* mc, Interrupts interrupt) {
    
    uint8_t request_register = gb_read(mc, g_interrupt_request_address);
    clear_bit(&request_register, interrupt);
    gb_write(mc, g_interrupt_request_address, request_register);
}

bool should_exit_halt(MemoryBankController* mc) {

    const uint8_t interrupt_requests = gb_read(mc, g_interrupt_request_address);
    const uint8_t interrupts_enabled = gb_read(mc, g_interrupt_request_address);

    return ((uint8_t) (interrupt_requests & interrupts_enabled) & 0x1FU) == 0;
}

bool is_requested(MemoryBankController* mc, Interrupts interrupt) {
    const uint8_t request_register = gb_read(mc, g_interrupt_request_address);
    return test_bit_8bit(request_register, interrupt);
}

bool is_enabled(MemoryBankController* mc, Interrupts interrupt) {
    const uint8_t interrupt_enable_register = gb_read(mc, g_interrupt_enabled_address);
    return test_bit_8bit(interrupt_enable_register, interrupt);
}

void call_interrupt_vector(Cpu* cpu, uint8_t interrupt_vector) {

    const uint8_t pc_low = (uint8_t) (cpu->program_counter & 0xFFU);
    const uint8_t pc_high = (uint8_t) (cpu->program_counter >> 8U);

    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr - 1), pc_high);
    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr - 2), pc_low);

    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr - 2);
    cpu->program_counter = (uint16_t) (interrupt_vector);
}

uint16_t to_vector(Interrupts interrupt) {
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