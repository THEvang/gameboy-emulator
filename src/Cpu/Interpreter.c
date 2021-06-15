#include "Cpu/Interpreter.h"
#include "Cpu/Operations.h"
#include "Cpu/CBOperations.h"
#include "Utilities/BitOperations.h"
#include "Adressing_Modes.h"

#include <stdio.h>
#include <stdlib.h>

int gb_execute(Opcode opcode, Cpu* cpu) {
    
    uint8_t* a = &(cpu->registers[Register_A]);
    uint8_t* b = &(cpu->registers[Register_B]);
    uint8_t* c = &(cpu->registers[Register_C]);
    uint8_t* d = &(cpu->registers[Register_D]);
    uint8_t* e = &(cpu->registers[Register_E]);
    uint8_t* f = &(cpu->registers[Register_F]);
    uint8_t* h = &(cpu->registers[Register_H]);
    uint8_t* l = &(cpu->registers[Register_L]);

    switch (opcode) {
    case Opcode_NOP:
        implied(cpu);
        return gb_nop();

    case Opcode_LD_BC_D16:
        return gb_ld_rr_d16(b, c, immediate_word(cpu));

    case Opcode_LD_ADDR_BC_A:
        implied(cpu);
        return gb_ld_addr_rr_a(*b, *c, cpu);

    case Opcode_INC_BC:
        implied(cpu);
        return gb_inc_rr(b, c);

    case Opcode_INC_B:
        implied(cpu);
        return gb_inc_r(b, f);

    case Opcode_DEC_B:
        implied(cpu);
        return gb_dec_r(b, f);

    case Opcode_LD_B_D8:
        return gb_ld_r_r(b, immediate_byte(cpu));

    case Opcode_RLCA:
        implied(cpu);
        return gb_rlca(cpu);

    case Opcode_LD_ADDR_A16_SP:
        return gb_ld_addr_a16_sp(immediate_word(cpu), cpu);

    case Opcode_ADD_HL_BC:
        implied(cpu);
        return gb_add_hl(combine_bytes(*b, *c), cpu);

    case Opcode_LD_A_ADDR_BC:
        implied(cpu);
        return gb_ld_a_addr_rr(*b, *c, cpu);

    case Opcode_DEC_BC:
        implied(cpu);
        return gb_dec_rr(b, c);

    case Opcode_INC_C:
        implied(cpu);
        return gb_inc_r(c, f);

    case Opcode_DEC_C:
        implied(cpu);
        return gb_dec_r(c, f);

    case Opcode_LD_C_D8:
        return gb_ld_r_r(c, immediate_byte(cpu));

    case Opcode_RRCA:
        implied(cpu);
        return gb_rrca(cpu);

    case Opcode_STOP:
        implied(cpu);
        return gb_stop(cpu);

    case Opcode_LD_DE_D16:
        return gb_ld_rr_d16(d, e, immediate_word(cpu));

    case Opcode_LD_ADDR_DE_A:
        implied(cpu);
        return gb_ld_addr_rr_a(*d, *e, cpu);

    case Opcode_INC_DE:
        implied(cpu);
        return gb_inc_rr(d, e);

    case Opcode_INC_D:
        implied(cpu);
        return gb_inc_r(d, f);

    case Opcode_DEC_D:
        implied(cpu);
        return gb_dec_r(d, f);

    case Opcode_LD_D_D8:
        return gb_ld_r_r(d, immediate_byte(cpu));

    case Opcode_RLA:
        implied(cpu);
        return gb_rla(cpu);

    case Opcode_JR_R8:
        return gb_jr(immediate_byte(cpu), true, cpu);

    case Opcode_ADD_HL_DE:
        implied(cpu);
        return gb_add_hl(combine_bytes(*d, *e), cpu);

    case Opcode_LD_A_ADDR_DE:
        implied(cpu);
        return gb_ld_a_addr_rr(*d, *e, cpu);

    case Opcode_DEC_DE:
        implied(cpu);
        return gb_dec_rr(d, e);

    case Opcode_INC_E:
        implied(cpu);
        return gb_inc_r(e, f);

    case Opcode_DEC_E:
        implied(cpu);
        return gb_dec_r(e, f);

    case Opcode_LD_E_D8:
        return gb_ld_r_r(e, immediate_byte(cpu));

    case Opcode_RRA:
        implied(cpu);
        return gb_rra(cpu);

    case Opcode_JR_NZ_R8:
        return gb_jr(immediate_byte(cpu), !test_flag(*f, Flag_Zero), cpu);

    case Opcode_LD_HL_D16:
        return gb_ld_rr_d16(h, l, immediate_word(cpu));

    case Opcode_LD_ADDR_HLI_A:
        implied(cpu);
        return gb_ldi_addr_hl_a(cpu);

    case Opcode_INC_HL:
        implied(cpu);
        return gb_inc_rr(h, l);

    case Opcode_INC_H:
        implied(cpu);
        return gb_inc_r(h, f);

    case Opcode_DEC_H:
        implied(cpu);
        return gb_dec_r(h, f);

    case Opcode_LD_H_D8:
        return gb_ld_r_r(h, immediate_byte(cpu));

    case Opcode_DAA:
        implied(cpu);
        return gb_daa(cpu);

    case Opcode_JR_Z_R8:
        return gb_jr(immediate_byte(cpu), test_flag(*f, Flag_Zero), cpu);

    case Opcode_ADD_HL_HL:
        implied(cpu);
        return gb_add_hl(combine_bytes(*h, *l), cpu);

    case Opcode_LD_A_ADDR_HLI:
        implied(cpu);
        return gb_ldi_a_addr_hl(cpu);

    case Opcode_DEC_HL:
        implied(cpu);
        return gb_dec_rr(h, l);

    case Opcode_INC_L:
        implied(cpu);
        return gb_inc_r(l, f);

    case Opcode_DEC_L:
        implied(cpu);
        return gb_dec_r(l, f);

    case Opcode_LD_L_D8:
        return gb_ld_r_r(l, immediate_byte(cpu));

    case Opcode_CPL:
        implied(cpu);
        return gb_cpl(a, f);

    case Opcode_JR_NC_R8:
        return gb_jr(immediate_byte(cpu), !test_flag(*f, Flag_Carry), cpu);

    case Opcode_LD_SP_D16:
        return gb_ld_sp(&(cpu->stack_ptr), immediate_word(cpu));

    case Opcode_LD_ADDR_HLD_A:
        implied(cpu);
        return gb_ld_addr_hld_a(cpu);

    case Opcode_INC_SP:
        implied(cpu);
        return gb_inc_sp(&(cpu->stack_ptr));

    case Opcode_INC_ADDR_HL:
        implied(cpu);
        return gb_inc_addr_hl(cpu);

    case Opcode_DEC_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_dec_r(&value, f);
        gb_write(cpu->memory_controller, combine_bytes(*h, *l), value);
        return cycles;
    }

    case Opcode_LD_ADDR_HL_D8:
        return gb_ld_addr_hl(immediate_byte(cpu), cpu);

    case Opcode_SCF:
        implied(cpu);
        return gb_scf(f);

    case Opcode_JR_C_R8:
        return gb_jr(immediate_byte(cpu), test_flag(*f, Flag_Carry), cpu);

    case Opcode_ADD_HL_SP:
        implied(cpu);
        return gb_add_hl(cpu->stack_ptr, cpu);

    case Opcode_LD_A_ADDR_HLD:
        implied(cpu);
        return gb_ld_a_addr_hld(cpu);

    case Opcode_DEC_SP:
        implied(cpu);
        return gb_dec_sp(&(cpu->stack_ptr));

    case Opcode_INC_A:
        implied(cpu);
        return gb_inc_r(a, f);

    case Opcode_DEC_A:
        implied(cpu);
        return gb_dec_r(a, f);

    case Opcode_LD_A_D8:
        return gb_ld_r_r(a, immediate_byte(cpu)) + 4;

    case Opcode_CCF:
        implied(cpu);
        return gb_ccf(f);

    case Opcode_LD_B_B:
        implied(cpu);
        return gb_ld_r_r(b, *b);

    case Opcode_LD_B_C:
        implied(cpu);
        return gb_ld_r_r(b, *c);

    case Opcode_LD_B_D:
        implied(cpu);
        return gb_ld_r_r(b, *d);

    case Opcode_LD_B_E:
        implied(cpu);
        return gb_ld_r_r(b, *e);

    case Opcode_LD_B_H:
        implied(cpu);
        return gb_ld_r_r(b, *h);

    case Opcode_LD_B_L:
        implied(cpu);
        return gb_ld_r_r(b, *l);

    case Opcode_LD_B_ADDR_HL:
        return gb_ld_r_r(b, hl_addressing(cpu));

    case Opcode_LD_B_A:
        implied(cpu);
        return gb_ld_r_r(b, *a);

    case Opcode_LD_C_B:
        implied(cpu);
        return gb_ld_r_r(c, *b);

    case Opcode_LD_C_C:
        implied(cpu);
        return gb_ld_r_r(c, *c);

    case Opcode_LD_C_D:
        implied(cpu);
        return gb_ld_r_r(c, *d);

    case Opcode_LD_C_E:
        implied(cpu);
        return gb_ld_r_r(c, *e);

    case Opcode_LD_C_H:
        implied(cpu);
        return gb_ld_r_r(c, *h);

    case Opcode_LD_C_L:
        implied(cpu);
        return gb_ld_r_r(c, *l);

    case Opcode_LD_C_ADDR_HL:
        return gb_ld_r_r(c, hl_addressing(cpu));

    case Opcode_LD_C_A:
        implied(cpu);
        return gb_ld_r_r(c, *a);

    case Opcode_LD_D_B:
        implied(cpu);
        return gb_ld_r_r(d, *b);

    case Opcode_LD_D_C:
        implied(cpu);
        return gb_ld_r_r(d, *c);

    case Opcode_LD_D_D:
        implied(cpu);
        return gb_ld_r_r(d, *d);

    case Opcode_LD_D_E:
        implied(cpu);
        return gb_ld_r_r(d, *e);

    case Opcode_LD_D_H:
        implied(cpu);
        return gb_ld_r_r(d, *h);

    case Opcode_LD_D_L:
        implied(cpu);
        return gb_ld_r_r(d, *l);

    case Opcode_LD_D_ADDR_HL:
        return gb_ld_r_r(d, hl_addressing(cpu));

    case Opcode_LD_D_A:
        implied(cpu);
        return gb_ld_r_r(d, *a);

    case Opcode_LD_E_B:
        implied(cpu);
        return gb_ld_r_r(e, *b);

    case Opcode_LD_E_C:
        implied(cpu);
        return gb_ld_r_r(e, *c);

    case Opcode_LD_E_D:
        implied(cpu);
        return gb_ld_r_r(e, *d);

    case Opcode_LD_E_E:
        implied(cpu);
        return gb_ld_r_r(e, *e);

    case Opcode_LD_E_H:
        implied(cpu);
        return gb_ld_r_r(e, *h);

    case Opcode_LD_E_L:
        implied(cpu);
        return gb_ld_r_r(e, *l);

    case Opcode_LD_E_ADDR_HL:
        return gb_ld_r_r(e, hl_addressing(cpu));

    case Opcode_LD_E_A:
        implied(cpu);
        return gb_ld_r_r(e, *a);

    case Opcode_LD_H_B:
        implied(cpu);
        return gb_ld_r_r(h, *b);

    case Opcode_LD_H_C:
        implied(cpu);
        return gb_ld_r_r(h, *c);

    case Opcode_LD_H_D:
        implied(cpu);
        return gb_ld_r_r(h, *d);

    case Opcode_LD_H_E:
        implied(cpu);
        return gb_ld_r_r(h, *e);

    case Opcode_LD_H_H:
        implied(cpu);
        return gb_ld_r_r(h, *h);

    case Opcode_LD_H_L:
        implied(cpu);
        return gb_ld_r_r(h, *l);

    case Opcode_LD_H_ADDR_HL:
        return gb_ld_r_r(h, hl_addressing(cpu)) + 4;

    case Opcode_LD_H_A:
        implied(cpu);
        return gb_ld_r_r(h, *a);

    case Opcode_LD_L_B:
        implied(cpu);
        return gb_ld_r_r(l, *b);

    case Opcode_LD_L_C:
        implied(cpu);
        return gb_ld_r_r(l, *c);

    case Opcode_LD_L_D:
        implied(cpu);
        return gb_ld_r_r(l, *d);

    case Opcode_LD_L_E:
        implied(cpu);
        return gb_ld_r_r(l, *e);

    case Opcode_LD_L_H:
        implied(cpu);
        return gb_ld_r_r(l, *h);

    case Opcode_LD_L_L:
        implied(cpu);
        return gb_ld_r_r(l, *l);

    case Opcode_LD_L_ADDR_HL:
        return gb_ld_r_r(l, hl_addressing(cpu));

    case Opcode_LD_L_A:
        implied(cpu);
        return gb_ld_r_r(l, *a);

    case Opcode_LD_ADDR_HL_B:
        implied(cpu);
        return gb_ld_addr_hl(*b, cpu);

    case Opcode_LD_ADDR_HL_C:
        implied(cpu);
        return gb_ld_addr_hl(*c, cpu);

    case Opcode_LD_ADDR_HL_D:
        implied(cpu);
        return gb_ld_addr_hl(*d, cpu);

    case Opcode_LD_ADDR_HL_E:
        implied(cpu);
        return gb_ld_addr_hl(*e, cpu);

    case Opcode_LD_ADDR_HL_H:
        implied(cpu);
        return gb_ld_addr_hl(*h, cpu);

    case Opcode_LD_ADDR_HL_L:
        implied(cpu);
        return gb_ld_addr_hl(*l, cpu);

    case Opcode_HALT:
        implied(cpu);
        return gb_halt(cpu);

    case Opcode_LD_ADDR_HL_A:
        implied(cpu);
        return gb_ld_addr_hl(*a, cpu);

    case Opcode_LD_A_B:
        implied(cpu);
        return gb_ld_r_r(a, *b);

    case Opcode_LD_A_C:
        implied(cpu);
        return gb_ld_r_r(a, *c);

    case Opcode_LD_A_D:
        implied(cpu);
        return gb_ld_r_r(a, *d);

    case Opcode_LD_A_E:
        implied(cpu);
        return gb_ld_r_r(a, *e);

    case Opcode_LD_A_H:
        implied(cpu);
        return gb_ld_r_r(a, *h);

    case Opcode_LD_A_L:
        implied(cpu);
        return gb_ld_r_r(a, *l);

    case Opcode_LD_A_ADDR_HL:
        return gb_ld_r_r(a, hl_addressing(cpu));

    case Opcode_LD_A_A:
        implied(cpu);
        return gb_ld_r_r(a, *a);

    case Opcode_ADD_A_B:
        implied(cpu);
        return gb_add(*b, cpu);

    case Opcode_ADD_A_C:
        implied(cpu);
        return gb_add(*c, cpu);

    case Opcode_ADD_A_D:
        implied(cpu);
        return gb_add(*d, cpu);

    case Opcode_ADD_A_E:
        implied(cpu);
        return gb_add(*e, cpu);

    case Opcode_ADD_A_H:
        implied(cpu);
        return gb_add(*h, cpu);

    case Opcode_ADD_A_L:
        implied(cpu);
        return gb_add(*l, cpu);

    case Opcode_ADD_A_ADDR_HL:
        return gb_add(hl_addressing(cpu), cpu);

    case Opcode_ADD_A_A:
        implied(cpu);
        return gb_add(*a, cpu);

    case Opcode_ADC_A_B:
        implied(cpu);
        return gb_adc(*b, cpu);

    case Opcode_ADC_A_C:
        implied(cpu);
        return gb_adc(*c, cpu);

    case Opcode_ADC_A_D:
        implied(cpu);
        return gb_adc(*d, cpu);

    case Opcode_ADC_A_E:
        implied(cpu);
        return gb_adc(*e, cpu);

    case Opcode_ADC_A_H:
        implied(cpu);
        return gb_adc(*h, cpu);

    case Opcode_ADC_A_L:
        implied(cpu);
        return gb_adc(*l, cpu);

    case Opcode_ADC_A_ADDR_HL:
        return gb_adc(hl_addressing(cpu), cpu);

    case Opcode_ADC_A_A:
        implied(cpu);
        return gb_adc(*a, cpu);

    case Opcode_SUB_B:
        implied(cpu);
        return gb_sub(*b, cpu);

    case Opcode_SUB_C:
        implied(cpu);
        return gb_sub(*c, cpu);

    case Opcode_SUB_D:
        implied(cpu);
        return gb_sub(*d, cpu);

    case Opcode_SUB_E:
        implied(cpu);
        return gb_sub(*e, cpu);

    case Opcode_SUB_H:
        implied(cpu);
        return gb_sub(*h, cpu);

    case Opcode_SUB_L:
        implied(cpu);
        return gb_sub(*l, cpu);

    case Opcode_SUB_ADDR_HL:
        return gb_sub(hl_addressing(cpu), cpu);

    case Opcode_SUB_A:
        implied(cpu);
        return gb_sub(*a, cpu);

    case Opcode_SBC_A_B:
        implied(cpu);
        return gb_sbc(*b, cpu);

    case Opcode_SBC_A_C:
        implied(cpu);
        return gb_sbc(*c, cpu);

    case Opcode_SBC_A_D:
        implied(cpu);
        return gb_sbc(*d, cpu);

    case Opcode_SBC_A_E:
        implied(cpu);
        return gb_sbc(*e, cpu);

    case Opcode_SBC_A_H:
        implied(cpu);
        return gb_sbc(*h, cpu);

    case Opcode_SBC_A_L:
        implied(cpu);
        return gb_sbc(*l, cpu);

    case Opcode_SBC_A_ADDR_HL:
        return gb_sbc(hl_addressing(cpu), cpu);

    case Opcode_SBC_A_A:
        implied(cpu);
        return gb_sbc(*a, cpu);

    case Opcode_AND_B:
        implied(cpu);
        return gb_and(*b, cpu);

    case Opcode_AND_C:
        implied(cpu);
        return gb_and(*c, cpu);

    case Opcode_AND_D:
        implied(cpu);
        return gb_and(*d, cpu);

    case Opcode_AND_E:
        implied(cpu);
        return gb_and(*e, cpu);

    case Opcode_AND_H:
        implied(cpu);
        return gb_and(*h, cpu);

    case Opcode_AND_L:
        implied(cpu);
        return gb_and(*l, cpu);

    case Opcode_AND_ADDR_HL:
        return gb_and(hl_addressing(cpu), cpu);

    case Opcode_AND_A:
        implied(cpu);
        return gb_and(*a, cpu);

    case Opcode_XOR_B:
        implied(cpu);
        return gb_xor(*b, cpu);

    case Opcode_XOR_C:
        implied(cpu);
        return gb_xor(*c, cpu);

    case Opcode_XOR_D:
        implied(cpu);
        return gb_xor(*d, cpu);

    case Opcode_XOR_E:
        implied(cpu);
        return gb_xor(*e, cpu);

    case Opcode_XOR_H:
        implied(cpu);
        return gb_xor(*h, cpu);

    case Opcode_XOR_L:
        implied(cpu);
        return gb_xor(*l, cpu);

    case Opcode_XOR_ADDR_HL:
        return gb_xor(hl_addressing(cpu), cpu);

    case Opcode_XOR_A:
        implied(cpu);
        return gb_xor(*a, cpu);

    case Opcode_OR_B:
        implied(cpu);
        return gb_or(*b, cpu);

    case Opcode_OR_C:
        implied(cpu);
        return gb_or(*c, cpu);

    case Opcode_OR_D:
        implied(cpu);
        return gb_or(*d, cpu);

    case Opcode_OR_E:
        implied(cpu);
        return gb_or(*e, cpu);

    case Opcode_OR_H:
        implied(cpu);
        return gb_or(*h, cpu);

    case Opcode_OR_L:
        implied(cpu);
        return gb_or(*l, cpu);

    case Opcode_OR_ADDR_HL:
        return gb_or(hl_addressing(cpu), cpu) + 4;

    case Opcode_OR_A:
        implied(cpu);
        return gb_or(*a, cpu);

    case Opcode_CP_B:
        implied(cpu);
        return gb_cp(*a, *b, f);

    case Opcode_CP_C:
        implied(cpu);
        return gb_cp(*a, *c, f);

    case Opcode_CP_D:
        implied(cpu);
        return gb_cp(*a, *d, f);

    case Opcode_CP_E:
        implied(cpu);
        return gb_cp(*a, *e, f);

    case Opcode_CP_H:
        implied(cpu);
        return gb_cp(*a, *h, f);

    case Opcode_CP_L:
        implied(cpu);
        return gb_cp(*a, *l, f);

    case Opcode_CP_ADDR_HL:
        return gb_cp(*a, hl_addressing(cpu), f);

    case Opcode_CP_A:
        implied(cpu);
        return gb_cp(*a, *a, f);

    case Opcode_RET_NZ:
        implied(cpu);
        return gb_ret(!test_flag(*f, Flag_Zero), cpu);

    case Opcode_POP_BC:
        implied(cpu);
        return gb_pop_rr(b, c, cpu);

    case Opcode_JP_NZ_A16:
        return gb_jump(immediate_word(cpu), !test_flag(*f, Flag_Zero), cpu);

    case Opcode_JP_A16:
        return gb_jump(immediate_word(cpu), true, cpu);

    case Opcode_CALL_NZ_A16:
        return gb_call(immediate_word(cpu), !test_flag(*f, Flag_Zero), cpu);

    case Opcode_PUSH_BC:
        implied(cpu);
        return gb_push_rr(*b, *c, cpu);

    case Opcode_ADD_A_D8:
        return gb_add(immediate_byte(cpu), cpu);

    case Opcode_RST_00H:
        implied(cpu);
        return gb_rst(0x00, cpu);

    case Opcode_RET_Z:
        implied(cpu);
        return gb_ret(test_flag(*f, Flag_Zero), cpu);

    case Opcode_RET:
        implied(cpu);
        return gb_ret(true, cpu);

    case Opcode_JP_Z_A16:
        return gb_jump(immediate_word(cpu), test_flag(*f, Flag_Zero), cpu);

    case Opcode_PREFIX_CB:
        implied(cpu);
        return gb_prefix_cb(cpu);

    case Opcode_CALL_Z_A16:
        return gb_call(immediate_word(cpu), test_flag(*f, Flag_Zero), cpu);

    case Opcode_CALL_A16:
        return gb_call(immediate_word(cpu), true, cpu);

    case Opcode_ADC_A_D8:
        return gb_adc(immediate_byte(cpu), cpu);

    case Opcode_RST_08H:
        implied(cpu);
        return gb_rst(0x08, cpu);

    case Opcode_RET_NC:
        implied(cpu);
        return gb_ret(!test_flag(*f, Flag_Carry), cpu);

    case Opcode_POP_DE:
        implied(cpu);
        return gb_pop_rr(d, e, cpu);

    case Opcode_JP_NC_A16:
        return gb_jump(immediate_word(cpu), !test_flag(*f, Flag_Carry), cpu);

    case Opcode_CALL_NC_A16:
        return gb_call(immediate_word(cpu), !test_flag(*f, Flag_Carry), cpu);

    case Opcode_PUSH_DE:
        implied(cpu);
        return gb_push_rr(*d, *e, cpu);

    case Opcode_SUB_D8:
        return gb_sub(immediate_byte(cpu), cpu) + 4;

    case Opcode_RST_10H:
        implied(cpu);
        return gb_rst(0x10, cpu);

    case Opcode_RET_C:
        implied(cpu);
        return gb_ret(test_flag(*f, Flag_Carry), cpu);

    case Opcode_RETI:
        implied(cpu);
        return gb_reti(cpu);

    case Opcode_JP_C_A16:
        return gb_jump(immediate_word(cpu), test_flag(*f, Flag_Carry), cpu);

    case Opcode_CALL_C_A16:
        return gb_call(immediate_word(cpu), test_flag(*f, Flag_Carry), cpu);

    case Opcode_SBC_A_D8:
        return gb_sbc(immediate_byte(cpu), cpu) + 4;

    case Opcode_RST_18H:
        implied(cpu);
        return gb_rst(0x18, cpu);

    case Opcode_LDH_ADDR_A8_A:
        return gb_ldh_addr_a8_a(immediate_byte(cpu), cpu);

    case Opcode_POP_HL:
        implied(cpu);
        return gb_pop_rr(h, l, cpu);

    case Opcode_LD_ADDR_C_A:
        implied(cpu);
        return gb_ld_addr_c_a(cpu);

    case Opcode_PUSH_HL:
        implied(cpu);
        return gb_push_rr(*h, *l, cpu);

    case Opcode_AND_D8:
        return gb_and(immediate_byte(cpu), cpu) + 4;

    case Opcode_RST_20H:
        implied(cpu);
        return gb_rst(0x20, cpu);

    case Opcode_ADD_SP_R8:
        return gb_add_sp_r8(immediate_byte(cpu), cpu);

    case Opcode_JP_ADDR_HL:
    {
        implied(cpu);
        uint16_t address = read_register_pair(*cpu, Register_H, Register_L);
        return gb_jump(address, true, cpu);
    }

    case Opcode_LD_ADDR_A16_A:
        return gb_ld_addr_a16_a(immediate_word(cpu), cpu);

    case Opcode_XOR_D8:
        return gb_xor(immediate_byte(cpu), cpu) + 4;

    case Opcode_RST_28H:
        implied(cpu);
        return gb_rst(0x28, cpu);

    case Opcode_LDH_A_ADDR_A8:
        return gb_ldh_a_addr_a8(immediate_byte(cpu), cpu);

    case Opcode_POP_AF:
    {
        implied(cpu);
        int cycles = gb_pop_rr(a, f, cpu);
        *f &= 0xF0u;
        return cycles;
    }
    case Opcode_LD_A_ADDR_C:
        implied(cpu);
        return gb_ld_a_addr_c(cpu);

    case Opcode_DI:
        implied(cpu);
        return gb_di(cpu);

    case Opcode_PUSH_AF:
        implied(cpu);
        return gb_push_rr(*a, *f, cpu);

    case Opcode_OR_D8:
        return gb_or(immediate_byte(cpu), cpu);

    case Opcode_RST_30H:
        implied(cpu);
        return gb_rst(0x30, cpu);

    case Opcode_LD_HL_SPR8:
        return gb_ld_hl_spr8(immediate_byte(cpu), cpu);

    case Opcode_LD_SP_HL:
        implied(cpu);
        return gb_ld_sp(&(cpu->stack_ptr), combine_bytes(*h, *l));

    case Opcode_LD_A_ADDR_A16:
        {
            uint16_t address = immediate_word(cpu);
            return gb_ld_r_r(a, gb_read(cpu->memory_controller, address));
        }

    case Opcode_EI:
        implied(cpu);
        return gb_ei(cpu);

    case Opcode_CP_D8:
        return gb_cp(*a, immediate_byte(cpu), f) +4;

    case Opcode_RST_38H:
        implied(cpu);
        return gb_rst(0x38, cpu);

    default:
        printf("Invalid Opcode: %d\n", opcode);
        exit(1);
    }
}

Cpu_Register get_cb_register(CB_Code opcode) {
    uint8_t lower = (uint8_t) (opcode) & 0x0F;

    switch(lower) {
        case 0x00:
        case 0x08:
            return Register_B;
        case 0x01:
        case 0x09:
            return Register_C;
        case 0x02:
        case 0x0A:
            return Register_D;
        case 0x03:
        case 0x0B:
            return Register_E;
        case 0x04:
        case 0x0C:
            return Register_H;
        case 0x05:
        case 0x0D:
            return Register_L;
        case 0x07:
        case 0x0E:
        default:
            return Register_A;
    }
}

int get_bit_index(CB_Code opcode) {
    
    uint8_t lower = (uint8_t)(opcode) & 0x0F;
    int column_index = lower <= 0x07 ? 0 : 1;

    uint8_t upper = (uint8_t) (opcode) & 0xF0;


    int row_index = 6;
    if(upper == 0x40 || upper == 0x80 || upper == 0xC0) {
        row_index = 0;
    } else if(upper == 0x50 || upper == 0x90 || upper == 0xD0) {
        row_index = 2;
    } else if(upper == 0x60 || upper == 0xA0 || upper == 0xE0) {
        row_index = 4;
    }  

    return column_index + row_index;
}

int gb_execute_cb(CB_Code opcode, Cpu* cpu) {

    uint8_t* reg = &(cpu->registers[get_cb_register(opcode)]);
    uint8_t* f = &(cpu->registers[Register_F]);

    switch (opcode) {
    case CB_Code_RLC_B:
    case CB_Code_RLC_C:
    case CB_Code_RLC_D:
    case CB_Code_RLC_E:
    case CB_Code_RLC_H:
    case CB_Code_RLC_L:
    case CB_Code_RLC_A:
        implied(cpu);
        return gb_rlc(reg, f);

    case CB_Code_RLC_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_rlc(&value, f);
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    case CB_Code_RRC_B:
    case CB_Code_RRC_C:
    case CB_Code_RRC_D:
    case CB_Code_RRC_E:
    case CB_Code_RRC_H:
    case CB_Code_RRC_L:
    case CB_Code_RRC_A:
        implied(cpu);
        return gb_rrc(reg, f);

    case CB_Code_RRC_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_rrc(&value, f);
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    case CB_Code_RL_B:
    case CB_Code_RL_C:
    case CB_Code_RL_D:
    case CB_Code_RL_E:
    case CB_Code_RL_H:
    case CB_Code_RL_L:
    case CB_Code_RL_A:
        implied(cpu);
        return gb_rl(reg, f);

    case CB_Code_RL_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_rl(&value, f);
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    case CB_Code_RR_B:
    case CB_Code_RR_C:
    case CB_Code_RR_D:
    case CB_Code_RR_E:
    case CB_Code_RR_H:
    case CB_Code_RR_L:
    case CB_Code_RR_A:
        implied(cpu);
        return gb_rr(reg, f);

    case CB_Code_RR_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_rr(&value, f);
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    case CB_Code_SLA_B:
    case CB_Code_SLA_C:
    case CB_Code_SLA_D:
    case CB_Code_SLA_E:
    case CB_Code_SLA_H:
    case CB_Code_SLA_L:
    case CB_Code_SLA_A:
        implied(cpu);
        return gb_sla(reg, f);

    case CB_Code_SLA_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_sla(&value, f);
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    case CB_Code_SRA_B:
    case CB_Code_SRA_C:
    case CB_Code_SRA_D:
    case CB_Code_SRA_E:
    case CB_Code_SRA_H:
    case CB_Code_SRA_L:
    case CB_Code_SRA_A:
        implied(cpu);
        return gb_sra(reg, f);

    case CB_Code_SRA_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_sra(&value, f);
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    case CB_Code_SWAP_B:
    case CB_Code_SWAP_C:
    case CB_Code_SWAP_D:
    case CB_Code_SWAP_E:
    case CB_Code_SWAP_H:
    case CB_Code_SWAP_L:
    case CB_Code_SWAP_A:
        implied(cpu);
        return gb_swap(reg, f);

    case CB_Code_SWAP_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_swap(&value, f);
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    case CB_Code_SRL_B:
    case CB_Code_SRL_C:
    case CB_Code_SRL_D:
    case CB_Code_SRL_E:
    case CB_Code_SRL_H:
    case CB_Code_SRL_L:
    case CB_Code_SRL_A:
        implied(cpu);
        return gb_slr(reg, f);

    case CB_Code_SRL_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_slr(&value, f);
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    case CB_Code_BIT_0_B:
    case CB_Code_BIT_0_C:
    case CB_Code_BIT_0_D:
    case CB_Code_BIT_0_E:
    case CB_Code_BIT_0_H:
    case CB_Code_BIT_0_L:
    case CB_Code_BIT_0_A:
    case CB_Code_BIT_1_B:
    case CB_Code_BIT_1_C:
    case CB_Code_BIT_1_D:
    case CB_Code_BIT_1_E:
    case CB_Code_BIT_1_H:
    case CB_Code_BIT_1_L:
    case CB_Code_BIT_1_A:
    case CB_Code_BIT_2_B:
    case CB_Code_BIT_2_C:
    case CB_Code_BIT_2_D:
    case CB_Code_BIT_2_E:
    case CB_Code_BIT_2_H:
    case CB_Code_BIT_2_L:
    case CB_Code_BIT_2_A:
    case CB_Code_BIT_3_B:
    case CB_Code_BIT_3_C:
    case CB_Code_BIT_3_D:
    case CB_Code_BIT_3_E:
    case CB_Code_BIT_3_H:
    case CB_Code_BIT_3_L:
    case CB_Code_BIT_3_A:
    case CB_Code_BIT_4_B:
    case CB_Code_BIT_4_C:
    case CB_Code_BIT_4_D:
    case CB_Code_BIT_4_E:
    case CB_Code_BIT_4_H:
    case CB_Code_BIT_4_L:
    case CB_Code_BIT_4_A:
    case CB_Code_BIT_5_B:
    case CB_Code_BIT_5_C:
    case CB_Code_BIT_5_D:
    case CB_Code_BIT_5_E:
    case CB_Code_BIT_5_H:
    case CB_Code_BIT_5_L:
    case CB_Code_BIT_5_A:
    case CB_Code_BIT_6_B:
    case CB_Code_BIT_6_C:
    case CB_Code_BIT_6_D:
    case CB_Code_BIT_6_E:
    case CB_Code_BIT_6_H:
    case CB_Code_BIT_6_L:
    case CB_Code_BIT_6_A:
    case CB_Code_BIT_7_B:
    case CB_Code_BIT_7_C:
    case CB_Code_BIT_7_D:
    case CB_Code_BIT_7_E:
    case CB_Code_BIT_7_H:
    case CB_Code_BIT_7_L:
    case CB_Code_BIT_7_A:
        implied(cpu);
        return gb_bit(*reg, get_bit_index(opcode), f);

    case CB_Code_BIT_0_ADDR_HL:
    case CB_Code_BIT_1_ADDR_HL:
    case CB_Code_BIT_2_ADDR_HL:
    case CB_Code_BIT_3_ADDR_HL:
    case CB_Code_BIT_4_ADDR_HL:
    case CB_Code_BIT_5_ADDR_HL:
    case CB_Code_BIT_6_ADDR_HL:
    case CB_Code_BIT_7_ADDR_HL:
        return gb_bit(hl_addressing(cpu), get_bit_index(opcode), f);

    case CB_Code_RES_0_B:
    case CB_Code_RES_0_C:
    case CB_Code_RES_0_D:
    case CB_Code_RES_0_E:
    case CB_Code_RES_0_H:
    case CB_Code_RES_0_L:
    case CB_Code_RES_0_A:
    case CB_Code_RES_1_B:
    case CB_Code_RES_1_C:
    case CB_Code_RES_1_D:
    case CB_Code_RES_1_E:
    case CB_Code_RES_1_H:
    case CB_Code_RES_1_L:
    case CB_Code_RES_1_A:
    case CB_Code_RES_2_B:
    case CB_Code_RES_2_C:
    case CB_Code_RES_2_D:
    case CB_Code_RES_2_E:
    case CB_Code_RES_2_H:
    case CB_Code_RES_2_L:
    case CB_Code_RES_2_A:
    case CB_Code_RES_3_B:
    case CB_Code_RES_3_C:
    case CB_Code_RES_3_D:
    case CB_Code_RES_3_E:
    case CB_Code_RES_3_H:
    case CB_Code_RES_3_L:
    case CB_Code_RES_3_A:
    case CB_Code_RES_4_B:
    case CB_Code_RES_4_C:
    case CB_Code_RES_4_D:
    case CB_Code_RES_4_E:
    case CB_Code_RES_4_H:
    case CB_Code_RES_4_L:
    case CB_Code_RES_4_A:
    case CB_Code_RES_5_B:
    case CB_Code_RES_5_C:
    case CB_Code_RES_5_D:
    case CB_Code_RES_5_E:
    case CB_Code_RES_5_H:
    case CB_Code_RES_5_L:
    case CB_Code_RES_5_A:
    case CB_Code_RES_6_B:
    case CB_Code_RES_6_C:
    case CB_Code_RES_6_D:
    case CB_Code_RES_6_E:
    case CB_Code_RES_6_H:
    case CB_Code_RES_6_L:
    case CB_Code_RES_6_A:
    case CB_Code_RES_7_B:
    case CB_Code_RES_7_C:
    case CB_Code_RES_7_D:
    case CB_Code_RES_7_E:
    case CB_Code_RES_7_H:
    case CB_Code_RES_7_L:
    case CB_Code_RES_7_A:
        implied(cpu);
        return gb_res(reg, get_bit_index(opcode));

    case CB_Code_RES_0_ADDR_HL:
    case CB_Code_RES_1_ADDR_HL:
    case CB_Code_RES_2_ADDR_HL:
    case CB_Code_RES_3_ADDR_HL:
    case CB_Code_RES_4_ADDR_HL:
    case CB_Code_RES_5_ADDR_HL:
    case CB_Code_RES_6_ADDR_HL:
    case CB_Code_RES_7_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_res(&value, get_bit_index(opcode));
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    case CB_Code_SET_0_B:
    case CB_Code_SET_0_C:
    case CB_Code_SET_0_D:
    case CB_Code_SET_0_E:
    case CB_Code_SET_0_H:
    case CB_Code_SET_0_L:
    case CB_Code_SET_0_A:
    case CB_Code_SET_1_B:
    case CB_Code_SET_1_C:
    case CB_Code_SET_1_D:
    case CB_Code_SET_1_E:
    case CB_Code_SET_1_H:
    case CB_Code_SET_1_L:
    case CB_Code_SET_1_A:
    case CB_Code_SET_2_B:
    case CB_Code_SET_2_C:
    case CB_Code_SET_2_D:
    case CB_Code_SET_2_E:
    case CB_Code_SET_2_H:
    case CB_Code_SET_2_L:
    case CB_Code_SET_2_A:
    case CB_Code_SET_3_B:
    case CB_Code_SET_3_C:
    case CB_Code_SET_3_D:
    case CB_Code_SET_3_E:
    case CB_Code_SET_3_H:
    case CB_Code_SET_3_L:
    case CB_Code_SET_3_A:
    case CB_Code_SET_4_B:
    case CB_Code_SET_4_C:
    case CB_Code_SET_4_D:
    case CB_Code_SET_4_E:
    case CB_Code_SET_4_H:
    case CB_Code_SET_4_L:
    case CB_Code_SET_4_A:
    case CB_Code_SET_5_B:
    case CB_Code_SET_5_C:
    case CB_Code_SET_5_D:
    case CB_Code_SET_5_E:
    case CB_Code_SET_5_H:
    case CB_Code_SET_5_L:
    case CB_Code_SET_5_A:
    case CB_Code_SET_6_B:
    case CB_Code_SET_6_C:
    case CB_Code_SET_6_D:
    case CB_Code_SET_6_E:
    case CB_Code_SET_6_H:
    case CB_Code_SET_6_L:
    case CB_Code_SET_6_A:
    case CB_Code_SET_7_B:
    case CB_Code_SET_7_C:
    case CB_Code_SET_7_D:
    case CB_Code_SET_7_E:
    case CB_Code_SET_7_H:
    case CB_Code_SET_7_L:
    case CB_Code_SET_7_A:
        implied(cpu);
        return gb_set(reg, get_bit_index(opcode));

    case CB_Code_SET_0_ADDR_HL:
    case CB_Code_SET_1_ADDR_HL:
    case CB_Code_SET_2_ADDR_HL:
    case CB_Code_SET_3_ADDR_HL:
    case CB_Code_SET_4_ADDR_HL:
    case CB_Code_SET_5_ADDR_HL:
    case CB_Code_SET_6_ADDR_HL:
    case CB_Code_SET_7_ADDR_HL:
    {
        uint8_t value = hl_addressing(cpu);
        int cycles = gb_set(&value, get_bit_index(opcode));
        gb_write(cpu->memory_controller, combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]), value);
        return cycles;
    }

    default:
        printf("Unimplemented CB Code: %d\n", opcode);
        exit(1);
    }
}