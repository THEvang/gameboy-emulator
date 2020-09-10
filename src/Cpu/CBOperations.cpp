#include "Cpu/CBOperations.hpp"

#include "Memory/Memory_Controller.hpp"
#include "Cpu/Interpreter.hpp"
#include "BitOperations.hpp"
#include "Cpu/Cpu.hpp"

uint8_t rlc(uint8_t value, uint8_t& flags) {

    is_set(value, 7) ? set_bit(flags,   Cpu::to_index(Cpu::Flag::Carry)) : 
        clear_bit(flags,                Cpu::to_index(Cpu::Flag::Carry));

    value = rotate_left<uint8_t>(value, 1);

    value == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags,        Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    return value;
}

Instruction RLC_R(Cpu::Register r) {
    return {[r](Cpu& cpu, Operand&) {

        auto flags = cpu.get(Cpu::Register::F);
        cpu.set(r, rlc(cpu.get(r), flags));
        cpu.set(Cpu::Register::F, flags);

        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction RLC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);

        auto flags = cpu.get(Cpu::Register::F);
        value = rlc(value, flags);
        cpu.set(Cpu::Register::F, flags);

        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t RRC(uint8_t value, uint8_t& flags) {
    
    is_set(value, 0) ? set_bit(flags, Cpu::to_index(Cpu::Flag::Carry))
        : clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));
    
    value = rotate_right<uint8_t>(value, 1);

    value == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));
    
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    return value;
}

Instruction RRC_R(Cpu::Register r) {
    return {[r](Cpu& cpu, Operand&) {
        auto flags = cpu.get(Cpu::Register::F);
        cpu.set(r, RRC(cpu.get(r), flags));
        cpu.set(Cpu::Register::F, flags);
        constexpr auto cycles = 8;
        return cycles;
    }, none};   
}

Instruction RRC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);

        auto flags = cpu.get(Cpu::Register::F);
        value = RRC(value, flags);
        cpu.m_memory_controller->write(address, value);
        cpu.set(Cpu::Register::F, flags);

        constexpr auto cycles = 16;
        return cycles;
    }, none}; 
}

uint8_t RL(uint8_t value, uint8_t& flags) {
    
    const auto new_carry_flag = is_set(value, 7);
    value = static_cast<uint8_t>(value << 1u);

    is_set(flags, Cpu::to_index(Cpu::Flag::Carry)) ? set_bit(value, 0)
        : clear_bit(value, 0);
    
    new_carry_flag ? set_bit(flags, Cpu::to_index(Cpu::Flag::Carry))
        : clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));

    value == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    return value;
}

Instruction RL_R(Cpu::Register r) {
    return {[r](Cpu& cpu, Operand&) {
        auto flags = cpu.get(Cpu::Register::F);
        cpu.set(r, RL(cpu.get(r), flags));
        cpu.set(Cpu::Register::F, flags);
        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction RL_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);

        value = RL(value, cpu.get(Cpu::Register::F));
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t SRL(uint8_t value, uint8_t& flags) {

    is_set(value, 0)                      ? 
        set_bit(flags, Cpu::to_index(Cpu::Flag::Carry))   :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));
    
    value = static_cast<uint8_t>(value >> 1u);
    clear_bit(value, 7);

    value == 0                            ?
        set_bit(flags, Cpu::to_index(Cpu::Flag::Zero))    :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    return value;
}

Instruction SRL_R(Cpu::Register r) {
    return {[r](Cpu& cpu, Operand&) {
        auto flags = cpu.get(Cpu::Register::F);
        cpu.set(r, SRL(cpu.get(r), flags));
        cpu.set(Cpu::Register::F, flags);
        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction SRL_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);
        value = SRL(value, cpu.get(Cpu::Register::F));
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t SLA(uint8_t value, uint8_t& flags) {

    is_set(value, 7)                      ? 
        set_bit(flags, Cpu::to_index(Cpu::Flag::Carry))   :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));
    
    value = static_cast<uint8_t>(value << 1u);
    clear_bit(value, 0);

    value == 0                            ?
        set_bit(flags, Cpu::to_index(Cpu::Flag::Zero))    :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    return value;
}

Instruction SLA_R(Cpu::Register r) {
    return {[r](Cpu& cpu, Operand&){
        auto flags = cpu.get(Cpu::Register::F);
        cpu.set(r, SLA(cpu.get(r), flags));
        cpu.set(Cpu::Register::F, flags);
        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction SLA_ADDR_HL() {
    return {[](Cpu& cpu, Operand&){
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);
        value = SLA(value, cpu.get(Cpu::Register::F));
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t SRA(uint8_t value, uint8_t& flags) {
    
    is_set(value, 0)                      ? 
        set_bit(flags,      Cpu::to_index(Cpu::Flag::Carry))   :
        clear_bit(flags,    Cpu::to_index(Cpu::Flag::Carry));
    
    const auto old_msb = is_set(value, 7);

    value = static_cast<uint8_t>(value >> 1u);

    old_msb ? set_bit(value, 7) : clear_bit(value, 7);

    value == 0                            ?
        set_bit(flags,      Cpu::to_index(Cpu::Flag::Zero))    :
        clear_bit(flags,    Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    return value;
}

Instruction SRA_R(Cpu::Register r) {
    return {[r](Cpu& cpu, Operand&) {
        auto flags = cpu.get(Cpu::Register::F);
        cpu.set(r, SRA(cpu.get(r), flags));
        cpu.set(Cpu::Register::F, flags);

        constexpr auto cycles = 8;
        return cycles;
    }, none}; 
}

Instruction SRA_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);
        value = SRA(value, cpu.get(Cpu::Register::F));
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t RR(uint8_t value, uint8_t& flags) {
    
    bool carry_status = is_set(flags, Cpu::to_index(Cpu::Flag::Carry));

    is_set(value, 0)                  ? 
        set_bit(flags,      Cpu::to_index(Cpu::Flag::Carry))   :
        clear_bit(flags,    Cpu::to_index(Cpu::Flag::Carry));

    value = static_cast<uint8_t>(value >> 1u);
    carry_status ? set_bit(value, 7) : clear_bit(value, 7);

    value == 0 ? 
        set_bit(flags,      Cpu::to_index(Cpu::Flag::Zero)) : 
        clear_bit(flags,    Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    return value;
}

Instruction RR_R(Cpu::Register r) {
    return {[r](Cpu& cpu, Operand&) {
        auto flags = cpu.get(Cpu::Register::F);
        cpu.set(r, RR(cpu.get(r), flags));
        cpu.set(Cpu::Register::F, flags);

        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction RR_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);
        value = RR(value, cpu.get(Cpu::Register::F));
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

uint8_t SWAP(uint8_t value, uint8_t& flags) {

    swap_nibbles(value);
    
    value == 0 ? 
        set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));

    return value;
}

Instruction SWAP_R(Cpu::Register r) {
    return {[r](Cpu& cpu, Operand&) {
        auto flags = cpu.get(Cpu::Register::F);
        cpu.set(r, SWAP(cpu.get(r), flags));
        cpu.set(Cpu::Register::F, flags);

        constexpr auto cycles = 8;
        return cycles;
    }, none};   
}

Instruction SWAP_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);
        value = SWAP(value, cpu.get(Cpu::Register::F));
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

void BIT(uint8_t value, int n, uint8_t& flags) {
    
    is_set(value, n) ? clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        set_bit(flags, Cpu::to_index(Cpu::Flag::Zero));
    
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    set_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));
}

Instruction BIT_R(Cpu::Register r, int n) {
    return {[r, n](Cpu& cpu, Operand&) {
        auto flags = cpu.get(Cpu::Register::F);
        BIT(cpu.get(r), n, flags);
        cpu.set(Cpu::Register::F, flags);
        return 8;
    }, none};
}

Instruction BIT_ADDR_HL(int n) {
    return {[n](Cpu& cpu, Operand&) {    
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        const auto value = cpu.m_memory_controller->read(address);

        auto flags = cpu.get(Cpu::Register::F);
        BIT(value, n, flags);
        cpu.m_memory_controller->write(address, value);
        cpu.set(Cpu::Register::F, flags);

        constexpr auto cycles = 12;
        return cycles;
    }, none};
}

Instruction RES_R(Cpu::Register r, int n) {
    return {[r, n](Cpu& cpu, Operand&) {
        auto value = cpu.get(r);
        clear_bit(value, n);
        cpu.set(r, value);

        constexpr auto cycles = 8;
        return cycles;
    }, none};
}

Instruction RES_ADDR_HL(int n) {
    return {[n](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, n);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none};
}

Instruction SET_R(Cpu::Register r, int n) {
    return {[r, n](Cpu& cpu, Operand&) {
        auto value = cpu.get(r);
        set_bit(value, n);
        cpu.set(r, value);
        constexpr auto cycles = 8;
        return cycles;
    }, none}; 
}

Instruction SET_ADDR_HL(int n) {
    return {[n](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, n);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }, none}; 
}