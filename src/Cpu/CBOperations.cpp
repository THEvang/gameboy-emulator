#include <Cpu/CBOperations.h>
#include <BitOperations.h>

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

FetchResult RLC_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = RLC(cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult RLC_C(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = RLC(cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult RLC_D(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = RLC(cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult RLC_E(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = RLC(cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult RLC_H(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = RLC(cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult RLC_L(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = RLC(cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult RLC_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = RLC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RLC_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = RLC(cpu.m_reg_a, cpu.m_reg_f);
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

FetchResult RRC_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = RRC(cpu.m_reg_b, cpu.m_reg_f);
    }}; 
}

FetchResult RRC_C(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = RRC(cpu.m_reg_c, cpu.m_reg_f);
    }}; 
}

FetchResult RRC_D(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = RRC(cpu.m_reg_d, cpu.m_reg_f);
    }}; 
}

FetchResult RRC_E(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = RRC(cpu.m_reg_e, cpu.m_reg_f);
    }}; 
}

FetchResult RRC_H(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = RRC(cpu.m_reg_h, cpu.m_reg_f);
    }}; 
}

FetchResult RRC_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = RRC(cpu.m_reg_l, cpu.m_reg_f);
    }}; 
}

FetchResult RRC_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = RRC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }}; 
}

FetchResult RRC_A(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = RRC(cpu.m_reg_a, cpu.m_reg_f);
    }}; 
}

uint8_t RL(uint8_t value, uint8_t& flags) {
    
    const auto new_carry_flag = is_set(value, 7);
    value <<= 1;

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

FetchResult RL_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = RL(cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult RL_C(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = RL(cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult RL_D(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = RL(cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult RL_E(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = RL(cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult RL_H(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = RL(cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult RL_L(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = RL(cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult RL_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = RL(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RL_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = RL(cpu.m_reg_a, cpu.m_reg_f);
    }};
}

uint8_t SRL(uint8_t value, uint8_t& flags) {

    is_set(value, 0)                      ? 
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);
    
    value >>= 1;
    clear_bit(value, 7);

    value == 0                            ?
        set_bit(flags, Cpu::zero_flag)    :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult SRL_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SRL(cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult SRL_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = SRL(cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult SRL_C(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = SRL(cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult SRL_D(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = SRL(cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult SRL_E(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = SRL(cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult SRL_H(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = SRL(cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult SRL_L(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = SRL(cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult SRL_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = SRL(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

uint8_t SLA(uint8_t value, uint8_t& flags) {

    is_set(value, 7)                      ? 
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);
    
    value <<= 1;
    clear_bit(value, 0);

    value == 0                            ?
        set_bit(flags, Cpu::zero_flag)    :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult SLA_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_b = SLA(cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult SLA_C(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_c = SLA(cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult SLA_D(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_d = SLA(cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult SLA_E(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = SLA(cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult SLA_H(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_h = SLA(cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult SLA_L(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = SLA(cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult SLA_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = SLA(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SLA_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_a = SLA(cpu.m_reg_a, cpu.m_reg_f);
    }};
}

uint8_t SRA(uint8_t value, uint8_t& flags) {
    
    is_set(value, 0)                      ? 
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);
    
    const auto old_msb = is_set(value, 7);

    value >>= 1;

    old_msb ? set_bit(value, 7) : clear_bit(value, 7);

    value == 0                            ?
        set_bit(flags, Cpu::zero_flag)    :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult SRA_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = SRA(cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult SRA_C(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = SRA(cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult SRA_D(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = SRA(cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult SRA_E(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = SRA(cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult SRA_H(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = SRA(cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult SRA_L(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = SRA(cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult SRA_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = SRA(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SRA_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SRA(cpu.m_reg_a, cpu.m_reg_f);
    }};
}

uint8_t RR(uint8_t value, uint8_t& flags) {
    
    bool carry_status = is_set(flags, Cpu::carry_flag);

    is_set(value, 0)                  ? 
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    value >>= 1;
    carry_status ? set_bit(value, 7) : clear_bit(value, 7);

    value == 0 ? 
        set_bit(flags, Cpu::zero_flag) : 
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);

    return value;
}

FetchResult RR_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = RR(cpu.m_reg_b, cpu.m_reg_f);
    }};
}


FetchResult RR_C(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = RR(cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult RR_D(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = RR(cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult RR_E(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = RR(cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult RR_H(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = RR(cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult RR_L(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = RR(cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult RR_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = RR(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RR_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = RR(cpu.m_reg_a, cpu.m_reg_f);
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

FetchResult SWAP_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = SWAP(cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult SWAP_C(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = SWAP(cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult SWAP_D(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = SWAP(cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult SWAP_E(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = SWAP(cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult SWAP_H(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = SWAP(cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult SWAP_L(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = SWAP(cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult SWAP_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = SWAP(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SWAP_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SWAP(cpu.m_reg_a, cpu.m_reg_f);
    }};
}

void BIT(uint8_t value, int n, uint8_t& flags) {
    
    is_set(value, n) ? clear_bit(flags, Cpu::zero_flag) :
        set_bit(flags, Cpu::zero_flag);
    
    clear_bit(flags, Cpu::sub_flag);
    set_bit(flags, Cpu::half_carry_flag);
}

FetchResult BIT_0_B(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 0, cpu.m_reg_f);
    }};
}

FetchResult BIT_0_C(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 0, cpu.m_reg_f);
    }};
}

FetchResult BIT_0_D(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 0, cpu.m_reg_f);
    }};
}
FetchResult BIT_0_E(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 0, cpu.m_reg_f);
    }};
}

FetchResult BIT_0_H(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 0, cpu.m_reg_f);
    }};
}

FetchResult BIT_0_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 0, cpu.m_reg_f);
    }};
}

FetchResult BIT_0_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {    
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 0, cpu.m_reg_f);
    }};
}

FetchResult BIT_0_A(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 0, cpu.m_reg_f);
    }};
}

FetchResult BIT_1_B(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 1, cpu.m_reg_f);
    }};
}

FetchResult BIT_1_C(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 1, cpu.m_reg_f);
    }};
}

FetchResult BIT_1_D(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 1, cpu.m_reg_f);
    }};
}

FetchResult BIT_1_E(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 1, cpu.m_reg_f);
    }};
}

FetchResult BIT_1_H(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 1, cpu.m_reg_f);
    }};
}

FetchResult BIT_1_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 1, cpu.m_reg_f);
    }};
}

FetchResult BIT_1_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 1, cpu.m_reg_f);
    }};
}

FetchResult BIT_1_A(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 1, cpu.m_reg_f);
    }};
}

FetchResult BIT_2_B(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 2, cpu.m_reg_f);
    }};
}

FetchResult BIT_2_C(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 2, cpu.m_reg_f);
    }};
}

FetchResult BIT_2_D(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 2, cpu.m_reg_f);
    }};
}

FetchResult BIT_2_E(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 2, cpu.m_reg_f);
    }};
}

FetchResult BIT_2_H(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 2, cpu.m_reg_f);
    }};
}

FetchResult BIT_2_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 2, cpu.m_reg_f);
    }};
}

FetchResult BIT_2_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 2, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult BIT_2_A(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 2, cpu.m_reg_f);
    }};
}

FetchResult BIT_3_B(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 3, cpu.m_reg_f);
    }};
}

FetchResult BIT_3_C(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 3, cpu.m_reg_f);
    }};
}

FetchResult BIT_3_D(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 3, cpu.m_reg_f);
    }};
}

FetchResult BIT_3_E(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 3, cpu.m_reg_f);
    }};
}

FetchResult BIT_3_H(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 3, cpu.m_reg_f);
    }};
}

FetchResult BIT_3_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 3, cpu.m_reg_f);
    }};
}

FetchResult BIT_3_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 3, cpu.m_reg_f);
    }};
}

FetchResult BIT_3_A(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 3, cpu.m_reg_f);
    }};
}

FetchResult BIT_4_B(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 4, cpu.m_reg_f);
    }};
}

FetchResult BIT_4_C(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 4, cpu.m_reg_f);
    }};
}

FetchResult BIT_4_D(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 4, cpu.m_reg_f);
    }};
}

FetchResult BIT_4_E(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 4, cpu.m_reg_f);
    }};
}

FetchResult BIT_4_H(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 4, cpu.m_reg_f);
    }};
}

FetchResult BIT_4_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 4, cpu.m_reg_f);
    }};
}

FetchResult BIT_4_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 4, cpu.m_reg_f);
    }};
}

FetchResult BIT_4_A(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 4, cpu.m_reg_f);
    }};
}

FetchResult BIT_5_B(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 5, cpu.m_reg_f);
    }};
}

FetchResult BIT_5_C(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 5, cpu.m_reg_f);
    }};
}

FetchResult BIT_5_D(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 5, cpu.m_reg_f);
    }};
}

FetchResult BIT_5_E(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 5, cpu.m_reg_f);
    }};
}

FetchResult BIT_5_H(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 5, cpu.m_reg_f);
    }};
}

FetchResult BIT_5_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 5, cpu.m_reg_f);
    }};
}

FetchResult BIT_5_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);  
        BIT(value, 5, cpu.m_reg_f);
    }};
}

FetchResult BIT_5_A(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 5, cpu.m_reg_f);
    }};
}

FetchResult BIT_6_B(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 6, cpu.m_reg_f);
    }};
}

FetchResult BIT_6_C(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 6, cpu.m_reg_f);
    }};
}

FetchResult BIT_6_D(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 6, cpu.m_reg_f);
    }};
}

FetchResult BIT_6_E(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 6, cpu.m_reg_f);
    }};
}

FetchResult BIT_6_H(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 6, cpu.m_reg_f);
    }};
}

FetchResult BIT_6_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 6, cpu.m_reg_f);
    }};
}

FetchResult BIT_6_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 6, cpu.m_reg_f);
    }};
}

FetchResult BIT_6_A(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 6, cpu.m_reg_f);
    }};
}

FetchResult BIT_7_B(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_b, 7, cpu.m_reg_f);
    }};
}

FetchResult BIT_7_C(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_c, 7, cpu.m_reg_f);
    }};
}

FetchResult BIT_7_D(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_d, 7, cpu.m_reg_f);
    }};
}

FetchResult BIT_7_E(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_e, 7, cpu.m_reg_f);
    }};
}

FetchResult BIT_7_H(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_h, 7, cpu.m_reg_f);
    }};
}

FetchResult BIT_7_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_l, 7, cpu.m_reg_f);
    }};
}

FetchResult BIT_7_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        BIT(value, 7, cpu.m_reg_f);
    }};
}

FetchResult BIT_7_A(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        BIT(cpu.m_reg_a, 7, cpu.m_reg_f);
    }};
}

FetchResult RES_0_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 0);
    }};
}

FetchResult RES_0_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 0);
    }};
}

FetchResult RES_0_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 0);
    }};
}

FetchResult RES_0_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 0);
    }};
}

FetchResult RES_0_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 0);
    }};
}

FetchResult RES_0_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 0);
    }};
}

FetchResult RES_0_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 0);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RES_0_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 0);
    }};
}

FetchResult RES_1_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 1);
    }};
}

FetchResult RES_1_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 1);
    }};
}

FetchResult RES_1_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 1);
    }};
}

FetchResult RES_1_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 1);
    }};
}

FetchResult RES_1_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 1);
    }};
}

FetchResult RES_1_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 1);
    }};
}

FetchResult RES_1_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 1);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RES_1_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 1);
    }};
}

FetchResult RES_2_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 2);
    }};
}

FetchResult RES_2_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 2);
    }};
}

FetchResult RES_2_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 2);
    }};
}

FetchResult RES_2_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 2);
    }};
}

FetchResult RES_2_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 2);
    }};
}

FetchResult RES_2_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 2);
    }};
}

FetchResult RES_2_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 2);
        cpu.m_memory_controller->write(address, value);

    }};
}

FetchResult RES_2_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 2);
    }};
}

FetchResult RES_3_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 3);
    }};
}

FetchResult RES_3_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 3);
    }};
}

FetchResult RES_3_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 3);
    }};
}

FetchResult RES_3_E(Cpu& cpu) {
     constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 3);
    }};
}

FetchResult RES_3_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 3);
    }};
}

FetchResult RES_3_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 3);
    }};
}

FetchResult RES_3_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 3);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RES_3_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 3);
    }};
}

FetchResult RES_4_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 4);
    }};
}

FetchResult RES_4_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 4);
    }};
}

FetchResult RES_4_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 4);
    }};
}

FetchResult RES_4_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 4);
    }};
}

FetchResult RES_4_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 4);
    }};
}

FetchResult RES_4_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 4);
    }};
}

FetchResult RES_4_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 4);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RES_4_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 4);
    }};
}

FetchResult RES_5_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 5);
    }};
}

FetchResult RES_5_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 5);
    }};
}

FetchResult RES_5_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 5);
    }};
}

FetchResult RES_5_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 5);
    }};
}

FetchResult RES_5_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 5);
    }};
}

FetchResult RES_5_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 5);
    }};
}

FetchResult RES_5_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 5);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RES_5_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 5);
    }};
}

FetchResult RES_6_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 6);
    }};
}

FetchResult RES_6_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 6);
    }};
}

FetchResult RES_6_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 6);
    }};
}

FetchResult RES_6_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 6);
    }};
}

FetchResult RES_6_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 6);
    }};
}

FetchResult RES_6_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 6);
    }};
}

FetchResult RES_6_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 6);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RES_6_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 6);
    }};
}

FetchResult RES_7_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_b, 7);
    }};
}

FetchResult RES_7_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_c, 7);
    }};
}

FetchResult RES_7_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_d, 7);
    }};
}

FetchResult RES_7_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_e, 7);
    }};
}

FetchResult RES_7_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_h, 7);
    }};
}

FetchResult RES_7_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_l, 7);
    }};
}

FetchResult RES_7_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        clear_bit(value, 7);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult RES_7_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_a, 7);
    }};
}

FetchResult SET_0_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 0);
    }};
}

FetchResult SET_0_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 0);
    }};
}
FetchResult SET_0_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 0);
    }};
}
FetchResult SET_0_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 0);
    }};
}
FetchResult SET_0_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 0);
    }};
}
FetchResult SET_0_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 0);
    }};
}

FetchResult SET_0_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 0);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SET_0_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 0);
    }};
}

FetchResult SET_1_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 1);
    }};
}

FetchResult SET_1_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 1);
    }};
}

FetchResult SET_1_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 1);
    }};
}

FetchResult SET_1_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 1);
    }};
}

FetchResult SET_1_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 1);
    }};
}

FetchResult SET_1_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 1);
    }};
}

FetchResult SET_1_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 1);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SET_1_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 1);
    }};
}

FetchResult SET_2_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 2);
    }};
}

FetchResult SET_2_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 2);
    }};
}

FetchResult SET_2_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 2);
    }};
}

FetchResult SET_2_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 2);
    }};
}

FetchResult SET_2_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 2);
    }};
}

FetchResult SET_2_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 2);
    }};
}

FetchResult SET_2_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 2);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SET_2_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 2);
    }};
}

FetchResult SET_3_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 3);
    }};
}

FetchResult SET_3_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 3);
    }};
}

FetchResult SET_3_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 3);
    }};
}

FetchResult SET_3_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 3);
    }};
}

FetchResult SET_3_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 3);
    }};
}

FetchResult SET_3_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 3);
    }};
}

FetchResult SET_3_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 3);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SET_3_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 3);
    }};
}

FetchResult SET_4_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 4);
    }};
}

FetchResult SET_4_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 4);
    }};
}

FetchResult SET_4_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 4);
    }};
}

FetchResult SET_4_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 4);
    }};
}

FetchResult SET_4_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 4);
    }};
}

FetchResult SET_4_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 4);
    }};
}

FetchResult SET_4_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 4);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SET_4_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 4);
    }};
}

FetchResult SET_5_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 5);
    }};
}

FetchResult SET_5_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 5);
    }};
}

FetchResult SET_5_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 5);
    }};
}

FetchResult SET_5_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 5);
    }};
}

FetchResult SET_5_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 5);
    }};
}

FetchResult SET_5_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 5);
    }};
}

FetchResult SET_5_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 5);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SET_5_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 5);
    }};
}

FetchResult SET_6_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 6);
    }};
}

FetchResult SET_6_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 6);
    }};
}

FetchResult SET_6_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 6);
    }};
}

FetchResult SET_6_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 6);
    }};
}

FetchResult SET_6_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 6);
    }};
}

FetchResult SET_6_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 6);
    }};
}

FetchResult SET_6_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 6);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SET_6_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 6);
    }};
}

FetchResult SET_7_B(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_b, 7);
    }};
}

FetchResult SET_7_C(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_c, 7);
    }};
}

FetchResult SET_7_D(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_d, 7);
    }};
}

FetchResult SET_7_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_e, 7);
    }};
}

FetchResult SET_7_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_h, 7);
    }};
}

FetchResult SET_7_L(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_l, 7);
    }};
}

FetchResult SET_7_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        set_bit(value, 7);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult SET_7_A(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        set_bit(cpu.m_reg_a, 7);
    }};
}