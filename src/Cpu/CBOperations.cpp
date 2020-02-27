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