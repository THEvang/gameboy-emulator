#include <cpu/Operations.h>
#include <BitOperations.h>
#include <string>
#include <iostream>

UnimplementedOperation::UnimplementedOperation(const std::string& msg)
    : runtime_error(msg) {

}

FetchResult NOP(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu&){}};
}

FetchResult STOP(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu&){}};
}

FetchResult HALT(Cpu& cpu) {

    throw UnimplementedOperation("HALT\n");
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_is_halted = true;
    }};
}

FetchResult RST(Cpu& cpu, uint8_t address) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [address](Cpu& cpu){

        const auto pc_high = (cpu.m_program_counter >> 8);
        const auto pc_low = (cpu.m_program_counter & 0xFF);

        cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);

        cpu.m_program_counter = combine_bytes(0x00, address);
        cpu.m_stack_ptr -= 2;
    }};
}

FetchResult DI(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_enabled_interrupts = false;
    }};
}

FetchResult EI(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        fetch(cpu);
        cpu.m_enabled_interrupts = true;
    }};
}

FetchResult JR(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
        cpu.m_program_counter += distance;
    }};
}

FetchResult JR_NZ(Cpu& cpu) {
    
    const auto cycles =  !is_set(cpu.m_reg_f, Cpu::zero_flag) ? 12 : 8;
    constexpr auto delta_pc = 2;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
            cpu.m_program_counter += distance;
        }
    }};
}

FetchResult JR_Z(Cpu& cpu) {

    const auto cycles = is_set(cpu.m_reg_f, Cpu::zero_flag) ? 12 : 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
            cpu.m_program_counter += distance;
        }
    }};
}

FetchResult JR_NC(Cpu& cpu) {

    const auto cycles = !is_set(cpu.m_reg_f, Cpu::carry_flag) ? 12 : 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
            cpu.m_program_counter += distance;
        }
    }};
}

FetchResult JR_C(Cpu& cpu) {

    const auto cycles = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 12 : 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto distance = static_cast<int8_t>(cpu.m_memory_controller->read(cpu.m_program_counter - 1));
            cpu.m_program_counter += distance;
        }
    }};
}

FetchResult RET(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
        const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
        
        cpu.m_program_counter = combine_bytes(pc_high, pc_low);
        cpu.m_stack_ptr += 2;
    }};
}

FetchResult RET_NZ(Cpu& cpu) {

    const auto cycles = !is_set(cpu.m_reg_f, Cpu::zero_flag) ? 20 : 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
            const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
            cpu.m_program_counter = combine_bytes(pc_high, pc_low);            
            cpu.m_stack_ptr += 2;
        }
    }};
}

FetchResult RET_Z(Cpu& cpu) {
    
    const auto cycles = is_set(cpu.m_reg_f, Cpu::zero_flag) ? 20 : 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
            const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
            cpu.m_program_counter = combine_bytes(pc_high, pc_low);        
            cpu.m_stack_ptr += 2;
        }
    }};
}

FetchResult RET_NC(Cpu& cpu) {

    const auto cycles = !is_set(cpu.m_reg_f, Cpu::carry_flag) ? 20 : 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
            const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
            cpu.m_program_counter = combine_bytes(pc_high, pc_low);
            cpu.m_stack_ptr += 2;
        }
    }};
}

FetchResult RET_C(Cpu& cpu) {

    const auto cycles = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 20 : 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
            const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
            cpu.m_program_counter = combine_bytes(pc_high, pc_low);
            cpu.m_stack_ptr += 2;
        }
    }};
}

FetchResult RETI(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 0;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
        const auto pc_high = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
        cpu.m_program_counter = combine_bytes(pc_high, pc_low);    
        cpu.m_stack_ptr += 2;
        cpu.m_enabled_interrupts = true;
    }};
}

FetchResult JUMP(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto low = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
        const auto high = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        const auto address = combine_bytes(high, low);
        cpu.m_program_counter = address; 
    }};
}

FetchResult JUMP_NZ(Cpu& cpu) {

    const auto cycles = !is_set(cpu.m_reg_f, Cpu::zero_flag) ? 16 : 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {        
        if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
            const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
            const auto address = combine_bytes(upper, lower);
            cpu.m_program_counter = address;
        }
    }};
}

FetchResult JUMP_Z(Cpu& cpu) {

    const auto cycles = is_set(cpu.m_reg_f, Cpu::zero_flag) ? 16 : 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
            const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
            const auto address = combine_bytes(upper, lower);
            cpu.m_program_counter = address;
        }
    }};
}

FetchResult JUMP_NC(Cpu& cpu) {

    const auto cycles = !is_set(cpu.m_reg_f, Cpu::carry_flag) ? 16 : 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
            const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
            const auto address = combine_bytes(upper, lower);
            cpu.m_program_counter = address;
        }
    }};
}

FetchResult JUMP_C(Cpu& cpu) {

    const auto cycles = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 16 : 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
            const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
            const auto address = combine_bytes(upper, lower);
            cpu.m_program_counter = address;
        }
    }};
}

FetchResult JUMP_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_program_counter = address;
    }};
}


FetchResult CALL(Cpu& cpu) {

    constexpr auto cycles = 24;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const uint8_t pc_high = (cpu.m_program_counter >> 8);
        const uint8_t pc_low = (cpu.m_program_counter & 0xFF);
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);
        const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
        const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        const auto address = combine_bytes(upper, lower);
        cpu.m_program_counter = address;
        cpu.m_stack_ptr -= 2;
    }};
}

FetchResult CALL_NZ(Cpu& cpu) {

    const auto cycles = !is_set(cpu.m_reg_f, Cpu::zero_flag) ? 24 : 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto pc_high = (cpu.m_program_counter >> 8);
            const auto pc_low = (cpu.m_program_counter & 0xFF);

            cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
            cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);

        
            const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
            const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
            const auto address = combine_bytes(upper, lower);
        
            cpu.m_program_counter = address;
            cpu.m_stack_ptr -= 2;
        }
    }};
}

FetchResult CALL_Z(Cpu& cpu) {

    const auto cycles = is_set(cpu.m_reg_f, Cpu::zero_flag) ? 24 : 12;
    constexpr auto delta_pc = 3;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::zero_flag)) {
            const auto pc_high = (cpu.m_program_counter >> 8);
            const auto pc_low = (cpu.m_program_counter & 0xFF);

            cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
            cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);

            
            const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
            const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
            const auto address = combine_bytes(upper, lower);
            
            cpu.m_program_counter = address;
            cpu.m_stack_ptr -= 2;
        }
    }};
}

FetchResult CALL_NC(Cpu& cpu) {

    const auto cycles = !is_set(cpu.m_reg_f, Cpu::carry_flag) ? 24 : 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(!is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto pc_high = (cpu.m_program_counter >> 8);
            const auto pc_low = (cpu.m_program_counter & 0xFF);

            cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
            cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);

            
            const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
            const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
            const auto address = combine_bytes(upper, lower);
            
            cpu.m_program_counter = address;
            cpu.m_stack_ptr -= 2;
            }
    }};
}

FetchResult CALL_C(Cpu& cpu) {

    const auto cycles = is_set(cpu.m_reg_f, Cpu::carry_flag) ? 24 : 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        if(is_set(cpu.m_reg_f, Cpu::carry_flag)) {
            const auto pc_high = (cpu.m_program_counter >> 8);
            const auto pc_low = (cpu.m_program_counter & 0xFF);

            cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
            cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);

            
            const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
            const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
            const auto address = combine_bytes(upper, lower);
            
            cpu.m_program_counter = address;
            cpu.m_stack_ptr -= 2;
        }
    }};
}

FetchResult LD_A_D8(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
    }};
}

FetchResult LD_A_A(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){}};
}

FetchResult LD_A_B(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_a = cpu.m_reg_b;
    }};
}

FetchResult LD_A_C(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_c;
    }};
}

FetchResult LD_A_D(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_d;
    }};
}

FetchResult LD_A_E(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_e;
    }};
}

FetchResult LD_A_H(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_h;
    }};
}

FetchResult LD_A_L(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = cpu.m_reg_l;
    }};
}

FetchResult LD_A_ADDR_BC(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {        
        const auto address = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);

    }};
}

FetchResult LD_A_ADDR_DE(Cpu& cpu) {

    constexpr auto cyles = 8;
    constexpr auto delta_pc = 1;
    
    return {cyles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);
    }};
}

FetchResult LD_A_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {    
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);
    }};
}

FetchResult LD_A_ADDR_A16(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto low = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
        const auto high = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        const auto address = combine_bytes(high, low);

        cpu.m_reg_a = cpu.m_memory_controller->read(address);
    }};
}

FetchResult LD_A_ADDR_C(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = 0xFF00 + cpu.m_reg_c;
        cpu.m_reg_a = cpu.m_memory_controller->read(address);
    }};
}

FetchResult LD_ADDR_A16_SP(Cpu& cpu) {

    constexpr auto cycles = 20;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {        
        const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
        const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        const auto address = combine_bytes(upper, lower);
        cpu.m_memory_controller->write(address, cpu.m_stack_ptr & 0xFF);
        cpu.m_memory_controller->write(address + 1, cpu.m_stack_ptr >> 8);
    }};
}

FetchResult LDI_ADDR_HL_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);

        address++;
        cpu.m_reg_h = (address >> 8);
        cpu.m_reg_l = (address & 0xFF);

    }};
}

FetchResult LDI_A_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);
        
        address++;
        cpu.m_reg_h = (address >> 8);
        cpu.m_reg_l = (address & 0xFF);
    }};
}

FetchResult LD_ADDR_BC_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);   
    }};
}

FetchResult LD_ADDR_DE_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        const auto address = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);    
    }};
}

FetchResult LD_B_D8(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
    }};
}

FetchResult LD_B_A(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_a;
    }};
}

FetchResult LD_B_B(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {}};
}

FetchResult LD_B_C(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_c;
    }};
}

FetchResult LD_B_D(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_d;
    }};
}

FetchResult LD_B_E(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_e;
    }};
}

FetchResult LD_B_H(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_h;
    }};
}

FetchResult LD_B_L(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = cpu.m_reg_l;
    }};
}

FetchResult LD_B_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_b = cpu.m_memory_controller->read(address);
    }};
}

FetchResult LD_C_D8(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
    }};
}

FetchResult LD_C_A(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_a;
    }};
}

FetchResult LD_C_B(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_b;
    }};
}

FetchResult LD_C_C(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {}};
}

FetchResult LD_C_D(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_d;
    }};
}

FetchResult LD_C_E(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_e;
    }};
}

FetchResult LD_C_H(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_h;
    }};
}

FetchResult LD_C_L(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_reg_l;
    }};
}

FetchResult LD_C_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {        
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_c = cpu.m_memory_controller->read(address);
    }};
}

FetchResult LD_D_D8(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
    }};
}

FetchResult LD_D_A(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_a;
    }};
}

FetchResult LD_D_B(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_b;
    }};}

FetchResult LD_D_C(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_c;
    }};}

FetchResult LD_D_D(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {}};
}

FetchResult LD_D_E(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_e;
    }};
}

FetchResult LD_D_H(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_h;
    }};
}
FetchResult LD_D_L(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = cpu.m_reg_l;
    }};
}

FetchResult LD_D_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_d = cpu.m_memory_controller->read(address);
    }};
}

FetchResult LD_E_D8(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        cpu.m_reg_e = value;
    }};
}

FetchResult LD_E_A(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_a;
    }};
}

FetchResult LD_E_B(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_b;
    }};
}

FetchResult LD_E_C(Cpu& cpu) {    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_c;
    }};
}

FetchResult LD_E_D(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_d;
    }};
}

FetchResult LD_E_E(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){}};
}

FetchResult LD_E_H(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_h;
    }};
}

FetchResult LD_E_L(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_e = cpu.m_reg_l;
    }};
}

FetchResult LD_E_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_e = cpu.m_memory_controller->read(address);
    }};
}

FetchResult LD_H_D8(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
    }};
}

FetchResult LD_H_A(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_a;
    }};
}

FetchResult LD_H_B(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_b;
    }};

}

FetchResult LD_H_C(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_c;
    }};

}

FetchResult LD_H_D(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_d;
    }};
}

FetchResult LD_H_E(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_e;
    }};
}

FetchResult LD_H_H(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {}};
}

FetchResult LD_H_L(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = cpu.m_reg_l;
    }};
}

FetchResult LD_H_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_h = cpu.m_memory_controller->read(address);
    }};    
}

FetchResult LD_L_D8(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
    }};
}

FetchResult LD_L_A(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_a;
    }};
}

FetchResult LD_L_B(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_b;
    }};
}

FetchResult LD_L_C(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_c;
    }};
}

FetchResult LD_L_D(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_d;
    }};    
}

FetchResult LD_L_E(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_e;
    }};
}

FetchResult LD_L_H(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_l = cpu.m_reg_h;
    }};
}

FetchResult LD_L_L(Cpu& cpu) {
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){}};    
}

FetchResult LD_L_ADDR_HL(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_l = cpu.m_memory_controller->read(address);
    }};
}

FetchResult LD_ADDR_HL_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);
    }};    
}

FetchResult LD_ADDR_HL_B(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_b);
    }};    
}

FetchResult LD_ADDR_HL_C(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_c);
    }};    
}

FetchResult LD_ADDR_HL_D(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_d);
    }};    
}

FetchResult LD_ADDR_HL_E(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_e);
    }};    
}

FetchResult LD_ADDR_HL_H(Cpu& cpu) {
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_h);
    }};    
}

FetchResult LD_ADDR_HL_L(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;
    
    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_l);
    }};   
}

FetchResult LD_ADDR_HL_ADDR_HL(Cpu& cpu) {    
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL ADDR HL");
}

FetchResult LD_ADDR_A16_A(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
        const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        const auto address = combine_bytes(upper, lower);

        cpu.m_memory_controller->write(address, cpu.m_reg_a);
    }};
}

FetchResult LD_BC_D16(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
        cpu.m_reg_b = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
    }};
}

FetchResult LD_DE_D16(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
        cpu.m_reg_d = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
    }};
}

FetchResult LD_HL_D16(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
        cpu.m_reg_h = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
    }};
}

FetchResult LD_HL_SPR8(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto distance = (cpu.m_memory_controller->read(cpu.m_program_counter - 1));

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
    }};
}

FetchResult LD_SP_D16(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 3;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter - 2);
        const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        const auto value = combine_bytes(upper, lower);

        cpu.m_stack_ptr = value;
        
    }};
}

FetchResult LD_SP_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_stack_ptr = value;
    }};
}

uint8_t ADD_8bit(uint8_t first, uint8_t second, uint8_t& flags) {
    
    half_carry_8bit(first, second)             ? 
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    overflows_8bit(first, second)          ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    first += second;

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);

    return first;
}

FetchResult ADD_A_D8(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult ADD_A_A(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult ADD_A_B(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult ADD_A_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult ADD_A_D(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult ADD_A_E(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult ADD_A_H(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult ADD_A_L(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult ADD_A_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = ADD_8bit(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

uint16_t ADD_16bit(uint16_t first, uint16_t second, uint8_t& flags) {
    
    overflows_16bit(first, second)                     ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    half_carry_16bit(first, second)                        ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    first += second;

    clear_bit(flags, Cpu::sub_flag);

    return first;
}

FetchResult ADD_HL_BC(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);

        const auto result = ADD_16bit(hl, bc, cpu.m_reg_f);

        cpu.m_reg_h = (result >> 8);
        cpu.m_reg_l = (result & 0xFF);
    }};
}

FetchResult ADD_HL_DE(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto de = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);

        const auto result = ADD_16bit(hl, de, cpu.m_reg_f);

        cpu.m_reg_h = (result >> 8);
        cpu.m_reg_l = (result & 0xFF);
    }};
}

FetchResult ADD_HL_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto result = ADD_16bit(hl, hl, cpu.m_reg_f);

        cpu.m_reg_h = (result >> 8);
        cpu.m_reg_l = (result & 0xFF);
    }};
}

FetchResult ADD_HL_SP(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto result = ADD_16bit(hl, cpu.m_stack_ptr, cpu.m_reg_f);

        cpu.m_reg_h = (result >> 8);
        cpu.m_reg_l = (result & 0xFF);
    }};
}

uint8_t SUB(uint8_t first, uint8_t second, uint8_t& flags) {
    
    half_borrow_8bit(first, second)            ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    underflows_8bit(first, second)         ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    first -= second;

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    set_bit(flags, Cpu::sub_flag);

    return first;
}

FetchResult SUB_D8(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        cpu.m_reg_a = SUB(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult SUB_A(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult SUB_B(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult SUB_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult SUB_D(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult SUB_E(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult SUB_H(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult SUB_L(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SUB(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult SUB_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = SUB(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

uint8_t INC(uint8_t value, uint8_t& flags) {
    
    half_carry_8bit(value, 1)                 ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    value++;

    value == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);

    return value;
}

FetchResult INC_A(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = INC(cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult INC_B(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = INC(cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult INC_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = INC(cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult INC_D(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = INC(cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult INC_E(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = INC(cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult INC_H(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = INC(cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult INC_L(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = INC(cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult INC_BC(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {        
        auto value = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        value++;

        cpu.m_reg_b = (value >> 8);
        cpu.m_reg_c = (value & 0xFF);
    }};
}

FetchResult INC_DE(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        auto value = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        value++;

        cpu.m_reg_d = (value >> 8);
        cpu.m_reg_e = (value & 0xFF);
    }};
}

FetchResult INC_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        auto value = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        value++;

        cpu.m_reg_h = (value >> 8);
        cpu.m_reg_l = (value & 0xFF);
    }};
}

FetchResult INC_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);

        value = INC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult INC_SP(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_stack_ptr++;
    }};
}

uint8_t DEC(uint8_t value, uint8_t& flags) {
    
    half_borrow_8bit(value, 1)                ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    value--;
    
    value == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    set_bit(flags, Cpu::sub_flag);

    return value;
}

FetchResult DEC_A(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = DEC(cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult DEC_B(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_b = DEC(cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult DEC_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = DEC(cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult DEC_D(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_d = DEC(cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult DEC_E(Cpu& cpu) {    
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = DEC(cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult DEC_H(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_h = DEC(cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult DEC_L(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = DEC(cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult DEC_BC(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        auto bc = combine_bytes(cpu.m_reg_b, cpu.m_reg_c);
        bc--;

        cpu.m_reg_b = (bc >> 8);
        cpu.m_reg_c = (bc & 0xFF);

    }};
}

FetchResult DEC_DE(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        auto de = combine_bytes(cpu.m_reg_d, cpu.m_reg_e);
        de--;

        cpu.m_reg_d = (de >> 8);
        cpu.m_reg_e = (de & 0xFF);
    }};
}

FetchResult DEC_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        auto hl = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        hl--;

        cpu.m_reg_h = (hl >> 8);
        cpu.m_reg_l = (hl & 0xFF);
    }};
}

FetchResult DEC_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        auto value = cpu.m_memory_controller->read(address);
        value = DEC(value, cpu.m_reg_f);
        cpu.m_memory_controller->write(address, value);
    }};
}

FetchResult DEC_SP(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_stack_ptr--;
    }};
}

FetchResult SCF(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
        set_bit(cpu.m_reg_f, Cpu::carry_flag);
    }};
}

FetchResult CCF(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
    
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

        is_set(cpu.m_reg_f, Cpu::carry_flag) ? 
            clear_bit(cpu.m_reg_f, Cpu::carry_flag) : set_bit(cpu.m_reg_f, Cpu::carry_flag);
        
    }};
}

FetchResult RRCA(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        is_set(cpu.m_reg_a, 0) ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
            : clear_bit(cpu.m_reg_f, Cpu::carry_flag);
        
        cpu.m_reg_a = rotate_right<uint8_t>(cpu.m_reg_a, 1);

        
        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }};
}

FetchResult RRA(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        const auto new_carry_flag = is_set(cpu.m_reg_a, 0);
        cpu.m_reg_a >>= 1;

        is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_a, 7) 
            : clear_bit(cpu.m_reg_a, 7);

        new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag) 
            : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);

    }};
}

FetchResult RLA(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto new_carry_flag = is_set(cpu.m_reg_a, 7);
        cpu.m_reg_a <<= 1;

        is_set(cpu.m_reg_f, Cpu::carry_flag) ? set_bit(cpu.m_reg_a, 0)
            : clear_bit(cpu.m_reg_a, 0);
        
        new_carry_flag ? set_bit(cpu.m_reg_f, Cpu::carry_flag)
            : clear_bit(cpu.m_reg_f, Cpu::carry_flag);

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }};
}

FetchResult RLCA(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        is_set(cpu.m_reg_a, 7) ? set_bit(cpu.m_reg_f, Cpu::carry_flag) : 
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);

        cpu.m_reg_a = rotate_left<uint8_t>(cpu.m_reg_a, 1);

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);
        clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }};
}

FetchResult DAA(Cpu& cpu) {    

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
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
    }};
}

FetchResult ADD_SP_R8(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto distance = (cpu.m_memory_controller->read(cpu.m_program_counter - 1));

        half_carry_8bit(cpu.m_stack_ptr, distance)     ?
            set_bit(cpu.m_reg_f, Cpu::half_carry_flag)  :
            clear_bit(cpu.m_reg_f, Cpu::half_carry_flag);


        overflows_8bit(cpu.m_stack_ptr, distance)  ? 
            set_bit(cpu.m_reg_f, Cpu::carry_flag)   :
            clear_bit(cpu.m_reg_f, Cpu::carry_flag);


        cpu.m_stack_ptr += static_cast<int8_t>(distance);

        clear_bit(cpu.m_reg_f, Cpu::zero_flag);
        clear_bit(cpu.m_reg_f, Cpu::sub_flag);

    }};    
}

uint8_t AND(uint8_t first, uint8_t second, uint8_t& flags) {
    
    first &= second;

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    set_bit(flags, Cpu::half_carry_flag);
    clear_bit(flags, Cpu::carry_flag);

    return first;
}

FetchResult AND_D8(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        cpu.m_reg_a = AND(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult AND_A(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult AND_B(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult AND_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult AND_D(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult AND_E(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult AND_H(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult AND_L(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = AND(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult AND_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = AND(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

uint8_t XOR(uint8_t first, uint8_t second, uint8_t& flags) {
    
    first ^= second;
    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);
    clear_bit(flags, Cpu::carry_flag);

    return first;
}

FetchResult XOR_D8(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        cpu.m_reg_a = XOR(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult XOR_A(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult XOR_B(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult XOR_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult XOR_D(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult XOR_E(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult XOR_H(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult XOR_L(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = XOR(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult XOR_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = XOR(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

uint8_t OR(uint8_t first, uint8_t second, uint8_t& flags) {
    
    first |= second;
    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    clear_bit(flags, Cpu::half_carry_flag);
    clear_bit(flags, Cpu::carry_flag);

    return first;
}

FetchResult OR_D8(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        cpu.m_reg_a = OR(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult OR_A(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult OR_B(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult OR_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult OR_D(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult OR_E(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult OR_H(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult OR_L(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = OR(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult OR_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = OR(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

void CP(uint8_t first, uint8_t second, uint8_t& flags) {

    underflows_8bit(first, second)         ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);

    half_borrow_8bit(first, second)            ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    (first == second) ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    set_bit(flags, Cpu::sub_flag);
}

FetchResult CP_D8(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        CP(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult CP_A(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult CP_B(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult CP_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult CP_D(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult CP_E(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
    }};
}



FetchResult CP_H(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult CP_L(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        CP(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult CP_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        CP(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult PUSH_AF(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_memory_controller->write(cpu.m_stack_ptr-1, cpu.m_reg_a);
        cpu.m_memory_controller->write(cpu.m_stack_ptr-2, cpu.m_reg_f);
        cpu.m_stack_ptr -= 2;
    }};
}

FetchResult PUSH_BC(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_memory_controller->write(cpu.m_stack_ptr-1, cpu.m_reg_b);
        cpu.m_memory_controller->write(cpu.m_stack_ptr-2, cpu.m_reg_c);
        cpu.m_stack_ptr -= 2;
    }};
}

FetchResult PUSH_DE(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_memory_controller->write(cpu.m_stack_ptr-1, cpu.m_reg_d);
        cpu.m_memory_controller->write(cpu.m_stack_ptr-2, cpu.m_reg_e);
        cpu.m_stack_ptr -= 2;
    }};
}

FetchResult PUSH_HL(Cpu& cpu) {

    constexpr auto cycles = 16;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_memory_controller->write(cpu.m_stack_ptr-1, cpu.m_reg_h);
        cpu.m_memory_controller->write(cpu.m_stack_ptr-2, cpu.m_reg_l);
        cpu.m_stack_ptr -= 2;
    }};
}

FetchResult POP_AF(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_f = cpu.m_memory_controller->read(cpu.m_stack_ptr) & 0xF0;
        cpu.m_reg_a = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
        cpu.m_stack_ptr += 2;
    }};
}

FetchResult POP_BC(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_c = cpu.m_memory_controller->read(cpu.m_stack_ptr) ;
        cpu.m_reg_b = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
        cpu.m_stack_ptr += 2;
    }};
}

FetchResult POP_DE(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_e = cpu.m_memory_controller->read(cpu.m_stack_ptr) ;
        cpu.m_reg_d = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
        cpu.m_stack_ptr += 2;
    }};
}

FetchResult POP_HL(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_stack_ptr) ;
        cpu.m_reg_h = cpu.m_memory_controller->read(cpu.m_stack_ptr + 1);
        cpu.m_stack_ptr += 2;
    }};
}

uint8_t ADC(uint8_t first, uint8_t second, uint8_t& flags) {
    
    const auto carry_value = is_set(flags, Cpu::carry_flag) ? 1 : 0;

    half_carry_8bit(first, second)       ?
        set_bit(flags, Cpu::half_carry_flag)          :
        clear_bit(flags, Cpu::half_carry_flag);

    overflows_8bit(first, second)        ?
        set_bit(flags, Cpu::carry_flag)               :
        clear_bit(flags, Cpu::carry_flag);

    first += second;

    if(!is_set(flags, Cpu::half_carry_flag)) {
        half_carry_8bit(first, carry_value)       ?
        set_bit(flags, Cpu::half_carry_flag)          :
        clear_bit(flags, Cpu::half_carry_flag);
    }

    if(!is_set(flags, Cpu::carry_flag)) {
        overflows_8bit(first, carry_value)        ?
            set_bit(flags, Cpu::carry_flag)               :
            clear_bit(flags, Cpu::carry_flag);
    }

    first += carry_value;

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    clear_bit(flags, Cpu::sub_flag);
    
    return first;
}

FetchResult ADC_A_D8(Cpu& cpu) {
    
    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        cpu.m_reg_a = ADC(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult ADC_A_A(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult ADC_A_B(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult ADC_A_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult ADC_A_D(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult ADC_A_E(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult ADC_A_H(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult ADC_A_L(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = ADC(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult ADC_A_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = ADC(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult LDH_ADDR_A8_A(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 2;

    return  {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        const uint16_t address = 0xFF00 + value;
        cpu.m_memory_controller->write(address, cpu.m_reg_a);    
    }};
}

FetchResult LDH_A_ADDR_A8(Cpu& cpu) {

    constexpr auto cycles = 12;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const uint16_t address = 0xFF00 + cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);             
    }};
}

FetchResult LD_ADDR_C_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {        
        const auto address = 0xFF00 + cpu.m_reg_c;
        cpu.m_memory_controller->write(address, cpu.m_reg_a);
    }};
}

uint8_t SBC(uint8_t first, uint8_t second, uint8_t& flags) {
    
    const auto carry_value = is_set(flags, Cpu::carry_flag) ? 1 : 0;

    half_borrow_8bit(first, second)            ?
        set_bit(flags, Cpu::half_carry_flag)  :
        clear_bit(flags, Cpu::half_carry_flag);

    underflows_8bit(first, second)         ?
        set_bit(flags, Cpu::carry_flag)   :
        clear_bit(flags, Cpu::carry_flag);
    
    first -= second;

    if(!is_set(flags, Cpu::half_carry_flag)) {
        half_borrow_8bit(first, carry_value)       ?
            set_bit(flags, Cpu::half_carry_flag)  :
            clear_bit(flags, Cpu::half_carry_flag);
    }

    if(!is_set(flags, Cpu::carry_flag)) {
        underflows_8bit(first, carry_value)         ?
            set_bit(flags, Cpu::carry_flag)   :
            clear_bit(flags, Cpu::carry_flag);
    }

    first -= carry_value;

    first == 0 ? set_bit(flags, Cpu::zero_flag) :
        clear_bit(flags, Cpu::zero_flag);

    set_bit(flags, Cpu::sub_flag);

    return first;
}

FetchResult SBC_A_D8(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 2;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto value = cpu.m_memory_controller->read(cpu.m_program_counter - 1);
        cpu.m_reg_a = SBC(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult SBC_A_A(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_a, cpu.m_reg_f);
    }};
}

FetchResult SBC_A_B(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_b, cpu.m_reg_f);
    }};
}

FetchResult SBC_A_C(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_c, cpu.m_reg_f);
    }};
}

FetchResult SBC_A_D(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_d, cpu.m_reg_f);
    }};
}

FetchResult SBC_A_E(Cpu& cpu) {
    
    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_e, cpu.m_reg_f);
    }};
}

FetchResult SBC_A_H(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_h, cpu.m_reg_f);
    }};
}

FetchResult SBC_A_L(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        cpu.m_reg_a = SBC(cpu.m_reg_a, cpu.m_reg_l, cpu.m_reg_f);
    }};
}

FetchResult SBC_A_ADDR_HL(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        const auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        const auto value = cpu.m_memory_controller->read(address);
        cpu.m_reg_a = SBC(cpu.m_reg_a, value, cpu.m_reg_f);
    }};
}

FetchResult PREFIX_CB(Cpu& cpu) {

    auto cycles = 4;
    auto delta_pc = 1;

    auto [cb_cycles, cb_delta_pc, cb_operation] = fetch_cb(cpu);
    return {cycles + cb_cycles, delta_pc + cb_delta_pc, cb_operation};
}

FetchResult LD_ADDR_HLD_A(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
            
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_memory_controller->write(address, cpu.m_reg_a);

        address--;

        cpu.m_reg_h = (address >> 8);
        cpu.m_reg_l = (address & 0xFF);

    }};
}

FetchResult LD_A_ADDR_HLD(Cpu& cpu) {

    constexpr auto cycles = 8;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu) {
        
        auto address = combine_bytes(cpu.m_reg_h, cpu.m_reg_l);
        cpu.m_reg_a = cpu.m_memory_controller->read(address);

        address--;
        cpu.m_reg_h = (address >> 8);
        cpu.m_reg_l = (address & 0xFF);

    }};
}

FetchResult CPL(Cpu& cpu) {

    constexpr auto cycles = 4;
    constexpr auto delta_pc = 1;

    return {cycles, delta_pc, [](Cpu& cpu){
        cpu.m_reg_a ^= 0xFF;

        set_bit(cpu.m_reg_f, Cpu::sub_flag);
        set_bit(cpu.m_reg_f, Cpu::half_carry_flag);
    }};
}