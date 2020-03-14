#include <cpu/Operations.h>
#include <BitOperations.h>
#include <string>
#include <iostream>

UnimplementedOperation::UnimplementedOperation(const std::string& msg)
    : runtime_error(msg) {

}

void NOP(Cpu& cpu) {
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void STOP(Cpu& cpu) {
    cpu.m_program_counter += 2;
    cpu.m_cycles += 4;
}

void HALT(Cpu& cpu) {
    cpu.m_is_halted = true;
    cpu.m_cycles += 4;
}

void RST(Cpu& cpu, uint8_t address) {

    const auto pc_high = ( (cpu.m_program_counter + 1) >> 8);
    const auto pc_low = ( (cpu.m_program_counter + 1) & 0xFF);

    cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
    cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);

    cpu.m_program_counter = combine_bytes(0x00, address);
    cpu.m_stack_ptr -= 2;
    cpu.m_cycles += 16;
}

void DI(Cpu& cpu) {
    cpu.m_enabled_interrupts = false;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void EI(Cpu& cpu) {

    cpu.m_cycles += 4;
    cpu.m_program_counter++;

    step(cpu);

    cpu.m_enabled_interrupts = true;
}

void JR(Cpu& cpu) {

    cpu.m_program_counter += 2;
    const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
    cpu.m_program_counter += distance;
    cpu.m_cycles += 12;
}

void JR_NZ(Cpu& cpu) {
    
    if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
        cpu.m_program_counter += 2;
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
        cpu.m_program_counter += distance;
        cpu.m_cycles += 12;
    } else {
        cpu.m_program_counter += 2;
        cpu.m_cycles += 8;
    }
}

void JR_Z(Cpu& cpu) {

    if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
        cpu.m_program_counter += 2;
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
        cpu.m_program_counter += distance;
        cpu.m_cycles += 12;
    } else {
        cpu.m_program_counter += 2;
        cpu.m_cycles += 8;
    }
}

void JR_NC(Cpu& cpu) {

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        cpu.m_program_counter += 2;
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
        cpu.m_program_counter += distance;
        cpu.m_cycles += 12;
    } else {
        cpu.m_program_counter += 2;
        cpu.m_cycles += 8;
    }
}

void JR_C(Cpu& cpu) {

    if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        cpu.m_program_counter += 2;
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
        cpu.m_program_counter += distance;
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

    if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
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
    if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
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

void RETI(Cpu& cpu) {
    const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
    const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
    
    cpu.m_program_counter = combine_bytes(pc_high, pc_low);
    
    cpu.m_stack_ptr += 2;
    cpu.m_cycles += 16;
    cpu.m_enabled_interrupts = true;
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
    if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
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

void JUMP_NC(Cpu& cpu) {
    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
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

    const uint8_t pc_high = ( (cpu.m_program_counter+3) >> 8);
    const uint8_t pc_low = ( (cpu.m_program_counter+3) & 0xFF);

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
        const auto pc_low = ( (cpu.m_program_counter+3) & 0xFF);

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
    
    if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
        const auto pc_high = ( (cpu.m_program_counter+3) >> 8);
        const auto pc_low = ( (cpu.m_program_counter+3) & 0xFF);

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

void CALL_NC(Cpu& cpu) {
    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        const auto pc_high = ( (cpu.m_program_counter+3) >> 8);
        const auto pc_low = ( (cpu.m_program_counter+3) & 0xFF);

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

void CALL_C(Cpu& cpu) {
    if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        const auto pc_high = ( (cpu.m_program_counter+3) >> 8);
        const auto pc_low = ( (cpu.m_program_counter+3) & 0xFF);

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

void LD_A_D8(Cpu& cpu) {
    cpu.m_reg_a = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LD_A_A(Cpu& cpu) {
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

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);

    cpu.m_reg_a = cpu.m_memory_controller->read(address);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
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
    const auto address = 0xFF00 + cpu.m_reg_c;
    cpu.m_reg_a = cpu.m_memory_controller->read(address);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_ADDR_A16_SP(Cpu& cpu) {
    const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter + 2);
    const auto address = combine_bytes(upper, lower);
    cpu.m_memory_controller->write(address, cpu.m_stack_ptr & 0xFF);
    cpu.m_memory_controller->write(address + 1, cpu.m_stack_ptr >> 8);

    cpu.m_program_counter += 3;
    cpu.m_cycles += 20;
}

void LDI_ADDR_HL_A(Cpu& cpu) {

    auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_a);

    address++;
    cpu.m_reg_h = (address >> 8);
    cpu.m_reg_l = (address & 0xFF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;

}

void LDI_A_ADDR_HL(Cpu& cpu) {

    auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_a = cpu.m_memory_controller->read(address);
    
    address++;
    cpu.m_reg_h = (address >> 8);
    cpu.m_reg_l = (address & 0xFF);

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
    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void LD_B_C(Cpu& cpu) {
    cpu.m_reg_b = cpu.m_reg_c;
    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void LD_B_D(Cpu& cpu) {
    cpu.m_reg_b = cpu.m_reg_d;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_B_E(Cpu& cpu) {
    cpu.m_reg_b = cpu.m_reg_e;
    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void LD_B_H(Cpu& cpu) {
    cpu.m_reg_b = cpu.m_reg_h;
    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void LD_B_L(Cpu& cpu) {
    cpu.m_reg_b = cpu.m_reg_l;
    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void LD_B_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_b = cpu.m_memory_controller->read(address);

    cpu.m_cycles += 8;
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
    cpu.m_reg_c = cpu.m_reg_b;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_C_C(Cpu& cpu) {
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_C_D(Cpu& cpu) {
    cpu.m_reg_c = cpu.m_reg_d;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_C_E(Cpu& cpu) {
    cpu.m_reg_c = cpu.m_reg_e;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_C_H(Cpu& cpu) {
    cpu.m_reg_c = cpu.m_reg_h;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_C_L(Cpu& cpu) {
    cpu.m_reg_c = cpu.m_reg_l;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_C_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_c = cpu.m_memory_controller->read(address);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_D_D8(Cpu& cpu) {
    cpu.m_reg_d = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_D_A(Cpu& cpu) {
    cpu.m_reg_d = cpu.m_reg_a;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_D_B(Cpu& cpu) {
    cpu.m_reg_d = cpu.m_reg_b;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_D_C(Cpu& cpu) {
    cpu.m_reg_d = cpu.m_reg_c;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_D_D(Cpu& cpu) {
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_D_E(Cpu& cpu) {
    cpu.m_reg_d = cpu.m_reg_e;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_D_H(Cpu& cpu) {
    cpu.m_reg_d = cpu.m_reg_h;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;}

void LD_D_L(Cpu& cpu) {
    cpu.m_reg_d = cpu.m_reg_l;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
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
    cpu.m_reg_e = cpu.m_reg_b;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_E_C(Cpu& cpu) {
    cpu.m_reg_e = cpu.m_reg_c;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_E_D(Cpu& cpu) {
    cpu.m_reg_e = cpu.m_reg_d;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_E_E(Cpu& cpu) {
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_E_H(Cpu& cpu) {
    cpu.m_reg_e = cpu.m_reg_h;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_E_L(Cpu& cpu) {
    cpu.m_reg_e = cpu.m_reg_l;
    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void LD_E_ADDR_HL(Cpu& cpu) {
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_e = cpu.m_memory_controller->read(address);
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
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
    cpu.m_reg_h = cpu.m_reg_c;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_H_D(Cpu& cpu) {
    cpu.m_reg_h = cpu.m_reg_d;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_H_E(Cpu& cpu) {
    cpu.m_reg_h = cpu.m_reg_e;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_H_H(Cpu& cpu) {
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
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
    cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LD_L_A(Cpu& cpu) {

    cpu.m_reg_l = cpu.m_reg_a;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_L_B(Cpu& cpu) {
    cpu.m_reg_l = cpu.m_reg_b;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
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
    cpu.m_reg_l = cpu.m_reg_h;
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void LD_L_L(Cpu& cpu) {
    cpu.m_cycles += 4;
    cpu.m_program_counter++;
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

    const auto distance = (cpu.m_memory_controller->read(cpu.m_program_counter + 1));

    half_carry_8bit(cpu.m_stack_ptr, distance)     ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);


    overflows_8bit(cpu.m_stack_ptr, distance)  ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    const auto result = cpu.m_stack_ptr + static_cast<int8_t>(distance);
    cpu.m_reg_h = (result >> 8);
    cpu.m_reg_l = (result & 0xFF);

    clear_bit(cpu.m_reg_f, Cpu::zero_flag);
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 12;
    cpu.m_program_counter += 2;
}

void LD_SP_D16(Cpu& cpu) {

    const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter+2);
    const auto value = combine_bytes(upper, lower);

    cpu.m_stack_ptr = value;
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
    
    half_carry_8bit(cpu.m_reg_a, value)             ? 
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)          ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void ADD_A_A(Cpu& cpu) {
    const auto value = cpu.m_reg_a;

    half_carry_8bit(cpu.m_reg_a, value)             ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)          ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADD_A_B(Cpu& cpu) {

    const auto value = cpu.m_reg_b;

    half_carry_8bit(cpu.m_reg_a, value)             ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)          ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADD_A_C(Cpu& cpu) {

    const auto value = cpu.m_reg_c;
    half_carry_8bit(cpu.m_reg_a, value)             ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)          ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADD_A_D(Cpu& cpu) {
    const auto value = cpu.m_reg_d;

    half_carry_8bit(cpu.m_reg_a, value)             ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)          ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADD_A_E(Cpu& cpu) {
    const auto value = cpu.m_reg_e;

    half_carry_8bit(cpu.m_reg_a, value)             ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)          ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADD_A_H(Cpu& cpu) {
    const auto value = cpu.m_reg_h;

    half_carry_8bit(cpu.m_reg_a, value)             ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)          ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADD_A_L(Cpu& cpu) {
    const auto value = cpu.m_reg_l;

    half_carry_8bit(cpu.m_reg_a, value)             ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)          ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADD_A_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);

    const auto value = cpu.m_memory_controller->read(address);
    half_carry_8bit(cpu.m_reg_a, value)             ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)          ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void ADD_HL_BC(Cpu& cpu) {
    
    auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);

    overflows_16bit(hl, bc)                     ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_carry_16bit(hl, bc)                        ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    hl += bc;

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_reg_h = (hl >> 8);
    cpu.m_reg_l = (hl & 0xFF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void ADD_HL_DE(Cpu& cpu) {

    auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto de = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);

    overflows_16bit(hl, de)                     ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_carry_16bit(hl, de)                        ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    hl += de;

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_reg_h = (hl >> 8);
    cpu.m_reg_l = (hl & 0xFF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void ADD_HL_HL(Cpu& cpu) {

    auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    
    overflows_16bit(value, value)               ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_carry_16bit(value, value)               ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    

    value += value;
    cpu.m_reg_h = (value >> 8);
    cpu.m_reg_l = (value & 0xFF);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void ADD_HL_SP(Cpu& cpu) {

    auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_stack_ptr;
    
    overflows_16bit(hl, value)               ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_carry_16bit(hl, value)               ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    

    hl += value;
    cpu.m_reg_h = (hl >> 8);
    cpu.m_reg_l = (hl & 0xFF);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SUB_D8(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a -= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void SUB_A(Cpu& cpu) {
    
    const auto value = cpu.m_reg_a;
    
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    

    cpu.m_reg_a -= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SUB_B(Cpu& cpu) {
    const auto value = cpu.m_reg_b;
    
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    

    cpu.m_reg_a -= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SUB_C(Cpu& cpu) {

    const auto value = cpu.m_reg_c;
    
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    

    cpu.m_reg_a -= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SUB_D(Cpu& cpu) {

    const auto value = cpu.m_reg_d;
    
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    

    cpu.m_reg_a -= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SUB_E(Cpu& cpu) {
    const auto value = cpu.m_reg_e;
    
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    

    cpu.m_reg_a -= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SUB_H(Cpu& cpu) {
    const auto value = cpu.m_reg_h;
    
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    

    cpu.m_reg_a -= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SUB_L(Cpu& cpu) {
    
    const auto value = cpu.m_reg_l;
    
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    

    cpu.m_reg_a -= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SUB_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    

    cpu.m_reg_a -= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void INC_A(Cpu& cpu) {

    half_carry_8bit(cpu.m_reg_a, 1)                 ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_a++;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_B(Cpu& cpu) {
    
    half_carry_8bit(cpu.m_reg_b, 1)                 ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_b++;

    cpu.m_reg_b == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_C(Cpu& cpu) {

    half_carry_8bit(cpu.m_reg_c, 1)                 ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_c++;

    cpu.m_reg_c == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_D(Cpu& cpu) {
    
    half_carry_8bit(cpu.m_reg_d, 1)                 ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_d++;

    cpu.m_reg_d == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_E(Cpu& cpu) {

    half_carry_8bit(cpu.m_reg_e, 1)                 ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_e++;

    cpu.m_reg_e == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_H(Cpu& cpu) {
    
    half_carry_8bit(cpu.m_reg_h, 1)                 ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_h++;

    cpu.m_reg_h == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_L(Cpu& cpu) {

    half_carry_8bit(cpu.m_reg_l, 1)                 ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_l++;

    cpu.m_reg_l == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void INC_BC(Cpu& cpu) {

    auto value = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
    value++;

    cpu.m_reg_b = (value >> 8);
    cpu.m_reg_c = (value & 0xFF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void INC_DE(Cpu& cpu) {
    
    auto value = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
    value++;

    cpu.m_reg_d = (value >> 8);
    cpu.m_reg_e = (value & 0xFF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void INC_HL(Cpu& cpu) {

    auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    value++;

    cpu.m_reg_h = (value >> 8);
    cpu.m_reg_l = (value & 0xFF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void INC_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    half_carry_8bit(value, 1) ? set_bit(cpu.m_reg_f, Cpu::half_carry_flag) :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    value++;

    value == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    cpu.m_memory_controller->write(address, value);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 12;
}

void INC_SP(Cpu& cpu) {
    cpu.m_stack_ptr++;
    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void DEC_A(Cpu& cpu) {

    half_borrow_8bit(cpu.m_reg_a, 1)                ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_a--;
    
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_B(Cpu& cpu) {

    half_borrow_8bit(cpu.m_reg_b, 1)                ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_b--;

    cpu.m_reg_b == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_C(Cpu& cpu) {

    half_borrow_8bit(cpu.m_reg_c, 1)                ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_c--;

    cpu.m_reg_c == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_D(Cpu& cpu) {
    
    half_borrow_8bit(cpu.m_reg_d, 1)                ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_d--;

    cpu.m_reg_d == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;    
}

void DEC_E(Cpu& cpu) {    
    
    half_borrow_8bit(cpu.m_reg_e, 1)                ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_e--;

    cpu.m_reg_e == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;    
}

void DEC_H(Cpu& cpu) {

    half_borrow_8bit(cpu.m_reg_h, 1)                ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_h--;

    cpu.m_reg_h == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_L(Cpu& cpu) {

    half_borrow_8bit(cpu.m_reg_l, 1)                ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_l--;

    cpu.m_reg_l == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles +=4;
}

void DEC_BC(Cpu& cpu) {

    auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
    bc--;

    cpu.m_reg_b = (bc >> 8);
    cpu.m_reg_c = (bc & 0xFF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void DEC_DE(Cpu& cpu) {

    auto de = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
    de--;

    cpu.m_reg_d = (de >> 8);
    cpu.m_reg_e = (de & 0xFF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void DEC_HL(Cpu& cpu) {
    auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    hl--;

    cpu.m_reg_h = (hl >> 8);
    cpu.m_reg_l = (hl & 0xFF);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void DEC_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    auto value = cpu.m_memory_controller->read(address);

    half_borrow_8bit(value, 1)                      ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    value--;

    value == 0                                  ?
        set_bit(cpu.m_reg_f, Cpu::zero_flag)    :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_memory_controller->write(address, value);

    cpu.m_program_counter++;
    cpu.m_cycles += 12;
}

void DEC_SP(Cpu& cpu) {
    cpu.m_stack_ptr--;
    cpu.m_cycles += 8;
    cpu.m_program_counter++;
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

    is_set(cpu.m_reg_a, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_a = rotate_right<uint8_t>(cpu.m_reg_a, 1);

    
    clear_bit(cpu.m_reg_f, Cpu::zero_flag);
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void RRA(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_a, 0);
    cpu.m_reg_a >>= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_a, 7) 
        : clear_bit(cpu.m_reg_a, 7);

    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag) 
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    clear_bit(cpu.m_reg_f, Cpu::zero_flag);
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void RLA(Cpu& cpu) {

    const auto new_carry_flag = is_set(cpu.m_reg_a, 7);
    cpu.m_reg_a <<= 1;

    is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_a, 0)
        : clear_bit(cpu.m_reg_a, 0);
    
    new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
        : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    clear_bit(cpu.m_reg_f, Cpu::zero_flag);
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void RLCA(Cpu& cpu) {

    is_set(cpu.m_reg_a, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a = rotate_left<uint8_t>(cpu.m_reg_a, 1);

    clear_bit(cpu.m_reg_f, Cpu::zero_flag);
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void DAA(Cpu& cpu) {    

    if(!is_set(cpu.m_reg_f, Cpu::sub_flag)) {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag) || cpu.m_reg_a > 0x99) {
            cpu.m_reg_a += 0x60;
            set_bit(cpu.m_reg_f, Cpu::carry_flag);
        }

        if(is_set(cpu.m_reg_f, Cpu::half_carry_flag) || (cpu.m_reg_a & 0x0F) > 0x09) {
            cpu.m_reg_a += 0x06;
        }
    } else {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            cpu.m_reg_a -= 0x60;
        }
        if(is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
            cpu.m_reg_a -= 0x6;
        }
    }

    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void ADD_SP_R8(Cpu& cpu) {
    const auto distance = (cpu.m_memory_controller->read(cpu.m_program_counter + 1));

    half_carry_8bit(cpu.m_stack_ptr, distance)     ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);


    overflows_8bit(cpu.m_stack_ptr, distance)  ? 
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);


    cpu.m_stack_ptr += static_cast<int8_t>(distance);

    clear_bit(cpu.m_reg_f, Cpu::zero_flag);
    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 16;
    cpu.m_program_counter += 2;
}

void AND_D8(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_reg_a &= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void AND_A(Cpu& cpu) {
    const auto value = cpu.m_reg_a;
    cpu.m_reg_a &= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void AND_B(Cpu& cpu) {
    const auto value = cpu.m_reg_b;
    cpu.m_reg_a &= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void AND_C(Cpu& cpu) {

    const auto value = cpu.m_reg_c;
    cpu.m_reg_a &= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void AND_D(Cpu& cpu) {
    const auto value = cpu.m_reg_d;
    cpu.m_reg_a &= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void AND_E(Cpu& cpu) {
    const auto value = cpu.m_reg_e;
    cpu.m_reg_a &= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void AND_H(Cpu& cpu) {
    const auto value = cpu.m_reg_h;
    cpu.m_reg_a &= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void AND_L(Cpu& cpu) {
    const auto value = cpu.m_reg_l;
    cpu.m_reg_a &= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void AND_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);
    cpu.m_reg_a &= value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void XOR_D8(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_reg_a ^= value;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void XOR_A(Cpu& cpu) {
    
    cpu.m_reg_a ^= cpu.m_reg_a;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void XOR_B(Cpu& cpu) {
    cpu.m_reg_a ^= cpu.m_reg_b;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void XOR_C(Cpu& cpu) {

    cpu.m_reg_a ^= cpu.m_reg_c;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void XOR_D(Cpu& cpu) {
    cpu.m_reg_a ^= cpu.m_reg_d;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void XOR_E(Cpu& cpu) {
    cpu.m_reg_a ^= cpu.m_reg_e;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void XOR_H(Cpu& cpu) {

    cpu.m_reg_a ^= cpu.m_reg_h;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void XOR_L(Cpu& cpu) {
    
    cpu.m_reg_a ^= cpu.m_reg_l;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void XOR_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);

    cpu.m_reg_a ^= value;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void OR_D8(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    cpu.m_reg_a |= value;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void OR_A(Cpu& cpu) {
    cpu.m_reg_a |= cpu.m_reg_a;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void OR_B(Cpu& cpu) {

    cpu.m_reg_a |= cpu.m_reg_b;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void OR_C(Cpu& cpu) {

    cpu.m_reg_a |= cpu.m_reg_c;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void OR_D(Cpu& cpu) {
    cpu.m_reg_a |= cpu.m_reg_d;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void OR_E(Cpu& cpu) {
    cpu.m_reg_a |= cpu.m_reg_e;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void OR_H(Cpu& cpu) {

    cpu.m_reg_a |= cpu.m_reg_h;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void OR_L(Cpu& cpu) {
    cpu.m_reg_a |= cpu.m_reg_l;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void OR_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);

    cpu.m_reg_a |= value;
    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);
    clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void CP_D8(Cpu& cpu) {
    
    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    (cpu.m_reg_a == value) ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void CP_A(Cpu& cpu) {
    const auto value = cpu.m_reg_a;

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    (cpu.m_reg_a == value) ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;    
}

void CP_B(Cpu& cpu) {

    const auto value = cpu.m_reg_b;

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    (cpu.m_reg_a == value) ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_C(Cpu& cpu) {

    const auto value = cpu.m_reg_c;

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    (cpu.m_reg_a == value) ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_D(Cpu& cpu) {
    const auto value = cpu.m_reg_d;

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    (cpu.m_reg_a == value) ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_E(Cpu& cpu) {

    const auto value = cpu.m_reg_e;

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    (cpu.m_reg_a  == value) ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_H(Cpu& cpu) {
    const auto value = cpu.m_reg_h;

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    (cpu.m_reg_a == value) ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_L(Cpu& cpu) {

    const auto value = cpu.m_reg_l;

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    (cpu.m_reg_a == value) ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 4;
    cpu.m_program_counter++;
}

void CP_ADDR_HL(Cpu& cpu) {

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    (cpu.m_reg_a == value) ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
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

    cpu.m_reg_f = cpu.m_memory_controller->read(cpu.m_stack_ptr) & 0xF0;
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

    half_carry_8bit(cpu.m_reg_a, value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)        ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_carry_8bit(cpu.m_reg_a, carry_value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        overflows_8bit(cpu.m_reg_a, carry_value)        ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void ADC_A_A(Cpu& cpu) {
    
    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_a;

    half_carry_8bit(cpu.m_reg_a, value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)        ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_carry_8bit(cpu.m_reg_a, carry_value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        overflows_8bit(cpu.m_reg_a, carry_value)        ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADC_A_B(Cpu& cpu) {

    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_b;

    half_carry_8bit(cpu.m_reg_a, value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)        ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_carry_8bit(cpu.m_reg_a, carry_value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        overflows_8bit(cpu.m_reg_a, carry_value)        ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADC_A_C(Cpu& cpu) {

    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_c;

    half_carry_8bit(cpu.m_reg_a, value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)        ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_carry_8bit(cpu.m_reg_a, carry_value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        overflows_8bit(cpu.m_reg_a, carry_value)        ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADC_A_D(Cpu& cpu) {
    
    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_d;

    half_carry_8bit(cpu.m_reg_a, value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)        ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_carry_8bit(cpu.m_reg_a, carry_value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        overflows_8bit(cpu.m_reg_a, carry_value)        ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADC_A_E(Cpu& cpu) {
    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_e;

    half_carry_8bit(cpu.m_reg_a, value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)        ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_carry_8bit(cpu.m_reg_a, carry_value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        overflows_8bit(cpu.m_reg_a, carry_value)        ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADC_A_H(Cpu& cpu) {

    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_h;

    half_carry_8bit(cpu.m_reg_a, value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)        ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_carry_8bit(cpu.m_reg_a, carry_value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        overflows_8bit(cpu.m_reg_a, carry_value)        ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADC_A_L(Cpu& cpu) {
    
    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_l;

    half_carry_8bit(cpu.m_reg_a, value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)        ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_carry_8bit(cpu.m_reg_a, carry_value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        overflows_8bit(cpu.m_reg_a, carry_value)        ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void ADC_A_ADDR_HL(Cpu& cpu) {

    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;

    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);

    half_carry_8bit(cpu.m_reg_a, value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    overflows_8bit(cpu.m_reg_a, value)        ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a += value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_carry_8bit(cpu.m_reg_a, carry_value)       ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)          :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        overflows_8bit(cpu.m_reg_a, carry_value)        ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)               :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a += carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void LDH_ADDR_A8_A(Cpu& cpu) {

    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    const uint16_t address = 0xFF00 + value;
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
    const auto address = 0xFF00 + cpu.m_reg_c;
    cpu.m_memory_controller->write(address, cpu.m_reg_a);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void SBC_A_D8(Cpu& cpu) {

    const auto carry_value = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_memory_controller->read(cpu.m_program_counter + 1);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    
    cpu.m_reg_a -= value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_borrow_8bit(cpu.m_reg_a, carry_value)       ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        underflows_8bit(cpu.m_reg_a, carry_value)         ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter += 2;
    cpu.m_cycles += 8;
}

void SBC_A_A(Cpu& cpu) {

    const auto carry_value =  is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_a;

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a -= value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_borrow_8bit(cpu.m_reg_a, carry_value)            ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        underflows_8bit(cpu.m_reg_a, carry_value)         ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;;
}

void SBC_A_B(Cpu& cpu) {

    const auto carry_value =  is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_b;

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a -= value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_borrow_8bit(cpu.m_reg_a, carry_value)            ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        underflows_8bit(cpu.m_reg_a, carry_value)         ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SBC_A_C(Cpu& cpu) {
    const auto carry_value =  is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_c;

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a -= value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_borrow_8bit(cpu.m_reg_a, carry_value)            ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        underflows_8bit(cpu.m_reg_a, carry_value)         ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SBC_A_D(Cpu& cpu) {

    const auto carry_value =  is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_d;

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a -= value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_borrow_8bit(cpu.m_reg_a, carry_value)            ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        underflows_8bit(cpu.m_reg_a, carry_value)         ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SBC_A_E(Cpu& cpu) {
    
    const auto carry_value =  is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_e;

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a -= value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_borrow_8bit(cpu.m_reg_a, carry_value)            ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        underflows_8bit(cpu.m_reg_a, carry_value)         ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SBC_A_H(Cpu& cpu) {

    const auto carry_value =  is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_h;

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a -= value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_borrow_8bit(cpu.m_reg_a, carry_value)            ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        underflows_8bit(cpu.m_reg_a, carry_value)         ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SBC_A_L(Cpu& cpu) {

    const auto carry_value =  is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto value = cpu.m_reg_l;

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a -= value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_borrow_8bit(cpu.m_reg_a, carry_value)            ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        underflows_8bit(cpu.m_reg_a, carry_value)         ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}

void SBC_A_ADDR_HL(Cpu& cpu) {

    const auto carry_value =  is_set(cpu.m_reg_f, Cpu::carry_flag) ? 1 : 0;
    const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    const auto value = cpu.m_memory_controller->read(address);

    half_borrow_8bit(cpu.m_reg_a, value)            ?
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    underflows_8bit(cpu.m_reg_a, value)         ?
        set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
        clear_bit(cpu.m_reg_f, Cpu::carry_flag);

    cpu.m_reg_a -= value;

    if(!is_set(cpu.m_reg_f, Cpu::half_carry_flag)) {
        half_borrow_8bit(cpu.m_reg_a, carry_value)            ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }

    if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
        underflows_8bit(cpu.m_reg_a, carry_value)         ?
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);
    }

    cpu.m_reg_a -= carry_value;

    cpu.m_reg_a == 0 ? set_bit(cpu.m_reg_f, Cpu::zero_flag) :
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);

    set_bit(cpu.m_reg_f, Cpu::sub_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 8;
}

void PREFIX_CB(Cpu& cpu) {
    cpu.m_program_counter++;
    cpu.m_cycles += 4;
    step_cb(cpu);
}

void LD_ADDR_HLD_A(Cpu& cpu) {

    auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_memory_controller->write(address, cpu.m_reg_a);

    address--;

    cpu.m_reg_h = (address >> 8);
    cpu.m_reg_l = (address & 0xFF);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void LD_A_ADDR_HLD(Cpu& cpu) {

    auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
    cpu.m_reg_a = cpu.m_memory_controller->read(address);

    address--;
    cpu.m_reg_h = (address >> 8);
    cpu.m_reg_l = (address & 0xFF);

    cpu.m_cycles += 8;
    cpu.m_program_counter++;
}

void CPL(Cpu& cpu) {

    cpu.m_reg_a ^= 0xFF;

    set_bit(cpu.m_reg_f, Cpu::sub_flag);
    set_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    cpu.m_program_counter++;
    cpu.m_cycles += 4;
}