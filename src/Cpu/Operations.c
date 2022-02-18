#include "Cpu/Operations.h"

#include <stdio.h>
#include <stdlib.h>

#include "Utilities/BitOperations.h"
#include "Cpu/CBOpcodes.h"
#include "Memory/Memory_Controller.h"
#include "Interpreter.h"
#include "Adressing_Modes.h"

int gb_nop() {
    return 4;
}

int gb_stop(MemoryBankController* mc) {
    mc->memory[0xFF04] = 0;
    return 4;
}

int gb_halt(Cpu* cpu, MemoryBankController* mc) {

    const uint16_t interrupt_request_addr = 0xFF0F;
    const uint16_t interrupt_enable_addr = 0xFFFF;

    const uint8_t interrupt_request = mc->read(mc, interrupt_request_addr);
    const uint8_t interrupt_enable = mc->read(mc, interrupt_enable_addr);

    if (cpu->interrupts_enabled) {
        cpu->is_halted = true;
        return 4;
    }

    if ( (interrupt_request & interrupt_enable & 0x1F) == 0) {
        cpu->is_halted = true;
        return 4;
    } else {
        cpu->halt_bug_triggered = true;
        return 4;
    }
}

int gb_rst(uint8_t address, Cpu* cpu, MemoryBankController* mc) {
            
    const uint8_t pc_high = (uint8_t) (cpu->program_counter >> 8u);
    const uint8_t pc_low =  (uint8_t) (cpu->program_counter & 0xFFu);

    mc->write(mc, (uint16_t) (cpu->stack_ptr - 1), pc_high);
    mc->write(mc, (uint16_t) (cpu->stack_ptr - 2), pc_low);

    cpu->program_counter = combine_bytes(0x00, address);
    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr - 2);

    return 16;
}

int gb_di(Cpu* cpu) {
    cpu->should_disable_interrupts = true;
    return 4;    
}

int gb_ei(Cpu* cpu) {
    cpu->should_enable_interrupts = true;
    return 4;
}

int jump_relative(uint8_t offset, Cpu* cpu) {
    cpu->program_counter = (uint16_t) (cpu->program_counter + (int8_t) offset);
    return 12;
}

int gb_jr(uint8_t offset, bool predicate, Cpu* cpu) {
    return predicate ? jump_relative(offset, cpu) : 8;
}

int ret(Cpu* cpu, MemoryBankController* mc) {
    const uint8_t pc_low = mc->read(mc, cpu->stack_ptr);
    const uint8_t pc_high = mc->read(mc, (uint16_t) (cpu->stack_ptr + 1));
    
    cpu->program_counter = combine_bytes(pc_high, pc_low);
    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr + 2);
    return 16;
}

int gb_ret(bool predicate, Cpu* cpu, MemoryBankController* mc) {
    return predicate ? ret(cpu, mc) : 8;
}

int gb_reti(Cpu* cpu, MemoryBankController* mc) {
    cpu->interrupts_enabled = true;
    return ret(cpu, mc);
}

int jump(Cpu* cpu, uint16_t address) {
    cpu->program_counter = address; 
    return 16;
}

int gb_jump(uint16_t address, bool predicate, Cpu* cpu) {
    return predicate ? jump(cpu, address) : 12;
}

int call(Cpu* cpu, uint16_t address, MemoryBankController* mc) {

    const uint8_t pc_high = (uint8_t) (cpu->program_counter >> 8u);
    const uint8_t pc_low = (uint8_t) (cpu->program_counter & 0xFFu);
    
    mc->write(mc, (uint16_t) (cpu->stack_ptr - 1), pc_high);
    mc->write(mc, (uint16_t) (cpu->stack_ptr - 2), pc_low);
    cpu->stack_ptr = (uint16_t)(cpu->stack_ptr -2);
    
    cpu->program_counter = address;

    return 24;
}

int gb_call(uint16_t address, bool predicate, Cpu* cpu, MemoryBankController* mc) {
    return predicate ? call(cpu, address, mc) : 12;
}

int gb_ld_r_r(uint8_t* dst, uint8_t src) {
    *dst = src;
    return 4;
}

int gb_ld_a_addr_rr(uint8_t r1, uint8_t r2, Cpu* cpu, MemoryBankController* mc) {
    const uint16_t address = combine_bytes(r1, r2);
    cpu->registers[Register_A] = mc->read(mc, address);
    return 8;
}

int gb_ld_a_addr_c(Cpu* cpu, MemoryBankController* mc) {

    const uint16_t address = (uint16_t) (0xFF00 + cpu->registers[Register_C]);
    cpu->registers[Register_A] =  mc->read(mc, address);

    return 8;
}

int gb_ld_addr_a16_sp(uint16_t address, Cpu* cpu, MemoryBankController* mc) {

    mc->write(mc, address, (uint8_t) (cpu->stack_ptr & 0xFFu));
    mc->write(mc, (uint16_t) (address + 1), (uint8_t) (cpu->stack_ptr >> 8u));
    return 20;
}

int gb_ldi_addr_hl_a(Cpu* cpu, MemoryBankController* mc) {

    uint16_t address = read_register_pair(*cpu, Register_H, Register_L);
    
    mc->write(mc, address, cpu->registers[Register_A]);

    address++;
    cpu->registers[Register_H] =  (uint8_t) (address >> 8u);
    cpu->registers[Register_L] =  (uint8_t) (address & 0xFFu);

    return 8;
}

int gb_ldi_a_addr_hl(Cpu* cpu, MemoryBankController* mc) {
    
    uint16_t address = read_register_pair(*cpu, Register_H, Register_L);
    cpu->registers[Register_A] = mc->read(mc, address);
    
    address++;
    cpu->registers[Register_H] = (uint8_t) (address >> 8u);
    cpu->registers[Register_L] = (uint8_t) (address & 0xFFu);

    return 8;
}

int gb_ld_addr_rr_a(uint8_t r1, uint8_t r2, Cpu* cpu, MemoryBankController* mc) {
    const uint16_t address = combine_bytes(r1, r2);
    mc->write(mc, address, cpu->registers[Register_A]);   
    return 8;
}

int gb_ld_addr_hl(uint8_t value, Cpu* cpu, MemoryBankController* mc) {
    const uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    mc->write(mc, address, value);
    return 8;
}

int gb_ld_addr_hl_addr_hl() {    
    printf("Unimplemented operation: LD ADDR HL ADDR HL\n");
    exit(1);
}

int gb_ld_addr_a16_a(uint16_t address, Cpu* cpu, MemoryBankController* mc) {
    mc->write(mc, address, cpu->registers[Register_A]);
    return 16;
}

int gb_ld_rr_d16(uint8_t* r1, uint8_t* r2, uint16_t value) {

    *r2 =  (uint8_t) (value & 0xFFu);
    *r1 =  (uint8_t) (value >> 8u);

    return 12;
}

int gb_ld_hl_spr8(uint8_t offset, Cpu* cpu) {

    uint8_t* flags = &(cpu->registers[Register_F]);

    half_carry_8bit((uint8_t) (cpu->stack_ptr), offset)     ?
        set_flag(flags, Flag_Half_Carry)  :
        clear_flag(flags, Flag_Half_Carry);


    overflows_8bit((uint8_t) (cpu->stack_ptr), offset) ?
        set_flag(flags, Flag_Carry)   :
        clear_flag(flags, Flag_Carry);

    const uint16_t result = (uint16_t) (cpu->stack_ptr + (int8_t) offset);

    cpu->registers[Register_H] =  (uint8_t) (result >> 8u);
    cpu->registers[Register_L] =  (uint8_t) (result & 0xFFu);

    clear_flag(flags, Flag_Zero);
    clear_flag(flags, Flag_Sub);

    return 12;
}

int gb_ld_sp(uint16_t* sp, uint16_t rr) {
    *sp = rr;
    return 12;
}

int gb_add(uint8_t value, Cpu* cpu) {

    uint8_t* flags = &(cpu->registers[Register_F]);
    uint8_t a = cpu->registers[Register_A];

    half_carry_8bit(a, value)             ? 
        set_flag(flags, Flag_Half_Carry)  :
        clear_flag(flags, Flag_Half_Carry);

    overflows_8bit(a, value)          ?
        set_flag(flags, Flag_Carry)   :
        clear_flag(flags, Flag_Carry);

    a = (uint8_t) (a + value);

    a == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub);

    cpu->registers[Register_A] = a;
    
    return 8;
}

int gb_add_hl(uint16_t value, Cpu* cpu) {
    
    uint8_t* flags = &(cpu->registers[Register_F]);
    uint16_t hl = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);

    overflows_16bit(hl, value) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

    half_carry_16bit(hl, value) ? set_flag(flags, Flag_Half_Carry) : clear_flag(flags, Flag_Half_Carry);

    hl = (uint16_t) (hl + value);

    clear_flag(flags, Flag_Sub);

    cpu->registers[Register_H] =  (uint8_t)(hl >> 8u);
    cpu->registers[Register_L] =  (uint8_t)(hl & 0xFFu);

    return 8;
}

int gb_sub(uint8_t r, Cpu* cpu) {

    uint8_t* a = &(cpu->registers[Register_A]);
    uint8_t* flags = &(cpu->registers[Register_F]);

    half_borrow_8bit(*a, r) ? set_flag(flags, Flag_Half_Carry) : clear_flag(flags, Flag_Half_Carry);

    underflows_8bit(*a, r) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

    *a = (uint8_t) (*a - r);

    *a == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    set_flag(flags, Flag_Sub);

    return 4;
}

void inc(uint8_t* value, uint8_t* flags) {
    
    half_carry_8bit(*value, 1) ? set_flag(flags, Flag_Half_Carry) : clear_flag(flags, Flag_Half_Carry);

    (*value)++;

    *value == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub);
}

int gb_inc_r(uint8_t* r, uint8_t* flags) {
    inc(r, flags);
    return 4;
}

int gb_inc_rr(uint8_t* r1, uint8_t* r2) {

    uint16_t value = combine_bytes(*r1, *r2);
    value++;

    *r1 =  (uint8_t) (value >> 8u);
    *r2 =  (uint8_t) (value & 0xFFu);

    return 8;
}

int gb_inc_addr_hl(Cpu* cpu, MemoryBankController* mc) {

    const uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    uint8_t value = mc->read(mc, address);
    inc(&value, &(cpu->registers[Register_F]));
    mc->write(mc, address, value);
    return 12;
}

int gb_inc_sp(uint16_t* sp) {
    (*sp)++;
    return 8;
}

int gb_dec_r(uint8_t* r, uint8_t* flags) {

    half_borrow_8bit(*r, 1) ? set_flag(flags, Flag_Half_Carry) : clear_flag(flags, Flag_Half_Carry);

    (*r)--;
    
    *r == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);
    set_flag(flags, Flag_Sub);

    return 4;
}

int gb_dec_rr(uint8_t* r1, uint8_t* r2) { 

    uint16_t value = combine_bytes(*r1, *r2);
    value--;

    *r1 =  (uint8_t) (value >> 8u);
    *r2 =  (uint8_t) (value & 0xFFu);

    return 8;
}

int gb_dec_sp(uint16_t* sp) {
    (*sp)--;
    return 8;
}

int gb_scf(uint8_t* flags) {

    clear_flag(flags, Flag_Sub | Flag_Half_Carry);
    set_flag(flags, Flag_Carry);

    return 4;
}

int gb_ccf(uint8_t* flags) {

    clear_flag(flags, Flag_Sub | Flag_Half_Carry);

    test_flag(*flags, Flag_Carry) ? clear_flag(flags, Flag_Carry) : set_flag(flags, Flag_Carry);
    
    return 4;
}

int gb_rra(Cpu* cpu) {
    
    uint8_t* flags = &(cpu->registers[Register_F]);
    
    uint8_t a = cpu->registers[Register_A];

    const bool new_carry_flag = test_bit_8bit(a, 0);
    a = (uint8_t) (a >> 1u);

    test_flag(*flags, Flag_Carry) ? set_bit(&a, 7) 
        : clear_bit(&a, 7);
    
    cpu->registers[Register_A] =  a;

    new_carry_flag ? set_flag(flags, Flag_Carry) 
        : clear_flag(flags, Flag_Carry);
    
    clear_flag(flags, Flag_Zero | Flag_Sub | Flag_Half_Carry);

    return 4;
}

int gb_rrca(Cpu* cpu) {

    uint8_t* flags = &(cpu->registers[Register_F]);

    test_bit_8bit(cpu->registers[Register_A], 0) ? set_flag(flags, Flag_Carry)
        : clear_flag(flags, Flag_Carry);
    
    cpu->registers[Register_A] = rotate_right(cpu->registers[Register_A], 1);

    clear_flag(flags, Flag_Zero | Flag_Sub | Flag_Half_Carry);

    return 4;
}

int gb_rla(Cpu* cpu) {
        
    uint8_t a = cpu->registers[Register_A];
    uint8_t* flags = &(cpu->registers[Register_F]);

    const bool new_carry_flag = test_bit_8bit(a, 7);
    a =  (uint8_t) (a << 1u);

    test_flag(*flags, Flag_Carry) ? set_bit(&a, 0) : clear_bit(&a, 0);
    
    cpu->registers[Register_A] =  a;

    new_carry_flag ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

    clear_flag(flags, Flag_Zero | Flag_Sub | Flag_Half_Carry);
    
    return 4;
}

int gb_rlca(Cpu* cpu) {

    uint8_t a = cpu->registers[Register_A];
    uint8_t* flags = &(cpu->registers[Register_F]);

    test_bit_8bit(a, 7) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

    cpu->registers[Register_A] = rotate_left(a, 1);

    clear_flag(flags, Flag_Zero | Flag_Sub | Flag_Half_Carry);

    return 4;
}

int gb_daa(Cpu* cpu) {

    uint8_t a = cpu->registers[Register_A];
    uint8_t* flags = &(cpu->registers[Register_F]);

    if(!test_flag(*flags, Flag_Sub)) {
        if(test_flag(*flags, Flag_Carry) || a > 0x99) {
            a += 0x60;
            set_flag(flags, Flag_Carry);
        }

        if(test_flag(*flags, Flag_Half_Carry) || (a & 0x0Fu) > 0x09) {
            a += 0x06;
        }
    } else {
        if(test_flag(*flags, Flag_Carry)) {
            a -= 0x60;
        }
        if(test_flag(*flags, Flag_Half_Carry)) {
            a -= 0x06;
        }
    }

    clear_flag(flags, Flag_Half_Carry);

    a == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    cpu->registers[Register_A] =  a;

    return 4;
}

int gb_add_sp_r8(uint8_t offset, Cpu* cpu) {

    uint8_t* flags = &(cpu->registers[Register_F]);

    half_carry_8bit( (uint8_t) (cpu->stack_ptr), offset)     ?
        set_flag(flags, Flag_Half_Carry)  :
        clear_flag(flags, Flag_Half_Carry);


    overflows_8bit( (uint8_t) (cpu->stack_ptr), offset)  ? 
        set_flag(flags, Flag_Carry)   :
        clear_flag(flags, Flag_Carry);


    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr + (int8_t) offset);

    clear_flag(flags, Flag_Zero | Flag_Sub);

    return 16;
}

int gb_and(uint8_t value, Cpu* cpu) {

    uint8_t a = cpu->registers[Register_A];
    uint8_t* flags = &(cpu->registers[Register_F]);

    a &= value;

    a == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub | Flag_Carry);
    set_flag(flags, Flag_Half_Carry);

    cpu->registers[Register_A] = a;
    return 4;
}

int gb_xor(uint8_t value, Cpu* cpu) {

    uint8_t* a = &(cpu->registers[Register_A]);
    uint8_t* flags = &(cpu->registers[Register_F]);

    *a ^= value;
    *a == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub | Flag_Half_Carry | Flag_Carry);

    return 4;
}

int gb_or(uint8_t value, Cpu* cpu) {

    uint8_t* a = &(cpu->registers[Register_A]);
    uint8_t* flags = &(cpu->registers[Register_F]);
    
    *a |= value;
    *a == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub | Flag_Half_Carry | Flag_Carry);

    return 4;
}

int gb_cp(uint8_t r1, uint8_t r2, uint8_t* flags) {

    underflows_8bit(r1, r2) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

    half_borrow_8bit(r1, r2) ? set_flag(flags, Flag_Half_Carry) : clear_flag(flags, Flag_Half_Carry);

    (r1 == r2) ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    set_flag(flags, Flag_Sub);
    
    return 4;
}

int gb_push_rr(uint8_t r1, uint8_t r2, Cpu* cpu, MemoryBankController* mc) {

    mc->write(mc, (uint16_t) (cpu->stack_ptr-1), r1);
    mc->write(mc, (uint16_t) (cpu->stack_ptr-2), r2);
    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr - 2);
    return 16;
}

int gb_pop_rr(uint8_t* r1, uint8_t* r2, Cpu* cpu, MemoryBankController* mc) {

    *r2 = mc->read(mc, cpu->stack_ptr);
    *r1 = mc->read(mc, (uint16_t) (cpu->stack_ptr + 1));
    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr + 2);
    return 12;
}

uint8_t ADC(uint8_t first, uint8_t second, uint8_t* flags) {
    
    const bool carry_value = test_flag(*flags, Flag_Carry) ? 1 : 0;

    half_carry_8bit(first, second) ? set_flag(flags, Flag_Half_Carry) : clear_flag(flags, Flag_Half_Carry);

    overflows_8bit(first, second) ? set_flag(flags,Flag_Carry) : clear_flag(flags, Flag_Carry);

    first = (uint8_t)(first + second);

    if(!test_flag(*flags, Flag_Half_Carry)) {
        half_carry_8bit(first, (uint8_t) (carry_value)) ? set_flag(flags, Flag_Half_Carry) 
            : clear_flag(flags, Flag_Half_Carry);
    }
    
    if(!test_flag(*flags, Flag_Carry)) {
        overflows_8bit(first, (uint8_t) (carry_value)) ? set_flag(flags, Flag_Carry) 
            : clear_flag(flags, Flag_Carry);
    }

    first = (uint8_t)(first + carry_value);

    first == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    clear_flag(flags, Flag_Sub);
    
    return first;
}

int gb_adc(uint8_t r, Cpu* cpu) {
    const uint8_t a = cpu->registers[Register_A];
    cpu->registers[Register_A] = ADC(a, r, &(cpu->registers[Register_F]));
    return 4;
}

int gb_ldh_addr_a8_a(uint8_t r, Cpu* cpu, MemoryBankController* mc) {
    const uint16_t address = (uint16_t) (0xFF00 + r);
    mc->write(mc, address, cpu->registers[Register_A]);    
    return 12;
}

int gb_ldh_a_addr_a8(uint8_t r, Cpu* cpu, MemoryBankController* mc) {
    const uint16_t address = (uint16_t) (0xFF00 + r);
    cpu->registers[Register_A] =  mc->read(mc, address);             
    return 12;
}

int gb_ld_addr_c_a(Cpu* cpu, MemoryBankController* mc) {
    const uint16_t address = (uint16_t) (0xFF00 + cpu->registers[Register_C]);
    mc->write(mc, address, cpu->registers[Register_A]);
    return 8;
}

uint8_t SBC(uint8_t first, uint8_t second, uint8_t* flags) {
    
    const bool carry_value = test_flag(*flags, Flag_Carry) ? 1 : 0;

    half_borrow_8bit(first, second)            ?
        set_flag(flags, Flag_Half_Carry)  :
        clear_flag(flags, Flag_Half_Carry);

    underflows_8bit(first, second)         ?
        set_flag(flags, Flag_Carry)   :
        clear_flag(flags, Flag_Carry);
    
    first = (uint8_t) (first - second);

    if(!test_flag(*flags, Flag_Half_Carry)) {
        half_borrow_8bit(first, (uint8_t) (carry_value))       ?
            set_flag(flags, Flag_Half_Carry)  :
            clear_flag(flags, Flag_Half_Carry);
    }

    if(!test_flag(*flags, Flag_Carry)) {
        underflows_8bit(first, (uint8_t) (carry_value))         ?
            set_flag(flags, Flag_Carry)   :
            clear_flag(flags, Flag_Carry);
    }

    first = (uint8_t) (first - carry_value);

    first == 0 ? set_flag(flags, Flag_Zero) : clear_flag(flags, Flag_Zero);

    set_flag(flags, Flag_Sub);

    return first;
}

int gb_sbc(uint8_t r, Cpu* cpu) {
    const uint8_t a = cpu->registers[Register_A];
    cpu->registers[Register_A] = SBC(a, r, &(cpu->registers[Register_F]));
    return 4;
}

int gb_prefix_cb(Cpu* cpu, MemoryBankController* mc) {
    CB_Code cb_opcode = (CB_Code) mc->read(mc, cpu->program_counter);
    return gb_execute_cb(cb_opcode, cpu, mc);
}

int gb_ld_addr_hld_a(Cpu* cpu, MemoryBankController* mc) {
        
    uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    mc->write(mc, address, cpu->registers[Register_A]);

    address--;

    cpu->registers[Register_H] =  (uint8_t) (address >> 8u);
    cpu->registers[Register_L] =  (uint8_t) (address & 0xFFu);
    
    return 8;
}

int gb_ld_a_addr_hld(Cpu* cpu, MemoryBankController* mc) {

    uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    cpu->registers[Register_A] =  mc->read(mc, address);

    address--;
    cpu->registers[Register_H] = (uint8_t) (address >> 8u);
    cpu->registers[Register_L] = (uint8_t) (address & 0xFFu);

    return 8;
}

int gb_cpl(uint8_t* a, uint8_t* flags) {

    *a ^= 0xFF;

    set_flag(flags, Flag_Sub | Flag_Half_Carry);
    
    return 4;
}