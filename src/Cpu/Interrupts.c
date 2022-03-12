#include <stdint.h>

#include "Cpu/Interrupts.h"
#include "Cpu/Cpu.h"
#include "Utilities/BitOperations.h"
#include "Registers.h"

int gb_handle_interrupts(Cpu* cpu, MemoryBankController* mc) {

    uint16_t vectors[5] = {0x40, 0x48, 0x50, 0x58, 0x60};

    for(int i = 0; i <= Interrupts_Joypad; i++) {
        if(gb_is_enabled(mc, (Interrupts) i) && gb_is_requested(mc, (Interrupts) i)) {
            const uint16_t vector = vectors[i];
            gb_call_interrupt_vector(cpu, vector, mc);
            gb_clear_interrupt(mc, (Interrupts) i);
            cpu->interrupts_enabled = false;
            return 20;
        }
    }

    return  4;
}

void gb_request_interrupt(MemoryBankController* mc, Interrupts interrupt) {
    
    uint8_t interrupt_request = mc->memory[IF] | 0xE0;

    set_bit(&interrupt_request, interrupt);
    mc->write(mc, IF, interrupt_request);
}

void gb_clear_interrupt(MemoryBankController* mc, Interrupts interrupt) {
    
    uint8_t interrupt_request = mc->memory[IF] | 0xE0;

    clear_bit(&interrupt_request, interrupt);
    mc->write(mc, IF, interrupt_request);
}

bool gb_should_exit_halt(MemoryBankController* mc) {

    const uint8_t interrupt_requests = mc->memory[IF] | 0xE0;
    const uint8_t interrupts_enabled = mc->memory[IE];

    return ((uint8_t) (interrupt_requests & interrupts_enabled) & 0x1FU) == 0;
}

bool gb_is_requested(MemoryBankController* mc, Interrupts interrupt) {
    const uint8_t interrupt_requests = mc->memory[IF] | 0xE0;
    return test_bit_8bit(interrupt_requests, interrupt);
}

bool gb_is_enabled(MemoryBankController* mc, Interrupts interrupt) {
    const uint8_t interrupts_enabled = mc->memory[IE];
    return test_bit_8bit(interrupts_enabled, interrupt);
}

void gb_call_interrupt_vector(Cpu* cpu, uint16_t interrupt_vector, MemoryBankController* mc) {

    const uint8_t pc_low = (uint8_t) (cpu->program_counter & 0xFFU);
    const uint8_t pc_high = (uint8_t) (cpu->program_counter >> 8U);

    mc->write(mc, --cpu->stack_ptr, pc_high);
    mc->write(mc, --cpu->stack_ptr, pc_low);

    cpu->program_counter = interrupt_vector;
}

