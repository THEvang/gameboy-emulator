#include "Cpu/CBOperations.h"

#include "Cpu/Cpu.h"
#include "Utilities/BitOperations.h"

int gb_rlc(uint8_t* r, uint8_t* flags) {

    test_bit_8bit(*r, 7) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

    *r = rotate_left(*r, 1);

    *r == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub | Flag_Half_Carry);

    return 8;
}

int gb_rrc(uint8_t* r, uint8_t* flags) {
    
    test_bit_8bit(*r, 0) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);
    
    *r = rotate_right(*r, 1);

    *r == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);
    
    clear_flag(flags, Flag_Sub | Flag_Half_Carry);

    return 8;
}

int gb_rl(uint8_t* r, uint8_t* flags) {

    const bool new_carry_flag = test_bit_8bit(*r, 7);
    *r = (uint8_t) (*r << 1u);

    test_flag(*flags, Flag_Carry) ? set_bit(r, 0) : clear_bit(r, 0);
    
    new_carry_flag ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

    *r == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub | Flag_Half_Carry);

    return 8;
}

int gb_slr(uint8_t* r, uint8_t* flags) {

    test_bit_8bit(*r, 0) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);
    
    *r = (uint8_t) (*r >> 1u);
    clear_bit(r, 7);

    *r == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub | Flag_Half_Carry);
    return 8;
}

int gb_sla(uint8_t* r, uint8_t* flags) {

    test_bit_8bit(*r, 7) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);
    
    *r = (uint8_t) (*r << 1u);
    clear_bit(r, 0);

    *r == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub | Flag_Half_Carry);

    return 8;
}

int gb_sra(uint8_t* r, uint8_t* flags) {
    
    test_bit_8bit(*r, 0) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);
    
    const bool old_msb = test_bit_8bit(*r, 7);

    *r = (uint8_t) (*r >> 1u);

    old_msb ? set_bit(r, 7) : clear_bit(r, 7);

    *r == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub | Flag_Half_Carry);

    return 8;
}

int gb_rr(uint8_t* r, uint8_t* flags) {

    bool carry_status = test_flag(*flags, Flag_Carry);

    test_bit_8bit(*r, 0) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

    *r = (uint8_t) (*r >> 1u);
    carry_status ? set_bit(r, 7) : clear_bit(r, 7);

    *r == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);
    clear_flag(flags, Flag_Sub | Flag_Half_Carry);

    return 8;
}

int gb_swap(uint8_t* r, uint8_t* flags) {

    *r = (uint8_t) (( (*r & 0x0FU) << 4U | (*r & 0xF0U) >> 4U));
    
    *r == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub | Flag_Half_Carry | Flag_Carry);

    return 8;
}

int gb_bit(uint8_t r, int n, uint8_t* flags) {
    
    test_bit_8bit(r, n) ? clear_flag(flags, Flag_Zero) : set_flag(flags, Flag_Zero);
    
    clear_flag(flags, Flag_Sub);
    set_flag(flags, Flag_Half_Carry);   
    
    return 8;
}

int gb_res(uint8_t* r, int n) {
    clear_bit(r, n);
    return 8;
}

int gb_set(uint8_t* r, int n) {
    set_bit(r, n);
    return 8;
}