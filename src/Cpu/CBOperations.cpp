#include <cpu/CBOperations.h>
#include <BitOperations.h>

void RLC_B(Cpu& cpu) {

     is_set(cpu.m_reg_b, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_b = rotate_left<uint8_t>(cpu.m_reg_b, 1);

    cpu.m_reg_b == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RLC_C(Cpu& cpu) {

     is_set(cpu.m_reg_c, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_c = rotate_left<uint8_t>(cpu.m_reg_c, 1);

    cpu.m_reg_c == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RLC_D(Cpu& cpu) {

     is_set(cpu.m_reg_d, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_d = rotate_left<uint8_t>(cpu.m_reg_d, 1);

    cpu.m_reg_d == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RLC_E(Cpu& cpu) {

     is_set(cpu.m_reg_e, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_e = rotate_left<uint8_t>(cpu.m_reg_e, 1);

    cpu.m_reg_e == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RLC_H(Cpu& cpu) {

     is_set(cpu.m_reg_h, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_h = rotate_left<uint8_t>(cpu.m_reg_h, 1);

    cpu.m_reg_h == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RLC_L(Cpu& cpu) {

     is_set(cpu.m_reg_l, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_l = rotate_left<uint8_t>(cpu.m_reg_l, 1);

    cpu.m_reg_l == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RLC_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

     is_set(value, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    value = rotate_left<uint8_t>(value, 1);

    value == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    cpu.m_memory_controller->write(address, value);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void RLC_A(Cpu& cpu) {

     is_set(cpu.m_reg_a, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a = rotate_left<uint8_t>(cpu.m_reg_a, 1);

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RRC_B(Cpu& cpu) {
    
    is_set(cpu.m_reg_b, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_b = rotate_right<uint8_t>(cpu.m_reg_b, 1);

    cpu.m_reg_b == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RRC_C(Cpu& cpu) {
    
    is_set(cpu.m_reg_c, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_c = rotate_right<uint8_t>(cpu.m_reg_c, 1);
    
    cpu.m_reg_c == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RRC_D(Cpu& cpu) {
    
    is_set(cpu.m_reg_d, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_d = rotate_right<uint8_t>(cpu.m_reg_d, 1);

    cpu.m_reg_d == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RRC_E(Cpu& cpu) {
    
    is_set(cpu.m_reg_e, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_e = rotate_right<uint8_t>(cpu.m_reg_e, 1);
    
    cpu.m_reg_e == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RRC_H(Cpu& cpu) {
    
    is_set(cpu.m_reg_h, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_h = rotate_right<uint8_t>(cpu.m_reg_h, 1);
    
    cpu.m_reg_h == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RRC_L(Cpu& cpu) {
    
    is_set(cpu.m_reg_l, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_l = rotate_right<uint8_t>(cpu.m_reg_l, 1);

    cpu.m_reg_l == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RRC_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    is_set(value, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    value = rotate_right<uint8_t>(value, 1);

    value == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void RRC_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_a = rotate_right<uint8_t>(cpu.m_reg_a, 1);
    
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RL_B(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_b, 7);
    cpu.m_reg_b <<= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_b, 0)
        : clear_bit(cpu.m_reg_b, 0);
    
    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_b == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RL_C(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_c, 7);
    cpu.m_reg_c <<= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_c, 0)
        : clear_bit(cpu.m_reg_c, 0);
    
    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_c == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RL_D(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_d, 7);
    cpu.m_reg_d <<= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_d, 0)
        : clear_bit(cpu.m_reg_d, 0);
    
    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_d == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RL_E(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_e, 7);
    cpu.m_reg_e <<= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_e, 0)
        : clear_bit(cpu.m_reg_e, 0);
    
    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_e == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RL_H(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_h, 7);
    cpu.m_reg_h <<= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_h, 0)
        : clear_bit(cpu.m_reg_h, 0);
    
    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_h == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RL_L(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_l, 7);
    cpu.m_reg_l <<= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_l, 0)
        : clear_bit(cpu.m_reg_l, 0);
    
    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_l == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RL_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    const auto new_carry_flag = is_set(value, 7);
    value <<= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(value, 0)
        : clear_bit(value, 0);
    
    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    value == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void RL_A(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_a, 7);
    cpu.m_reg_a <<= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_a, 0)
        : clear_bit(cpu.m_reg_a, 0);
    
    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRL_A(Cpu& cpu) {

    is_set(cpu.m_reg_a, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_a >>= 1;
    clear_bit(cpu.m_reg_a, 7);

    cpu.m_reg_a == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRL_B(Cpu& cpu) {

    is_set(cpu.m_reg_b, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_b >>= 1;
    clear_bit(cpu.m_reg_b, 7);

    cpu.m_reg_b == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRL_C(Cpu& cpu) {

    is_set(cpu.m_reg_c, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_c >>= 1;
    clear_bit(cpu.m_reg_c, 7);

    cpu.m_reg_c == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRL_D(Cpu& cpu) {

    is_set(cpu.m_reg_d, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_d >>= 1;
    clear_bit(cpu.m_reg_d, 7);

    cpu.m_reg_d == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRL_E(Cpu& cpu) {

    is_set(cpu.m_reg_e, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_e >>= 1;
    clear_bit(cpu.m_reg_e, 7);

    cpu.m_reg_e == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRL_H(Cpu& cpu) {

    is_set(cpu.m_reg_h, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_h >>= 1;
    clear_bit(cpu.m_reg_h, 7);

    cpu.m_reg_h == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRL_L(Cpu& cpu) {

    is_set(cpu.m_reg_l, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_l >>= 1;
    clear_bit(cpu.m_reg_l, 7);

    cpu.m_reg_l == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRL_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    is_set(value, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    value >>= 1;
    clear_bit(value, 7);

    value == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SLA_B(Cpu& cpu) {

    is_set(cpu.m_reg_b, 7)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_b <<= 1;
    clear_bit(cpu.m_reg_b, 0);

    cpu.m_reg_b == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SLA_C(Cpu& cpu) {

    is_set(cpu.m_reg_c, 7)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_c <<= 1;
    clear_bit(cpu.m_reg_c, 0);

    cpu.m_reg_c == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SLA_D(Cpu& cpu) {

    is_set(cpu.m_reg_d, 7)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_d <<= 1;
    clear_bit(cpu.m_reg_d, 0);

    cpu.m_reg_d == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SLA_E(Cpu& cpu) {

    is_set(cpu.m_reg_e, 7)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_e <<= 1;
    clear_bit(cpu.m_reg_e, 0);

    cpu.m_reg_e == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SLA_H(Cpu& cpu) {

    is_set(cpu.m_reg_h, 7)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_h <<= 1;
    clear_bit(cpu.m_reg_h, 0);

    cpu.m_reg_h == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SLA_L(Cpu& cpu) {

    is_set(cpu.m_reg_l, 7)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_l <<= 1;
    clear_bit(cpu.m_reg_l, 0);

    cpu.m_reg_l == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SLA_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    is_set(value, 7)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    value <<= 1;
    clear_bit(value, 0);

    value == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SLA_A(Cpu& cpu) {

    is_set(cpu.m_reg_a, 7)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_a <<= 1;
    clear_bit(cpu.m_reg_a, 0);

    cpu.m_reg_a == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRA_B(Cpu& cpu) {

    is_set(cpu.m_reg_b, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    const auto old_msb = is_set(cpu.m_reg_b, 7);

    cpu.m_reg_b >>= 1;

    old_msb ? set_bit(cpu.m_reg_b, 7) : clear_bit(cpu.m_reg_b, 7);

    cpu.m_reg_b == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRA_C(Cpu& cpu) {

    is_set(cpu.m_reg_c, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    const auto old_msb = is_set(cpu.m_reg_c, 7);

    cpu.m_reg_c >>= 1;

    old_msb ? set_bit(cpu.m_reg_c, 7) : clear_bit(cpu.m_reg_c, 7);

    cpu.m_reg_c == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRA_D(Cpu& cpu) {

    is_set(cpu.m_reg_d, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    const auto old_msb = is_set(cpu.m_reg_d, 7);

    cpu.m_reg_d >>= 1;

    old_msb ? set_bit(cpu.m_reg_d, 7) : clear_bit(cpu.m_reg_d, 7);

    cpu.m_reg_d == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRA_E(Cpu& cpu) {

    is_set(cpu.m_reg_e, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    const auto old_msb = is_set(cpu.m_reg_e, 7);

    cpu.m_reg_e >>= 1;

    old_msb ? set_bit(cpu.m_reg_e, 7) : clear_bit(cpu.m_reg_e, 7);

    cpu.m_reg_e == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRA_H(Cpu& cpu) {

    is_set(cpu.m_reg_h, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    const auto old_msb = is_set(cpu.m_reg_h, 7);

    cpu.m_reg_h >>= 1;

    old_msb ? set_bit(cpu.m_reg_h, 7) : clear_bit(cpu.m_reg_h, 7);

    cpu.m_reg_h == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRA_L(Cpu& cpu) {

    is_set(cpu.m_reg_l, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    const auto old_msb = is_set(cpu.m_reg_l, 7);

    cpu.m_reg_l >>= 1;

    old_msb ? set_bit(cpu.m_reg_l, 7) : clear_bit(cpu.m_reg_l, 7);

    cpu.m_reg_l == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SRA_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    is_set(value, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    const auto old_msb = is_set(value, 7);

    value >>= 1;

    old_msb ? set_bit(value, 7) : clear_bit(value, 7);

    value == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SRA_A(Cpu& cpu) {

    is_set(cpu.m_reg_a, 0)                      ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    const auto old_msb = is_set(cpu.m_reg_a, 7);

    cpu.m_reg_a >>= 1;

    old_msb ? set_bit(cpu.m_reg_a, 7) : clear_bit(cpu.m_reg_a, 7);

    cpu.m_reg_a == 0                            ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RR_B(Cpu& cpu) {

    bool carry_status = is_set(cpu.m_reg_f, Cpu::carry_flag);

    is_set(cpu.m_reg_b, 0)                  ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_b >>= 1;
    carry_status ? set_bit(cpu.m_reg_b, 7) : clear_bit(cpu.m_reg_b, 7);

    cpu.m_reg_b == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}


void RR_C(Cpu& cpu) {

    bool carry_status = is_set(cpu.m_reg_f, Cpu::carry_flag);

    is_set(cpu.m_reg_c, 0)                  ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_c >>= 1;
    carry_status ? set_bit(cpu.m_reg_c, 7) : clear_bit(cpu.m_reg_c, 7);

    cpu.m_reg_c == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RR_D(Cpu& cpu) {

    bool carry_status = is_set(cpu.m_reg_f, Cpu::carry_flag);

    is_set(cpu.m_reg_d, 0)                  ? 
    set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_d >>= 1;
    carry_status ? set_bit(cpu.m_reg_d, 7) : clear_bit(cpu.m_reg_d, 7);

    cpu.m_reg_d == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RR_E(Cpu& cpu) {

    bool carry_status = is_set(cpu.m_reg_f, Cpu::carry_flag);

    is_set(cpu.m_reg_e, 0)                  ? 
    set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_e >>= 1;
    carry_status ? set_bit(cpu.m_reg_e, 7) : clear_bit(cpu.m_reg_e, 7);

    cpu.m_reg_e == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RR_H(Cpu& cpu) {

    bool carry_status = is_set(cpu.m_reg_f, Cpu::carry_flag);

    is_set(cpu.m_reg_h, 0)                  ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_h >>= 1;
    carry_status ? set_bit(cpu.m_reg_h, 7) : clear_bit(cpu.m_reg_h, 7);

    cpu.m_reg_h == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RR_L(Cpu& cpu) {

    bool carry_status = is_set(cpu.m_reg_f, Cpu::carry_flag);

    is_set(cpu.m_reg_l, 0)                  ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_l >>= 1;
    carry_status ? set_bit(cpu.m_reg_l, 7) : clear_bit(cpu.m_reg_l, 7);

    cpu.m_reg_l == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void RR_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    bool carry_status = is_set(cpu.m_reg_f, Cpu::carry_flag);

    is_set(value, 0)                  ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    value >>= 1;
    carry_status ? set_bit(value, 7) : clear_bit(value, 7);

    value == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void RR_A(Cpu& cpu) {

    bool carry_status = is_set(cpu.m_reg_f, Cpu::carry_flag);

    is_set(cpu.m_reg_a, 0)                  ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a >>= 1;
    carry_status ? set_bit(cpu.m_reg_a, 7) : clear_bit(cpu.m_reg_a, 7);

    cpu.m_reg_a == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SWAP_B(Cpu& cpu) {

    swap_nibbles(cpu.m_reg_b);
    
    cpu.m_reg_b == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void SWAP_C(Cpu& cpu) {

    swap_nibbles(cpu.m_reg_c);
    
    cpu.m_reg_c == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void SWAP_D(Cpu& cpu) {

    swap_nibbles(cpu.m_reg_d);
    
    cpu.m_reg_d == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void SWAP_E(Cpu& cpu) {

    swap_nibbles(cpu.m_reg_e);
    
    cpu.m_reg_e == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void SWAP_H(Cpu& cpu) {

    swap_nibbles(cpu.m_reg_h);
    
    cpu.m_reg_h == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void SWAP_L(Cpu& cpu) {

    swap_nibbles(cpu.m_reg_l);
    
    cpu.m_reg_l == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void SWAP_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    swap_nibbles(value);
    
    value == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void SWAP_A(Cpu& cpu) {

    swap_nibbles(cpu.m_reg_a);
    
    cpu.m_reg_a == 0 ? 
        set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_0_B(Cpu& cpu) {
    
    is_set(cpu.m_reg_b, 0) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_0_C(Cpu& cpu) {
    
    is_set(cpu.m_reg_c, 0) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_0_D(Cpu& cpu) {
    
    is_set(cpu.m_reg_d, 0) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}
void BIT_0_E(Cpu& cpu) {
    
    is_set(cpu.m_reg_e, 0) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_0_H(Cpu& cpu) {
    
    is_set(cpu.m_reg_h, 0) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_0_L(Cpu& cpu) {
    
    is_set(cpu.m_reg_l, 0) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_0_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    
    is_set(value, 0) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;

}

void BIT_0_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 0) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_1_B(Cpu& cpu) {
    
    is_set(cpu.m_reg_b, 1) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_1_C(Cpu& cpu) {
    
    is_set(cpu.m_reg_c, 1) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_1_D(Cpu& cpu) {
    
    is_set(cpu.m_reg_d, 1) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_1_E(Cpu& cpu) {
    
    is_set(cpu.m_reg_e, 1) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_1_H(Cpu& cpu) {
    
    is_set(cpu.m_reg_h, 1) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_1_L(Cpu& cpu) {
    
    is_set(cpu.m_reg_l, 1) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_1_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    
    is_set(value, 1) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;

}

void BIT_1_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 1) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_2_B(Cpu& cpu) {
    
    is_set(cpu.m_reg_b, 2) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_2_C(Cpu& cpu) {
    
    is_set(cpu.m_reg_c, 2) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_2_D(Cpu& cpu) {
    
    is_set(cpu.m_reg_d, 2) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_2_E(Cpu& cpu) {
    
    is_set(cpu.m_reg_e, 2) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_2_H(Cpu& cpu) {
    
    is_set(cpu.m_reg_h, 2) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_2_L(Cpu& cpu) {
    
    is_set(cpu.m_reg_l, 2) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_2_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    
    is_set(value, 2) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;

}

void BIT_2_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 2) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_3_B(Cpu& cpu) {
    
    is_set(cpu.m_reg_b, 3) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_3_C(Cpu& cpu) {
    
    is_set(cpu.m_reg_c, 3) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_3_D(Cpu& cpu) {
    
    is_set(cpu.m_reg_d, 3) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_3_E(Cpu& cpu) {
    
    is_set(cpu.m_reg_e, 3) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_3_H(Cpu& cpu) {
    
    is_set(cpu.m_reg_h, 3) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_3_L(Cpu& cpu) {
    
    is_set(cpu.m_reg_l, 3) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_3_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    
    is_set(value, 3) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void BIT_3_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 3) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_4_B(Cpu& cpu) {
    
    is_set(cpu.m_reg_b, 4) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_4_C(Cpu& cpu) {
    
    is_set(cpu.m_reg_c, 4) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_4_D(Cpu& cpu) {
    
    is_set(cpu.m_reg_d, 4) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_4_E(Cpu& cpu) {
    
    is_set(cpu.m_reg_e, 4) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_4_H(Cpu& cpu) {
    
    is_set(cpu.m_reg_h, 4) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_4_L(Cpu& cpu) {
    
    is_set(cpu.m_reg_l, 4) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_4_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    
    is_set(value, 4) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;

}

void BIT_4_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 4) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_5_B(Cpu& cpu) {
    
    is_set(cpu.m_reg_b, 5) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_5_C(Cpu& cpu) {
    
    is_set(cpu.m_reg_c, 5) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_5_D(Cpu& cpu) {
    
    is_set(cpu.m_reg_d, 5) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_5_E(Cpu& cpu) {
    
    is_set(cpu.m_reg_e, 5) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_5_H(Cpu& cpu) {
    
    is_set(cpu.m_reg_h, 5) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_5_L(Cpu& cpu) {
    
    is_set(cpu.m_reg_l, 5) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_5_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    
    is_set(value, 5) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;

}

void BIT_5_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 5) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_6_B(Cpu& cpu) {
    
    is_set(cpu.m_reg_b, 6) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_6_C(Cpu& cpu) {
    
    is_set(cpu.m_reg_c, 6) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_6_D(Cpu& cpu) {
    
    is_set(cpu.m_reg_d, 6) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_6_E(Cpu& cpu) {
    
    is_set(cpu.m_reg_e, 6) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_6_H(Cpu& cpu) {
    
    is_set(cpu.m_reg_h, 6) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_6_L(Cpu& cpu) {
    
    is_set(cpu.m_reg_l, 6) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_6_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    
    is_set(value, 6) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;

}

void BIT_6_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 6) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_7_B(Cpu& cpu) {
    
    is_set(cpu.m_reg_b, 7) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_7_C(Cpu& cpu) {
    
    is_set(cpu.m_reg_c, 7) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_7_D(Cpu& cpu) {
    
    is_set(cpu.m_reg_d, 7) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_7_E(Cpu& cpu) {
    
    is_set(cpu.m_reg_e, 7) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_7_H(Cpu& cpu) {
    
    is_set(cpu.m_reg_h, 7) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_7_L(Cpu& cpu) {
    
    is_set(cpu.m_reg_l, 7) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void BIT_7_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    
    is_set(value, 7) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;

}

void BIT_7_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 7) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_0_B(Cpu& cpu) {
    clear_bit(cpu.m_reg_b, 0);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_0_C(Cpu& cpu) {
    clear_bit(cpu.m_reg_c, 0);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_0_D(Cpu& cpu) {
    clear_bit(cpu.m_reg_d, 0);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_0_E(Cpu& cpu) {
    clear_bit(cpu.m_reg_e, 0);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_0_H(Cpu& cpu) {
    clear_bit(cpu.m_reg_h, 0);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_0_L(Cpu& cpu) {
    clear_bit(cpu.m_reg_l, 0);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_0_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    clear_bit(value, 0);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void RES_0_A(Cpu& cpu) {
    clear_bit(cpu.m_reg_a, 0);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_1_B(Cpu& cpu) {
    clear_bit(cpu.m_reg_b, 1);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_1_C(Cpu& cpu) {
    clear_bit(cpu.m_reg_c, 1);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_1_D(Cpu& cpu) {
    clear_bit(cpu.m_reg_d, 1);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_1_E(Cpu& cpu) {
    clear_bit(cpu.m_reg_e, 1);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_1_H(Cpu& cpu) {
    clear_bit(cpu.m_reg_h, 1);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_1_L(Cpu& cpu) {
    clear_bit(cpu.m_reg_l, 1);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_1_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    clear_bit(value, 1);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void RES_1_A(Cpu& cpu) {
    clear_bit(cpu.m_reg_a, 1);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_2_B(Cpu& cpu) {
    clear_bit(cpu.m_reg_b, 2);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_2_C(Cpu& cpu) {
    clear_bit(cpu.m_reg_c, 2);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_2_D(Cpu& cpu) {
    clear_bit(cpu.m_reg_d, 2);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_2_E(Cpu& cpu) {
    clear_bit(cpu.m_reg_e, 2);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_2_H(Cpu& cpu) {
    clear_bit(cpu.m_reg_h, 2);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_2_L(Cpu& cpu) {
    clear_bit(cpu.m_reg_l, 2);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_2_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    clear_bit(value, 2);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void RES_2_A(Cpu& cpu) {
    clear_bit(cpu.m_reg_a, 2);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_3_B(Cpu& cpu) {
    clear_bit(cpu.m_reg_b, 3);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_3_C(Cpu& cpu) {
    clear_bit(cpu.m_reg_c, 3);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_3_D(Cpu& cpu) {
    clear_bit(cpu.m_reg_d, 3);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_3_E(Cpu& cpu) {
    clear_bit(cpu.m_reg_e, 3);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_3_H(Cpu& cpu) {
    clear_bit(cpu.m_reg_h, 3);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_3_L(Cpu& cpu) {
    clear_bit(cpu.m_reg_l, 3);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_3_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    clear_bit(value, 3);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void RES_3_A(Cpu& cpu) {
    clear_bit(cpu.m_reg_a, 3);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_4_B(Cpu& cpu) {
    clear_bit(cpu.m_reg_b, 4);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_4_C(Cpu& cpu) {
    clear_bit(cpu.m_reg_c, 4);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_4_D(Cpu& cpu) {
    clear_bit(cpu.m_reg_d, 4);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_4_E(Cpu& cpu) {
    clear_bit(cpu.m_reg_e, 4);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_4_H(Cpu& cpu) {
    clear_bit(cpu.m_reg_h, 4);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_4_L(Cpu& cpu) {
    clear_bit(cpu.m_reg_l, 4);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_4_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    clear_bit(value, 4);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void RES_4_A(Cpu& cpu) {
    clear_bit(cpu.m_reg_a, 4);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_5_B(Cpu& cpu) {
    clear_bit(cpu.m_reg_b, 5);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_5_C(Cpu& cpu) {
    clear_bit(cpu.m_reg_c, 5);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_5_D(Cpu& cpu) {
    clear_bit(cpu.m_reg_d, 5);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_5_E(Cpu& cpu) {
    clear_bit(cpu.m_reg_e, 5);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_5_H(Cpu& cpu) {
    clear_bit(cpu.m_reg_h, 5);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_5_L(Cpu& cpu) {
    clear_bit(cpu.m_reg_l, 5);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_5_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    clear_bit(value, 5);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void RES_5_A(Cpu& cpu) {
    clear_bit(cpu.m_reg_a, 5);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_6_B(Cpu& cpu) {
    clear_bit(cpu.m_reg_b, 6);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_6_C(Cpu& cpu) {
    clear_bit(cpu.m_reg_c, 6);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_6_D(Cpu& cpu) {
    clear_bit(cpu.m_reg_d, 6);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_6_E(Cpu& cpu) {
    clear_bit(cpu.m_reg_e, 6);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_6_H(Cpu& cpu) {
    clear_bit(cpu.m_reg_h, 6);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_6_L(Cpu& cpu) {
    clear_bit(cpu.m_reg_l, 6);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_6_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    clear_bit(value, 6);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void RES_6_A(Cpu& cpu) {
    clear_bit(cpu.m_reg_a, 6);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_7_B(Cpu& cpu) {
    clear_bit(cpu.m_reg_b, 7);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_7_C(Cpu& cpu) {
    clear_bit(cpu.m_reg_c, 7);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_7_D(Cpu& cpu) {
    clear_bit(cpu.m_reg_d, 7);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_7_E(Cpu& cpu) {
    clear_bit(cpu.m_reg_e, 7);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_7_H(Cpu& cpu) {
    clear_bit(cpu.m_reg_h, 7);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_7_L(Cpu& cpu) {
    clear_bit(cpu.m_reg_l, 7);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void RES_7_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    clear_bit(value, 7);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 16;
}

void RES_7_A(Cpu& cpu) {
    clear_bit(cpu.m_reg_a, 7);
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void SET_0_B(Cpu& cpu) {
    set_bit(cpu.m_reg_b, 0);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_0_C(Cpu& cpu) {
    set_bit(cpu.m_reg_c, 0);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}
void SET_0_D(Cpu& cpu) {
    set_bit(cpu.m_reg_d, 0);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}
void SET_0_E(Cpu& cpu) {
    set_bit(cpu.m_reg_e, 0);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}
void SET_0_H(Cpu& cpu) {
    set_bit(cpu.m_reg_h, 0);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}
void SET_0_L(Cpu& cpu) {
    set_bit(cpu.m_reg_l, 0);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_0_ADDR_HL(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    set_bit(value, 0);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SET_0_A(Cpu& cpu) {
    set_bit(cpu.m_reg_a, 0);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_1_B(Cpu& cpu) {
    set_bit(cpu.m_reg_b, 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_1_C(Cpu& cpu) {
    set_bit(cpu.m_reg_c, 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_1_D(Cpu& cpu) {
    set_bit(cpu.m_reg_d, 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_1_E(Cpu& cpu) {
    set_bit(cpu.m_reg_e, 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_1_H(Cpu& cpu) {
    set_bit(cpu.m_reg_h, 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_1_L(Cpu& cpu) {
    set_bit(cpu.m_reg_l, 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_1_ADDR_HL(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    set_bit(value, 1);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SET_1_A(Cpu& cpu) {
    set_bit(cpu.m_reg_a, 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_2_B(Cpu& cpu) {
    set_bit(cpu.m_reg_b, 2);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_2_C(Cpu& cpu) {
    set_bit(cpu.m_reg_c, 2);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_2_D(Cpu& cpu) {
    set_bit(cpu.m_reg_d, 2);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_2_E(Cpu& cpu) {
    set_bit(cpu.m_reg_e, 2);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_2_H(Cpu& cpu) {
    set_bit(cpu.m_reg_h, 2);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_2_L(Cpu& cpu) {
    set_bit(cpu.m_reg_l, 2);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_2_ADDR_HL(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    set_bit(value, 2);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SET_2_A(Cpu& cpu) {
    set_bit(cpu.m_reg_a, 2);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_3_B(Cpu& cpu) {
    set_bit(cpu.m_reg_b, 3);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_3_C(Cpu& cpu) {
    set_bit(cpu.m_reg_c, 3);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_3_D(Cpu& cpu) {
    set_bit(cpu.m_reg_d, 3);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_3_E(Cpu& cpu) {
    set_bit(cpu.m_reg_e, 3);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_3_H(Cpu& cpu) {
    set_bit(cpu.m_reg_h, 3);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_3_L(Cpu& cpu) {
    set_bit(cpu.m_reg_l, 3);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_3_ADDR_HL(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    set_bit(value, 3);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SET_3_A(Cpu& cpu) {
    set_bit(cpu.m_reg_a, 3);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_4_B(Cpu& cpu) {
    set_bit(cpu.m_reg_b, 4);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_4_C(Cpu& cpu) {
    set_bit(cpu.m_reg_c, 4);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_4_D(Cpu& cpu) {
    set_bit(cpu.m_reg_d, 4);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_4_E(Cpu& cpu) {
    set_bit(cpu.m_reg_e, 4);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_4_H(Cpu& cpu) {
    set_bit(cpu.m_reg_h, 4);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_4_L(Cpu& cpu) {
    set_bit(cpu.m_reg_l, 4);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_4_ADDR_HL(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    set_bit(value, 4);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SET_4_A(Cpu& cpu) {
    set_bit(cpu.m_reg_a, 4);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_5_B(Cpu& cpu) {
    set_bit(cpu.m_reg_b, 5);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_5_C(Cpu& cpu) {
    set_bit(cpu.m_reg_c, 5);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_5_D(Cpu& cpu) {
    set_bit(cpu.m_reg_d, 5);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_5_E(Cpu& cpu) {
    set_bit(cpu.m_reg_e, 5);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_5_H(Cpu& cpu) {
    set_bit(cpu.m_reg_h, 5);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_5_L(Cpu& cpu) {
    set_bit(cpu.m_reg_l, 5);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_5_ADDR_HL(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    set_bit(value, 5);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SET_5_A(Cpu& cpu) {
    set_bit(cpu.m_reg_a, 5);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_6_B(Cpu& cpu) {
    set_bit(cpu.m_reg_b, 6);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_6_C(Cpu& cpu) {
    set_bit(cpu.m_reg_c, 6);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_6_D(Cpu& cpu) {
    set_bit(cpu.m_reg_d, 6);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_6_E(Cpu& cpu) {
    set_bit(cpu.m_reg_e, 6);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_6_H(Cpu& cpu) {
    set_bit(cpu.m_reg_h, 6);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_6_L(Cpu& cpu) {
    set_bit(cpu.m_reg_l, 6);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_6_ADDR_HL(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    set_bit(value, 6);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SET_6_A(Cpu& cpu) {
    set_bit(cpu.m_reg_a, 6);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_7_B(Cpu& cpu) {
    set_bit(cpu.m_reg_b, 7);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_7_C(Cpu& cpu) {
    set_bit(cpu.m_reg_c, 7);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_7_D(Cpu& cpu) {
    set_bit(cpu.m_reg_d, 7);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_7_E(Cpu& cpu) {
    set_bit(cpu.m_reg_e, 7);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_7_H(Cpu& cpu) {
    set_bit(cpu.m_reg_h, 7);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_7_L(Cpu& cpu) {
    set_bit(cpu.m_reg_l, 7);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SET_7_ADDR_HL(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    set_bit(value, 7);

    cpu.m_memory_controller->write(address, value);

    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void SET_7_A(Cpu& cpu) {
    set_bit(cpu.m_reg_a, 7);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}