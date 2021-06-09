#include "Cpu/Operations.hpp"

#include <stdio.h>

#include "Utilities/BitOperations.h"
#include "Cpu/Cpu.hpp"
#include "Cpu/Interpreter.hpp"
#include "Cpu/CBOpcodes.hpp"
#include "Memory/Memory_Controller.hpp"

Instruction NOP() {
    return {[](Cpu&, Operand&) { return 4;}, implied};
}

Instruction STOP() {
    return {[](Cpu&, Operand&){ return 4;}, implied};
}

Instruction HALT() {
    return {[](Cpu& cpu, Operand&) {
        
        constexpr auto cycles = 4;
        if(cpu.interrupts_enabled) {
            cpu.is_halted = true;
        } else {

            const uint16_t interrupt_request_addr = 0xFF0F;
            const uint16_t interrupt_enable_addr = 0xFFFF;

            const auto interrupt_request = read(cpu.memory_controller,interrupt_request_addr);
            const auto interrupt_enable = read(cpu.memory_controller,interrupt_enable_addr);

            if((interrupt_request & interrupt_enable & 0x1Fu) == 0) {
                cpu.is_halted = true;
            } else {
                printf("HALT BUG");
                exit(1);
            }
        }
        return cycles;
    }, implied};
}

Instruction RST(uint8_t address) {
    return {[address](Cpu& cpu, Operand&){
        
        const auto pc_high = static_cast<uint8_t>(cpu.program_counter >> 8u);
        const auto pc_low =  static_cast<uint8_t>(cpu.program_counter & 0xFFu);

        write(cpu.memory_controller, static_cast<uint16_t>(cpu.stack_ptr - 1), pc_high);
        write(cpu.memory_controller, static_cast<uint16_t>(cpu.stack_ptr - 2), pc_low);

        cpu.program_counter = combine_bytes(0x00, address);
        cpu.stack_ptr = static_cast<uint16_t>(cpu.stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }, implied};
}

Instruction DI() {
    return {[](Cpu& cpu, Operand&) {
        cpu.should_disable_interrupts = true;
        return 4;
    }, implied};
}

Instruction EI() {
    return {[](Cpu& cpu, Operand&) {
        cpu.should_enable_interrupts = true;
        return 4;
    }, implied};
}

int jump_relative(Cpu& cpu, Operand& op) {
    const auto distance = static_cast<int8_t>(std::get<uint8_t>(op));
    cpu.program_counter = static_cast<uint16_t>(cpu.program_counter + distance);
    return 12;
}

Instruction JR() {
    return {[](Cpu& cpu, Operand& op) {
        return jump_relative(cpu, op);
    }, immediate};
}

Instruction JR_NZ() {
    return {[](Cpu& cpu, Operand& op) {
        return !test_flag(cpu.registers[Register_F], Flag_Zero) ? jump_relative(cpu, op) : 8;
    }, immediate};
}

Instruction JR_Z() {
    return {[](Cpu& cpu, Operand& op) {
        return test_flag(cpu.registers[Register_F], Flag_Zero) ? jump_relative(cpu, op) : 8;
    }, immediate};
}

Instruction JR_NC() {
    return {[](Cpu& cpu, Operand& op) {
        return !test_flag(cpu.registers[Register_F], Flag_Carry) ? jump_relative(cpu, op) : 8;
    }, immediate};
}

Instruction JR_C() {
    return {[](Cpu& cpu, Operand& op) {
        return test_flag(cpu.registers[Register_F], Flag_Carry) ? jump_relative(cpu, op) : 8;
    }, immediate};
}

int ret(Cpu& cpu) {            
    const auto pc_low = read(cpu.memory_controller,cpu.stack_ptr);
    const auto pc_high = read(cpu.memory_controller,static_cast<uint16_t>(cpu.stack_ptr + 1));
    
    cpu.program_counter = combine_bytes(pc_high, pc_low);
    cpu.stack_ptr = static_cast<uint16_t>(cpu.stack_ptr + 2);
    constexpr auto cycles = 16;
    return cycles;
}

Instruction RET() {
    return {[](Cpu& cpu, Operand&) {
        return ret(cpu);
    }, implied};
}

Instruction RET_NZ() {
    return {[](Cpu& cpu, Operand&) {  
        return !test_flag(cpu.registers[Register_F], Flag_Zero) ? ret(cpu) : 8;
    }, implied};
}

Instruction RET_Z() {
    return {[](Cpu& cpu, Operand&) {
        return test_flag(cpu.registers[Register_F], Flag_Zero) ? ret(cpu) : 8; 
    }, implied};
}

Instruction RET_NC() {
    return {[](Cpu& cpu, Operand&) {
        return !test_flag(cpu.registers[Register_F], Flag_Carry) ? ret(cpu) : 8;
    }, implied};
}

Instruction RET_C() {
    return {[](Cpu& cpu, Operand&) {
       return test_flag(cpu.registers[Register_F], Flag_Carry) ? ret(cpu) : 8;
    }, implied};
}

Instruction RETI() {
    return {[](Cpu& cpu, Operand&) {
        cpu.interrupts_enabled = true;
        return ret(cpu);
    }, implied};
}

int jump(Cpu& cpu, Operand& op) {
    const auto address = std::get<uint16_t>(op);
    cpu.program_counter = address; 
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
        return !test_flag(cpu.registers[Register_F], Flag_Zero) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_Z() {
    return {[](Cpu& cpu, Operand& op) {
        return test_flag(cpu.registers[Register_F], Flag_Zero) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_NC() {
    return {[](Cpu& cpu, Operand& op) {
        return !test_flag(cpu.registers[Register_F], Flag_Carry) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_C() {
    return {[](Cpu& cpu, Operand& op) {
        return test_flag(cpu.registers[Register_F], Flag_Carry) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = read_register_pair(cpu, Register_H, Register_L);
        cpu.program_counter = address;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

int call(Cpu& cpu, Operand& op) {

    const auto pc_high = static_cast<uint8_t>(cpu.program_counter >> 8u);
    const auto pc_low = static_cast<uint8_t>(cpu.program_counter & 0xFFu);
    
    write(cpu.memory_controller, static_cast<uint16_t>(cpu.stack_ptr - 1), pc_high);
    write(cpu.memory_controller, static_cast<uint16_t>(cpu.stack_ptr - 2), pc_low);
    cpu.stack_ptr = static_cast<uint16_t>(cpu.stack_ptr -2);
    
     cpu.program_counter = std::get<uint16_t>(op);

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
        return !test_flag(cpu.registers[Register_F], Flag_Zero) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction CALL_Z() {
    return {[](Cpu& cpu, Operand& op) {
        return test_flag(cpu.registers[Register_F], Flag_Zero) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction CALL_NC() {
    return {[](Cpu& cpu, Operand& op) {
        return !test_flag(cpu.registers[Register_F], Flag_Carry) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction CALL_C() {
    return {[](Cpu& cpu, Operand& op) {
        return test_flag(cpu.registers[Register_F], Flag_Carry) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction LD_R_R(Cpu_Register dst, Cpu_Register src) {
    return {[dst, src](Cpu& cpu, Operand&){

        uint8_t* flags = &(cpu.registers[Register_F]);

        cpu.registers[dst] =  cpu.registers[src];
        return 4;
    }, implied};
}

Instruction LD_R_D8(Cpu_Register dst) {
    return {[dst](Cpu& cpu, Operand& op) {
        cpu.registers[dst] =  std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction LD_A_ADDR_RR(Cpu_Register r1, Cpu_Register r2) {
    return {[r1, r2](Cpu& cpu, Operand&) {        
        const auto address = read_register_pair(cpu, r1, r2);
        cpu.registers[Register_A] =  read(cpu.memory_controller,address);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_A_ADDR_A16() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.registers[Register_A] =  std::get<uint8_t>(op);
        constexpr auto cycles = 16;
        return cycles;
    }, extended_address};
}

Instruction LD_A_ADDR_C() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = static_cast<uint16_t>(0xFF00 + cpu.registers[Register_C]);
        cpu.registers[Register_A] =  read(cpu.memory_controller,address);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_ADDR_A16_SP() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = std::get<uint16_t>(op);        
        write(cpu.memory_controller, address, static_cast<uint8_t>(cpu.stack_ptr & 0xFFu));
        write(cpu.memory_controller, static_cast<uint16_t>(address + 1), static_cast<uint8_t>(cpu.stack_ptr >> 8u));
        constexpr auto cycles = 20;
        return cycles;
    }, immediate_extended};
}

Instruction LDI_ADDR_HL_A() {
    return {[](Cpu& cpu, Operand&) {
        auto address = read_register_pair(cpu, Register_H, Register_L);
        
        write(cpu.memory_controller, address, cpu.registers[Register_A]);

        address++;
        cpu.registers[Register_H] =  static_cast<uint8_t>(address >> 8u);
        cpu.registers[Register_L] =  static_cast<uint8_t>(address & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LDI_A_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        auto address = read_register_pair(cpu, Register_H, Register_L);
        cpu.registers[Register_A] = read(cpu.memory_controller,address);
        
        address++;
        cpu.registers[Register_H] = static_cast<uint8_t>(address >> 8u);
        cpu.registers[Register_L] = static_cast<uint8_t>(address & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_ADDR_RR_A(Cpu_Register r1, Cpu_Register r2) {
    return {[r1, r2](Cpu& cpu, Operand&) {
        const auto address = read_register_pair(cpu, r1, r2);
        write(cpu.memory_controller, address, cpu.registers[Register_A]);   
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_R_ADDR_HL(Cpu_Register dst) {
    return {[dst](Cpu& cpu, Operand& op) {
        cpu.registers[dst] =  std::get<uint8_t>(op);
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LD_ADDR_HL_R(Cpu_Register r) {
    return {[r](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        write(cpu.memory_controller, address, cpu.registers[r]);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};    
}

Instruction LD_ADDR_HL_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        const auto value = std::get<uint8_t>(op);
        write(cpu.memory_controller, address, value);
        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LD_ADDR_HL_ADDR_HL() {    
    printf("Unimplemented operation: LD ADDR HL ADDR HL");
    exit(1);
}

Instruction LD_ADDR_A16_A() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = std::get<uint16_t>(op);
        write(cpu.memory_controller, address, cpu.registers[Register_A]);
        constexpr auto cycles = 16;
        return cycles;
    }, immediate_extended};
}

Instruction LD_RR_D16(Cpu_Register r1, Cpu_Register r2) {
    return {[r1, r2](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint16_t>(op);

        cpu.registers[r2] =  static_cast<uint8_t>(value & 0xFFu);
        cpu.registers[r1] =  static_cast<uint8_t>(value >> 8u);

        constexpr auto cycles = 12;
        return cycles;
    }, immediate_extended};
}

Instruction LD_HL_SPR8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto distance = std::get<uint8_t>(op);

        uint8_t* flags = &(cpu.registers[Register_F]);

        half_carry_8bit(static_cast<uint8_t>(cpu.stack_ptr), distance)     ?
            set_flag(flags, Flag_Half_Carry)  :
            clear_flag(flags, Flag_Half_Carry);


        overflows_8bit(static_cast<uint8_t>(cpu.stack_ptr), distance)  ? 
            set_flag(flags, Flag_Carry)   :
            clear_flag(flags, Flag_Carry);

        const auto result = static_cast<uint16_t>(cpu.stack_ptr + static_cast<int8_t>(distance));
        cpu.registers[Register_H] =  static_cast<uint8_t>(result >> 8u);
        cpu.registers[Register_L] =  static_cast<uint8_t>(result & 0xFFu);

        clear_flag(flags, Flag_Zero);
        clear_flag(flags, Flag_Sub);

        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LD_SP_D16() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.stack_ptr = std::get<uint16_t>(op);
        constexpr auto cycles = 12;
        return cycles;
    }, immediate_extended};
}

Instruction LD_SP_HL() {
    return {[](Cpu& cpu, Operand&) {
        cpu.stack_ptr =  combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

uint8_t ADD_8bit(uint8_t first, uint8_t second, uint8_t* flags) {
    
    half_carry_8bit(first, second)             ? 
        set_bit(flags, Flag_Half_Carry)  :
        clear_bit(flags, Flag_Half_Carry);

    overflows_8bit(first, second)          ?
        set_bit(flags, Flag_Carry)   :
        clear_bit(flags, Flag_Carry);

    first = static_cast<uint8_t>(first + second);

    first == 0 ? set_bit(flags, Flag_Zero) :
        clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);

    return first;
}

Instruction ADD_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);

        cpu.registers[Register_A] = ADD_8bit(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction ADD_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {

        const auto a = cpu.registers[Register_A];
        const auto r = cpu.registers[src];
        
        cpu.registers[Register_A] = ADD_8bit(a, r, &(cpu.registers[Register_F]));

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = ADD_8bit(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

uint16_t ADD_16bit(uint16_t first, uint16_t second, uint8_t* flags) {
    
    overflows_16bit(first, second) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);

    half_carry_16bit(first, second) ? set_bit(flags, Flag_Half_Carry) : clear_bit(flags, Flag_Half_Carry);

    first = static_cast<uint16_t>(first + second);

    clear_bit(flags, Flag_Sub);

    return first;
}

Instruction ADD_HL_RR(Cpu_Register r1, Cpu_Register r2) {
    return {[r1, r2](Cpu& cpu, Operand&) {
        
        const auto hl = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        const auto value = combine_bytes(cpu.registers[r1], cpu.registers[r2]);

        const auto result = ADD_16bit(hl, value, &(cpu.registers[Register_F]));

        cpu.registers[Register_H] =  static_cast<uint8_t>(result >> 8u);
        cpu.registers[Register_L] =  static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied}; 
}

Instruction ADD_HL_SP() {
    return {[](Cpu& cpu, Operand&) {
        
        const auto hl = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        const auto result = ADD_16bit(hl, cpu.stack_ptr, &(cpu.registers[Register_F]));

        cpu.registers[Register_H] =  static_cast<uint8_t>(result >> 8u);
        cpu.registers[Register_L] =  static_cast<uint8_t>(result & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

uint8_t SUB(uint8_t first, uint8_t second, uint8_t* flags) {
    
    half_borrow_8bit(first, second)            ?
        set_bit(flags,   Flag_Half_Carry)  :
        clear_bit(flags, Flag_Half_Carry);

    underflows_8bit(first, second)         ?
        set_bit(flags,   Flag_Carry)   :
        clear_bit(flags, Flag_Carry);

    first = static_cast<uint8_t>(first - second);

    first == 0 ? set_bit(flags, Flag_Zero) :
        clear_bit(flags,        Flag_Zero);

    set_bit(flags, Flag_Sub);

    return first;
}

Instruction SUB_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = SUB(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction SUB_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto acc = cpu.registers[Register_A];
        const auto r = cpu.registers[src];
        
        cpu.registers[Register_A] = SUB(acc, r, &(cpu.registers[Register_F]));

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SUB_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = SUB(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

uint8_t INC(uint8_t value, uint8_t* flags) {
    
    half_carry_8bit(value, 1) ? set_bit(flags, Flag_Half_Carry) : clear_bit(flags, Flag_Half_Carry);

    value++;

    value == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);

    return value;
}

Instruction INC_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {
        uint8_t r = cpu.registers[src];
        cpu.registers[src] = INC(r, &(cpu.registers[Register_F]));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction INC_RR(Cpu_Register r1, Cpu_Register r2) {
    return {[r1, r2](Cpu& cpu, Operand&) {        
        auto value = combine_bytes(cpu.registers[r1], cpu.registers[r2]);
        value++;

        cpu.registers[r1] =  static_cast<uint8_t>(value >> 8u);
        cpu.registers[r2] =  static_cast<uint8_t>(value & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction INC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller,address);

        value = INC(value, &(cpu.registers[Register_F]));
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction INC_SP() {
    return {[](Cpu& cpu, Operand&) {
        cpu.stack_ptr++;
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

uint8_t DEC(uint8_t value, uint8_t* flags) {
    
    half_borrow_8bit(value, 1)                ?
        set_bit(flags, Flag_Half_Carry)  :
        clear_bit(flags, Flag_Half_Carry);

    value--;
    
    value == 0 ? set_bit(flags, Flag_Zero) :
        clear_bit(flags, Flag_Zero);

    set_bit(flags, Flag_Sub);

    return value;
}

Instruction DEC_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto r = cpu.registers[src];
        cpu.registers[src] = DEC(r, &(cpu.registers[Register_F]));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DEC_RR(Cpu_Register r1, Cpu_Register r2) { 
    return {[r1, r2](Cpu& cpu, Operand&) {

        auto value = combine_bytes(cpu.registers[r1], cpu.registers[r2]);
        value--;

        cpu.registers[r1] =  static_cast<uint8_t>(value >> 8u);
        cpu.registers[r2] =  static_cast<uint8_t>(value & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction DEC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller,address);
        value = DEC(value, &(cpu.registers[Register_F]));
        write(cpu.memory_controller, address, value);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction DEC_SP() {
    return {[](Cpu& cpu, Operand&) {
        cpu.stack_ptr--;
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction SCF() {
    return {[](Cpu& cpu, Operand&) {

        uint8_t* flags = &(cpu.registers[Register_F]);

        clear_flag(flags, Flag_Sub);
        clear_flag(flags, Flag_Half_Carry);
        set_flag(flags, Flag_Carry);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CCF() {
    return {[](Cpu& cpu, Operand&) {

        uint8_t* flags = &(cpu.registers[Register_F]);

        clear_flag(flags, Flag_Sub);
        clear_flag(flags, Flag_Half_Carry);

        test_flag(*flags, Flag_Carry) ? 
            clear_flag(flags, Flag_Carry) : set_flag(flags, Flag_Carry);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RRCA() {
    return {[](Cpu& cpu, Operand&) {

        uint8_t* flags = &(cpu.registers[Register_F]);

        test_bit_8bit(cpu.registers[Register_A], 0) ? set_flag(flags, Flag_Carry)
            : clear_flag(flags, Flag_Carry);
        
        cpu.registers[Register_A] = rotate_right(cpu.registers[Register_A], 1);

        clear_flag(flags, Flag_Zero);
        clear_flag(flags, Flag_Sub);
        clear_flag(flags, Flag_Half_Carry);

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RRA() {
    return {[](Cpu& cpu, Operand&) {

        uint8_t* flags = &(cpu.registers[Register_F]);
        
        auto a = cpu.registers[Register_A];

        const auto new_carry_flag = test_bit_8bit(a, 0);
        a = static_cast<uint8_t>(a >> 1u);

        test_flag(*flags, Flag_Carry) ? set_bit(&a, 7) 
            : clear_bit(&a, 7);
        
        cpu.registers[Register_A] =  a;

        new_carry_flag ? set_flag(flags, Flag_Carry) 
            : clear_flag(flags, Flag_Carry);
        
        clear_flag(flags, Flag_Zero);
        clear_flag(flags, Flag_Sub);
        clear_flag(flags, Flag_Half_Carry);
    
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RLA() {
    return {[](Cpu& cpu, Operand&) {
        
        auto a = cpu.registers[Register_A];
        uint8_t* flags = &(cpu.registers[Register_F]);

        const auto new_carry_flag = test_bit_8bit(a, 7);
        a =  static_cast<uint8_t>(a << 1u);

        test_flag(*flags, Flag_Carry) ? set_bit(&a, 0) : clear_bit(&a, 0);
        
        cpu.registers[Register_A] =  a;

        new_carry_flag ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

        clear_flag(flags, Flag_Zero);
        clear_flag(flags, Flag_Sub);
        clear_flag(flags, Flag_Half_Carry);
        
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RLCA() {
    return {[](Cpu& cpu, Operand&) {

        auto a = cpu.registers[Register_A];
        uint8_t* flags = &(cpu.registers[Register_F]);

        test_bit_8bit(a, 7) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

        cpu.registers[Register_A] = rotate_left(a, 1);

        clear_flag(flags, Flag_Zero);
        clear_flag(flags, Flag_Sub);
        clear_flag(flags, Flag_Half_Carry);

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DAA() {    
    return {[](Cpu& cpu, Operand&) {

        auto a = cpu.registers[Register_A];
        uint8_t* flags = &(cpu.registers[Register_F]);

        if(!test_flag(*flags, Flag_Sub)) {
            if(test_flag(*flags, Flag_Carry) || a > 0x99) {
                a += 0x60;
                set_flag(flags, Flag_Carry);
            }

            if(test_flag(*flags, Flag_Half_Carry) || (a & 0x0Fu) > 0x09) {
                a += 0x06;
            }
        } else {
            if(test_flag(*flags, Flag_Carry)) {
                a -= 0x60;
            }
            if(test_flag(*flags, Flag_Half_Carry)) {
                a -= 0x06;
            }
        }

        clear_flag(flags, Flag_Half_Carry);

        a == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

        cpu.registers[Register_A] =  a;

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_SP_R8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto distance = std::get<uint8_t>(op);

        uint8_t* flags = &(cpu.registers[Register_F]);

        half_carry_8bit(static_cast<uint8_t>(cpu.stack_ptr), distance)     ?
            set_flag(flags, Flag_Half_Carry)  :
            clear_flag(flags, Flag_Half_Carry);


        overflows_8bit(static_cast<uint8_t>(cpu.stack_ptr), distance)  ? 
            set_flag(flags, Flag_Carry)   :
            clear_flag(flags, Flag_Carry);


        cpu.stack_ptr = static_cast<uint16_t>(cpu.stack_ptr + static_cast<int8_t>(distance));

        clear_flag(flags, Flag_Zero);
        clear_flag(flags, Flag_Sub);

        constexpr auto cycles = 16;
        return cycles;
    }, immediate};    
}

uint8_t AND(uint8_t first, uint8_t second, uint8_t* flags) {
    
    first &= second;

    first == 0 ? set_bit(flags, Flag_Zero) :
        clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    set_bit(flags, Flag_Half_Carry);
    clear_bit(flags, Flag_Carry);

    return first;
}

Instruction AND_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = AND(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction AND_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto a = cpu.registers[Register_A];
        const auto r = cpu.registers[src];
        
        cpu.registers[Register_A] = AND(a, r, &(cpu.registers[Register_F]));

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction AND_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = AND(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

uint8_t XOR(uint8_t first, uint8_t second, uint8_t* flags) {
    
    first ^= second;
    first == 0 ? set_bit(flags, Flag_Zero) :
        clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);
    clear_bit(flags, Flag_Carry);

    return first;
}

Instruction XOR_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = XOR(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction XOR_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {
        auto a = cpu.registers[Register_A];
        const auto r = cpu.registers[src];

        a = XOR(a, r, &(cpu.registers[Register_F]));

        cpu.registers[Register_A] =  a;

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction XOR_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = XOR(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

uint8_t OR(uint8_t first, uint8_t second, uint8_t* flags) {
    
    first |= second;
    first == 0 ? set_bit(flags, Flag_Zero) :
        clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);
    clear_bit(flags, Flag_Carry);

    return first;
}

Instruction OR_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = OR(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction OR_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {
        cpu.registers[Register_A] = OR(cpu.registers[Register_A], cpu.registers[src], &(cpu.registers[Register_F]));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction OR_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = OR(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

void CP(uint8_t first, uint8_t second, uint8_t* flags) {

    underflows_8bit(first, second)         ?
        set_bit(flags, static_cast<int>(Flag_Carry))   :
        clear_bit(flags, static_cast<int>(Flag_Carry));

    half_borrow_8bit(first, second)            ?
        set_bit(flags,      Flag_Half_Carry)  :
        clear_bit(flags,    Flag_Half_Carry);

    (first == second) ? 
        set_bit(flags,      Flag_Zero) :
        clear_bit(flags,    Flag_Zero);

    set_bit(flags, Flag_Sub);
}

Instruction CP_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        CP(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction CP_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto a = cpu.registers[Register_A];
        const auto r = cpu.registers[src];
        CP(a, r, &(cpu.registers[Register_F]));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CP_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        CP(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction PUSH_RR(Cpu_Register r1, Cpu_Register r2) {
    return {[r1, r2](Cpu& cpu, Operand&) {
        write(cpu.memory_controller, static_cast<uint16_t>(cpu.stack_ptr-1), cpu.registers[r1]);
        write(cpu.memory_controller, static_cast<uint16_t>(cpu.stack_ptr-2), cpu.registers[r2]);
        cpu.stack_ptr = static_cast<uint16_t>(cpu.stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }, implied};
}

Instruction POP_AF() {
    return {[](Cpu& cpu, Operand&) {
        cpu.registers[Register_F] =  read(cpu.memory_controller,cpu.stack_ptr) & 0xF0u;
        cpu.registers[Register_A] =  read(cpu.memory_controller,static_cast<uint16_t>(cpu.stack_ptr + 1));
        cpu.stack_ptr = static_cast<uint16_t>(cpu.stack_ptr + 2);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction POP_RR(Cpu_Register r1, Cpu_Register r2) {
    return {[r1, r2](Cpu& cpu, Operand&) {
        cpu.registers[r2] =  read(cpu.memory_controller,cpu.stack_ptr);
        cpu.registers[r1] =  read(cpu.memory_controller,static_cast<uint16_t>(cpu.stack_ptr + 1));
        cpu.stack_ptr = static_cast<uint16_t>(cpu.stack_ptr + 2);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

uint8_t ADC(uint8_t first, uint8_t second, uint8_t* flags) {
    
    const auto carry_value = test_bit_8bit(*flags, Flag_Carry) ? 1 : 0;

    half_carry_8bit(first, second)       ?
        set_bit(flags,      Flag_Half_Carry)          :
        clear_bit(flags,    Flag_Half_Carry);

    overflows_8bit(first, second)        ?
        set_bit(flags,      Flag_Carry)               :
        clear_bit(flags,    Flag_Carry);

    first = static_cast<uint8_t>(first + second);

    if(!test_bit_8bit(*flags, Flag_Half_Carry)) {
        half_carry_8bit(first, static_cast<uint8_t>(carry_value))       ?
        set_bit(flags,      Flag_Half_Carry)          :
        clear_bit(flags,    Flag_Half_Carry);
    }
    
    if(!test_bit_8bit(*flags, Flag_Carry)) {
        overflows_8bit(first, static_cast<uint8_t>(carry_value))        ?
            set_bit(flags,      Flag_Carry)               :
            clear_bit(flags,    Flag_Carry);
    }

    first = static_cast<uint8_t>(first + carry_value);

    first == 0 ? set_bit(flags, Flag_Zero) :
        clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    
    return first;
}

Instruction ADC_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = ADC(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction ADC_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto r = cpu.registers[src];
        const auto a = cpu.registers[Register_A];
        cpu.registers[Register_A] = ADC(a, r, &(cpu.registers[Register_F]));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADC_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.registers[Register_A] = ADC(cpu.registers[Register_A], value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LDH_ADDR_A8_A() {
    return  {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        const auto address = static_cast<uint16_t>(0xFF00 + value);
        write(cpu.memory_controller, address, cpu.registers[Register_A]);    
        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LDH_A_ADDR_A8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = static_cast<uint16_t>(0xFF00 + std::get<uint8_t>(op));
        cpu.registers[Register_A] =  read(cpu.memory_controller,address);             
        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LD_ADDR_C_A() {
    return {[](Cpu& cpu, Operand&) {        
        const auto address = static_cast<uint16_t>(0xFF00 + cpu.registers[Register_C]);
        write(cpu.memory_controller, address, cpu.registers[Register_A]);
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

uint8_t SBC(uint8_t first, uint8_t second, uint8_t* flags) {
    
    const auto carry_value = test_bit_8bit(*flags, Flag_Carry) ? 1 : 0;

    half_borrow_8bit(first, second)            ?
        set_bit(flags, Flag_Half_Carry)  :
        clear_bit(flags, Flag_Half_Carry);

    underflows_8bit(first, second)         ?
        set_bit(flags, Flag_Carry)   :
        clear_bit(flags, Flag_Carry);
    
    first = static_cast<uint8_t>(first - second);

    if(!test_bit_8bit(*flags, Flag_Half_Carry)) {
        half_borrow_8bit(first, static_cast<uint8_t>(carry_value))       ?
            set_bit(flags, Flag_Half_Carry)  :
            clear_bit(flags, Flag_Half_Carry);
    }

    if(!test_bit_8bit(*flags, Flag_Carry)) {
        underflows_8bit(first, static_cast<uint8_t>(carry_value))         ?
            set_bit(flags, Flag_Carry)   :
            clear_bit(flags, Flag_Carry);
    }

    first = static_cast<uint8_t>(first - carry_value);

    first == 0 ? set_bit(flags, Flag_Zero) :
        clear_bit(flags, Flag_Zero);

    set_bit(flags, Flag_Sub);

    return first;
}

Instruction SBC_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        const auto a = cpu.registers[Register_A];
        cpu.registers[Register_A] = SBC(a, value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction SBC_R(Cpu_Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto a = cpu.registers[Register_A];
        const auto r = cpu.registers[src];
        cpu.registers[Register_A] = SBC(a, r, &(cpu.registers[Register_F]));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SBC_A_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        auto a = cpu.registers[Register_A];
        cpu.registers[Register_A] = SBC(a, value, &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction PREFIX_CB() {
    return {[](Cpu& cpu, Operand&) {
        const auto cb_opcode = static_cast<CBCode>(read(cpu.memory_controller,static_cast<uint16_t>(cpu.program_counter - 1)));
        const auto instruction = fetch_cb(cb_opcode);
        auto operand = instruction.read_operand(cpu);
        return instruction.execute(cpu, operand);
    }, [](Cpu& cpu) -> Operand {
        cpu.program_counter += 2;
        return {static_cast<uint8_t>(0)};
    }};
}

Instruction LD_ADDR_HLD_A() {
    return {[](Cpu& cpu, Operand&) {
            
        auto address = read_register_pair(cpu, Register_H, Register_L);
        write(cpu.memory_controller, address, cpu.registers[Register_A]);

        address--;

        cpu.registers[Register_H] =  static_cast<uint8_t>(address >> 8u);
        cpu.registers[Register_L] =  static_cast<uint8_t>(address & 0xFFu);
        
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_A_ADDR_HLD() {
    return {[](Cpu& cpu, Operand&) {
        
        auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        cpu.registers[Register_A] =  read(cpu.memory_controller,address);

        address--;
        cpu.registers[Register_H] =  static_cast<uint8_t>(address >> 8u);
        cpu.registers[Register_L] =  static_cast<uint8_t>(address & 0xFFu);

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction CPL() {
    return {[](Cpu& cpu, Operand&){
        auto a = cpu.registers[Register_A];
        a ^= 0xFF;
        cpu.registers[Register_A] =  a;

        uint8_t* flags = &(cpu.registers[Register_F]);

        set_flag(flags, Flag_Sub);
        set_flag(flags, Flag_Half_Carry);
        
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}