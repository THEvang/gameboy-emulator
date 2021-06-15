#include "Cpu/Operations.h"

#include <stdio.h>
#include <stdlib.h>

#include "Utilities/BitOperations.h"
#include "Cpu/CBOpcodes.h"
#include "Memory/Memory_Controller.h"
#include "Adressing_Modes.h"
#include "Interpreter.h"

int gb_nop() {
    return 4;
}

int gb_stop() {
    return 4;
}

int gb_halt(Cpu* cpu) {

    if(cpu->interrupts_enabled) {
        cpu->is_halted = true;
    } else {

        const uint16_t interrupt_request_addr = 0xFF0F;
        const uint16_t interrupt_enable_addr = 0xFFFF;

        const uint8_t interrupt_request = gb_read(cpu->memory_controller, interrupt_request_addr);
        const uint8_t interrupt_enable = gb_read(cpu->memory_controller, interrupt_enable_addr);

        if((interrupt_request & interrupt_enable & 0x1Fu) == 0) {
            cpu->is_halted = true;
        } else {
            printf("HALT BUG");
            exit(1);
        }
    }
    return 4;
}

int gb_rst(uint8_t address, Cpu* cpu) {
            
    const uint8_t pc_high = (uint8_t) (cpu->program_counter >> 8u);
    const uint8_t pc_low =  (uint8_t) (cpu->program_counter & 0xFFu);

    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr - 1), pc_high);
    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr - 2), pc_low);

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
    cpu->program_counter += (int8_t) offset;
    return 12;
}

int gb_jr(uint8_t offset, bool predicate, Cpu* cpu) {
    return predicate ? jump_relative(offset, cpu) : 8;
}

int ret(Cpu* cpu) {            
    const uint8_t pc_low = gb_read(cpu->memory_controller, cpu->stack_ptr);
    const uint8_t pc_high = gb_read(cpu->memory_controller, (uint16_t) (cpu->stack_ptr + 1));
    
    cpu->program_counter = combine_bytes(pc_high, pc_low);
    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr + 2);
    return 16;
}

int gb_ret(bool predicate, Cpu* cpu) {
    return predicate ? ret(cpu) : 8;
}

int gb_reti(Cpu* cpu) {
    cpu->interrupts_enabled = true;
    return ret(cpu);
}

int jump(Cpu* cpu, uint16_t address) {
    cpu->program_counter = address; 
    return 16;
}

int gb_jump(uint16_t address, bool predicate, Cpu* cpu) {
    return predicate ? jump(cpu, address) : 12;
}

int call(Cpu* cpu, uint16_t address) {

    const uint8_t pc_high = (uint8_t) (cpu->program_counter >> 8u);
    const uint8_t pc_low = (uint8_t) (cpu->program_counter & 0xFFu);
    
    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr - 1), pc_high);
    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr - 2), pc_low);
    cpu->stack_ptr = (uint16_t)(cpu->stack_ptr -2);
    
    cpu->program_counter = address;

    return 24;
}

int gb_call(uint16_t address, bool predicate, Cpu* cpu) {
    return predicate ? call(cpu, address) : 12;
}

int gb_ld_r_r(uint8_t* dst, uint8_t src) {
    *dst = src;
    return 4;
}

int gb_ld_a_addr_rr(uint8_t r1, uint8_t r2, Cpu* cpu) {
    const uint16_t address = combine_bytes(r1, r2);
    cpu->registers[Register_A] = gb_read(cpu->memory_controller,address);
    return 8;
}

int LD_A_ADDR_A16(uint16_t address, Cpu* cpu) {
    cpu->registers[Register_A] = gb_read(cpu->memory_controller, address);
    return 16;
}

int gb_ld_a_addr_c(Cpu* cpu) {

    const uint16_t address = (uint16_t) (0xFF00 + cpu->registers[Register_C]);
    cpu->registers[Register_A] =  gb_read(cpu->memory_controller,address);

    return 8;
}

int gb_ld_addr_a16_sp(uint16_t address, Cpu* cpu) {

    gb_write(cpu->memory_controller, address, (uint8_t) (cpu->stack_ptr & 0xFFu));
    gb_write(cpu->memory_controller, (uint16_t) (address + 1), (uint8_t) (cpu->stack_ptr >> 8u));
    return 20;
}

int gb_ldi_addr_hl_a(Cpu* cpu) {

    uint16_t address = read_register_pair(*cpu, Register_H, Register_L);
    
    gb_write(cpu->memory_controller, address, cpu->registers[Register_A]);

    address++;
    cpu->registers[Register_H] =  (uint8_t) (address >> 8u);
    cpu->registers[Register_L] =  (uint8_t) (address & 0xFFu);

    return 8;
}

int gb_ldi_a_addr_hl(Cpu* cpu) {
    
    uint16_t address = read_register_pair(*cpu, Register_H, Register_L);
    cpu->registers[Register_A] = gb_read(cpu->memory_controller,address);
    
    address++;
    cpu->registers[Register_H] = (uint8_t) (address >> 8u);
    cpu->registers[Register_L] = (uint8_t) (address & 0xFFu);

    return 8;
}

int gb_ld_addr_rr_a(uint8_t r1, uint8_t r2, Cpu* cpu) {
    const uint16_t address = combine_bytes(r1, r2);
    gb_write(cpu->memory_controller, address, cpu->registers[Register_A]);   
    return 8;
}

int gb_ld_addr_hl(uint8_t value, Cpu* cpu) {
    const uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    gb_write(cpu->memory_controller, address, value);
    return 8;
}

int gb_ld_addr_hl_addr_hl() {    
    printf("Unimplemented operation: LD ADDR HL ADDR HL\n");
    exit(1);
}

int gb_ld_addr_a16_a(uint16_t address, Cpu* cpu) {
    gb_write(cpu->memory_controller, address, cpu->registers[Register_A]);
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

int gb_ld_sp_d16(uint16_t rr, Cpu* cpu) {
    cpu->stack_ptr = rr;
    return 12;
}

int gb_ld_sp_hl(Cpu* cpu) {
    cpu->stack_ptr =  combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    return 8;
}

uint8_t ADD_8bit(uint8_t first, uint8_t second, uint8_t* flags) {
    
    half_carry_8bit(first, second)             ? 
        set_bit(flags, Flag_Half_Carry)  :
        clear_bit(flags, Flag_Half_Carry);

    overflows_8bit(first, second)          ?
        set_bit(flags, Flag_Carry)   :
        clear_bit(flags, Flag_Carry);

    first = (uint8_t) (first + second);

    first == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);

    return first;
}

int gb_add(uint8_t r, Cpu* cpu) {
    cpu->registers[Register_A] = ADD_8bit(cpu->registers[Register_A], r, &(cpu->registers[Register_F]));
    return 8;
}

uint16_t ADD_16bit(uint16_t first, uint16_t second, uint8_t* flags) {
    
    overflows_16bit(first, second) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);

    half_carry_16bit(first, second) ? set_bit(flags, Flag_Half_Carry) : clear_bit(flags, Flag_Half_Carry);

    first = (uint16_t) (first + second);

    clear_bit(flags, Flag_Sub);

    return first;
}

int gb_add_hl_rr(uint8_t r1, uint8_t r2, Cpu* cpu) {
    
    const uint16_t hl = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    const uint16_t value = combine_bytes(r1, r2);

    const uint16_t result = ADD_16bit(hl, value, &(cpu->registers[Register_F]));

    cpu->registers[Register_H] =  (uint8_t)(result >> 8u);
    cpu->registers[Register_L] =  (uint8_t)(result & 0xFFu);

    return 8;
}

int gb_add_hl_sp(Cpu* cpu) {
        
    const uint16_t hl = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    const uint16_t result = ADD_16bit(hl, cpu->stack_ptr, &(cpu->registers[Register_F]));

    cpu->registers[Register_H] =  (uint8_t) (result >> 8u);
    cpu->registers[Register_L] =  (uint8_t) (result & 0xFFu);

    return 8;
}

uint8_t SUB(uint8_t first, uint8_t second, uint8_t* flags) {
    
    half_borrow_8bit(first, second) ? set_bit(flags,   Flag_Half_Carry) :
        clear_bit(flags, Flag_Half_Carry);

    underflows_8bit(first, second) ? set_bit(flags,   Flag_Carry) :
        clear_bit(flags, Flag_Carry);

    first = (uint8_t) (first - second);

    first == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    set_bit(flags, Flag_Sub);

    return first;
}

int gb_sub(uint8_t r, Cpu* cpu) {
    cpu->registers[Register_A] = SUB(cpu->registers[Register_A], r, &(cpu->registers[Register_F]));
    return 4;
}

void inc(uint8_t* value, uint8_t* flags) {
    
    half_carry_8bit(*value, 1) ? set_bit(flags, Flag_Half_Carry) : clear_bit(flags, Flag_Half_Carry);

    (*value)++;

    *value == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
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

int gb_inc_addr_hl(Cpu* cpu) {

    const uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    uint8_t value = gb_read(cpu->memory_controller,address);
    inc(&value, &(cpu->registers[Register_F]));
    gb_write(cpu->memory_controller, address, value);
    return 12;
}

int gb_inc_sp(uint16_t* sp) {
    (*sp)++;
    return 8;
}

uint8_t DEC(uint8_t value, uint8_t* flags) {
    
    half_borrow_8bit(value, 1) ? set_bit(flags, Flag_Half_Carry) : clear_bit(flags, Flag_Half_Carry);

    value--;
    
    value == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);
    set_bit(flags, Flag_Sub);

    return value;
}

int gb_dec_r(uint8_t* r, uint8_t* flags) {
    *r = DEC(*r, flags);
    return 4;
}

int gb_dec_addr_hl(Cpu* cpu) {

    const uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    uint8_t value = gb_read(cpu->memory_controller,address);
    value = DEC(value, &(cpu->registers[Register_F]));
    gb_write(cpu->memory_controller, address, value);
    return 12;
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

    clear_flag(flags, Flag_Sub);
    clear_flag(flags, Flag_Half_Carry);
    set_flag(flags, Flag_Carry);

    return 4;
}

int gb_ccf(uint8_t* flags) {

    clear_flag(flags, Flag_Sub);
    clear_flag(flags, Flag_Half_Carry);

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
    
    clear_flag(flags, Flag_Zero);
    clear_flag(flags, Flag_Sub);
    clear_flag(flags, Flag_Half_Carry);

    return 4;
}

int gb_rrca(Cpu* cpu) {

    uint8_t* flags = &(cpu->registers[Register_F]);

    test_bit_8bit(cpu->registers[Register_A], 0) ? set_flag(flags, Flag_Carry)
        : clear_flag(flags, Flag_Carry);
    
    cpu->registers[Register_A] = rotate_right(cpu->registers[Register_A], 1);

    clear_flag(flags, Flag_Zero);
    clear_flag(flags, Flag_Sub);
    clear_flag(flags, Flag_Half_Carry);

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

    clear_flag(flags, Flag_Zero);
    clear_flag(flags, Flag_Sub);
    clear_flag(flags, Flag_Half_Carry);
    
    return 4;
}

int gb_rlca(Cpu* cpu) {

    uint8_t a = cpu->registers[Register_A];
    uint8_t* flags = &(cpu->registers[Register_F]);

    test_bit_8bit(a, 7) ? set_flag(flags, Flag_Carry) : clear_flag(flags, Flag_Carry);

    cpu->registers[Register_A] = rotate_left(a, 1);

    clear_flag(flags, Flag_Zero);
    clear_flag(flags, Flag_Sub);
    clear_flag(flags, Flag_Half_Carry);

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


    cpu->stack_ptr += (int8_t) offset;

    clear_flag(flags, Flag_Zero);
    clear_flag(flags, Flag_Sub);

    return 16;
}

int gb_and(uint8_t value, Cpu* cpu) {

    uint8_t a = cpu->registers[Register_A];
    uint8_t* flags = &(cpu->registers[Register_F]);

    a &= value;

    a == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    set_bit(flags, Flag_Half_Carry);
    clear_bit(flags, Flag_Carry);

    cpu->registers[Register_A] = a;
    return 4;
}

uint8_t XOR(uint8_t first, uint8_t second, uint8_t* flags) {
    
    first ^= second;
    first == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);
    clear_bit(flags, Flag_Carry);

    return first;
}

int gb_xor(uint8_t value, Cpu* cpu) {
    cpu->registers[Register_A] = XOR(cpu->registers[Register_A], value, &(cpu->registers[Register_F]));
    return 4;
}

uint8_t OR(uint8_t first, uint8_t second, uint8_t* flags) {
    
    first |= second;
    first == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    clear_bit(flags, Flag_Half_Carry);
    clear_bit(flags, Flag_Carry);

    return first;
}

int gb_or(uint8_t value, Cpu* cpu) {
    cpu->registers[Register_A] = OR(cpu->registers[Register_A], value, &(cpu->registers[Register_F]));
    return 4;
}

int gb_cp(uint8_t r1, uint8_t r2, uint8_t* flags) {

    underflows_8bit(r1, r2) ? set_bit(flags, Flag_Carry) : clear_bit(flags, Flag_Carry);

    half_borrow_8bit(r1, r2) ? set_bit(flags, Flag_Half_Carry) : clear_bit(flags, Flag_Half_Carry);

    (r1 == r2) ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    set_bit(flags, Flag_Sub);
    
    return 4;
}

int gb_push_rr(uint8_t r1, uint8_t r2, Cpu* cpu) {

    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr-1), r1);
    gb_write(cpu->memory_controller, (uint16_t) (cpu->stack_ptr-2), r2);
    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr - 2);
    return 16;
}

int gb_pop_af(Cpu* cpu) {

    cpu->registers[Register_F] =  gb_read(cpu->memory_controller, cpu->stack_ptr) & 0xF0u;
    cpu->registers[Register_A] =  gb_read(cpu->memory_controller, (uint16_t) (cpu->stack_ptr + 1));
    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr + 2);
    return 12;
}

int gb_pop_rr(uint8_t* r1, uint8_t* r2, Cpu* cpu) {

    *r2 = gb_read(cpu->memory_controller, cpu->stack_ptr);
    *r1 = gb_read(cpu->memory_controller, (uint16_t) (cpu->stack_ptr + 1));
    cpu->stack_ptr = (uint16_t) (cpu->stack_ptr + 2);
    return 12;
}

uint8_t ADC(uint8_t first, uint8_t second, uint8_t* flags) {
    
    const bool carry_value = test_bit_8bit(*flags, Flag_Carry) ? 1 : 0;

    half_carry_8bit(first, second) ? set_bit(flags, Flag_Half_Carry) : clear_bit(flags, Flag_Half_Carry);

    overflows_8bit(first, second) ? set_bit(flags,Flag_Carry) : clear_bit(flags,    Flag_Carry);

    first = (uint8_t)(first + second);

    if(!test_bit_8bit(*flags, Flag_Half_Carry)) {
        half_carry_8bit(first, (uint8_t) (carry_value)) ? set_bit(flags, Flag_Half_Carry) 
            : clear_bit(flags,    Flag_Half_Carry);
    }
    
    if(!test_bit_8bit(*flags, Flag_Carry)) {
        overflows_8bit(first, (uint8_t) (carry_value)) ? set_bit(flags, Flag_Carry) 
            : clear_bit(flags, Flag_Carry);
    }

    first = (uint8_t)(first + carry_value);

    first == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    clear_bit(flags, Flag_Sub);
    
    return first;
}

int gb_adc(uint8_t r, Cpu* cpu) {
    const uint8_t a = cpu->registers[Register_A];
    cpu->registers[Register_A] = ADC(a, r, &(cpu->registers[Register_F]));
    return 4;
}

int gb_ldh_addr_a8_a(uint8_t r, Cpu* cpu) {
    const uint16_t address = (uint16_t) (0xFF00 + r);
    gb_write(cpu->memory_controller, address, cpu->registers[Register_A]);    
    return 12;
}

int gb_ldh_a_addr_a8(uint8_t r, Cpu* cpu) {
    const uint16_t address = (uint16_t) (0xFF00 + r);
    cpu->registers[Register_A] =  gb_read(cpu->memory_controller, address);             
    return 12;
}

int gb_ld_addr_c_a(Cpu* cpu) {
    const uint16_t address = (uint16_t) (0xFF00 + cpu->registers[Register_C]);
    gb_write(cpu->memory_controller, address, cpu->registers[Register_A]);
    return 8;
}

uint8_t SBC(uint8_t first, uint8_t second, uint8_t* flags) {
    
    const bool carry_value = test_bit_8bit(*flags, Flag_Carry) ? 1 : 0;

    half_borrow_8bit(first, second)            ?
        set_bit(flags, Flag_Half_Carry)  :
        clear_bit(flags, Flag_Half_Carry);

    underflows_8bit(first, second)         ?
        set_bit(flags, Flag_Carry)   :
        clear_bit(flags, Flag_Carry);
    
    first = (uint8_t) (first - second);

    if(!test_bit_8bit(*flags, Flag_Half_Carry)) {
        half_borrow_8bit(first, (uint8_t) (carry_value))       ?
            set_bit(flags, Flag_Half_Carry)  :
            clear_bit(flags, Flag_Half_Carry);
    }

    if(!test_bit_8bit(*flags, Flag_Carry)) {
        underflows_8bit(first, (uint8_t) (carry_value))         ?
            set_bit(flags, Flag_Carry)   :
            clear_bit(flags, Flag_Carry);
    }

    first = (uint8_t) (first - carry_value);

    first == 0 ? set_bit(flags, Flag_Zero) : clear_bit(flags, Flag_Zero);

    set_bit(flags, Flag_Sub);

    return first;
}

int gb_sbc(uint8_t r, Cpu* cpu) {
    const uint8_t a = cpu->registers[Register_A];
    cpu->registers[Register_A] = SBC(a, r, &(cpu->registers[Register_F]));
    return 4;
}

int gb_prefix_cb(Cpu* cpu) {
    CB_Code cb_opcode = (CB_Code) gb_read(cpu->memory_controller, cpu->program_counter);
    return execute_cb(cb_opcode, cpu);
}

int gb_ld_addr_hld_a(Cpu* cpu) {
        
    uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    gb_write(cpu->memory_controller, address, cpu->registers[Register_A]);

    address--;

    cpu->registers[Register_H] =  (uint8_t) (address >> 8u);
    cpu->registers[Register_L] =  (uint8_t) (address & 0xFFu);
    
    return 8;
}

int gb_ld_a_addr_hld(Cpu* cpu) {

    uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    cpu->registers[Register_A] =  gb_read(cpu->memory_controller, address);

    address--;
    cpu->registers[Register_H] = (uint8_t) (address >> 8u);
    cpu->registers[Register_L] = (uint8_t) (address & 0xFFu);

    return 8;
}

int gb_cpl(Cpu* cpu) {

    uint8_t a = cpu->registers[Register_A];
    a ^= 0xFF;
    cpu->registers[Register_A] =  a;

    uint8_t* flags = &(cpu->registers[Register_F]);

    set_flag(flags, Flag_Sub);
    set_flag(flags, Flag_Half_Carry);
    
    return 4;
}