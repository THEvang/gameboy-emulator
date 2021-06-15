#include "Cpu/CBOperations.h"

#include "Cpu/Cpu.h"
#include "Utilities/BitOperations.h"

uint8_t rlc(uint8_t value, uint8_t* flags) {

    test_bit_8bit(value, 7) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);

    value = rotate_left(value, 1);

    value == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return value;
}

int gb_rlc(uint8_t* r, uint8_t* flags) {
    *r = rlc(*r, flags);
    return 8;
}

int gb_rrc(uint8_t* r, uint8_t* flags) {
    
    test_bit_8bit(*r, 0) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);
    
    *r = rotate_right(*r, 1);

    *r == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);
    
    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return 8;
}

int gb_rl(uint8_t* r, uint8_t* flags) {

    const bool new_carry_flag = test_bit_8bit(*r, 7);
    *r = (uint8_t) (*r << 1u);

    test_bit_8bit(*flags, Flag_Carry) ? set_bit(r, 0) : clear_bit(r, 0);
    
    new_carry_flag ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);

    *r == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return 8;
}

int gb_slr(uint8_t* r, uint8_t* flags) {

    test_bit_8bit(*r, 0) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);
    
    *r = (uint8_t) (*r >> 1u);
    clear_bit(r, 7);

    *r == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);
    return 8;
}

int gb_sla(uint8_t* r, uint8_t* flags) {

    test_bit_8bit(*r, 7) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);
    
    *r = (uint8_t) (*r << 1u);
    clear_bit(r, 0);

    *r == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return 8;
}

int gb_sra(uint8_t* r, uint8_t* flags) {
    
    test_bit_8bit(*r, 0) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);
    
    const bool old_msb = test_bit_8bit(*r, 7);

    *r = (uint8_t) (*r >> 1u);

    old_msb ? set_bit(r, 7) : clear_bit(r, 7);

    *r == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return 8;
}

int gb_rr(uint8_t* r, uint8_t* flags) {

    bool carry_status = test_bit_8bit(*flags, Flag_Carry);

    test_bit_8bit(*r, 0) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);

    *r = (uint8_t) (*r >> 1u);
    carry_status ? set_bit(r, 7) : clear_bit(r, 7);

    *r == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);
    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);

    return 8;
}

int gb_swap(uint8_t* r, uint8_t* flags) {

    swap_nibbles(r);
    
    *r == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);
    clear_bit(flags, Flag_Carry);

    return 8;
}

int gb_bit(uint8_t r, int n, uint8_t* flags) {
    
    test_bit_8bit(r, n) ? clear_bit(flags, Flag_Zero) : set_bit(flags, Flag_Zero);
    
    clear_bit(flags, Flag_Sub);
    set_bit(flags, Flag_Half_Carry);   
    
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