#pragma once

#include <stdint.h>
#include "Cpu/Cpu.h"
#include "Memory/Memory_Controller.h"

int gb_nop();
int gb_stop(MemoryBankController* mc);
int gb_halt(Cpu*, MemoryBankController*);
int gb_rst(uint8_t address, Cpu* cpu, MemoryBankController*); 
int gb_di(Cpu* cpu);
int gb_ei(Cpu* cpu);

int gb_jr(uint8_t offset, bool predicate, Cpu* cpu);
int gb_ret(bool predicate, Cpu* cpu, MemoryBankController*);
int gb_reti(Cpu* cpu, MemoryBankController*);

int gb_jump(uint16_t address, bool predicate, Cpu* cpu);
int gb_call(uint16_t address, bool predicate, Cpu* cpu, MemoryBankController*);

int gb_ld_r_r(uint8_t* dst, uint8_t src);

int gb_ld_a_addr_rr(uint8_t r1, uint8_t r2, Cpu* cpu, MemoryBankController* mc);
int gb_ld_a_addr_c(Cpu* cpu, MemoryBankController*);
int gb_ld_a_addr_a16(uint16_t address, Cpu* cpu);
int gb_ld_addr_a16_sp(uint16_t address, Cpu* cpu, MemoryBankController*);

int gb_ldi_addr_hl_a(Cpu* cpu, MemoryBankController*);
int gb_ldi_a_addr_hl(Cpu* cpu, MemoryBankController*);

int gb_ld_addr_rr_a(uint8_t r1, uint8_t r2, Cpu* cpu, MemoryBankController*);

int gb_ld_addr_hl(uint8_t value, Cpu* cpu, MemoryBankController*);
int gb_ld_addr_a16_a(uint16_t address, Cpu* cpu, MemoryBankController*);

int gb_ld_rr_d16(uint8_t* r1, uint8_t* r2, uint16_t value);
int gb_ld_hl_spr8(uint8_t offset, Cpu* cpu);

int gb_ld_sp(uint16_t* sp, uint16_t rr);

int gb_add(uint8_t r, Cpu* cpu);
int gb_add_hl(uint16_t value, Cpu* cpu);

int gb_sub(uint8_t r, Cpu* cpu);

int gb_inc_r(uint8_t* reg, uint8_t* flags);
int gb_inc_rr(uint8_t* r1, uint8_t* r2);
int gb_inc_addr_hl(Cpu* cpu, MemoryBankController*);
int gb_inc_sp(uint16_t* sp);

int gb_dec_r(uint8_t* r1, uint8_t* flags);
int gb_dec_rr(uint8_t* r1, uint8_t* r2);
int gb_dec_sp(uint16_t* sp);

int gb_scf(uint8_t* flags);
int gb_ccf(uint8_t* flags);

int gb_rra(Cpu*);
int gb_rrca(Cpu*);

int gb_rla(Cpu*);
int gb_rlca(Cpu*);

int gb_daa(Cpu* cpu);

int gb_add_sp_r8(uint8_t offset, Cpu* cpu);

int gb_and(uint8_t r, Cpu* Cpu);
int gb_xor(uint8_t r, Cpu* cpu);
int gb_or(uint8_t r, Cpu* cpu);
int gb_cp(uint8_t r1, uint8_t r2, uint8_t* flags);

int gb_push_rr(uint8_t r1, uint8_t r2, Cpu* cpu, MemoryBankController*);
int gb_pop_rr(uint8_t* r1, uint8_t* r2, Cpu* cpu, MemoryBankController*);

int gb_adc(uint8_t r, Cpu* cpu);

int gb_ldh_addr_a8_a(uint8_t r, Cpu* cpu, MemoryBankController*);
int gb_ldh_a_addr_a8(uint8_t r, Cpu* cpu, MemoryBankController*);
int gb_ld_addr_c_a(Cpu* cpu, MemoryBankController*);
int gb_sbc(uint8_t r, Cpu* cpu);

int gb_prefix_cb(Cpu* cpu, MemoryBankController*);

int gb_ld_addr_hld_a(Cpu*, MemoryBankController*);
int gb_ld_a_addr_hld(Cpu*, MemoryBankController*);

int gb_cpl(uint8_t* a, uint8_t* flags);