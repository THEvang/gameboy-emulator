#include "Cpu/CBOperations.hpp"

#include "Memory/Memory_Controller.hpp"
#include "Cpu/Interpreter.hpp"
#include "BitOperations.hpp"
#include "Cpu/Cpu.hpp"

uint8_t RLC(uint8_t value, uint8_t& flags) {

    is_set(value, 7) ? set_bit(flags, Cpu::carry_flag) : 
        clear_bit(flags, Cpu::carry_flag);

    value = rotate_left<uint8_t>(value, 1);

    value == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult RLC_B() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {

        constexpr auto cycles = 8;
        cpu.m_reg_b = RLC(cpu.m_reg_b, cpu.m_reg_f);
        return cycles;
    }};
}

FetchResult RLC_C() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = RLC(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RLC_D() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = RLC(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RLC_E() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = RLC(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RLC_H() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = RLC(cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RLC_L() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = RLC(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RLC_ADDR_HL() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = RLC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RLC_A() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = RLC(cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t RRC(uint8_t value, uint8_t& flags) {
    
    is_set(value, 0) ? set_bit(flags, Cpu::carry_flag)
        : clear_bit(flags, Cpu::carry_flag);
    
    value = rotate_right<uint8_t>(value, 1);

    value == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);
    
    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult RRC_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = RRC(cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }}; 
}

FetchResult RRC_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = RRC(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }}; 
}

FetchResult RRC_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = RRC(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }}; 
}

FetchResult RRC_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = RRC(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }}; 
}

FetchResult RRC_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = RRC(cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }}; 
}

FetchResult RRC_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = RRC(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }}; 
}

FetchResult RRC_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = RRC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }}; 
}

FetchResult RRC_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = RRC(cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }}; 
}

uint8_t RL(uint8_t value, uint8_t& flags) {
    
    const auto new_carry_flag = is_set(value, 7);
    value = static_cast<uint8_t>(value << 1u);

    is_set(flags, Cpu::carry_flag) ? set_bit(value, 0)
        : clear_bit(value, 0);
    
    new_carry_flag ? set_bit(flags, Cpu::carry_flag)
        : clear_bit(flags, Cpu::carry_flag);

    value == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult RL_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = RL(cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RL_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = RL(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RL_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = RL(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RL_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = RL(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RL_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = RL(cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RL_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = RL(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RL_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = RL(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RL_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = RL(cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t SRL(uint8_t value, uint8_t& flags) {

    is_set(value, 0)                      ? 
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);
    
    value = static_cast<uint8_t>(value >> 1u);
    clear_bit(value, 7);

    value == 0                            ?
        set_bit(flags, Cpu::zero_flag)    :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult SRL_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SRL(cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRL_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = SRL(cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRL_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = SRL(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRL_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = SRL(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRL_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = SRL(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRL_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = SRL(cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRL_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = SRL(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRL_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = SRL(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

uint8_t SLA(uint8_t value, uint8_t& flags) {

    is_set(value, 7)                      ? 
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);
    
    value = static_cast<uint8_t>(value << 1u);
    clear_bit(value, 0);

    value == 0                            ?
        set_bit(flags, Cpu::zero_flag)    :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult SLA_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_b = SLA(cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SLA_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_c = SLA(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SLA_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_d = SLA(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SLA_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = SLA(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SLA_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_h = SLA(cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SLA_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = SLA(cpu.m_reg_l, cpu.m_reg_f);
        
        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SLA_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = SLA(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SLA_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu){
        cpu.m_reg_a = SLA(cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t SRA(uint8_t value, uint8_t& flags) {
    
    is_set(value, 0)                      ? 
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);
    
    const auto old_msb = is_set(value, 7);

    value = static_cast<uint8_t>(value >> 1u);

    old_msb ? set_bit(value, 7) : clear_bit(value, 7);

    value == 0                            ?
        set_bit(flags, Cpu::zero_flag)    :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult SRA_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = SRA(cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRA_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = SRA(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRA_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = SRA(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRA_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = SRA(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRA_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = SRA(cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRA_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = SRA(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SRA_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = SRA(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SRA_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SRA(cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t RR(uint8_t value, uint8_t& flags) {
    
    bool carry_status = is_set(flags, Cpu::carry_flag);

    is_set(value, 0)                  ? 
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    value = static_cast<uint8_t>(value >> 1u);
    carry_status ? set_bit(value, 7) : clear_bit(value, 7);

    value == 0 ? 
        set_bit(flags, Cpu::zero_flag) : 
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult RR_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = RR(cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}


FetchResult RR_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = RR(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RR_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = RR(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RR_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = RR(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RR_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = RR(cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RR_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = RR(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RR_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = RR(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RR_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = RR(cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

uint8_t SWAP(uint8_t value, uint8_t& flags) {

    swap_nibbles(value);
    
    value == 0 ? 
        set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);
    clear_bit(flags, Cpu::carry_flag);

    return value;
}

FetchResult SWAP_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = SWAP(cpu.m_reg_b, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SWAP_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = SWAP(cpu.m_reg_c, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SWAP_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = SWAP(cpu.m_reg_d, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SWAP_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = SWAP(cpu.m_reg_e, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SWAP_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = SWAP(cpu.m_reg_h, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SWAP_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = SWAP(cpu.m_reg_l, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SWAP_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = SWAP(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SWAP_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SWAP(cpu.m_reg_a, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

void BIT(uint8_t value, int n, uint8_t& flags) {
    
    is_set(value, n) ? clear_bit(flags, Cpu::zero_flag) :
        set_bit(flags, Cpu::zero_flag);
    
    clear_bit(flags, Cpu::sub_flag);
    set_bit(flags, Cpu::half_carry_flag);
}

FetchResult BIT_0_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 0, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_0_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 0, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_0_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 0, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}
FetchResult BIT_0_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 0, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_0_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 0, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_0_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 0, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_0_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {    
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 0, cpu.m_reg_f);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult BIT_0_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 0, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_1_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 1, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_1_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 1, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_1_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 1, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_1_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 1, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_1_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 1, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_1_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 1, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_1_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 1, cpu.m_reg_f);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult BIT_1_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 1, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_2_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 2, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_2_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 2, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_2_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 2, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_2_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 2, cpu.m_reg_f);
    
        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_2_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 2, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_2_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 2, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_2_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 2, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult BIT_2_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 2, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_3_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 3, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_3_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 3, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_3_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 3, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_3_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 3, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_3_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 3, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_3_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 3, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_3_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 3, cpu.m_reg_f);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult BIT_3_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 3, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_4_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 4, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_4_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 4, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_4_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 4, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_4_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 4, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_4_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 4, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_4_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 4, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_4_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 4, cpu.m_reg_f);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult BIT_4_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 4, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_5_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 5, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_5_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 5, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_5_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 5, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_5_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 5, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_5_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 5, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_5_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 5, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_5_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);  
        BIT(value, 5, cpu.m_reg_f);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult BIT_5_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 5, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_6_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 6, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_6_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 6, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_6_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 6, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_6_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 6, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_6_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 6, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_6_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 6, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_6_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 6, cpu.m_reg_f);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult BIT_6_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 6, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_7_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 7, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_7_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 7, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_7_D() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 7, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_7_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 7, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_7_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 7, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_7_L() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 7, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult BIT_7_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 7, cpu.m_reg_f);

        constexpr auto cycles = 12;
        return cycles;
    }};
}

FetchResult BIT_7_A() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 7, cpu.m_reg_f);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_0_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_0_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_0_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 0);
    
        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_0_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_0_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_0_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_0_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 0);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RES_0_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_1_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_1_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_1_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_1_E() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_1_H() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_1_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_1_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 1);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RES_1_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_2_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_2_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_2_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_2_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_2_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_2_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_2_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 2);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RES_2_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_3_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_3_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 3);
        
        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_3_D() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_3_E() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_3_H() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_3_L() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_3_ADDR_HL() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 3);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RES_3_A() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_4_B() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_4_C() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_4_D() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_4_E() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_4_H() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_4_L() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_4_ADDR_HL() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 4);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RES_4_A() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_5_B() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_5_C() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_5_D() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_5_E() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_5_H() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_5_L() {
    
    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_5_ADDR_HL() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 5);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RES_5_A() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 5);
    
        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_6_B() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_6_C() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_6_D() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_6_E() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_6_H() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_6_L() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_6_ADDR_HL() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 6);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RES_6_A() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_7_B() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_7_C() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_7_D() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_7_E() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_7_H() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_7_L() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult RES_7_ADDR_HL() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 7);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult RES_7_A() {

    constexpr auto delta_pc = 1;
    
    return {delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_0_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_0_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}
FetchResult SET_0_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}
FetchResult SET_0_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 0);
    
        constexpr auto cycles = 8;
        return cycles;
    }};
}
FetchResult SET_0_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}
FetchResult SET_0_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_0_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 0);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SET_0_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 0);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_1_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_1_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_1_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_1_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_1_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_1_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_1_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 1);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SET_1_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 1);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_2_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_2_C() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 2);
        
        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_2_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_2_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_2_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_2_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_2_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 2);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SET_2_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 2);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_3_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_3_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_3_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_3_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_3_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_3_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_3_ADDR_HL() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 3);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SET_3_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 3);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_4_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_4_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_4_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_4_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_4_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_4_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_4_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 4);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SET_4_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 4);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_5_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_5_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_5_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_5_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_5_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_5_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_5_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 5);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SET_5_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 5);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_6_B() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_6_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_6_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_6_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_6_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_6_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_6_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 6);
        cpu.m_memory_controller->write(address, value);
        
        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SET_6_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 6);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_7_B() {
    
    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_7_C() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_7_D() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_7_E() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_7_H() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_7_L() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 7);

        constexpr auto cycles = 8;
        return cycles;
    }};
}

FetchResult SET_7_ADDR_HL() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 7);
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 16;
        return cycles;
    }};
}

FetchResult SET_7_A() {

    constexpr auto delta_pc = 1;

    return {delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 7);
        
        constexpr auto cycles = 8;
        return cycles;
    }};
}