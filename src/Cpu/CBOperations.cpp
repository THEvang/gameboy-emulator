#include "Cpu/CBOperations.hpp"

#include "Memory/Memory_Controller.h"
#include "Cpu/Interpreter.hpp"
#include "Utilities/BitOperations.h"
#include "Adressing_Modes.hpp"

uint8_t rlc(uint8_t value, uint8_t* flags) {

    test_bit_8bit(value, 7) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);

    value = rotate_left(value, 1);

    value == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return value;
}

Instruction RLC_R(Cpu_Register r) {
    return {[r](Cpu& cpu, Operand&) {
        cpu.registers[r] = rlc(cpu.registers[r], &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction RLC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller, address);

        value = rlc(value, &(cpu.registers[Register_F]));

        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t RRC(uint8_t value, uint8_t* flags) {
    
    test_bit_8bit(value, 0) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);
    
    value = rotate_right(value, 1);

    value == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);
    
    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return value;
}

Instruction RRC_R(Cpu_Register r) {
    return {[r](Cpu& cpu, Operand&) {
        cpu.registers[r] = RRC(cpu.registers[r], &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, &none};   
}

Instruction RRC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller, address);

        value = RRC(value, &(cpu.registers[Register_F]));
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none}; 
}

uint8_t RL(uint8_t value, uint8_t* flags) {
    
    const auto new_carry_flag = test_bit_8bit(value, 7);
    value = static_cast<uint8_t>(value << 1u);

    test_bit_8bit(*flags, Flag_Carry) ? set_bit(&value, 0)
        : clear_bit(&value, 0);
    
    new_carry_flag ? set_bit(flags, Flag_Carry)
        : clear_bit(flags, Flag_Carry);

    value == 0 ? set_bit(flags, Flag_Zero) :
        clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return value;
}

Instruction RL_R(Cpu_Register r) {
    return {[r](Cpu& cpu, Operand&) {
        cpu.registers[r] = RL(cpu.registers[r], &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction RL_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller, address);

        value = RL(value, &(cpu.registers[Register_F]));
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t SRL(uint8_t value, uint8_t* flags) {

    test_bit_8bit(value, 0)                      ? 
        set_bit(flags, Flag_Carry)   :
        clear_bit(flags, Flag_Carry);
    
    value = static_cast<uint8_t>(value >> 1u);
    clear_bit(&value, 7);

    value == 0                            ?
        set_bit(flags, Flag_Zero)    :
        clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return value;
}

Instruction SRL_R(Cpu_Register r) {
    return {[r](Cpu& cpu, Operand&) {
        cpu.registers[r] = SRL(cpu.registers[r], &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction SRL_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller,address);
        value = SRL(value, &(cpu.registers[Register_F]));
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t SLA(uint8_t value, uint8_t* flags) {

    test_bit_8bit(value, 7)                      ? 
        set_bit(flags, Flag_Carry)   :
        clear_bit(flags, Flag_Carry);
    
    value = static_cast<uint8_t>(value << 1u);
    clear_bit(&value, 0);

    value == 0                            ?
        set_bit(flags, Flag_Zero)    :
        clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return value;
}

Instruction SLA_R(Cpu_Register r) {
    return {[r](Cpu& cpu, Operand&){
        cpu.registers[r] = SLA(cpu.registers[r], &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction SLA_ADDR_HL() {
    return {[](Cpu& cpu, Operand&){
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller, address);
        value = SLA(value, &(cpu.registers[Register_F]));
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t SRA(uint8_t value, uint8_t* flags) {
    
    test_bit_8bit(value, 0)                      ? 
        set_bit(flags,      Flag_Carry)   :
        clear_bit(flags,    Flag_Carry);
    
    const auto old_msb = test_bit_8bit(value, 7);

    value = static_cast<uint8_t>(value >> 1u);

    old_msb ? set_bit(&value, 7) : clear_bit(&value, 7);

    value == 0                            ?
        set_bit(flags,      Flag_Zero)    :
        clear_bit(flags,    Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return value;
}

Instruction SRA_R(Cpu_Register r) {
    return {[r](Cpu& cpu, Operand&) {
        cpu.registers[r] = SRA(cpu.registers[r], &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, none}; 
}

Instruction SRA_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller, address);
        value = SRA(value, &(cpu.registers[Register_F]));
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t RR(uint8_t value, uint8_t* flags) {
    
    bool carry_status = test_bit_8bit(*flags, Flag_Carry);

    test_bit_8bit(value, 0)                  ? 
        set_bit(flags,      Flag_Carry)   :
        clear_bit(flags,    Flag_Carry);

    value = static_cast<uint8_t>(value >> 1u);
    carry_status ? set_bit(&value, 7) : clear_bit(&value, 7);

    value == 0 ? 
        set_bit(flags,      Flag_Zero) : 
        clear_bit(flags,    Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return value;
}

Instruction RR_R(Cpu_Register r) {
    return {[r](Cpu& cpu, Operand&) {
        cpu.registers[r] = RR(cpu.registers[r], &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction RR_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller, address);
        value = RR(value, &(cpu.registers[Register_F]));
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t SWAP(uint8_t value, uint8_t* flags) {

    swap_nibbles(&value);
    
    value == 0 ? 
        set_bit(flags, Flag_Zero) :
        clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);
    clear_bit(flags, Flag_Carry);

    return value;
}

Instruction SWAP_R(Cpu_Register r) {
    return {[r](Cpu& cpu, Operand&) {
        cpu.registers[r] = SWAP(cpu.registers[r], &(cpu.registers[Register_F]));
        constexpr auto cycles = 8;
        return cycles;
    }, none};   
}

Instruction SWAP_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller, address);
        value = SWAP(value, &(cpu.registers[Register_F]));
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

void BIT(uint8_t value, int n, uint8_t* flags) {
    
    test_bit_8bit(value, n) ? clear_bit(flags, Flag_Zero) :
        set_bit(flags, Flag_Zero);
    
    clear_bit(flags, Flag_Sub);
    set_bit(flags, Flag_Half_Carry);
}

Instruction BIT_R(Cpu_Register r, int n) {
    return {[r, n](Cpu& cpu, Operand&) {
        BIT(cpu.registers[r], n, &(cpu.registers[Register_F]));
        return 8;
    }, none};
}

Instruction BIT_ADDR_HL(int n) {
    return {[n](Cpu& cpu, Operand&) {    
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        const auto value = read(cpu.memory_controller, address);

        auto flags = cpu.registers[Register_F];
        BIT(value, n, &flags);
        write(cpu.memory_controller, address, value);
        cpu.registers[Register_F] = flags;

        constexpr auto cycles = 12;
        return cycles;
    }, none};
}

Instruction RES_R(Cpu_Register r, int n) {
    return {[r, n](Cpu& cpu, Operand&) {
        clear_bit(&(cpu.registers[r]), n);
        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction RES_ADDR_HL(int n) {
    return {[n](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller, address);
        clear_bit(&value, n);
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

Instruction SET_R(Cpu_Register r, int n) {
    return {[r, n](Cpu& cpu, Operand&) {
        auto value = cpu.registers[r];
        set_bit(&value, n);
        cpu.registers[r] = value;
        constexpr auto cycles = 8;
        return cycles;
    }, none}; 
}

Instruction SET_ADDR_HL(int n) {
    return {[n](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
        auto value = read(cpu.memory_controller, address);
        set_bit(&value, n);
        write(cpu.memory_controller, address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none}; 
}