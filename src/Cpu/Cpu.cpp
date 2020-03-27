#include <cpu/Cpu.h>
#include <cpu/Operations.h>
#include <cpu/Opcodes.h>
#include <cpu/CBOperations.h>
#include <cpu/CBOpcodes.h>
#include <iostream>
#include <BitOperations.h>

Cpu::Cpu(MemoryBankController* memory_controller)     
    : m_memory_controller(memory_controller) 
{

    m_memory_controller->write(0xFF05, 0);
    m_memory_controller->write(0xFF06, 0);
    m_memory_controller->write(0xFF07, 0);

    m_memory_controller->write(0xFF10, 0x80);
    m_memory_controller->write(0xFF11, 0xBF);
    m_memory_controller->write(0xFF12, 0xF3);

    m_memory_controller->write(0xFF14, 0xBF);
    m_memory_controller->write(0xFF16, 0x3F);
    m_memory_controller->write(0xFF17, 0x00);
    m_memory_controller->write(0xFF19, 0xBF);

    m_memory_controller->write(0xFF1A, 0x7F);
    m_memory_controller->write(0xFF1B, 0xFF);
    m_memory_controller->write(0xFF1C, 0x9F);
    m_memory_controller->write(0xFF1E, 0xBF);

    m_memory_controller->write(0xFF20, 0xFF);
    m_memory_controller->write(0xFF21, 0x00);
    m_memory_controller->write(0xFF22, 0x00);
    m_memory_controller->write(0xFF23, 0xBF);
    m_memory_controller->write(0xFF24, 0x77);
    m_memory_controller->write(0xFF25, 0xF3);
    m_memory_controller->write(0xFF26, 0xF1);

    
    m_memory_controller->write(0xFF40, 0x91);
    m_memory_controller->write(0xFF42, 0x00);
    m_memory_controller->write(0xFF43, 0x00);
    m_memory_controller->write(0xFF45, 0x00);
    m_memory_controller->write(0xFF47, 0xFC);
    m_memory_controller->write(0xFF48, 0xFF);
    m_memory_controller->write(0xFF49, 0xFF);

    m_memory_controller->write(0xFF4A, 0x00);
    m_memory_controller->write(0xFF4B, 0x00);
    m_memory_controller->write(0xFFFF, 0x00);
}

void timer(Cpu& cpu) {

    constexpr auto div_addr = 0xFF04;
    constexpr auto tima_addr = 0xFF05;
    constexpr auto tma_addr = 0xFF06;
    constexpr auto tac_addr = 0xFF07;

    if(cpu.timer.increment_div(cpu.m_cycles)) {
        auto div_value = cpu.m_memory_controller->read(div_addr);
        div_value++;
        cpu.m_memory_controller->write(div_addr, div_value);
    }
    
    if(cpu.timer.increment_tima(cpu.m_cycles, cpu.m_memory_controller->read(tac_addr))) {
        auto tima_value = cpu.m_memory_controller->read(tima_addr);

        if(overflows_8bit(tima_value, 1)) {
            const auto tima_reset_value = cpu.m_memory_controller->read(tma_addr);
            cpu.m_memory_controller->write(tima_addr, tima_reset_value);

            auto if_register = cpu.m_memory_controller->read(0xFF0F);
            set_bit(if_register, 2);
            cpu.m_memory_controller->write(0xFF0F, if_register);

        } else {
            tima_value++;
            cpu.m_memory_controller->write(tima_addr, tima_value);
        }
    }
}

void handle_interrupts(Cpu& cpu) {
    
    const auto interrupt_request_addr = 0xFF0F;
    const auto interrupt_enable_addr = 0xFFFF;

    auto interrupt_request_register = cpu.m_memory_controller->read(interrupt_request_addr);
    auto interrupt_enable_register = cpu.m_memory_controller->read(interrupt_enable_addr);

    if(is_set(interrupt_request_register, static_cast<int>(Interrupts::V_Blank))
        && is_set(interrupt_enable_register, static_cast<int>(Interrupts::V_Blank))) {
        
        if(cpu.m_is_halted) {
            cpu.m_program_counter++;
            cpu.m_is_halted = false;
        }

        const auto pc_low = cpu.m_program_counter & 0xFF;
        const auto pc_high = cpu.m_program_counter >> 8;
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);
        cpu.m_stack_ptr -= 2;
        cpu.m_enabled_interrupts = false;
        cpu.m_program_counter = 0x40;

        clear_bit(interrupt_request_register, static_cast<int>(Interrupts::V_Blank));
        cpu.m_enabled_interrupts = false;
        cpu.m_memory_controller->write(interrupt_request_addr, interrupt_request_register);

        return;
    }

    if(is_set(interrupt_request_register, static_cast<int>(Interrupts::LCD_STAT)) 
        && is_set(interrupt_enable_register, static_cast<int>(Interrupts::LCD_STAT))) {
        
        
        if(cpu.m_is_halted) {
            cpu.m_program_counter++;
            cpu.m_is_halted = false;
        }

        const auto pc_low = cpu.m_program_counter & 0xFF;
        const auto pc_high = cpu.m_program_counter >> 8;
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);
        cpu.m_stack_ptr -= 2;
        cpu.m_enabled_interrupts = false;
        cpu.m_program_counter = 0x48;
        
        clear_bit(interrupt_request_register, static_cast<int>(Interrupts::LCD_STAT));
        cpu.m_enabled_interrupts = false;
        cpu.m_memory_controller->write(interrupt_request_addr, interrupt_request_register);

        return;
    }

    if(is_set(interrupt_request_register, static_cast<int>(Interrupts::Timer))
        && is_set(interrupt_enable_register, static_cast<int>(Interrupts::Timer))) {
        
        
        if(cpu.m_is_halted) {
            cpu.m_program_counter++;
            cpu.m_is_halted = false;
        }

        const auto pc_low = cpu.m_program_counter & 0xFF;
        const auto pc_high = cpu.m_program_counter >> 8;
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);
        cpu.m_stack_ptr -= 2;
        cpu.m_enabled_interrupts = false;
        cpu.m_program_counter = 0x50;

        clear_bit(interrupt_request_register, static_cast<int>(Interrupts::Timer));
        cpu.m_memory_controller->write(interrupt_request_addr, interrupt_request_register);

        return;
    }

    if(is_set(interrupt_request_register, static_cast<int>(Interrupts::Serial))
        && is_set(interrupt_enable_register, static_cast<int>(Interrupts::Serial))) {
        
        
        if(cpu.m_is_halted) {
            cpu.m_program_counter++;
            cpu.m_is_halted = false;
        }

        const auto pc_low = cpu.m_program_counter & 0xFF;
        const auto pc_high = cpu.m_program_counter >> 8;
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);
        cpu.m_stack_ptr -= 2;
        cpu.m_enabled_interrupts = false;
        cpu.m_program_counter = 0x58;

        clear_bit(interrupt_request_register, static_cast<int>(Interrupts::Serial));
        cpu.m_enabled_interrupts = false;
        cpu.m_memory_controller->write(interrupt_request_addr, interrupt_request_register);

        return;
    }
    
    if(is_set(interrupt_request_register, static_cast<int>(Interrupts::Joypad))
        && is_set(interrupt_enable_register, static_cast<int>(Interrupts::Joypad))) {
        

        if(cpu.m_is_halted) {
            cpu.m_program_counter++;
            cpu.m_is_halted = false;
        }

        const auto pc_low = cpu.m_program_counter & 0xFF;
        const auto pc_high = cpu.m_program_counter >> 8;
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 1, pc_high);
        cpu.m_memory_controller->write(cpu.m_stack_ptr - 2, pc_low);
        cpu.m_stack_ptr -= 2;
        cpu.m_enabled_interrupts = false;
        cpu.m_program_counter = 0x60;

        clear_bit(interrupt_request_register, static_cast<int>(Interrupts::Joypad));
        cpu.m_enabled_interrupts = false;
        cpu.m_memory_controller->write(interrupt_request_addr, interrupt_request_register);

        return;
    }

}

FetchResult fetch(Cpu& cpu) {

    const auto opcode = cpu.m_memory_controller->read(cpu.m_program_counter);

    switch(static_cast<Opcode>(opcode)) {
        case Opcode::NOP:
            return NOP(cpu);

        case Opcode::LD_BC_D16:
            return LD_BC_D16(cpu);

        case Opcode::LD_ADDR_BC_A:
            return LD_ADDR_BC_A(cpu);

        case Opcode::INC_BC:
            return INC_BC(cpu);
        
        case Opcode::INC_B:
            return INC_B(cpu);
        
        case Opcode::DEC_B:
            return DEC_B(cpu);

        case Opcode::LD_B_D8:
            return LD_B_D8(cpu);
        
        case Opcode::RLCA:
            return RLCA(cpu);

        case Opcode::LD_ADDR_A16_SP:
            return LD_ADDR_A16_SP(cpu);

        case Opcode::ADD_HL_BC:
            return ADD_HL_BC(cpu);

        case Opcode::LD_A_ADDR_BC:
            return LD_A_ADDR_BC(cpu);

        case Opcode::DEC_BC:
            return DEC_BC(cpu);
        
        case Opcode::INC_C:
            return INC_C(cpu);
        
        case Opcode::DEC_C:
            return DEC_C(cpu);
        
        case Opcode::LD_C_D8:
            return LD_C_D8(cpu);
        
        case Opcode::RRCA:
            return RRCA(cpu);
        
        case Opcode::STOP:
            return STOP(cpu);

        case Opcode::LD_DE_D16:
            return LD_DE_D16(cpu);
        
        case Opcode::LD_ADDR_DE_A:
            return LD_ADDR_DE_A(cpu);
        
        case Opcode::INC_DE:
            return INC_DE(cpu);
        
        case Opcode::INC_D:
            return INC_D(cpu);
        
        case Opcode::DEC_D:
            return DEC_D(cpu);
        
        case Opcode::LD_D_D8:
            return LD_D_D8(cpu);
        
        case Opcode::RLA:
            return RLA(cpu);

        case Opcode::JR_R8:
            return JR(cpu);
        
        case Opcode::ADD_HL_DE:
            return ADD_HL_DE(cpu);
        
        case Opcode::LD_A_ADDR_DE:
            return LD_A_ADDR_DE(cpu);
        
        case Opcode::DEC_DE:
            return DEC_DE(cpu);
        
        case Opcode::INC_E:
            return INC_E(cpu);

        case Opcode::DEC_E:
            return DEC_E(cpu);
        
        case Opcode::LD_E_D8:
            return LD_E_D8(cpu);
        
        case Opcode::RRA:
            return RRA(cpu);

        case Opcode::JR_NZ_R8:
            return JR_NZ(cpu);
        
        case Opcode::LD_HL_D16:
            return LD_HL_D16(cpu);
        
        case Opcode::LD_ADDR_HLI_A:
            return LDI_ADDR_HL_A(cpu);
        
        case Opcode::INC_HL:
            return INC_HL(cpu);

        case Opcode::INC_H:
            return INC_H(cpu);
        
        case Opcode::DEC_H:
            return DEC_H(cpu);
        
        case Opcode::LD_H_D8:
            return LD_H_D8(cpu);
        
        case Opcode::DAA:
            return DAA(cpu);
        
        case Opcode::JR_Z_R8:
            return JR_Z(cpu);

        case Opcode::ADD_HL_HL:
            return ADD_HL_HL(cpu);
        
        case Opcode::LD_A_ADDR_HLI:
            return LDI_A_ADDR_HL(cpu);
        
        case Opcode::DEC_HL:
            return DEC_HL(cpu);
        
        case Opcode::INC_L:
            return INC_L(cpu);
        
        case Opcode::DEC_L:
            return DEC_L(cpu);
        
        case Opcode::LD_L_D8:
            return LD_L_D8(cpu);
        
        case Opcode::CPL:
            return CPL(cpu);
        
        case Opcode::JR_NC_R8:
            return JR_NC(cpu);
        
        case Opcode::LD_SP_D16:
            return LD_SP_D16(cpu);
        
        case Opcode::LD_ADDR_HLD_A:
            return LD_ADDR_HLD_A(cpu);
        
        case Opcode::INC_SP:
            return INC_SP(cpu);
        
        case Opcode::INC_ADDR_HL:
            return INC_ADDR_HL(cpu);
        
        case Opcode::DEC_ADDR_HL:
            return DEC_ADDR_HL(cpu);
        
        case Opcode::LD_ADDR_HL_D8:
            return LD_A_ADDR_HL(cpu);
        
        case Opcode::SCF:
            return SCF(cpu);
        
        case Opcode::JR_C_R8:
            return JR_C(cpu);
        
        case Opcode::ADD_HL_SP:
            return ADD_HL_SP(cpu);
        
        case Opcode::LD_A_ADDR_HLD:
            return LD_A_ADDR_HLD(cpu);
        
        case Opcode::DEC_SP:
            return DEC_SP(cpu);
        
        case Opcode::INC_A:
            return INC_A(cpu);
        
        case Opcode::DEC_A:
            return DEC_A(cpu);
        
        case Opcode::LD_A_D8:
            return LD_A_D8(cpu);

        case Opcode::CCF:
            return CCF(cpu);
        
        case Opcode::LD_B_B:
            return LD_B_B(cpu);
        
        case Opcode::LD_B_C:
            return LD_B_C(cpu);
        
        case Opcode::LD_B_D:
            return LD_B_D(cpu);
        
        case Opcode::LD_B_E:
            return LD_B_E(cpu);
        
        case Opcode::LD_B_H:
            return LD_B_H(cpu);
        
        case Opcode::LD_B_L:
            return LD_B_L(cpu);
        
        case Opcode::LD_B_ADDR_HL:
            return LD_B_ADDR_HL(cpu);
        
        case Opcode::LD_B_A:
            return LD_B_A(cpu);
        
        case Opcode::LD_C_B:
            return LD_C_B(cpu);
        
        case Opcode::LD_C_C:
            return LD_C_C(cpu);
            break;
        
        case Opcode::LD_C_D:
            return LD_C_D(cpu);
        
        case Opcode::LD_C_E:
            return LD_C_E(cpu);
        
        case Opcode::LD_C_H:
            return LD_C_H(cpu);

        case Opcode::LD_C_L:
            return LD_C_L(cpu);
        
        case Opcode::LD_C_ADDR_HL:
            return LD_C_ADDR_HL(cpu);
        
        case Opcode::LD_C_A:
            return LD_C_A(cpu);

        case Opcode::LD_D_B:
            return LD_D_B(cpu);

        case Opcode::LD_D_C:
            return LD_D_C(cpu);

        case Opcode::LD_D_D:
            return LD_D_D(cpu);

        case Opcode::LD_D_E:
            return LD_D_E(cpu);

        case Opcode::LD_D_H:
            return LD_D_H(cpu);

        case Opcode::LD_D_L:
            return LD_D_L(cpu);

        case Opcode::LD_D_ADDR_HL:
            return LD_D_ADDR_HL(cpu);

        case Opcode::LD_D_A:
            return LD_D_A(cpu);

        case Opcode::LD_E_B:
            return LD_E_B(cpu);

        case Opcode::LD_E_C:
            return LD_E_C(cpu);

        case Opcode::LD_E_D:
            return LD_E_D(cpu);

        case Opcode::LD_E_E:
            return LD_E_E(cpu);

        case Opcode::LD_E_H:
            return LD_E_H(cpu);

        case Opcode::LD_E_L:
            return LD_E_L(cpu);

        case Opcode::LD_E_ADDR_HL:
            return LD_E_ADDR_HL(cpu);

        case Opcode::LD_E_A:
            return LD_E_A(cpu);

        case Opcode::LD_H_B:
            return LD_H_B(cpu);

        case Opcode::LD_H_C:
            return LD_H_C(cpu);

        case Opcode::LD_H_D:
            return LD_H_D(cpu);

        case Opcode::LD_H_E:
            return LD_H_E(cpu);

        case Opcode::LD_H_H:
            return LD_H_H(cpu);

        case Opcode::LD_H_L:
            return LD_H_L(cpu);

        case Opcode::LD_H_ADDR_HL:
            return LD_H_ADDR_HL(cpu);

        case Opcode::LD_H_A:
            return LD_H_A(cpu);

        case Opcode::LD_L_B: 
            return LD_L_B(cpu);
        
        case Opcode::LD_L_C:
            return LD_L_C(cpu);
        
        case Opcode::LD_L_D:
            return LD_L_D(cpu);
        
        case Opcode::LD_L_E:
            return LD_L_E(cpu);
        
        case Opcode::LD_L_H:
            return LD_L_H(cpu);
        
        case Opcode::LD_L_L:
            return LD_L_L(cpu);
        
        case Opcode::LD_L_ADDR_HL:
            return LD_L_ADDR_HL(cpu);
        
        case Opcode::LD_L_A:
            return LD_L_A(cpu);
        
        case Opcode::LD_ADDR_HL_B:
            return LD_ADDR_HL_B(cpu);

        case Opcode::LD_ADDR_HL_C:
            return LD_ADDR_HL_C(cpu);

        case Opcode::LD_ADDR_HL_D:
            return LD_ADDR_HL_D(cpu);
        
        case Opcode::LD_ADDR_HL_E:
            return LD_ADDR_HL_E(cpu);
        
        case Opcode::LD_ADDR_HL_H:
            return LD_ADDR_HL_H(cpu);
        
        case Opcode::LD_ADDR_HL_L:
            return LD_ADDR_HL_L(cpu);
        
        case Opcode::HALT:
            return HALT(cpu);
        
        case Opcode::LD_ADDR_HL_A:
            return LD_ADDR_HL_A(cpu);

        case Opcode::LD_A_B:
            return LD_A_B(cpu);
        
        case Opcode::LD_A_C:
            return LD_A_C(cpu);
        
        case Opcode::LD_A_D:
            return LD_A_D(cpu);
        
        case Opcode::LD_A_E:
            return LD_A_E(cpu);
        
        case Opcode::LD_A_H:
            return LD_A_H(cpu);
        
        case Opcode::LD_A_L:
            return LD_A_L(cpu);
        
        case Opcode::LD_A_ADDR_HL:
            return LD_A_ADDR_HL(cpu);
        
        case Opcode::LD_A_A:
            return LD_A_A(cpu);
        
        case Opcode::ADD_A_B:
            return ADD_A_B(cpu);
        
        case Opcode::ADD_A_C:
            return ADD_A_C(cpu);
        
        case Opcode::ADD_A_D:
            return ADD_A_D(cpu);

        case Opcode::ADD_A_E:
            return ADD_A_E(cpu);
        
        case Opcode::ADD_A_H:
            return ADD_A_H(cpu);
        
        case Opcode::ADD_A_L:
            return ADD_A_L(cpu);
        
        case Opcode::ADD_A_ADDR_HL:
            return ADD_A_ADDR_HL(cpu);
            
        case Opcode::ADD_A_A:
            return ADD_A_A(cpu);

        case Opcode::ADC_A_B:
            return ADC_A_B(cpu);

        case Opcode::ADC_A_C:
            return ADC_A_C(cpu);

        case Opcode::ADC_A_D:
            return ADC_A_D(cpu);
        
        case Opcode::ADC_A_E:
            return ADC_A_E(cpu);
        
        case Opcode::ADC_A_H:
            return ADC_A_H(cpu);
        
        case Opcode::ADC_A_L:
            return ADC_A_L(cpu);
        
        case Opcode::ADC_A_ADDR_HL:
            return ADC_A_ADDR_HL(cpu);
        
        case Opcode::ADC_A_A:
            return ADC_A_A(cpu);
        
        case Opcode::SUB_B:
            return SUB_B(cpu);
        
        case Opcode::SUB_C:
            return SUB_C(cpu);
        
        case Opcode::SUB_D:
            return SUB_D(cpu);
        
        case Opcode::SUB_E:
            return SUB_E(cpu);
        
        case Opcode::SUB_H:
            return SUB_H(cpu);
        
        case Opcode::SUB_L:
            return SUB_L(cpu);
        
        case Opcode::SUB_ADDR_HL:
            return SUB_ADDR_HL(cpu);
        
        case Opcode::SUB_A:
            return SUB_A(cpu);
        
        case Opcode::SBC_A_B:
            return SBC_A_B(cpu);
        
        case Opcode::SBC_A_C:
            return SBC_A_C(cpu);
        
        case Opcode::SBC_A_D:
            return SBC_A_D(cpu);
        
        case Opcode::SBC_A_E:
            return SBC_A_E(cpu);
        
        case Opcode::SBC_A_H:
            return SBC_A_H(cpu);
        
        case Opcode::SBC_A_L:
            return SBC_A_L(cpu);
        
        case Opcode::SBC_A_ADDR_HL:
            return SBC_A_ADDR_HL(cpu);

        case Opcode::SBC_A_A:
            return SBC_A_A(cpu);
        
        case Opcode::AND_B:
            return AND_B(cpu);
        
        case Opcode::AND_C:
            return AND_C(cpu);
        
        case Opcode::AND_D:
            return AND_D(cpu);
        
        case Opcode::AND_E:
            return AND_E(cpu);
        
        case Opcode::AND_H:
            return AND_H(cpu);
        
        case Opcode::AND_L:
            return AND_L(cpu);
        
        case Opcode::AND_ADDR_HL:
            return AND_ADDR_HL(cpu);

        case Opcode::AND_A:
            return AND_A(cpu);
        
        case Opcode::XOR_B:
            return XOR_B(cpu);
        
        case Opcode::XOR_C:
            return XOR_C(cpu);
        
        case Opcode::XOR_D:
            return XOR_D(cpu);
        
        case Opcode::XOR_E:
            return XOR_E(cpu);
        
        case Opcode::XOR_H:
            return XOR_H(cpu);
        
        case Opcode::XOR_L:
            return XOR_L(cpu);
        
        case Opcode::XOR_ADDR_HL:
            return XOR_ADDR_HL(cpu);
        
        case Opcode::XOR_A:
            return XOR_A(cpu);
        
        case Opcode::OR_B:
            return OR_B(cpu);
        
        case Opcode::OR_C:
            return OR_C(cpu);
        
        case Opcode::OR_D:
            return OR_D(cpu);
        
        case Opcode::OR_E:
            return OR_E(cpu);
        
        case Opcode::OR_H:
            return OR_H(cpu);
        
        case Opcode::OR_L:
            return OR_L(cpu);
        
        case Opcode::OR_ADDR_HL:
            return OR_ADDR_HL(cpu);
            
        case Opcode::OR_A:
            return OR_A(cpu);
        
        case Opcode::CP_B:
            return CP_B(cpu);
        
        case Opcode::CP_C:
            return CP_C(cpu);
        
        case Opcode::CP_D:
            return CP_D(cpu);
        
        case Opcode::CP_E:
            return CP_E(cpu);
        
        case Opcode::CP_H:
            return CP_H(cpu);
        
        case Opcode::CP_L:
            return CP_L(cpu);
        
        case Opcode::CP_ADDR_HL:
            return CP_ADDR_HL(cpu);
        
        case Opcode::CP_A:
            return CP_A(cpu);
        
        case Opcode::RET_NZ:
            return RET_NZ(cpu);
        
        case Opcode::POP_BC:
            return POP_BC(cpu);

        case Opcode::JP_NZ_A16:
            return JUMP_NZ(cpu);
        
        case Opcode::JP_A16:
            return JUMP(cpu);
        
        case Opcode::CALL_NZ_A16:
            return CALL_NZ(cpu);
        
        case Opcode::PUSH_BC:
            return PUSH_BC(cpu);
        
        case Opcode::ADD_A_D8:
            return ADD_A_D8(cpu);
        
        case Opcode::RST_00H:
            return RST(cpu, 0x00);
        
        case Opcode::RET_Z:
            return RET_Z(cpu);
        
        case Opcode::RET:
            return RET(cpu);
        
        case Opcode::JP_Z_A16:
            return JUMP_Z(cpu);
        
        case Opcode::PREFIX_CB:
            return PREFIX_CB(cpu);
        
        case Opcode::CALL_Z_A16: 
            return CALL_Z(cpu);
        
        case Opcode::CALL_A16:
            return CALL(cpu);
        
        case Opcode::ADC_A_D8:
            return ADC_A_D8(cpu);
        
        case Opcode::RST_08H:
            return RST(cpu, 0x08);
        
        case Opcode::RET_NC:
            return RET_NC(cpu);
        
        case Opcode::POP_DE:
            return POP_DE(cpu);
        
        case Opcode::JP_NC_A16:
            return JUMP_NC(cpu);
        
        case Opcode::CALL_NC_A16:
            return CALL_NC(cpu);
        
        case Opcode::PUSH_DE:
            return PUSH_DE(cpu);
        
        case Opcode::SUB_D8:
            return SUB_D8(cpu);
        
        case Opcode::RST_10H:
            return RST(cpu, 0x10);
        
        case Opcode::RET_C:
            return RET_C(cpu);
        
        case Opcode::RETI:
            return RETI(cpu);
        
        case Opcode::JP_C_A16:
            return JUMP_C(cpu);
        
        case Opcode::CALL_C_A16:
            return CALL_C(cpu);
        
        case Opcode::SBC_A_D8:
            return SBC_A_D8(cpu);
        
        case Opcode::RST_18H:
            return RST(cpu, 0x18);
        
        case Opcode::LDH_ADDR_A8_A:
            return LDH_ADDR_A8_A(cpu);
        
        case Opcode::POP_HL:
            return POP_HL(cpu);
        
        case Opcode::LD_ADDR_C_A:
            return LD_ADDR_C_A(cpu); 

        case Opcode::PUSH_HL:
            return PUSH_HL(cpu);
        
        case Opcode::AND_D8:
            return AND_D8(cpu);
        
        case Opcode::RST_20H:
            return RST(cpu, 0x20);
        
        case Opcode::ADD_SP_R8:
            return ADD_SP_R8(cpu);
        
        case Opcode::JP_ADDR_HL:
            return JUMP_ADDR_HL(cpu);
        
        case Opcode::LD_ADDR_A16_A:
            return LD_ADDR_A16_A(cpu);

        case Opcode::XOR_D8:
            return XOR_D8(cpu);
        
        case Opcode::RST_28H:
            return RST(cpu, 0x28);
        
        case Opcode::LDH_A_ADDR_A8:
            return LDH_A_ADDR_A8(cpu);
        
        case Opcode::POP_AF:
            return POP_AF(cpu);
        
        case Opcode::LD_A_ADDR_C:
            return LD_A_ADDR_C(cpu);
        
        case Opcode::DI:
            return DI(cpu);
        
        case Opcode::PUSH_AF:
            return PUSH_AF(cpu);
        
        case Opcode::OR_D8:
            return OR_D8(cpu);
        
        case Opcode::RST_30H:
            return RST(cpu, 0x30);
        
        case Opcode::LD_HL_SPR8:
            return LD_HL_SPR8(cpu);
        
        case Opcode::LD_SP_HL:
            return LD_SP_HL(cpu);
        
        case Opcode::LD_A_ADDR_A16:
            return LD_A_ADDR_A16(cpu);
        
        case Opcode::EI:
            return EI(cpu);
        
        case Opcode::CP_D8:
            return CP_D8(cpu);
        
        case Opcode::RST_38H:
            return RST(cpu, 0x38);

        default:
            throw UnimplementedOperation("Invalid Opcode");
            break;
    }
}

FetchResult fetch_cb(Cpu& cpu) {

     auto opcode = cpu.m_memory_controller->read(cpu.m_program_counter);
    
     switch (static_cast<CBCode>(opcode)) {
         case CBCode::RLC_B:
            RLC_B(cpu);
            break;
        
        case CBCode::RLC_C :
            RLC_C(cpu);
            break;
        
        case CBCode::RLC_D:
            RLC_D(cpu);
            break;
        
        case CBCode::RLC_E:
            RLC_E(cpu);
            break;
        
        case CBCode::RLC_H:
            RLC_H(cpu);
            break;
        
        case CBCode::RLC_L:
            RLC_L(cpu);
            break;
        
        case CBCode::RLC_ADDR_HL:
            RLC_ADDR_HL(cpu);
            break;
        
        case CBCode::RLC_A:
            RLC_A(cpu);
            break;
        
        case CBCode::RRC_B:
            RRC_B(cpu);
            break;
        
        case CBCode::RRC_C:
            RRC_C(cpu);
            break;
        
        case CBCode::RRC_D:
            RRC_D(cpu);
            break;
        
        case CBCode::RRC_E:
            RRC_E(cpu);
            break;
        
        case CBCode::RRC_H:
            RRC_H(cpu);
            break;
        
        case CBCode::RRC_L:
            RRC_L(cpu);
            break;
        
        case CBCode::RRC_ADDR_HL:
            RRC_ADDR_HL(cpu);
            break;
        
        case CBCode::RRC_A:
            RRC_A(cpu);
            break;
        
        case CBCode::RL_B:
            RL_B(cpu);
            break;
        
        case CBCode::RL_C:
            RL_C(cpu);
            break;
        
        case CBCode::RL_D:
            RL_D(cpu);
            break;
        
        case CBCode::RL_E:
            RL_E(cpu);
            break;
        
        case CBCode::RL_H:
            RL_H(cpu);
            break;
        
        case CBCode::RL_L:
            RL_L(cpu);
            break;

        case CBCode::RL_ADDR_HL:
            RL_ADDR_HL(cpu);
            break;
        
        case CBCode::RL_A:
            RL_A(cpu);
            break;

        case CBCode::RR_B:
            RR_B(cpu);
            break;

        case CBCode::RR_C:
            RR_C(cpu);
            break;
        
        case CBCode::RR_D:
            RR_D(cpu);
            break;

        case CBCode::RR_E:
            RR_E(cpu);
            break;

        case CBCode::RR_H:
            RR_H(cpu);
            break;

        case CBCode::RR_L:
            RR_L(cpu);
            break;    
            
        case CBCode::RR_ADDR_HL:
            RR_ADDR_HL(cpu);
            break;

        case CBCode::RR_A:
            RR_A(cpu);
            break;
        
        case CBCode::SLA_B:
            SLA_B(cpu);
            break;

        case CBCode::SLA_C:
            SLA_C(cpu);
            break;

        case CBCode::SLA_D:
            SLA_D(cpu);
            break;

        case CBCode::SLA_E:
            SLA_E(cpu);
            break;

        case CBCode::SLA_H:
            SLA_H(cpu);
            break;

        case CBCode::SLA_L:
            SLA_L(cpu);
            break;

        case CBCode::SLA_ADDR_HL:
            SLA_ADDR_HL(cpu);
            break;

        case CBCode::SLA_A:
            SLA_A(cpu);
            break;

        case CBCode::SRA_B:
            SRA_B(cpu);
            break;

        case CBCode::SRA_C:
            SRA_C(cpu);
            break;

        case CBCode::SRA_D:
            SRA_D(cpu);
            break;

        case CBCode::SRA_E:
            SRA_E(cpu);
            break;

        case CBCode::SRA_H:
            SRA_H(cpu);
            break;

        case CBCode::SRA_L:
            SRA_L(cpu);
            break;

        case CBCode::SRA_ADDR_HL:
            SRA_ADDR_HL(cpu);
            break;
        
        case CBCode::SRA_A:
            SRA_A(cpu);
            break;
        
        case CBCode::SWAP_B:
            SWAP_B(cpu);
            break;

        case CBCode::SWAP_C:
            SWAP_C(cpu);
            break;

        case CBCode::SWAP_D:
            SWAP_D(cpu);
            break;

        case CBCode::SWAP_E:
            SWAP_E(cpu);
            break;

        case CBCode::SWAP_H:
            SWAP_H(cpu);
            break;

        case CBCode::SWAP_L:
            SWAP_L(cpu);
            break;

        case CBCode::SWAP_ADDR_HL:
            SWAP_ADDR_HL(cpu);
            break;

        case CBCode::SWAP_A:
            SWAP_A(cpu);
            break;
        
        case CBCode::SRL_B:
            SRL_B(cpu);            
            break;

        case CBCode::SRL_C:
            SRL_C(cpu);
            break;

        case CBCode::SRL_D:
            SRL_D(cpu);
            break;

        case CBCode::SRL_E:
            SRL_E(cpu);
            break;

        case CBCode::SRL_H:
            SRL_H(cpu);
            break;

        case CBCode::SRL_L:
            SRL_L(cpu); 
            break;

        case CBCode::SRL_ADDR_HL:
            SRL_ADDR_HL(cpu);
            break;

        case CBCode::SRL_A:
            SRL_A(cpu);
            break;
        
        case CBCode::BIT_0_B:
            BIT_0_B(cpu);
            break;
        
        case CBCode::BIT_0_C:
            BIT_0_C(cpu);
            break;

        case CBCode::BIT_0_D:
            BIT_0_D(cpu);
            break;

        case CBCode::BIT_0_E:
            BIT_0_E(cpu);
            break;

        case CBCode::BIT_0_H:
            BIT_0_H(cpu);
            break;

        case CBCode::BIT_0_L:
            BIT_0_L(cpu);
            break;

        case CBCode::BIT_0_ADDR_HL:
            BIT_0_ADDR_HL(cpu);
            break;

        case CBCode::BIT_0_A:
            BIT_0_A(cpu);
            break;

        case CBCode::BIT_1_B:
            BIT_1_B(cpu);
            break;
        
        case CBCode::BIT_1_C:
            BIT_1_C(cpu);
            break;

        case CBCode::BIT_1_D:
            BIT_1_D(cpu);
            break;

        case CBCode::BIT_1_E:
            BIT_1_E(cpu);
            break;

        case CBCode::BIT_1_H:
            BIT_1_H(cpu);
            break;

        case CBCode::BIT_1_L:
            BIT_1_L(cpu);
            break;

        case CBCode::BIT_1_ADDR_HL:
            BIT_1_ADDR_HL(cpu);
            break;

        case CBCode::BIT_1_A:
            BIT_1_A(cpu);
            break;

        case CBCode::BIT_2_B:
            BIT_2_B(cpu);
            break;
        
        case CBCode::BIT_2_C:
            BIT_2_C(cpu);
            break;

        case CBCode::BIT_2_D:
            BIT_2_D(cpu);
            break;

        case CBCode::BIT_2_E:
            BIT_2_E(cpu);
            break;

        case CBCode::BIT_2_H:
            BIT_2_H(cpu);
            break;

        case CBCode::BIT_2_L:
            BIT_2_L(cpu);
            break;

        case CBCode::BIT_2_ADDR_HL:
            BIT_2_ADDR_HL(cpu);
            break;

        case CBCode::BIT_2_A:
            BIT_2_A(cpu);
            break;

        case CBCode::BIT_3_B:
            BIT_3_B(cpu);
            break;
        
        case CBCode::BIT_3_C:
            BIT_3_C(cpu);
            break;

        case CBCode::BIT_3_D:
            BIT_3_D(cpu);
            break;

        case CBCode::BIT_3_E:
            BIT_3_E(cpu);
            break;

        case CBCode::BIT_3_H:
            BIT_3_H(cpu);
            break;

        case CBCode::BIT_3_L:
            BIT_3_L(cpu);
            break;

        case CBCode::BIT_3_ADDR_HL:
            BIT_3_ADDR_HL(cpu);
            break;

        case CBCode::BIT_3_A:
            BIT_3_A(cpu);
            break;
       
       case CBCode::BIT_4_B:
            BIT_4_B(cpu);
            break;
        
        case CBCode::BIT_4_C:
            BIT_4_C(cpu);
            break;

        case CBCode::BIT_4_D:
            BIT_4_D(cpu);
            break;

        case CBCode::BIT_4_E:
            BIT_4_E(cpu);
            break;

        case CBCode::BIT_4_H:
            BIT_4_H(cpu);
            break;

        case CBCode::BIT_4_L:
            BIT_4_L(cpu);
            break;

        case CBCode::BIT_4_ADDR_HL:
            BIT_4_ADDR_HL(cpu);
            break;

        case CBCode::BIT_4_A:
            BIT_4_A(cpu);
            break;

       case CBCode::BIT_5_B:
            BIT_5_B(cpu);
            break;
        
        case CBCode::BIT_5_C:
            BIT_5_C(cpu);
            break;

        case CBCode::BIT_5_D:
            BIT_5_D(cpu);
            break;

        case CBCode::BIT_5_E:
            BIT_5_E(cpu);
            break;

        case CBCode::BIT_5_H:
            BIT_5_H(cpu);
            break;

        case CBCode::BIT_5_L:
            BIT_5_L(cpu);
            break;

        case CBCode::BIT_5_ADDR_HL:
            BIT_5_ADDR_HL(cpu);
            break;

        case CBCode::BIT_5_A:
            BIT_5_A(cpu);
            break;
        
        case CBCode::BIT_6_B:
            BIT_6_B(cpu);
            break;
        
        case CBCode::BIT_6_C:
            BIT_6_C(cpu);
            break;

        case CBCode::BIT_6_D:
            BIT_6_D(cpu);
            break;

        case CBCode::BIT_6_E:
            BIT_6_E(cpu);
            break;

        case CBCode::BIT_6_H:
            BIT_6_H(cpu);
            break;

        case CBCode::BIT_6_L:
            BIT_6_L(cpu);
            break;

        case CBCode::BIT_6_ADDR_HL:
            BIT_6_ADDR_HL(cpu);
            break;

        case CBCode::BIT_6_A:
            BIT_6_A(cpu);
            break;

        case CBCode::BIT_7_B:
            BIT_7_B(cpu);
            break;
        
        case CBCode::BIT_7_C:
            BIT_7_C(cpu);
            break;

        case CBCode::BIT_7_D:
            BIT_7_D(cpu);
            break;

        case CBCode::BIT_7_E:
            BIT_7_E(cpu);
            break;

        case CBCode::BIT_7_H:
            BIT_7_H(cpu);
            break;

        case CBCode::BIT_7_L:
            BIT_7_L(cpu);
            break;

        case CBCode::BIT_7_ADDR_HL:
            BIT_7_ADDR_HL(cpu);
            break;

        case CBCode::BIT_7_A:
            BIT_7_A(cpu);
            break;
        
        case CBCode::RES_0_B:
            RES_0_B(cpu);
            break;

        case CBCode::RES_0_C:
            RES_0_C(cpu);
            break;

        case CBCode::RES_0_D:
            RES_0_D(cpu);
            break;

        case CBCode::RES_0_E:
            RES_0_E(cpu);
            break;

        case CBCode::RES_0_H:
            RES_0_H(cpu);
            break;

        case CBCode::RES_0_L:
            RES_0_L(cpu);
            break;

        case CBCode::RES_0_ADDR_HL:
            RES_0_ADDR_HL(cpu);
            break;

        case CBCode::RES_0_A:
            RES_0_A(cpu);
            break;
            
        case CBCode::RES_1_B:
            RES_1_B(cpu);
            break;

        case CBCode::RES_1_C:
            RES_1_C(cpu);
            break;

        case CBCode::RES_1_D:
            RES_1_D(cpu);
            break;

        case CBCode::RES_1_E:
            RES_1_E(cpu);
            break;

        case CBCode::RES_1_H:
            RES_1_H(cpu);
            break;

        case CBCode::RES_1_L:
            RES_1_L(cpu);
            break;

        case CBCode::RES_1_ADDR_HL:
            RES_1_ADDR_HL(cpu);
            break;

        case CBCode::RES_1_A:
            RES_1_A(cpu);
            break;
        
        case CBCode::RES_2_B:
            RES_2_B(cpu);
            break;

        case CBCode::RES_2_C:
            RES_2_C(cpu);
            break;

        case CBCode::RES_2_D:
            RES_2_D(cpu);
            break;

        case CBCode::RES_2_E:
            RES_2_E(cpu);
            break;

        case CBCode::RES_2_H:
            RES_2_H(cpu);
            break;

        case CBCode::RES_2_L:
            RES_2_L(cpu);
            break;

        case CBCode::RES_2_ADDR_HL:
            RES_2_ADDR_HL(cpu);
            break;

        case CBCode::RES_2_A:
            RES_2_A(cpu);
            break;

        case CBCode::RES_3_B:
            RES_3_B(cpu);
            break;

        case CBCode::RES_3_C:
            RES_3_C(cpu);
            break;

        case CBCode::RES_3_D:
            RES_3_D(cpu);
            break;

        case CBCode::RES_3_E:
            RES_3_E(cpu);
            break;

        case CBCode::RES_3_H:
            RES_3_H(cpu);
            break;

        case CBCode::RES_3_L:
            RES_3_L(cpu);
            break;

        case CBCode::RES_3_ADDR_HL:
            RES_3_ADDR_HL(cpu);
            break;

        case CBCode::RES_3_A:
            RES_3_A(cpu);
            break;

        case CBCode::RES_4_B:
            RES_4_B(cpu);
            break;

        case CBCode::RES_4_C:
            RES_4_C(cpu);
            break;

        case CBCode::RES_4_D:
            RES_4_D(cpu);
            break;

        case CBCode::RES_4_E:
            RES_4_E(cpu);
            break;

        case CBCode::RES_4_H:
            RES_4_H(cpu);
            break;

        case CBCode::RES_4_L:
            RES_4_L(cpu);
            break;

        case CBCode::RES_4_ADDR_HL:
            RES_4_ADDR_HL(cpu);
            break;

        case CBCode::RES_4_A:
            RES_4_A(cpu);
            break;
        
        case CBCode::RES_5_B:
            RES_5_B(cpu);
            break;

        case CBCode::RES_5_C:
            RES_5_C(cpu);
            break;

        case CBCode::RES_5_D:
            RES_5_D(cpu);
            break;

        case CBCode::RES_5_E:
            RES_5_E(cpu);
            break;

        case CBCode::RES_5_H:
            RES_5_H(cpu);
            break;

        case CBCode::RES_5_L:
            RES_5_L(cpu);
            break;

        case CBCode::RES_5_ADDR_HL:
            RES_5_ADDR_HL(cpu);
            break;

        case CBCode::RES_5_A:
            RES_5_A(cpu);
            break;
        
        case CBCode::RES_6_B:
            RES_6_B(cpu);
            break;

        case CBCode::RES_6_C:
            RES_6_C(cpu);
            break;

        case CBCode::RES_6_D:
            RES_6_D(cpu);
            break;

        case CBCode::RES_6_E:
            RES_6_E(cpu);
            break;

        case CBCode::RES_6_H:
            RES_6_H(cpu);
            break;

        case CBCode::RES_6_L:
            RES_6_L(cpu);
            break;

        case CBCode::RES_6_ADDR_HL:
            RES_6_ADDR_HL(cpu);
            break;

        case CBCode::RES_6_A:
            RES_6_A(cpu);
            break;
        
        case CBCode::RES_7_B:
            RES_7_B(cpu);
            break;

        case CBCode::RES_7_C:
            RES_7_C(cpu);
            break;

        case CBCode::RES_7_D:
            RES_7_D(cpu);
            break;

        case CBCode::RES_7_E:
            RES_7_E(cpu);
            break;

        case CBCode::RES_7_H:
            RES_7_H(cpu);
            break;

        case CBCode::RES_7_L:
            RES_7_L(cpu);
            break;

        case CBCode::RES_7_ADDR_HL:
            RES_7_ADDR_HL(cpu);
            break;

        case CBCode::RES_7_A:
            RES_7_A(cpu);
            break;
        
        case CBCode::SET_0_B:
            SET_0_B(cpu);
            break;

        case CBCode::SET_0_C:
            SET_0_C(cpu);
            break;

        case CBCode::SET_0_D:
            SET_0_D(cpu);
            break;

        case CBCode::SET_0_E:
            SET_0_E(cpu);
            break;

        case CBCode::SET_0_H:
            SET_0_H(cpu);
            break;

        case CBCode::SET_0_L:
            SET_0_L(cpu);
            break;

        case CBCode::SET_0_ADDR_HL:
            SET_0_ADDR_HL(cpu);
            break;

        case CBCode::SET_0_A:
            SET_0_A(cpu);
            break;

        case CBCode::SET_1_B:
            SET_1_B(cpu);
            break;

        case CBCode::SET_1_C:
            SET_1_C(cpu);
            break;

        case CBCode::SET_1_D:
            SET_1_D(cpu);
            break;

        case CBCode::SET_1_E:
            SET_1_E(cpu);
            break;

        case CBCode::SET_1_H:
            SET_1_H(cpu);
            break;

        case CBCode::SET_1_L:
            SET_1_L(cpu);
            break;

        case CBCode::SET_1_ADDR_HL:
            SET_1_ADDR_HL(cpu);
            break;

        case CBCode::SET_1_A:
            SET_1_A(cpu);
            break;
                
        case CBCode::SET_2_B:
            SET_2_B(cpu);
            break;

        case CBCode::SET_2_C:
            SET_2_C(cpu);
            break;

        case CBCode::SET_2_D:
            SET_2_D(cpu);
            break;

        case CBCode::SET_2_E:
            SET_2_E(cpu);
            break;

        case CBCode::SET_2_H:
            SET_2_H(cpu);
            break;

        case CBCode::SET_2_L:
            SET_2_L(cpu);
            break;

        case CBCode::SET_2_ADDR_HL:
            SET_2_ADDR_HL(cpu);
            break;

        case CBCode::SET_2_A:
            SET_2_A(cpu);
            break;

        case CBCode::SET_3_B:
            SET_3_B(cpu);
            break;

        case CBCode::SET_3_C:
            SET_3_C(cpu);
            break;

        case CBCode::SET_3_D:
            SET_3_D(cpu);
            break;

        case CBCode::SET_3_E:
            SET_3_E(cpu);
            break;

        case CBCode::SET_3_H:
            SET_3_H(cpu);
            break;

        case CBCode::SET_3_L:
            SET_3_L(cpu);
            break;

        case CBCode::SET_3_ADDR_HL:
            SET_3_ADDR_HL(cpu);
            break;

        case CBCode::SET_3_A:
            SET_3_A(cpu);
            break;
        
        case CBCode::SET_4_B:
            SET_4_B(cpu);
            break;

        case CBCode::SET_4_C:
            SET_4_C(cpu);
            break;

        case CBCode::SET_4_D:
            SET_4_D(cpu);
            break;

        case CBCode::SET_4_E:
            SET_4_E(cpu);
            break;

        case CBCode::SET_4_H:
            SET_4_H(cpu);
            break;

        case CBCode::SET_4_L:
            SET_4_L(cpu);
            break;

        case CBCode::SET_4_ADDR_HL:
            SET_4_ADDR_HL(cpu);
            break;

        case CBCode::SET_4_A:
            SET_4_A(cpu);
            break;
        
        case CBCode::SET_5_B:
            SET_5_B(cpu);
            break;

        case CBCode::SET_5_C:
            SET_5_C(cpu);
            break;

        case CBCode::SET_5_D:
            SET_5_D(cpu);
            break;

        case CBCode::SET_5_E:
            SET_5_E(cpu);
            break;

        case CBCode::SET_5_H:
            SET_5_H(cpu);
            break;

        case CBCode::SET_5_L:
            SET_5_L(cpu);
            break;

        case CBCode::SET_5_ADDR_HL:
            SET_5_ADDR_HL(cpu);
            break;

        case CBCode::SET_5_A:
            SET_5_A(cpu);
            break;
        
        case CBCode::SET_6_B:
            SET_6_B(cpu);
            break;

        case CBCode::SET_6_C:
            SET_6_C(cpu);
            break;

        case CBCode::SET_6_D:
            SET_6_D(cpu);
            break;

        case CBCode::SET_6_E:
            SET_6_E(cpu);
            break;

        case CBCode::SET_6_H:
            SET_6_H(cpu);
            break;

        case CBCode::SET_6_L:
            SET_6_L(cpu);
            break;

        case CBCode::SET_6_ADDR_HL:
            SET_6_ADDR_HL(cpu);
            break;

        case CBCode::SET_6_A:
            SET_6_A(cpu);
            break;
        
        case CBCode::SET_7_B:
            SET_7_B(cpu);
            break;

        case CBCode::SET_7_C:
            SET_7_C(cpu);
            break;

        case CBCode::SET_7_D:
            SET_7_D(cpu);
            break;

        case CBCode::SET_7_E:
            SET_7_E(cpu);
            break;

        case CBCode::SET_7_H:
            SET_7_H(cpu);
            break;

        case CBCode::SET_7_L:
            SET_7_L(cpu);
            break;

        case CBCode::SET_7_ADDR_HL:
            SET_7_ADDR_HL(cpu);
            break;

        case CBCode::SET_7_A:
            SET_7_A(cpu);
            break;
            
        default:
            throw UnimplementedOperation("Unimplemented CB Code\n");
            break;
     }
 }