#include <cpu/Operations.h>
#include <BitOperations.h>
#include <string>
#include <iostream>

UnimplementedOperation::UnimplementedOperation(const std::string& msg)
    : runtime_error(msg) {

}

void NOP(Cpu& cpu) {
    cpu.m_cycles = 4;
    cpu.m_program_counter++;
}

void STOP(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: STOP");
}

void HALT(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: HALT");
}

void RST(Cpu& cpu, uint8_t address) {

    const auto pc_high = ( (cpu.m_program_counter + 1) >> 8);
    const auto pc_low = ( (cpu.m_program_counter + 1) & 0xF);

    cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
    cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);

    cpu.m_program_counter = 0x0000 + address;
    cpu.m_stack_ptr -= 2;
    cpu.m_cycles += 16;
    //throw UnimplementedOperation("RST\n");
}

void DI(Cpu& cpu) {
    
    cpu.m_cycles += 4;
    cpu.m_enabled_interrupts = false;
    cpu.m_program_counter++;
}

void EI(Cpu& cpu) {
    cpu.m_cycles += 4;
    cpu.m_enabled_interrupts = true;
    cpu.m_program_counter++;
}

void JR(Cpu& cpu) {

    cpu.m_program_counter += 2;
    const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
    cpu.m_program_counter += distance;
    cpu.m_cycles += 12;
}

void JR_NZ(Cpu& cpu) {
    
    if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter+1));
        cpu.m_program_counter += (distance + 2);
        cpu.m_cycles += 12;
    } else {
        cpu.m_program_counter += 2;
        cpu.m_cycles += 8;
    }
}

void JR_Z(Cpu& cpu) {

    if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter+1));
        cpu.m_program_counter += (distance + 2);
        cpu.m_cycles += 12;
    } else {
        cpu.m_program_counter += 2;
        cpu.m_cycles += 8;
    }
}

void JR_NC(Cpu& cpu) {

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter+1));
        cpu.m_program_counter += (distance + 2);
        cpu.m_cycles += 12;
    } else {
        cpu.m_program_counter += 2;
        cpu.m_cycles += 8;
    }
}

void JR_C(Cpu& cpu) {

    if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter+1));
        cpu.m_program_counter += (distance + 2);
        cpu.m_cycles += 12;
    } else {
        cpu.m_program_counter += 2;
        cpu.m_cycles += 8;
    }
}

void RET(Cpu& cpu) {

    const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
    const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
    
    cpu.m_program_counter = combine_bytes(pc_high, pc_low);
    
    cpu.m_stack_ptr += 2;
    cpu.m_cycles += 16;
}

void RET_NZ(Cpu& cpu) {

    throw UnimplementedOperation("Unimplemented operation: RET NZ");
}

void RET_Z(Cpu& cpu) {

    if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
        const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
        const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
        cpu.m_program_counter = combine_bytes(pc_high, pc_low);
        
        cpu.m_stack_ptr += 2;
        cpu.m_cycles += 20;
    } else {
        cpu.m_program_counter++;
        cpu.m_cycles += 8;
    }
}

void RET_NC(Cpu& cpu) {

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
        const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
        cpu.m_program_counter = combine_bytes(pc_high, pc_low);
        
        cpu.m_stack_ptr += 2;
        cpu.m_cycles += 20;
    } else {
        cpu.m_program_counter++;
        cpu.m_cycles += 8;
    }
}

void RET_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RET C");
}

void RETI(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: RETI");
}

void JUMP(Cpu& cpu) {

    const auto low = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    const auto high = cpu.m_memory_controller->read(cpu.m_program_counter + 2);
    const auto address = combine_bytes(high, low);

    cpu.m_program_counter = address;
    cpu.m_cycles += 16;
}

void JUMP_NZ(Cpu& cpu) {

    if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
        const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
        const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter + 2);
        const auto address = combine_bytes(upper, lower);

        cpu.m_program_counter = address;
        cpu.m_cycles += 16;
    } else {
        cpu.m_program_counter += 3;
        cpu.m_cycles += 12;
    }
}

void JUMP_Z(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: JUMP Z");
}

void JUMP_NC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: JUMP NC");
}

void JUMP_C(Cpu& cpu) {

    if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
        const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter + 2);
        const auto address = combine_bytes(upper, lower);

        cpu.m_program_counter = address;
        cpu.m_cycles += 16;
    } else {
        cpu.m_program_counter += 3;
        cpu.m_cycles += 12;
    }
}

void JUMP_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_program_counter = address;
    cpu.m_cycles += 4;
}

void CALL(Cpu& cpu) {

    const auto pc_high = ( (cpu.m_program_counter+3) >> 8);
    const auto pc_low = ( (cpu.m_program_counter+3) & 0xF);

    cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
    cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);

    const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter + 2);
    const auto address = combine_bytes(upper, lower);
    
    cpu.m_program_counter = address;
    cpu.m_stack_ptr -= 2;
    cpu.m_cycles += 24;
}

void CALL_NZ(Cpu& cpu) {

    if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
        const auto pc_high = ( (cpu.m_program_counter+3) >> 8);
        const auto pc_low = ( (cpu.m_program_counter+3) & 0xF);

        cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);

        
        const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
        const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter + 2);
        const auto address = combine_bytes(upper, lower);
        
        cpu.m_program_counter = address;
        cpu.m_stack_ptr -= 2;
        cpu.m_cycles += 24;
    } else {
        cpu.m_cycles += 12;
        cpu.m_program_counter += 3;
    }
}

void CALL_Z(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: CALL Z");
}

void CALL_NC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: CALL NC");
}

void CALL_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: CALL C");
}

void LD_A_D8(Cpu& cpu) {

    cpu.m_reg_a = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LD_A_A(Cpu& cpu) {
    cpu.m_reg_a = cpu.m_reg_a;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_A_B(Cpu& cpu) {

    cpu.m_reg_a = cpu.m_reg_b;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_A_C(Cpu& cpu) {
    cpu.m_reg_a = cpu.m_reg_c;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_A_D(Cpu& cpu) {
    
    cpu.m_reg_a = cpu.m_reg_d;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_A_E(Cpu& cpu) {
    cpu.m_reg_a = cpu.m_reg_e;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_A_H(Cpu& cpu) {

    cpu.m_reg_a = cpu.m_reg_h;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_A_L(Cpu& cpu) {
    
    cpu.m_reg_a = cpu.m_reg_l;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_A_ADDR_BC(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);

    cpu.m_reg_a = cpu.m_memory_controller->read(address);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_A_ADDR_DE(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);

    cpu.m_reg_a = cpu.m_memory_controller->read(address);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_A_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LD A ADDR HL");
}

void LD_A_ADDR_A16(Cpu& cpu) {

    const auto low = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    const auto high = cpu.m_memory_controller->read(cpu.m_program_counter + 2);
    const auto address = combine_bytes(high, low);

    cpu.m_reg_a = cpu.m_memory_controller->read(address);

    cpu.m_program_counter += 3;
    cpu.m_cycles += 16;
}

void LD_A_ADDR_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A ADDR C");
}

void LD_ADDR_SP(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation LD ADDR SP");
}

void LDI_ADDR_HL_A(Cpu& cpu) {

    auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_a);

    address++;
    cpu.m_reg_h = (address >> 8);
    cpu.m_reg_l = (address & 0xF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;

}

void LDI_A_ADDR_HL(Cpu& cpu) {

    auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_a = cpu.m_memory_controller->read(address);
    
    address++;
    cpu.m_reg_h = (address >> 8);
    cpu.m_reg_l = (address & 0xF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void LD_ADDR_BC_A(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
    cpu.m_memory_controller->write(address, cpu.m_reg_a);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_ADDR_DE_A(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
    cpu.m_memory_controller->write(address, cpu.m_reg_a);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_B_D8(Cpu& cpu) {

    cpu.m_reg_b = cpu.m_memory_controller->read(cpu.m_program_counter + 1);

    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LD_B_A(Cpu& cpu) {
    cpu.m_reg_b = cpu.m_reg_a;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_B_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B B");
}

void LD_B_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B C");
}

void LD_B_D(Cpu& cpu) {

    cpu.m_reg_b = cpu.m_reg_d;

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_B_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B E");
}

void LD_B_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B H");
}

void LD_B_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B L");
}

void LD_B_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_b = cpu.m_memory_controller->read(address);

    cpu.m_cycles += 2;
    cpu.m_program_counter++;
}

void LD_C_D8(Cpu& cpu) {

    cpu.m_reg_c = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LD_C_A(Cpu& cpu) {
    cpu.m_reg_c = cpu.m_reg_a;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_C_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C B");
}

void LD_C_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C C");
}

void LD_C_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C D");
}

void LD_C_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C E");
}

void LD_C_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C H");
}

void LD_C_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C L");
}

void LD_C_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_c = cpu.m_memory_controller->read(address);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_D_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D D8");
}

void LD_D_A(Cpu& cpu) {

    cpu.m_reg_d = cpu.m_reg_a;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_D_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D B");
}

void LD_D_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D C");
}

void LD_D_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D D");
}

void LD_D_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D E");
}

void LD_D_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D H");
}

void LD_D_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D L");
}

void LD_D_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_d = cpu.m_memory_controller->read(address);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_E_D8(Cpu& cpu) {
    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_reg_e = value;
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LD_E_A(Cpu& cpu) {
    cpu.m_reg_e = cpu.m_reg_a;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_E_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E B");
}

void LD_E_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E C");
}

void LD_E_D(Cpu& cpu) {
    cpu.m_reg_e = cpu.m_reg_d;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_E_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E E");
}

void LD_E_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E H");
}

void LD_E_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E L");
}

void LD_E_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E ADDR HL");
}

void LD_H_D8(Cpu& cpu) {

    cpu.m_reg_h = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void LD_H_A(Cpu& cpu) {

    cpu.m_reg_h = cpu.m_reg_a;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_H_B(Cpu& cpu) {
    cpu.m_reg_h = cpu.m_reg_b;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_H_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H C");
}

void LD_H_D(Cpu& cpu) {
    cpu.m_reg_h = cpu.m_reg_d;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_H_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H E");
}

void LD_H_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H H");
}

void LD_H_L(Cpu& cpu) {
    cpu.m_reg_h = cpu.m_reg_l;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_H_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_h = cpu.m_memory_controller->read(address);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void LD_L_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L D8");
}

void LD_L_A(Cpu& cpu) {

    cpu.m_reg_l = cpu.m_reg_a;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_L_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L B");
}

void LD_L_C(Cpu& cpu) {
    cpu.m_reg_l = cpu.m_reg_c;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_L_D(Cpu& cpu) {
    cpu.m_reg_l = cpu.m_reg_d;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_L_E(Cpu& cpu) {
    cpu.m_reg_l = cpu.m_reg_e;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_L_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L H");
}

void LD_L_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L L");
}

void LD_L_ADDR_HL(Cpu& cpu) {
    
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_l = cpu.m_memory_controller->read(address);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_ADDR_HL_A(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_a);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;    
}

void LD_ADDR_HL_B(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_b);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_ADDR_HL_C(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_c);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_ADDR_HL_D(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_d);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_ADDR_HL_E(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_e);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_ADDR_HL_H(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_h);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_ADDR_HL_L(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_l);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_ADDR_HL_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL ADDR HL");
}

void LD_ADDR_A16_A(Cpu& cpu) {
    const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter+2);
    const auto address = combine_bytes(upper, lower);

    cpu.m_memory_controller->write(address, cpu.m_reg_a);
    cpu.m_cycles += 16;
    cpu.m_program_counter += 3;
}

void LD_BC_D16(Cpu& cpu) {

    cpu.m_reg_c = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_reg_b = cpu.m_memory_controller->read(cpu.m_program_counter + 2);

    cpu.m_cycles += 12;
    cpu.m_program_counter += 3;
}

void LD_DE_D16(Cpu& cpu) {

    cpu.m_reg_e = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_reg_d = cpu.m_memory_controller->read(cpu.m_program_counter + 2);

    cpu.m_cycles += 12;
    cpu.m_program_counter += 3;
}

void LD_HL_D16(Cpu& cpu) {

    cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_reg_h = cpu.m_memory_controller->read(cpu.m_program_counter+2);

    cpu.m_cycles += 12;
    cpu.m_program_counter += 3;
}

void LD_HL_SPR8(Cpu& cpu) {

    const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter + 1));

    clear_bit(cpu.m_reg_f, Cpu::zero_flag);
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    if(half_carry_16bit(cpu.m_stack_ptr, distance)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(overflows_16bit(cpu.m_stack_ptr, distance)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    const auto result = cpu.m_stack_ptr + distance;
    cpu.m_reg_h = (result >> 8);
    cpu.m_reg_l = (result & 0xF);

    cpu.m_cycles += 12;
    cpu.m_program_counter += 2;
    throw UnimplementedOperation("LD HL SPR8");
}

void LD_SP_D16(Cpu& cpu) {

    const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter+2);
    const auto address = combine_bytes(upper, lower);

    cpu.m_stack_ptr = address;
    cpu.m_cycles += 12;
    cpu.m_program_counter += 3;
}

void LD_SP_HL(Cpu& cpu) {

    const auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_stack_ptr = value;
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void ADD_A_D8(Cpu& cpu) {


    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    if(half_carry_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(overflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void ADD_A_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A A");
}

void ADD_A_B(Cpu& cpu) {

    const auto value = cpu.m_reg_b;
    if(half_carry_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(overflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADD_A_C(Cpu& cpu) {

    const auto value = cpu.m_reg_c;
    if(half_carry_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(overflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADD_A_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A D");
}

void ADD_A_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A E");
}

void ADD_A_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A H");
}

void ADD_A_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A L");
}

void ADD_A_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A ADDR HL");
}

void ADD_HL_BC(Cpu& cpu) {
    
    auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);

    if(overflows_16bit(hl, bc)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_carry_16bit(hl, bc)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    hl += bc;

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_reg_h = (hl >> 8);
    cpu.m_reg_l = (hl & 0xF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;

}

void ADD_HL_DE(Cpu& cpu) {

    auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto de = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);

    if(overflows_16bit(hl, de)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_carry_16bit(hl, de)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    hl += de;

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_reg_h = (hl >> 8);
    cpu.m_reg_l = (hl & 0xF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void ADD_HL_HL(Cpu& cpu) {

    auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    
    if(overflows_16bit(value, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_carry_16bit(value, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    value += value;
    cpu.m_reg_h = (value >> 8);
    cpu.m_reg_l = (value & 0xF);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void ADD_HL_SP(Cpu& cpu) {
    throw UnimplementedOperation("ADD HL SP\n");
}

void SUB_D8(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void SUB_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB A");
}

void SUB_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB B");
}

void SUB_C(Cpu& cpu) {

    const auto value = cpu.m_reg_c;
    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SUB_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB D");
}

void SUB_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB E");
}

void SUB_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB H");
}

void SUB_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB L");
}

void SUB_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB ADDR HL");
}

void INC_A(Cpu& cpu) {

    if(half_carry_8bit(cpu.m_reg_a, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_a++;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_B(Cpu& cpu) {
    
    if(half_carry_8bit(cpu.m_reg_b, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_b++;

    if(cpu.m_reg_b == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_C(Cpu& cpu) {

    if(half_carry_8bit(cpu.m_reg_c, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_c++;

    if(cpu.m_reg_c == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_D(Cpu& cpu) {
    
    if(half_carry_8bit(cpu.m_reg_d, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_d++;

    if(cpu.m_reg_d == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_E(Cpu& cpu) {

    if(half_carry_8bit(cpu.m_reg_e, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_e++;

    if(cpu.m_reg_e == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_H(Cpu& cpu) {
    
    if(half_carry_8bit(cpu.m_reg_h, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_h++;

    if(cpu.m_reg_h == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_L(Cpu& cpu) {

    if(half_carry_8bit(cpu.m_reg_l, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_l++;

    if(cpu.m_reg_l == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_BC(Cpu& cpu) {

    auto value = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
    value++;

    cpu.m_reg_b = (value >> 8);
    cpu.m_reg_c = (value & 0xF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void INC_DE(Cpu& cpu) {
    
    auto value = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
    value++;

    cpu.m_reg_d = (value >> 8);
    cpu.m_reg_e = (value & 0xF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void INC_HL(Cpu& cpu) {

    auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    value++;

    cpu.m_reg_h = (value >> 8);
    cpu.m_reg_l = (value & 0xF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void INC_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC ADDR HL");
}

void INC_SP(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC SP");
}

void DEC_A(Cpu& cpu) {

    if(half_borrow_8bit(cpu.m_reg_a, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_a--;
    
    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_B(Cpu& cpu) {

    if(half_borrow_8bit(cpu.m_reg_b, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_b--;

    if(cpu.m_reg_b == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_C(Cpu& cpu) {

    if(half_borrow_8bit(cpu.m_reg_c, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_c--;

    if(cpu.m_reg_c == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC D");
}

void DEC_E(Cpu& cpu) {    
    
    if(half_borrow_8bit(cpu.m_reg_e, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_e--;

    if(cpu.m_reg_e == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;    
}

void DEC_H(Cpu& cpu) {

    if(half_borrow_8bit(cpu.m_reg_h, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_h--;

    if(cpu.m_reg_h == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_L(Cpu& cpu) {

    if(half_borrow_8bit(cpu.m_reg_l, 1)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    cpu.m_reg_l--;

    if(cpu.m_reg_l == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_BC(Cpu& cpu) {

    auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
    bc--;

    cpu.m_reg_b = (bc >> 8);
    cpu.m_reg_c = (bc & 0xF);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void DEC_DE(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC DE");
}

void DEC_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC HL");
}

void DEC_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC ADDR HL");
}

void DEC_SP(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC SP");
}

void SCF(Cpu& cpu) {

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    set_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void CCF(Cpu& cpu) {

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag) : set_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void RRCA(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RRCA");
}

void RRA(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_a, 0);
    cpu.m_reg_a >>= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_a, 7) : clear_bit(cpu.m_reg_a, 7);

    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void RLA(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RLA");
}

void RLCA(Cpu& cpu) {

    is_set(cpu.m_reg_a, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a = rotate_left(cpu.m_reg_a, 1);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void DDA(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DDA");
}

void ADD_SP_R8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD SP R8");
}

void AND_D8(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_reg_a &= value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void AND_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND A");
}

void AND_B(Cpu& cpu) {
    const auto value = cpu.m_reg_b;
    cpu.m_reg_a &= value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void AND_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND C");
}

void AND_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND D");
}

void AND_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND E");
}

void AND_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND H");
}

void AND_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND L");
}

void AND_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND ADDR HL");
}

void XOR_D8(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_reg_a ^= value;
    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void XOR_A(Cpu& cpu) {
    
    throw UnimplementedOperation("Unimplemented operation: XOR A");
}

void XOR_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR B");
}

void XOR_C(Cpu& cpu) {

    cpu.m_reg_a ^= cpu.m_reg_c;
    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void XOR_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR D");
}

void XOR_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR E");
}

void XOR_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR H");
}

void XOR_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR L");
}

void XOR_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);

    cpu.m_reg_a ^= value;
    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void OR_D8(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_reg_a |= value;
    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void OR_A(Cpu& cpu) {
    cpu.m_reg_a |= cpu.m_reg_a;
    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void OR_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR B");
}

void OR_C(Cpu& cpu) {

    cpu.m_reg_a |= cpu.m_reg_c;
    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void OR_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR D");
}

void OR_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR E");
}

void OR_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR H");
}

void OR_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR L");
}

void OR_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR ADDR HL");
}

void CP_D8(Cpu& cpu) {
    
    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if((cpu.m_reg_a - value) == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void CP_A(Cpu& cpu) {
    const auto value = cpu.m_reg_a;

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if( (cpu.m_reg_a - value) == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;    
}

void CP_B(Cpu& cpu) {

    const auto value = cpu.m_reg_b;

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if( (cpu.m_reg_a - value) == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_C(Cpu& cpu) {

    const auto value = cpu.m_reg_c;

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if( (cpu.m_reg_a - value) == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_D(Cpu& cpu) {
    const auto value = cpu.m_reg_d;

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if( (cpu.m_reg_a - value) == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_E(Cpu& cpu) {

    const auto value = cpu.m_reg_e;

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if( (cpu.m_reg_a - value) == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP H");
}

void CP_L(Cpu& cpu) {

    const auto value = cpu.m_reg_l;

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if( (cpu.m_reg_a - value) == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP ADDR HL");
}

void PUSH_AF(Cpu& cpu) {

    cpu.m_memory_controller->write(cpu.m_stack_ptr-1, cpu.m_reg_a);
    cpu.m_memory_controller->write(cpu.m_stack_ptr-2, cpu.m_reg_f);

    cpu.m_stack_ptr -= 2;
    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void PUSH_BC(Cpu& cpu) {

    cpu.m_memory_controller->write(cpu.m_stack_ptr-1, cpu.m_reg_b);
    cpu.m_memory_controller->write(cpu.m_stack_ptr-2, cpu.m_reg_c);

    cpu.m_stack_ptr -= 2;
    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void PUSH_DE(Cpu& cpu) {

    cpu.m_memory_controller->write(cpu.m_stack_ptr-1, cpu.m_reg_d);
    cpu.m_memory_controller->write(cpu.m_stack_ptr-2, cpu.m_reg_e);

    cpu.m_stack_ptr -= 2;
    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void PUSH_HL(Cpu& cpu) {

    cpu.m_memory_controller->write(cpu.m_stack_ptr-1, cpu.m_reg_h);
    cpu.m_memory_controller->write(cpu.m_stack_ptr-2, cpu.m_reg_l);

    cpu.m_stack_ptr -= 2;
    cpu.m_cycles += 16;
    cpu.m_program_counter++;
}

void POP_AF(Cpu& cpu) {

    cpu.m_reg_f = cpu.m_memory_controller->read(cpu.m_stack_ptr);
    cpu.m_reg_a = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
    cpu.m_stack_ptr += 2;
    cpu.m_program_counter++;
    cpu.m_cycles += 12;
}

void POP_BC(Cpu& cpu) {

    cpu.m_reg_c = cpu.m_memory_controller->read(cpu.m_stack_ptr);
    cpu.m_reg_b = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
    cpu.m_stack_ptr += 2;
    cpu.m_program_counter++;
    cpu.m_cycles += 12;
}

void POP_DE(Cpu& cpu) {

    cpu.m_reg_e = cpu.m_memory_controller->read(cpu.m_stack_ptr);
    cpu.m_reg_d = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
    cpu.m_stack_ptr += 2;
    cpu.m_program_counter++;
    cpu.m_cycles += 12;
}

void POP_HL(Cpu& cpu) {

    cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_stack_ptr);
    cpu.m_reg_h = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
    cpu.m_stack_ptr += 2;
    cpu.m_program_counter++;
    cpu.m_cycles += 12;

}

void ADC_A_D8(Cpu& cpu) {

    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);

    if(half_carry_8bit(cpu.m_reg_a, value + carry_value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(overflows_8bit(cpu.m_reg_a, value + carry_value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += value + carry_value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void ADC_A_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A A");
}

void ADC_A_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A B");
}

void ADC_A_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A C");
}

void ADC_A_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A D");
}

void ADC_A_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A E");
}

void ADC_A_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A H");
}

void ADC_A_L(Cpu& cpu) {
    
    const uint8_t carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;

    if(half_carry_8bit(cpu.m_reg_a, cpu.m_reg_l + carry_value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(overflows_8bit(cpu.m_reg_a, cpu.m_reg_l + carry_value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += cpu.m_reg_l + carry_value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADC_A_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A ADDR HL");
}

void LDH_ADDR_A8_A(Cpu& cpu) {

    const uint16_t address = 0xFF00 + cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_memory_controller->write(address, cpu.m_reg_a);
    cpu.m_cycles += 12;
    cpu.m_program_counter += 2;
}

void LDH_A_ADDR_A8(Cpu& cpu) {
    
    const uint16_t address = 0xFF00 + cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_reg_a = cpu.m_memory_controller->read(address);    
    cpu.m_cycles += 12;
    cpu.m_program_counter += 2;
}

void LD_ADDR_C_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR C A");
}

void SBC_A_D8(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1)
        + (is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0);

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void SBC_A_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A A");
}

void SBC_A_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A B");
}

void SBC_A_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A C");
}

void SBC_A_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A D");
}

void SBC_A_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A E");
}

void SBC_A_H(Cpu& cpu) {

    const auto value = cpu.m_reg_h
        + (is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0);

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SBC_A_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A L");
}

void SBC_A_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address)
        + (is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0);

    if(half_borrow_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(underflows_8bit(cpu.m_reg_a, value)) {
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= value;

    if(cpu.m_reg_a == 0) {
        set_bit(cpu.m_reg_f, Cpu::zero_flag);
    }

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void PREFIX_CB(Cpu& cpu) {
    cpu.m_program_counter++;
    cpu.m_cycles += 4;

    step_cb(cpu);

    throw UnimplementedOperation("PREFIX CB");
}

void LD_ADDR_HLD_A(Cpu& cpu) {

    auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_a);

    address--;

    cpu.m_reg_h = (address >> 8);
    cpu.m_reg_l = (address & 0xF);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_A_ADDR_HLD(Cpu& cpu) {
    throw UnimplementedOperation("LD A ADDR HLD\n");
}