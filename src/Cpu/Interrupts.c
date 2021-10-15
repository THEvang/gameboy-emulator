#include "Cpu/Interrupts.h"

#include "Cpu/Cpu.h"
#include "Utilities/BitOperations.h"

int gb_handle_interrupts(Cpu* cpu) {

    for(int i = 0; i <= Interrupts_Joypad; i++) {
        if(gb_is_enabled(cpu->memory_controller, (Interrupts) i) && gb_is_requested(cpu->memory_controller, (Interrupts) i)) {
            const uint16_t vector = gb_to_vector((Interrupts) i);
            gb_call_interrupt_vector(cpu, vector);
            gb_clear_interrupt(cpu->memory_controller, (Interrupts) i);
            cpu->interrupts_enabled = false;
            return 20;
        }
    }

    return  4;
}

void gb_request_interrupt(MemoryBankController* mc, Interrupts interrupt) {
    
    uint8_t interrupt_request = mc->memory[g_interrupt_request_address] | 0xE0;

    set_bit(&interrupt_request, interrupt);
    gb_write(mc, g_interrupt_request_address, interrupt_request);
}

void gb_clear_interrupt(MemoryBankController* mc, Interrupts interrupt) {
    
    uint8_t interrupt_request = mc->memory[g_interrupt_request_address] | 0xE0;

    clear_bit(&interrupt_request, interrupt);
    gb_write(mc, g_interrupt_request_address, interrupt_request);
}

bool gb_should_exit_halt(MemoryBankController* mc) {

    const uint8_t interrupt_requests = mc->memory[g_interrupt_request_address] | 0xE0;
    const uint8_t interrupts_enabled = mc->memory[g_interrupt_enabled_address];

    return ((uint8_t) (interrupt_requests & interrupts_enabled) & 0x1FU) == 0;
}

bool gb_is_requested(MemoryBankController* mc, Interrupts interrupt) {
    const uint8_t interrupt_requests = mc->memory[g_interrupt_request_address] | 0xE0;
    return test_bit_8bit(interrupt_requests, interrupt);
}

bool gb_is_enabled(MemoryBankController* mc, Interrupts interrupt) {
    const uint8_t interrupts_enabled = mc->memory[g_interrupt_enabled_address];
    return test_bit_8bit(interrupts_enabled, interrupt);
}

void gb_call_interrupt_vector(Cpu* cpu, uint16_t interrupt_vector) {

    const uint8_t pc_low = (uint8_t) (cpu->program_counter & 0xFFU);
    const uint8_t pc_high = (uint8_t) (cpu->program_counter >> 8U);

    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr - 1), pc_high);
    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr - 2), pc_low);

    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr - 2);
    cpu->program_counter = (uint16_t) (interrupt_vector);
}

uint16_t gb_to_vector(Interrupts interrupt) {
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