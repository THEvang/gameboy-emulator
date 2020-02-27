#include <cpu/CBOperations.h>
#include <BitOperations.h>

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
    cpu.m_cycles += 8;

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
    cpu.m_cycles += 8;

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
    cpu.m_cycles += 8;

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
    cpu.m_cycles += 12;
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
    cpu.m_cycles += 8;

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
    cpu.m_cycles += 8;

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
    cpu.m_cycles += 8;

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
    cpu.m_cycles += 8;

}

void BIT_7_A(Cpu& cpu) {
    
    is_set(cpu.m_reg_a, 7) ? clear_bit(cpu.m_reg_f, Cpu::zero_flag) :
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}