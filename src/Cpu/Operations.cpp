#include "Cpu/Operations.h"

#include "BitOperations.h"
#include "Cpu/Cpu.h"
#include "Cpu/Interpreter.h"
#include "Cpu/CBOpcodes.h"
#include "Memory/Memory_Controller.h"

FetchResult NOP() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu&){
        constexpr auto cycles = 4; 
        return cycles;
    }};
}

FetchResult STOP() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu&){
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult HALT() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        constexpr auto cycles = 4;
        if(cpu.m_interrupts_enabled) {
            cpu.m_is_halted = true;
        } else {

            const uint16_t interrupt_request_addr = 0xFF0F;
            const uint16_t interrupt_enable_addr = 0xFFFF;

            const auto interrupt_request = cpu.m_memory_controller->read(interrupt_request_addr);
            const auto interrupt_enable = cpu.m_memory_controller->read(interrupt_enable_addr);

            if((interrupt_request & interrupt_enable & 0x1Fu) == 0) {
                cpu.m_is_halted = true;
            } else {
                throw UnimplementedOperation("HALT BUG");
            }
        }
        return cycles;
    }};
}

FetchResult RST(uint8_t address) {


    constexpr auto delta_pc = 1;

    return {delta_pc, [address](Cpu& cpu){

        const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
        const auto pc_low =  static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);

        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);

        cpu.m_program_counter = combine_bytes(0x00, address);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult DI() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_should_disable_interrupts = true;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult EI() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_should_enable_interrupts = true;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult JR() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
        cpu.m_program_counter = static_cast<uint16_t>(cpu.m_program_counter + distance);
        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult JR_NZ() {
    
    constexpr auto delta_pc = 2;
    
    return {delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
            cpu.m_program_counter = static_cast<uint16_t>(cpu.m_program_counter + distance);
            return 12;
        }
        return 8;
    }};
}

FetchResult JR_Z() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
            cpu.m_program_counter = static_cast<uint16_t>(cpu.m_program_counter + distance);
            return 12;
        }
        return 8;
    }};
}

FetchResult JR_NC() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
            cpu.m_program_counter = static_cast<uint16_t>(cpu.m_program_counter + distance);
            return 12;
        }
        return 8;
    }};
}

FetchResult JR_C() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
            cpu.m_program_counter = static_cast<uint16_t>(cpu.m_program_counter + distance);
            return 12;
        }
        return 8;
    }};
}

FetchResult RET() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
        const auto pc_high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        
        cpu.m_program_counter = combine_bytes(pc_high, pc_low);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RET_NZ() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
            const auto pc_high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
            cpu.m_program_counter = combine_bytes(pc_high, pc_low);            
            cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
            return 20;
        }
        return 8;
    }};
}

FetchResult RET_Z() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
            const auto pc_high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
            cpu.m_program_counter = combine_bytes(pc_high, pc_low);        
            cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
            return 20;
        }
        return 8;

    }};
}

FetchResult RET_NC() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
            const auto pc_high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
            cpu.m_program_counter = combine_bytes(pc_high, pc_low);
            cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
            return 20;
        }
        return 8;
    }};
}

FetchResult RET_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
            const auto pc_high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
            cpu.m_program_counter = combine_bytes(pc_high, pc_low);
            cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
            return 20;
        }
        return 8;
    }};
}

FetchResult RETI() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
        const auto pc_high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        cpu.m_program_counter = combine_bytes(pc_high, pc_low);    
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
        cpu.m_interrupts_enabled = true;
        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult JUMP() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        const auto low = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        const auto high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        const auto address = combine_bytes(high, low);
        cpu.m_program_counter = address; 
        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult JUMP_NZ() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {        
        if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
            const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
            const auto address = combine_bytes(upper, lower);
            cpu.m_program_counter = address;
            return 16;
        }
        return 12;
    }};
}

FetchResult JUMP_Z() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
            const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
            const auto address = combine_bytes(upper, lower);
            cpu.m_program_counter = address;
            return 16;
        }
        return 12;
    }};
}

FetchResult JUMP_NC() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
            const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
            const auto address = combine_bytes(upper, lower);
            cpu.m_program_counter = address;
            return 16;
        }
        return 12;
    }};
}

FetchResult JUMP_C() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
            const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
            const auto address = combine_bytes(upper, lower);
            cpu.m_program_counter = address;
            return 16;
        }
        return 12;
    }};
}

FetchResult JUMP_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_program_counter = address;
        constexpr auto cycles = 4;
        return cycles;
    }};
}


FetchResult CALL() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
        const auto pc_low = static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);
        
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);
        
        const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        
        const auto address = combine_bytes(upper, lower);
        
        cpu.m_program_counter = address;
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr -2);
        
        constexpr auto cycles = 24;
        return cycles;
    }};
}

FetchResult CALL_NZ() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
            const auto pc_low = static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);

            cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
            cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);

        
            const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
            const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
            const auto address = combine_bytes(upper, lower);
        
            cpu.m_program_counter = address;
            cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr -2);

            return 24;
        }
        return 12;
    }};
}

FetchResult CALL_Z() {

    constexpr auto delta_pc = 3;
    
    return {delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
            const auto pc_low = static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);

            cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
            cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);

            
            const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
            const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
            const auto address = combine_bytes(upper, lower);
            
            cpu.m_program_counter = address;
            cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr -2);

            return 24;
        }
        return 12;
    }};
}

FetchResult CALL_NC() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
            const auto pc_low = static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);

            cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
            cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);

            
            const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
            const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
            const auto address = combine_bytes(upper, lower);
            
            cpu.m_program_counter = address;
            cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr -2);

            return 24;
            }
        return 12;
    }};
}

FetchResult CALL_C() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
            const auto pc_low =  static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);

            cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
            cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);

            
            const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
            const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
            const auto address = combine_bytes(upper, lower);
            
            cpu.m_program_counter = address;
            cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr -2);
            return 24;
        }
        return 12;
    }};
}

FetchResult LD_A_D8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_A_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu&){
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_A_B() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_a = cpu.m_reg_b;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_A_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_c;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_A_D() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_d;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_A_E() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_e;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_A_H() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_h;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_A_L() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_l;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_A_ADDR_BC() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {        
        const auto address = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_A_ADDR_DE() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_A_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {    
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_A_ADDR_A16() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        const auto low = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        const auto high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        const auto address = combine_bytes(high, low);

        cpu.m_reg_a = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult LD_A_ADDR_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = static_cast<uint16_t>(0xFF00 + cpu.m_reg_c);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_ADDR_A16_SP() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {        
        const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        const auto address = combine_bytes(upper, lower);
        cpu.m_memory_controller->write(address, static_cast<uint8_t>(cpu.m_stack_ptr & 0xFFu));
        cpu.m_memory_controller->write(static_cast<uint16_t>(address + 1), static_cast<uint8_t>(cpu.m_stack_ptr >> 8u));

        constexpr auto cycles = 20;
        return cycles;
    }};
}

FetchResult LDI_ADDR_HL_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);

        address++;
        cpu.m_reg_h = static_cast<uint8_t>(address >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(address & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LDI_A_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);
        
        address++;
        cpu.m_reg_h = static_cast<uint8_t>(address >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(address & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_ADDR_BC_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);   

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_ADDR_DE_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        const auto address = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);    

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_B_D8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_B_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_a;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_B_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu&) {
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_B_C() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_c;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_B_D() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_d;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_B_E() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_e;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_B_H() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_h;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_B_L() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_l;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_B_ADDR_HL() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_b = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_C_D8() {
    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_C_A() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_a;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_C_B() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_b;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_C_C() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu&) {
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_C_D() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_d;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_C_E() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_e;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_C_H() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_h;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_C_L() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_l;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_C_ADDR_HL() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {        
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_c = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_D_D8() {
    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_D_A() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_a;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_D_B() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_b;

        constexpr auto cycles = 4;
        return cycles;
    }};}

FetchResult LD_D_C() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_c;

        constexpr auto cycles = 4;
        return cycles;
    }};}

FetchResult LD_D_D() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu&) {
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_D_E() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_e;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_D_H() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_h;

        constexpr auto cycles = 4;
        return cycles;
    }};
}
FetchResult LD_D_L() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_l;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_D_ADDR_HL() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_d = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_E_D8() {
    constexpr auto delta_pc = 2;
    
    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_E_A() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_a;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_E_B() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_b;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_E_C() {    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_c;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_E_D() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_d;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_E_E() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu&){
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_E_H() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_h;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_E_L() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_l;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_E_ADDR_HL() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_e = cpu.m_memory_controller->read(address);
        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_H_D8() {
    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_H_A() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_a;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_H_B() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_b;

        constexpr auto cycles = 4;
        return cycles;
    }};

}

FetchResult LD_H_C() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_c;

        constexpr auto cycles = 4;
        return cycles;
    }};

}

FetchResult LD_H_D() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_d;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_H_E() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_e;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_H_H() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu&) {
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_H_L() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_l;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_H_ADDR_HL() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_h = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }};    
}

FetchResult LD_L_D8() {
    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_L_A() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_a;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_L_B() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_b;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_L_C() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_c;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_L_D() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_d;

        constexpr auto cycles = 4;
        return cycles;
    }};    
}

FetchResult LD_L_E() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_e;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_L_H() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_h;

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult LD_L_L() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu&){
        constexpr auto cycles = 4;
        return cycles;
    }};    
}

FetchResult LD_L_ADDR_HL() {
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_l = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_ADDR_HL_A() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);

        constexpr auto cycles = 8;
        return cycles;
    }};    
}

FetchResult LD_ADDR_HL_B() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_b);

        constexpr auto cycles = 8;
        return cycles;
    }};    
}

FetchResult LD_ADDR_HL_C() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_c);

        constexpr auto cycles = 8;
        return cycles;
    }};    
}

FetchResult LD_ADDR_HL_D() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_d);

        constexpr auto cycles = 8;
        return cycles;
    }};    
}

FetchResult LD_ADDR_HL_E() {
    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_e);

        constexpr auto cycles = 8;
        return cycles;
    }};    
}

FetchResult LD_ADDR_HL_H() {
    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_h);

        constexpr auto cycles = 8;
        return cycles;
    }};    
}

FetchResult LD_ADDR_HL_L() {
    
    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_l);

        constexpr auto cycles = 8;
        return cycles;
    }};   
}

FetchResult LD_ADDR_HL_D8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult LD_ADDR_HL_ADDR_HL() {    
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL ADDR HL");
}

FetchResult LD_ADDR_A16_A() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        const auto address = combine_bytes(upper, lower);

        cpu.m_memory_controller->write(address, cpu.m_reg_a);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult LD_BC_D16() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        cpu.m_reg_b = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult LD_DE_D16() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        cpu.m_reg_d = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult LD_HL_D16() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        cpu.m_reg_h = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult LD_HL_SPR8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto distance = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        half_carry_8bit(static_cast<uint8_t>(cpu.m_stack_ptr), distance)     ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);


        overflows_8bit(static_cast<uint8_t>(cpu.m_stack_ptr), distance)  ? 
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);

        const auto result = static_cast<uint16_t>(cpu.m_stack_ptr + static_cast<int8_t>(distance));
        cpu.m_reg_h = static_cast<uint8_t>(result >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(result & 0xFFu);

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult LD_SP_D16() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto lower = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        const auto upper = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        const auto value = combine_bytes(upper, lower);

        cpu.m_stack_ptr = value;

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult LD_SP_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_stack_ptr = value;

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t ADD_8bit(uint8_t first, uint8_t second, uint8_t& flags) {
    
    half_carry_8bit(first, second)             ? 
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    overflows_8bit(first, second)          ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    first = static_cast<uint8_t>(first + second);

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);

    return first;
}

FetchResult ADD_A_D8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult ADD_A_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADD_A_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADD_A_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADD_A_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADD_A_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADD_A_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADD_A_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADD_A_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint16_t ADD_16bit(uint16_t first, uint16_t second, uint8_t& flags) {
    
    overflows_16bit(first, second)                     ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    half_carry_16bit(first, second)                        ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    first = static_cast<uint16_t>(first + second);

    clear_bit(flags, Cpu::sub_flag);

    return first;
}

FetchResult ADD_HL_BC() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);

        const auto result = ADD_16bit(hl, bc, cpu.m_reg_f);

        cpu.m_reg_h = static_cast<uint8_t>(result >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult ADD_HL_DE() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto de = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);

        const auto result = ADD_16bit(hl, de, cpu.m_reg_f);

        cpu.m_reg_h = static_cast<uint8_t>(result >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult ADD_HL_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto result = ADD_16bit(hl, hl, cpu.m_reg_f);

        cpu.m_reg_h = static_cast<uint8_t>(result >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult ADD_HL_SP() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto result = ADD_16bit(hl, cpu.m_stack_ptr, cpu.m_reg_f);

        cpu.m_reg_h = static_cast<uint8_t>(result >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t SUB(uint8_t first, uint8_t second, uint8_t& flags) {
    
    half_borrow_8bit(first, second)            ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    underflows_8bit(first, second)         ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    first = static_cast<uint8_t>(first - second);

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    set_bit(flags, Cpu::sub_flag);

    return first;
}

FetchResult SUB_D8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        cpu.m_reg_a = SUB(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SUB_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SUB_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SUB_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SUB_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SUB_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SUB_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SUB_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SUB_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = SUB(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t INC(uint8_t value, uint8_t& flags) {
    
    half_carry_8bit(value, 1)                 ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    value++;

    value == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);

    return value;
}

FetchResult INC_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = INC(cpu.m_reg_a, cpu.m_reg_f);
        
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult INC_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = INC(cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles; 
    }};
}

FetchResult INC_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = INC(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult INC_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = INC(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult INC_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = INC(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult INC_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = INC(cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult INC_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = INC(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult INC_BC() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {        
        auto value = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        value++;

        cpu.m_reg_b = static_cast<uint8_t>(value >> 8u);
        cpu.m_reg_c = static_cast<uint8_t>(value & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult INC_DE() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        auto value = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        value++;

        cpu.m_reg_d = static_cast<uint8_t>(value >> 8u);
        cpu.m_reg_e = static_cast<uint8_t>(value & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult INC_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        value++;

        cpu.m_reg_h = static_cast<uint8_t>(value >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(value & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult INC_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);

        value = INC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult INC_SP() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_stack_ptr++;

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t DEC(uint8_t value, uint8_t& flags) {
    
    half_borrow_8bit(value, 1)                ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    value--;
    
    value == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    set_bit(flags, Cpu::sub_flag);

    return value;
}

FetchResult DEC_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = DEC(cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult DEC_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = DEC(cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult DEC_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = DEC(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult DEC_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = DEC(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult DEC_E() {    
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = DEC(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult DEC_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = DEC(cpu.m_reg_h, cpu.m_reg_f);
        
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult DEC_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = DEC(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult DEC_BC() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        bc--;

        cpu.m_reg_b = static_cast<uint8_t>(bc >> 8u);
        cpu.m_reg_c = static_cast<uint8_t>(bc & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult DEC_DE() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        auto de = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        de--;

        cpu.m_reg_d = static_cast<uint8_t>(de >> 8u);
        cpu.m_reg_e = static_cast<uint8_t>(de & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult DEC_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        hl--;

        cpu.m_reg_h = static_cast<uint8_t>(hl >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(hl & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult DEC_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = DEC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult DEC_SP() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_stack_ptr--;

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SCF() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
        set_bit(cpu.m_reg_f, Cpu::carry_flag);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult CCF() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
    
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

        is_set(cpu.m_reg_f, Cpu::carry_flag) ? 
            clear_bit(cpu.m_reg_f, Cpu::carry_flag) : set_bit(cpu.m_reg_f, Cpu::carry_flag);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult RRCA() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        is_set(cpu.m_reg_a, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
            : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
        
        cpu.m_reg_a = rotate_right<uint8_t>(cpu.m_reg_a, 1);

        
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult RRA() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        const auto new_carry_flag = is_set(cpu.m_reg_a, 0);
        cpu.m_reg_a = static_cast<uint8_t>(cpu.m_reg_a >> 1u);

        is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_a, 7) 
            : clear_bit(cpu.m_reg_a, 7);

        new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag) 
            : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult RLA() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto new_carry_flag = is_set(cpu.m_reg_a, 7);
        cpu.m_reg_a =  static_cast<uint8_t>(cpu.m_reg_a << 1u);

        is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_a, 0)
            : clear_bit(cpu.m_reg_a, 0);
        
        new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
            : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
        
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult RLCA() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        is_set(cpu.m_reg_a, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);

        cpu.m_reg_a = rotate_left<uint8_t>(cpu.m_reg_a, 1);

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult DAA() {    

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {

        if(!is_set(cpu.m_reg_f, Cpu::sub_flag)) {
            if(is_set(cpu.m_reg_f, Cpu::carry_flag) || cpu.m_reg_a > 0x99) {
                cpu.m_reg_a = static_cast<uint8_t>(cpu.m_reg_a + 0x60);
                set_bit(cpu.m_reg_f, Cpu::carry_flag);
            }

            if(is_set(cpu.m_reg_f, Cpu::half_carry_flag) || (cpu.m_reg_a & 0x0Fu) > 0x09) {
                cpu.m_reg_a = static_cast<uint8_t>(cpu.m_reg_a + 0x06);
            }
        } else {
            if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
                cpu.m_reg_a = static_cast<uint8_t>(cpu.m_reg_a - 0x60);
            }
            if(is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
                cpu.m_reg_a = static_cast<uint8_t>(cpu.m_reg_a - 0x06);
            }
        }

        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

        cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
            clear_bit(cpu.m_reg_f, Cpu::zero_flag);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADD_SP_R8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto distance = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        half_carry_8bit(static_cast<uint8_t>(cpu.m_stack_ptr), distance)     ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);


        overflows_8bit(static_cast<uint8_t>(cpu.m_stack_ptr), distance)  ? 
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);


        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + static_cast<int8_t>(distance));

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);

        constexpr auto cycles = 16;
        return cycles;
    }};    
}

uint8_t AND(uint8_t first, uint8_t second, uint8_t& flags) {
    
    first &= second;

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    set_bit(flags, Cpu::half_carry_flag);
    clear_bit(flags, Cpu::carry_flag);

    return first;
}

FetchResult AND_D8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        cpu.m_reg_a = AND(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult AND_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult AND_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult AND_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult AND_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult AND_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult AND_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult AND_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult AND_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = AND(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t XOR(uint8_t first, uint8_t second, uint8_t& flags) {
    
    first ^= second;
    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);
    clear_bit(flags, Cpu::carry_flag);

    return first;
}

FetchResult XOR_D8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        cpu.m_reg_a = XOR(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult XOR_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult XOR_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult XOR_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult XOR_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult XOR_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult XOR_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult XOR_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult XOR_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = XOR(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t OR(uint8_t first, uint8_t second, uint8_t& flags) {
    
    first |= second;
    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);
    clear_bit(flags, Cpu::carry_flag);

    return first;
}

FetchResult OR_D8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        cpu.m_reg_a = OR(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult OR_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
        
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult OR_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult OR_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult OR_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult OR_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult OR_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult OR_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult OR_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = OR(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

void CP(uint8_t first, uint8_t second, uint8_t& flags) {

    underflows_8bit(first, second)         ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    half_borrow_8bit(first, second)            ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    (first == second) ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    set_bit(flags, Cpu::sub_flag);
}

FetchResult CP_D8() {
    
    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        CP(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult CP_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult CP_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult CP_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult CP_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult CP_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}



FetchResult CP_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult CP_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult CP_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        CP(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult PUSH_AF() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-1), cpu.m_reg_a);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-2), cpu.m_reg_f);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult PUSH_BC() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-1), cpu.m_reg_b);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-2), cpu.m_reg_c);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult PUSH_DE() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-1), cpu.m_reg_d);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-2), cpu.m_reg_e);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult PUSH_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-1), cpu.m_reg_h);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-2), cpu.m_reg_l);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult POP_AF() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_f = cpu.m_memory_controller->read(cpu.m_stack_ptr) & 0xF0u;
        cpu.m_reg_a = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult POP_BC() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_memory_controller->read(cpu.m_stack_ptr) ;
        cpu.m_reg_b = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult POP_DE() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = cpu.m_memory_controller->read(cpu.m_stack_ptr) ;
        cpu.m_reg_d = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult POP_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_stack_ptr) ;
        cpu.m_reg_h = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

uint8_t ADC(uint8_t first, uint8_t second, uint8_t& flags) {
    
    const auto carry_value = is_set(flags, Cpu::carry_flag) ? 1 : 0;

    half_carry_8bit(first, second)       ?
        set_bit(flags, Cpu::half_carry_flag)          :
        clear_bit(flags, Cpu::half_carry_flag);

    overflows_8bit(first, second)        ?
        set_bit(flags, Cpu::carry_flag)               :
        clear_bit(flags, Cpu::carry_flag);

    first = static_cast<uint8_t>(first + second);

    if(!is_set(flags, Cpu::half_carry_flag)) {
        half_carry_8bit(first, static_cast<uint8_t>(carry_value))       ?
        set_bit(flags, Cpu::half_carry_flag)          :
        clear_bit(flags, Cpu::half_carry_flag);
    }

    if(!is_set(flags, Cpu::carry_flag)) {
        overflows_8bit(first, static_cast<uint8_t>(carry_value))        ?
            set_bit(flags, Cpu::carry_flag)               :
            clear_bit(flags, Cpu::carry_flag);
    }

    first = static_cast<uint8_t>(first + carry_value);

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    
    return first;
}

FetchResult ADC_A_D8() {
    
    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        cpu.m_reg_a = ADC(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult ADC_A_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADC_A_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADC_A_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADC_A_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADC_A_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADC_A_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
        
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADC_A_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
    
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult ADC_A_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = ADC(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LDH_ADDR_A8_A() {

    constexpr auto delta_pc = 2;

    return  {delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        const auto address = static_cast<uint16_t>(0xFF00 + value);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);    

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult LDH_A_ADDR_A8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = static_cast<uint16_t>(0xFF00 + cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
        cpu.m_reg_a = cpu.m_memory_controller->read(address);             

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult LD_ADDR_C_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {        
        const auto address = static_cast<uint16_t>(0xFF00 + cpu.m_reg_c);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t SBC(uint8_t first, uint8_t second, uint8_t& flags) {
    
    const auto carry_value = is_set(flags, Cpu::carry_flag) ? 1 : 0;

    half_borrow_8bit(first, second)            ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    underflows_8bit(first, second)         ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);
    
    first = static_cast<uint8_t>(first - second);

    if(!is_set(flags, Cpu::half_carry_flag)) {
        half_borrow_8bit(first, static_cast<uint8_t>(carry_value))       ?
            set_bit(flags, Cpu::half_carry_flag)  :
            clear_bit(flags, Cpu::half_carry_flag);
    }

    if(!is_set(flags, Cpu::carry_flag)) {
        underflows_8bit(first, static_cast<uint8_t>(carry_value))         ?
            set_bit(flags, Cpu::carry_flag)   :
            clear_bit(flags, Cpu::carry_flag);
    }

    first = static_cast<uint8_t>(first - carry_value);

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    set_bit(flags, Cpu::sub_flag);

    return first;
}

FetchResult SBC_A_D8() {

    constexpr auto delta_pc = 2;

    return {delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));
        cpu.m_reg_a = SBC(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SBC_A_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SBC_A_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SBC_A_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SBC_A_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SBC_A_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SBC_A_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SBC_A_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }};
}

FetchResult SBC_A_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = SBC(cpu.m_reg_a, value, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult PREFIX_CB() {

    auto delta_pc = 2;
    return {delta_pc, [](Cpu& cpu) {

        const auto cb_opcode = static_cast<CBCode>(cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
        const auto result = fetch_cb(cb_opcode);
        return result.operation(cpu);
    }};
}

FetchResult LD_ADDR_HLD_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
            
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);

        address--;

        cpu.m_reg_h = static_cast<uint8_t>(address >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(address & 0xFFu);
        
        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult LD_A_ADDR_HLD() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);

        address--;
        cpu.m_reg_h = static_cast<uint8_t>(address >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(address & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult CPL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_a ^= 0xFF;

        set_bit(cpu.m_reg_f, Cpu::sub_flag);
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
        
        constexpr auto cycles = 4;
        return cycles;
    }};
}