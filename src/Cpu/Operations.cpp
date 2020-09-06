#include "Cpu/Operations.hpp"

#include "BitOperations.hpp"
#include "Cpu/Cpu.hpp"
#include "Cpu/Interpreter.hpp"
#include "Cpu/CBOpcodes.hpp"
#include "Memory/Memory_Controller.hpp"

Instruction NOP() {
    return {[](Cpu&, Operand&) { return 4;}, immediate};
}

Instruction STOP() {
    return {[](Cpu&, Operand&){ return 4;}};
}

Instruction HALT() {
    return {[](Cpu& cpu, Operand& op) {
        
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
    }, implied};
}

Instruction RST(uint8_t address) {
    return {[address](Cpu& cpu, Operand& op){
        
        const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
        const auto pc_low =  static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);

        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);

        cpu.m_program_counter = combine_bytes(0x00, address);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }, immediate};
}

Instruction DI() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_should_disable_interrupts = true;
        return 4;
    }, implied};
}

Instruction EI() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_should_enable_interrupts = true;
        return 4;
    }, implied};
}


void jump_relative(Cpu& cpu) {
    const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
    cpu.m_program_counter = static_cast<uint16_t>(cpu.m_program_counter + distance);
}

Instruction JR() {
    return {[](Cpu& cpu, Operand& op) {
        jump_relative(cpu);
        constexpr auto cycles = 12;
        return cycles;
    }, };
}

Instruction JR_NZ() {
    
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

Instruction JR_Z() {

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

Instruction JR_NC() {

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

Instruction JR_C() {

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

int ret(Cpu& cpu) {            
    const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
    const auto pc_high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
    
    cpu.m_program_counter = combine_bytes(pc_high, pc_low);
    cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
    constexpr auto cycles = 16;
    return cycles;
}

Instruction RET() {
    return {[](Cpu& cpu, Operand& op) {
        return ret(cpu);
    }, implied};
}

Instruction RET_NZ() {
    return {[](Cpu& cpu, Operand& op) {        
        return !is_set(cpu.m_reg_f, Cpu::zero_flag) ? ret(cpu) : 8;
    }, implied};
}

Instruction RET_Z() {
    return {[](Cpu& cpu, Operand&) {
        is_set(cpu.m_reg_f, Cpu::zero_flag) ? ret(cpu) : 8; 
    }, implied};
}

Instruction RET_NC() {
    return {[](Cpu& cpu, Operand& op) {
        !is_set(cpu.m_reg_f, Cpu::carry_flag) ? ret(cpu) : 8;
    }, implied};
}

Instruction RET_C() {
    return {[](Cpu& cpu, Operand& op) {
        is_set(cpu.m_reg_f, Cpu::carry_flag) ? ret(cpu) : 8;
    }, implied};
}

Instruction RETI() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_interrupts_enabled = true;
        return ret(cpu);
    }, implied};
}

int jump(Cpu& cpu, Operand& op) {
    const auto address = std::get<uint16_t>(op);
    cpu.m_program_counter = address; 
    constexpr auto cycles = 16;
    return cycles;
}

Instruction JUMP() {
    return {[](Cpu& cpu, Operand& op) {
        return jump(cpu, op);
    }, immediate_extended};
}

Instruction JUMP_NZ() {
    return {[](Cpu& cpu, Operand& op) {        
        return !is_set(cpu.m_reg_f, Cpu::zero_flag) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_Z() {
    return {[](Cpu& cpu, Operand& op) {
        return is_set(cpu.m_reg_f, Cpu::zero_flag) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_NC() {
    return {[](Cpu& cpu, Operand& op) {
        !is_set(cpu.m_reg_f, Cpu::carry_flag) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_C() {
    return {[](Cpu& cpu, Operand& op) {
        is_set(cpu.m_reg_f, Cpu::carry_flag) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_program_counter = address;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

int call(Cpu& cpu, Operand& op) {

    const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
    const auto pc_low = static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);
    
    cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
    cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);
    cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr -2);
    
     cpu.m_program_counter = std::get<uint16_t>(op);

    constexpr auto cycles = 24;
    return cycles;
}

Instruction CALL() {
    return {[](Cpu& cpu, Operand& op) {
        return call(cpu, op);
    }, immediate_extended};
}

Instruction CALL_NZ() {
    return {[](Cpu& cpu, Operand& op) {
        return !is_set(cpu.m_reg_f, Cpu::zero_flag) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction CALL_Z() {
    return {[](Cpu& cpu, Operand& op) {
        return is_set(cpu.m_reg_f, Cpu::zero_flag) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction CALL_NC() {
    return {[](Cpu& cpu, Operand& op) {
        return !is_set(cpu.m_reg_f, Cpu::carry_flag) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction CALL_C() {
    return {[](Cpu& cpu, Operand& op) {
        return is_set(cpu.m_reg_f, Cpu::carry_flag) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction LD_A_D8() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_a = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction LD_A_A() {
    return {[](Cpu&, Operand&){ return 4; }, implied};
}

Instruction LD_A_B() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_a = cpu.m_reg_b;
        return 4;
    }, implied};
}

Instruction LD_A_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = cpu.m_reg_c;
        return 4;
    }, implied};
}

Instruction LD_A_D() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_a = cpu.m_reg_d;
    }, implied};
}

Instruction LD_A_E() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_a = cpu.m_reg_e;
        return 4;
    }, implied};
}

Instruction LD_A_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = cpu.m_reg_h;
        return 4;
    }, implied};
}

Instruction LD_A_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = cpu.m_reg_l;
        constexpr auto cycles = 4;
        return cycles;
    }};
}

Instruction LD_A_ADDR_BC() {
    return {[](Cpu& cpu, Operand& op) {        
        const auto address = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_A_ADDR_DE() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_A_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {    
        cpu.m_reg_a = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LD_A_ADDR_A16() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_a = std::get<uint8_t>(op);
        constexpr auto cycles = 16;
        return cycles;
    }, extended_address};
}

Instruction LD_A_ADDR_C() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = static_cast<uint16_t>(0xFF00 + cpu.m_reg_c);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_ADDR_A16_SP() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = std::get<uint16_t>(op);        
        cpu.m_memory_controller->write(address, static_cast<uint8_t>(cpu.m_stack_ptr & 0xFFu));
        cpu.m_memory_controller->write(static_cast<uint16_t>(address + 1), static_cast<uint8_t>(cpu.m_stack_ptr >> 8u));
        constexpr auto cycles = 20;
        return cycles;
    }, immediate_extended};
}

Instruction LDI_ADDR_HL_A() {
    return {[](Cpu& cpu, Operand&) {
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);

        address++;
        cpu.m_reg_h = static_cast<uint8_t>(address >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(address & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LDI_A_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);
        
        address++;
        cpu.m_reg_h = static_cast<uint8_t>(address >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(address & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_ADDR_BC_A() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);   

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_ADDR_DE_A() {
    return {[](Cpu& cpu, Operand&){
        const auto address = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);    

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_B_D8() {
    return {delta_pc, [](Cpu& cpu, Operand& op) {
        cpu.m_reg_b = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction LD_B_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_b = cpu.m_reg_a;
        constexpr auto cycles = 4;
        return cycles;
    }}, implied;
}

Instruction LD_B_B() {
    return {[](Cpu&, Operand&) {
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_B_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_b = cpu.m_reg_c;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_B_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_b = cpu.m_reg_d;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_B_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_b = cpu.m_reg_e;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_B_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_b = cpu.m_reg_h;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_B_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_b = cpu.m_reg_l;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_B_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_b = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_C_D8() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_c = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction LD_C_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_c = cpu.m_reg_a;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_C_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_c = cpu.m_reg_b;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_C_C() {
    return {[](Cpu&, Operand&) {
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_C_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_c = cpu.m_reg_d;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_C_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_c = cpu.m_reg_e;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_C_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_c = cpu.m_reg_h;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_C_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_c = cpu.m_reg_l;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_C_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {        
        cpu.m_reg_c = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LD_D_D8() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_d = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction LD_D_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_d = cpu.m_reg_a;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_D_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_d = cpu.m_reg_b;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_D_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_d = cpu.m_reg_c;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_D_D() {
    return {[](Cpu&, Operand&) {
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_D_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_d = cpu.m_reg_e;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_D_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_d = cpu.m_reg_h;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}
Instruction LD_D_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_d = cpu.m_reg_l;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_D_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_d = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LD_E_D8() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_e = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction LD_E_A() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_e = cpu.m_reg_a;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_E_B() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_e = cpu.m_reg_b;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_E_C() {    
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_e = cpu.m_reg_c;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_E_D() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_e = cpu.m_reg_d;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_E_E() {
    return {[](Cpu&, Operand&){
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_E_H() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_e = cpu.m_reg_h;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_E_L() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_e = cpu.m_reg_l;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_E_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_e = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LD_H_D8() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_h = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction LD_H_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_h = cpu.m_reg_a;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_H_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_h = cpu.m_reg_b;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_H_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_h = cpu.m_reg_c;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_H_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_h = cpu.m_reg_d;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_H_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_h = cpu.m_reg_e;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_H_H() {
    return {[](Cpu&, Operand&) {
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_H_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_h = cpu.m_reg_l;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_H_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_h = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};    
}

Instruction LD_L_D8() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_l = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction LD_L_A() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_l = cpu.m_reg_a;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_L_B() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_l = cpu.m_reg_b;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_L_C() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_l = cpu.m_reg_c;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_L_D() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_l = cpu.m_reg_d;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};    
}

Instruction LD_L_E() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_l = cpu.m_reg_e;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_L_H() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_l = cpu.m_reg_h;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction LD_L_L() {
    return {[](Cpu&, Operand&){
        constexpr auto cycles = 4;
        return cycles;
    }, implied};    
}

Instruction LD_L_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_l = std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LD_ADDR_HL_A() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};    
}

Instruction LD_ADDR_HL_B() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_b);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};    
}

Instruction LD_ADDR_HL_C() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_c);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};    
}

Instruction LD_ADDR_HL_D() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_d);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};    
}

Instruction LD_ADDR_HL_E() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_e);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};    
}

Instruction LD_ADDR_HL_H() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_h);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};    
}

Instruction LD_ADDR_HL_L() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_l);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};   
}

Instruction LD_ADDR_HL_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = std::get<uint8_t>(op);
        cpu.m_memory_controller->write(address, value);
        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LD_ADDR_HL_ADDR_HL() {    
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL ADDR HL");
}

Instruction LD_ADDR_A16_A() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = std::get<uint16_t>(op);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);
        constexpr auto cycles = 16;
        return cycles;
    }, immediate_extended};
}

Instruction LD_BC_D16() {
    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        cpu.m_reg_b = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 12;
        return cycles;
    }};
}

Instruction LD_DE_D16() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        cpu.m_reg_d = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 12;
        return cycles;
    }};
}

Instruction LD_HL_D16() {

    constexpr auto delta_pc = 3;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 2));
        cpu.m_reg_h = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1));

        constexpr auto cycles = 12;
        return cycles;
    }};
}

Instruction LD_HL_SPR8() {

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

Instruction LD_SP_D16() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_stack_ptr = std::get<uint16_t>(op);
        constexpr auto cycles = 12;
        return cycles;
    }, immediate_extended};
}

Instruction LD_SP_HL() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_stack_ptr =  combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
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

Instruction ADD_A_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction ADD_A_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_A_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_A_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_A_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_A_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_A_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_A_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_A_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
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

Instruction ADD_HL_BC() {
    return {[](Cpu& cpu, Operand&) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);

        const auto result = ADD_16bit(hl, bc, cpu.m_reg_f);

        cpu.m_reg_h = static_cast<uint8_t>(result >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction ADD_HL_DE() {
    return {[](Cpu& cpu, Operand&) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto de = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);

        const auto result = ADD_16bit(hl, de, cpu.m_reg_f);

        cpu.m_reg_h = static_cast<uint8_t>(result >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction ADD_HL_HL() {
    return {[](Cpu& cpu, Operand&) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto result = ADD_16bit(hl, hl, cpu.m_reg_f);

        cpu.m_reg_h = static_cast<uint8_t>(result >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction ADD_HL_SP() {
    return {[](Cpu& cpu, Operand&) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto result = ADD_16bit(hl, cpu.m_stack_ptr, cpu.m_reg_f);

        cpu.m_reg_h = static_cast<uint8_t>(result >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
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

Instruction SUB_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = SUB(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction SUB_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SUB_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SUB_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SUB_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SUB_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SUB_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SUB_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SUB_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = SUB(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
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

Instruction INC_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = INC(cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction INC_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_b = INC(cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles; 
    }, implied};
}

Instruction INC_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_c = INC(cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction INC_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_d = INC(cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction INC_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_e = INC(cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction INC_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_h = INC(cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction INC_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_l = INC(cpu.m_reg_l, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction INC_BC() {
    return {[](Cpu& cpu, Operand&) {        
        auto value = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        value++;

        cpu.m_reg_b = static_cast<uint8_t>(value >> 8u);
        cpu.m_reg_c = static_cast<uint8_t>(value & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction INC_DE() {
    return {[](Cpu& cpu, Operand&) {
        auto value = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        value++;

        cpu.m_reg_d = static_cast<uint8_t>(value >> 8u);
        cpu.m_reg_e = static_cast<uint8_t>(value & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction INC_HL() {
    return {[](Cpu& cpu, Operand&) {
        auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        value++;

        cpu.m_reg_h = static_cast<uint8_t>(value >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(value & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction INC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);

        value = INC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction INC_SP() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_stack_ptr++;
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
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

Instruction DEC_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = DEC(cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DEC_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_b = DEC(cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DEC_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_c = DEC(cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DEC_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_d = DEC(cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DEC_E() {    
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_e = DEC(cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DEC_H() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_reg_h = DEC(cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DEC_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_l = DEC(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DEC_BC() {
    return {[](Cpu& cpu, Operand&) {
        
        auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        bc--;

        cpu.m_reg_b = static_cast<uint8_t>(bc >> 8u);
        cpu.m_reg_c = static_cast<uint8_t>(bc & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction DEC_DE() {
    return {[](Cpu& cpu, Operand&) {
        
        auto de = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        de--;

        cpu.m_reg_d = static_cast<uint8_t>(de >> 8u);
        cpu.m_reg_e = static_cast<uint8_t>(de & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction DEC_HL() {
    return {[](Cpu& cpu, Operand&) {
        
        auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        hl--;

        cpu.m_reg_h = static_cast<uint8_t>(hl >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(hl & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction DEC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = DEC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction DEC_SP() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_stack_ptr--;
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction SCF() {
    return {[](Cpu& cpu, Operand&) {
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CCF() {
    return {[](Cpu& cpu, Operand&) {
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
        is_set(cpu.m_reg_f, Cpu::carry_flag) ? 
            clear_bit(cpu.m_reg_f, Cpu::carry_flag) : set_bit(cpu.m_reg_f, Cpu::carry_flag);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RRCA() {
    return {[](Cpu& cpu, Operand&) {
        is_set(cpu.m_reg_a, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
            : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
        
        cpu.m_reg_a = rotate_right<uint8_t>(cpu.m_reg_a, 1);

        
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RRA() {
    return {[](Cpu& cpu, Operand&) {
        
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
    }, implied};
}

Instruction RLA() {
    return {[](Cpu& cpu, Operand&) {
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
    }, implied};
}

Instruction RLCA() {
    return {[](Cpu& cpu, Operand&) {
        is_set(cpu.m_reg_a, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);

        cpu.m_reg_a = rotate_left<uint8_t>(cpu.m_reg_a, 1);

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DAA() {    
    return {[](Cpu& cpu, Operand&) {

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
    }, implied};
}

Instruction ADD_SP_R8() {
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

Instruction AND_D8() {
    return {[](Cpu& cpu, Operand&) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = AND(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction AND_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction AND_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction AND_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction AND_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction AND_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction AND_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction AND_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction AND_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = AND(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
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

Instruction XOR_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = XOR(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction XOR_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction XOR_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction XOR_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction XOR_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction XOR_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction XOR_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction XOR_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction XOR_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = XOR(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
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

Instruction OR_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = OR(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction OR_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction OR_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction OR_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction OR_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction OR_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction OR_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction OR_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction OR_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = OR(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
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

Instruction CP_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        CP(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction CP_A() {
    return {[](Cpu& cpu, Operand&) {
        CP(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CP_B() {
    return {[](Cpu& cpu, Operand&) {
        CP(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CP_C() {
    return {[](Cpu& cpu, Operand&) {
        CP(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CP_D() {
    return {[](Cpu& cpu, Operand&) {
        CP(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CP_E() {
    return {[](Cpu& cpu, Operand&) {
        CP(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CP_H() {
    return {[](Cpu& cpu, Operand&) {
        CP(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CP_L() {
    return {[](Cpu& cpu, Operand&) {
        CP(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CP_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        CP(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction PUSH_AF() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-1), cpu.m_reg_a);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-2), cpu.m_reg_f);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }, implied};
}

Instruction PUSH_BC() {
    return {[](Cpu& cpu, Operand& operand) {
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-1), cpu.m_reg_b);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-2), cpu.m_reg_c);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }, implied};
}

Instruction PUSH_DE() {
    return {[](Cpu& cpu, Operand& operand) {
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-1), cpu.m_reg_d);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-2), cpu.m_reg_e);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }, implied};
}

Instruction PUSH_HL() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-1), cpu.m_reg_h);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-2), cpu.m_reg_l);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }, implied};
}

Instruction POP_AF() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_f = cpu.m_memory_controller->read(cpu.m_stack_ptr) & 0xF0u;
        cpu.m_reg_a = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction POP_BC() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_c = cpu.m_memory_controller->read(cpu.m_stack_ptr) ;
        cpu.m_reg_b = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction POP_DE() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_e = cpu.m_memory_controller->read(cpu.m_stack_ptr) ;
        cpu.m_reg_d = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction POP_HL() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_stack_ptr) ;
        cpu.m_reg_h = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
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

Instruction ADC_A_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = ADC(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction ADC_A_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADC_A_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADC_A_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADC_A_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADC_A_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADC_A_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADC_A_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADC_A_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = ADC(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LDH_ADDR_A8_A() {
    return  {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        const auto address = static_cast<uint16_t>(0xFF00 + value);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);    
        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LDH_A_ADDR_A8() {
    return {[](Cpu& cpu, Operation& op) {
        const auto address = static_cast<uint16_t>(0xFF00 + std::get<uint8_t>(op));
        cpu.m_reg_a = cpu.m_memory_controller->read(address);             
        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LD_ADDR_C_A() {
    return {[](Cpu& cpu, Operand&) {        
        const auto address = static_cast<uint16_t>(0xFF00 + cpu.m_reg_c);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
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

Instruction SBC_A_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = SBC(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction SBC_A_A() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SBC_A_B() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SBC_A_C() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SBC_A_D() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SBC_A_E() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SBC_A_H() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SBC_A_L() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SBC_A_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.m_reg_a = SBC(cpu.m_reg_a, value, cpu.m_reg_f);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction PREFIX_CB() {

    auto delta_pc = 2;
    return {delta_pc, [](Cpu& cpu) {

        const auto cb_opcode = static_cast<CBCode>(cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
        const auto result = fetch_cb(cb_opcode);
        return result.operation(cpu);
    }};
}

Instruction LD_ADDR_HLD_A() {
    return {[](Cpu& cpu, Operand&) {
            
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);

        address--;

        cpu.m_reg_h = static_cast<uint8_t>(address >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(address & 0xFFu);
        
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_A_ADDR_HLD() {
    return {[](Cpu& cpu, Operand&) {
        
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);

        address--;
        cpu.m_reg_h = static_cast<uint8_t>(address >> 8u);
        cpu.m_reg_l = static_cast<uint8_t>(address & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction CPL() {
    return {[](Cpu& cpu, Operand&){
        cpu.m_reg_a ^= 0xFF;

        set_bit(cpu.m_reg_f, Cpu::sub_flag);
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
        
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}