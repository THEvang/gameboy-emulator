#include <tuple>
#include "Cpu/Operations.hpp"

#include "BitOperations.hpp"
#include "Cpu/Cpu.hpp"
#include "Cpu/Interpreter.hpp"
#include "Cpu/CBOpcodes.hpp"
#include "Memory/Memory_Controller.hpp"

Instruction NOP() {
    return {[](Cpu&, Operand&) { return 4;}, implied};
}

Instruction STOP() {
    return {[](Cpu&, Operand&){ return 4;}, implied};
}

Instruction HALT() {
    return {[](Cpu& cpu, Operand&) {
        
        constexpr auto cycles = 4;
        if(cpu.m_interrupts_enabled) {
            cpu.m_is_halted = true;
        } else {

            const uint16_t interrupt_request_addr = 0xFF0F;
            const uint16_t interrupt_enable_addr = 0xFFFF;

            const auto interrupt_request = cpu.m_memory_controller->read(interrupt_request_addr);
            const auto interrupt_enable = cpu.m_memory_controller->read(interrupt_enable_addr);

            if((interrupt_request & interrupt_enable & 0x1Fu) == 0) {
                cpu.m_is_halted = true;
            } else {
                throw UnimplementedOperation("HALT BUG");
            }
        }
        return cycles;
    }, implied};
}

Instruction RST(uint8_t address) {
    return {[address](Cpu& cpu, Operand&){
        
        const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
        const auto pc_low =  static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);

        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);

        cpu.m_program_counter = combine_bytes(0x00, address);
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }, implied};
}

Instruction DI() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_should_disable_interrupts = true;
        return 4;
    }, implied};
}

Instruction EI() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_should_enable_interrupts = true;
        return 4;
    }, implied};
}


int jump_relative(Cpu& cpu, Operand& op) {
    const auto distance = static_cast<int8_t>(std::get<uint8_t>(op));
    cpu.m_program_counter = static_cast<uint16_t>(cpu.m_program_counter + distance);
    return 12;
}

Instruction JR() {
    return {[](Cpu& cpu, Operand& op) {
        return jump_relative(cpu, op);
    }, immediate};
}

Instruction JR_NZ() {
    return {[](Cpu& cpu, Operand& op) {
        return !cpu.test_flag(Cpu::Flag::Zero) ? jump_relative(cpu, op) : 8;
    }, immediate};
}

Instruction JR_Z() {
    return {[](Cpu& cpu, Operand& op) {
        return cpu.test_flag(Cpu::Flag::Zero) ? jump_relative(cpu, op) : 8;
    }, immediate};
}

Instruction JR_NC() {
    return {[](Cpu& cpu, Operand& op) {
        return !cpu.test_flag(Cpu::Flag::Carry) ? jump_relative(cpu, op) : 8;
    }, immediate};
}

Instruction JR_C() {
    return {[](Cpu& cpu, Operand& op) {
        return cpu.test_flag(Cpu::Flag::Carry) ? jump_relative(cpu, op) : 8;
    }, immediate};
}

int ret(Cpu& cpu) {            
    const auto pc_low = cpu.m_memory_controller->read(cpu.m_stack_ptr);
    const auto pc_high = cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1));
    
    cpu.m_program_counter = combine_bytes(pc_high, pc_low);
    cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
    constexpr auto cycles = 16;
    return cycles;
}

Instruction RET() {
    return {[](Cpu& cpu, Operand&) {
        return ret(cpu);
    }, implied};
}

Instruction RET_NZ() {
    return {[](Cpu& cpu, Operand&) {        
        return !cpu.test_flag(Cpu::Flag::Zero) ? ret(cpu) : 8;
    }, implied};
}

Instruction RET_Z() {
    return {[](Cpu& cpu, Operand&) {
        return cpu.test_flag(Cpu::Flag::Zero) ? ret(cpu) : 8; 
    }, implied};
}

Instruction RET_NC() {
    return {[](Cpu& cpu, Operand&) {
        return !cpu.test_flag(Cpu::Flag::Carry) ? ret(cpu) : 8;
    }, implied};
}

Instruction RET_C() {
    return {[](Cpu& cpu, Operand&) {
       return cpu.test_flag(Cpu::Flag::Carry) ? ret(cpu) : 8;
    }, implied};
}

Instruction RETI() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_interrupts_enabled = true;
        return ret(cpu);
    }, implied};
}

int jump(Cpu& cpu, Operand& op) {
    const auto address = std::get<uint16_t>(op);
    cpu.m_program_counter = address; 
    constexpr auto cycles = 16;
    return cycles;
}

Instruction JUMP() {
    return {[](Cpu& cpu, Operand& op) {
        return jump(cpu, op);
    }, immediate_extended};
}

Instruction JUMP_NZ() {
    return {[](Cpu& cpu, Operand& op) {        
        return !cpu.test_flag(Cpu::Flag::Zero) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_Z() {
    return {[](Cpu& cpu, Operand& op) {
        return cpu.test_flag(Cpu::Flag::Zero) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_NC() {
    return {[](Cpu& cpu, Operand& op) {
        return !cpu.test_flag(Cpu::Flag::Carry) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_C() {
    return {[](Cpu& cpu, Operand& op) {
        return cpu.test_flag(Cpu::Flag::Carry) ? jump(cpu, op) : 12;
    }, immediate_extended};
}

Instruction JUMP_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = cpu.get({Cpu::Register::H, Cpu::Register::L});
        cpu.m_program_counter = address;
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

int call(Cpu& cpu, Operand& op) {

    const auto pc_high = static_cast<uint8_t>(cpu.m_program_counter >> 8u);
    const auto pc_low = static_cast<uint8_t>(cpu.m_program_counter & 0xFFu);
    
    cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 1), pc_high);
    cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr - 2), pc_low);
    cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr -2);
    
     cpu.m_program_counter = std::get<uint16_t>(op);

    constexpr auto cycles = 24;
    return cycles;
}

Instruction CALL() {
    return {[](Cpu& cpu, Operand& op) {
        return call(cpu, op);
    }, immediate_extended};
}

Instruction CALL_NZ() {
    return {[](Cpu& cpu, Operand& op) {
        return !cpu.test_flag(Cpu::Flag::Zero) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction CALL_Z() {
    return {[](Cpu& cpu, Operand& op) {
        return cpu.test_flag(Cpu::Flag::Zero) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction CALL_NC() {
    return {[](Cpu& cpu, Operand& op) {
        return !cpu.test_flag(Cpu::Flag::Carry) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction CALL_C() {
    return {[](Cpu& cpu, Operand& op) {
        return cpu.test_flag(Cpu::Flag::Carry) ? call(cpu, op) : 12;
    }, immediate_extended};
}

Instruction LD_R_R(Cpu::Register dst, Cpu::Register src) {
    return {[dst, src](Cpu& cpu, Operand&){
        cpu.set(dst, cpu.get(src));
        return 4;
    }, implied};
}

Instruction LD_R_D8(Cpu::Register dst) {
    return {[dst](Cpu& cpu, Operand& op) {
        cpu.set(dst, std::get<uint8_t>(op));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction LD_A_ADDR_RR(std::pair<Cpu::Register, Cpu::Register> rr) {
    return {[rr](Cpu& cpu, Operand&) {        
        const auto address = cpu.get(rr);
        cpu.set(Cpu::Register::A, cpu.m_memory_controller->read(address));
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_A_ADDR_A16() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.set(Cpu::Register::A, std::get<uint8_t>(op));
        constexpr auto cycles = 16;
        return cycles;
    }, extended_address};
}

Instruction LD_A_ADDR_C() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = static_cast<uint16_t>(0xFF00 + cpu.get(Cpu::Register::C));
        cpu.set(Cpu::Register::A, cpu.m_memory_controller->read(address));

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_ADDR_A16_SP() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = std::get<uint16_t>(op);        
        cpu.m_memory_controller->write(address, static_cast<uint8_t>(cpu.m_stack_ptr & 0xFFu));
        cpu.m_memory_controller->write(static_cast<uint16_t>(address + 1), static_cast<uint8_t>(cpu.m_stack_ptr >> 8u));
        constexpr auto cycles = 20;
        return cycles;
    }, immediate_extended};
}

Instruction LDI_ADDR_HL_A() {
    return {[](Cpu& cpu, Operand&) {
        auto address = cpu.get({Cpu::Register::H, Cpu::Register::L});
        cpu.m_memory_controller->write(address, cpu.get(Cpu::Register::A));

        address++;
        cpu.set(Cpu::Register::H, static_cast<uint8_t>(address >> 8u));
        cpu.set(Cpu::Register::L, static_cast<uint8_t>(address & 0xFFu));

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LDI_A_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        auto address = cpu.get({Cpu::Register::H, Cpu::Register::L});
        cpu.set(Cpu::Register::A, cpu.m_memory_controller->read(address));
        
        address++;
        cpu.set(Cpu::Register::H, static_cast<uint8_t>(address >> 8u));
        cpu.set(Cpu::Register::L, static_cast<uint8_t>(address & 0xFFu));

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_ADDR_RR_A(std::pair<Cpu::Register, Cpu::Register> rr) {
    return {[rr](Cpu& cpu, Operand&) {
        const auto address = cpu.get(rr);
        cpu.m_memory_controller->write(address, cpu.get(Cpu::Register::A));   
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_R_ADDR_HL(Cpu::Register dst) {
    return {[dst](Cpu& cpu, Operand& op) {
        cpu.set(dst, std::get<uint8_t>(op));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LD_ADDR_HL_R(Cpu::Register r) {
    return {[r](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        cpu.m_memory_controller->write(address, cpu.get(r));
        constexpr auto cycles = 8;
        return cycles;
    }, implied};    
}

Instruction LD_ADDR_HL_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        const auto value = std::get<uint8_t>(op);
        cpu.m_memory_controller->write(address, value);
        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LD_ADDR_HL_ADDR_HL() {    
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL ADDR HL");
}

Instruction LD_ADDR_A16_A() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = std::get<uint16_t>(op);
        cpu.m_memory_controller->write(address, cpu.get(Cpu::Register::A));
        constexpr auto cycles = 16;
        return cycles;
    }, immediate_extended};
}

Instruction LD_RR_D16(std::pair<Cpu::Register, Cpu::Register> rr) {
    return {[rr](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint16_t>(op);

        cpu.set(rr.second, static_cast<uint8_t>(value & 0xFFu));
        cpu.set(rr.first, static_cast<uint8_t>(value >> 8u));

        constexpr auto cycles = 12;
        return cycles;
    }, immediate_extended};
}

Instruction LD_HL_SPR8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto distance = std::get<uint8_t>(op);

        half_carry_8bit(static_cast<uint8_t>(cpu.m_stack_ptr), distance)     ?
            cpu.set_flag(Cpu::Flag::Half_Carry)  :
            cpu.clear_flag(Cpu::Flag::Half_Carry);


        overflows_8bit(static_cast<uint8_t>(cpu.m_stack_ptr), distance)  ? 
            cpu.set_flag(Cpu::Flag::Carry)   :
            cpu.clear_flag(Cpu::Flag::Carry);

        const auto result = static_cast<uint16_t>(cpu.m_stack_ptr + static_cast<int8_t>(distance));
        cpu.set(Cpu::Register::H, static_cast<uint8_t>(result >> 8u));
        cpu.set(Cpu::Register::L, static_cast<uint8_t>(result & 0xFFu));

        cpu.clear_flag(Cpu::Flag::Zero);
        cpu.clear_flag(Cpu::Flag::Sub);

        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LD_SP_D16() {
    return {[](Cpu& cpu, Operand& op) {
        cpu.m_stack_ptr = std::get<uint16_t>(op);
        constexpr auto cycles = 12;
        return cycles;
    }, immediate_extended};
}

Instruction LD_SP_HL() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_stack_ptr =  combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

uint8_t ADD_8bit(uint8_t first, uint8_t second, uint8_t& flags) {
    
    half_carry_8bit(first, second)             ? 
        set_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry))  :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    overflows_8bit(first, second)          ?
        set_bit(flags, Cpu::to_index(Cpu::Flag::Carry))   :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));

    first = static_cast<uint8_t>(first + second);

    first == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));

    return first;
}

Instruction ADD_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);

        cpu.set(Cpu::Register::A, ADD_8bit(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction ADD_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {

        const auto a = cpu.get(Cpu::Register::A);
        const auto r = cpu.get(src);
        
        cpu.set(Cpu::Register::A, ADD_8bit(a, r, cpu.get(Cpu::Register::F)));

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, ADD_8bit(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

uint16_t ADD_16bit(uint16_t first, uint16_t second, uint8_t& flags) {
    
    overflows_16bit(first, second)                     ?
        set_bit(flags, Cpu::to_index(Cpu::Flag::Carry))   :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));

    half_carry_16bit(first, second)                        ?
        set_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry))  :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    first = static_cast<uint16_t>(first + second);

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));

    return first;
}

Instruction ADD_HL_RR(std::pair<Cpu::Register, Cpu::Register> rr) {
    return {[rr](Cpu& cpu, Operand&) {
        
        const auto hl = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        const auto value = combine_bytes(cpu.get(rr.first), cpu.get(rr.second));

        const auto result = ADD_16bit(hl, value, cpu.get(Cpu::Register::F));

        cpu.set(Cpu::Register::H, static_cast<uint8_t>(result >> 8u));
        cpu.set(Cpu::Register::L, static_cast<uint8_t>(result & 0xFFu));

        constexpr auto cycles = 8;
        return cycles;
    }, implied}; 
}

Instruction ADD_HL_SP() {
    return {[](Cpu& cpu, Operand&) {
        
        const auto hl = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        const auto result = ADD_16bit(hl, cpu.m_stack_ptr, cpu.get(Cpu::Register::F));

        cpu.set(Cpu::Register::H, static_cast<uint8_t>(result >> 8u));
        cpu.set(Cpu::Register::L, static_cast<uint8_t>(result & 0xFFu));

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

uint8_t SUB(uint8_t first, uint8_t second, uint8_t& flags) {
    
    half_borrow_8bit(first, second)            ?
        set_bit(flags,   Cpu::to_index(Cpu::Flag::Half_Carry))  :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    underflows_8bit(first, second)         ?
        set_bit(flags,   Cpu::to_index(Cpu::Flag::Carry))   :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));

    first = static_cast<uint8_t>(first - second);

    first == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags,        Cpu::to_index(Cpu::Flag::Zero));

    set_bit(flags, Cpu::to_index(Cpu::Flag::Sub));

    return first;
}

Instruction SUB_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, SUB(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction SUB_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto acc = cpu.get(Cpu::Register::A);
        const auto r = cpu.get(src);
        
        cpu.set(Cpu::Register::A, SUB(acc, r, cpu.get(Cpu::Register::F)));

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SUB_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, SUB(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

uint8_t INC(uint8_t value, uint8_t& flags) {
    
    half_carry_8bit(value, 1)                 ?
        set_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry))  :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    value++;

    value == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));

    return value;
}

Instruction INC_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {
        auto r = cpu.get(src);
        cpu.set(src, INC(r, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction INC_RR(std::pair<Cpu::Register, Cpu::Register> rr) {
    return {[rr](Cpu& cpu, Operand&) {        
        auto value = combine_bytes(cpu.get(rr.first), cpu.get(rr.second));
        value++;

        cpu.set(rr.first, static_cast<uint8_t>(value >> 8u));
        cpu.set(rr.second, static_cast<uint8_t>(value & 0xFFu));

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction INC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);

        value = INC(value, cpu.get(Cpu::Register::F));
        cpu.m_memory_controller->write(address, value);

        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction INC_SP() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_stack_ptr++;
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

uint8_t DEC(uint8_t value, uint8_t& flags) {
    
    half_borrow_8bit(value, 1)                ?
        set_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry))  :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    value--;
    
    value == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    set_bit(flags, Cpu::to_index(Cpu::Flag::Sub));

    return value;
}

Instruction DEC_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto r = cpu.get(src);
        cpu.set(src, DEC(r, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DEC_RR(std::pair<Cpu::Register, Cpu::Register> rr) { 
    return {[rr](Cpu& cpu, Operand&) {

        auto value = combine_bytes(cpu.get(rr.first), cpu.get(rr.second));
        value--;

        cpu.set(rr.first, static_cast<uint8_t>(value >> 8u));
        cpu.set(rr.second, static_cast<uint8_t>(value & 0xFFu));

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction DEC_ADDR_HL() {
    return {[](Cpu& cpu, Operand&) {
        const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        auto value = cpu.m_memory_controller->read(address);
        value = DEC(value, cpu.get(Cpu::Register::F));
        cpu.m_memory_controller->write(address, value);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction DEC_SP() {
    return {[](Cpu& cpu, Operand&) {
        cpu.m_stack_ptr--;
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction SCF() {
    return {[](Cpu& cpu, Operand&) {
        cpu.clear_flag(Cpu::Flag::Sub);
        cpu.clear_flag(Cpu::Flag::Half_Carry);
        cpu.set_flag(Cpu::Flag::Carry);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CCF() {
    return {[](Cpu& cpu, Operand&) {
        cpu.clear_flag(Cpu::Flag::Sub);
        cpu.clear_flag(Cpu::Flag::Half_Carry);
        cpu.test_flag(Cpu::Flag::Carry) ? 
            cpu.clear_flag(Cpu::Flag::Carry) : cpu.set_flag(Cpu::Flag::Carry);
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RRCA() {
    return {[](Cpu& cpu, Operand&) {

        is_set(cpu.get(Cpu::Register::A), 0) ? cpu.set_flag(Cpu::Flag::Carry)
            : cpu.clear_flag(Cpu::Flag::Carry);
        
        cpu.set(Cpu::Register::A, rotate_right<uint8_t>(cpu.get(Cpu::Register::A), 1));

        cpu.clear_flag(Cpu::Flag::Zero);
        cpu.clear_flag(Cpu::Flag::Sub);
        cpu.clear_flag(Cpu::Flag::Half_Carry);

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RRA() {
    return {[](Cpu& cpu, Operand&) {
        
        auto a = cpu.get(Cpu::Register::A);

        const auto new_carry_flag = is_set(a, 0);
        a = static_cast<uint8_t>(a >> 1u);

        cpu.test_flag(Cpu::Flag::Carry) ? set_bit(a, 7) 
            : clear_bit(a, 7);
        
        cpu.set(Cpu::Register::A, a);

        new_carry_flag ? cpu.set_flag(Cpu::Flag::Carry) 
            : cpu.clear_flag(Cpu::Flag::Carry);
        
        cpu.clear_flag(Cpu::Flag::Zero);
        cpu.clear_flag(Cpu::Flag::Sub);
        cpu.clear_flag(Cpu::Flag::Half_Carry);
    
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RLA() {
    return {[](Cpu& cpu, Operand&) {
        
        auto a = cpu.get(Cpu::Register::A);

        const auto new_carry_flag = is_set(a, 7);
        a =  static_cast<uint8_t>(a << 1u);

        cpu.test_flag(Cpu::Flag::Carry) ? set_bit(a, 0)
            : clear_bit(a, 0);
        
        cpu.set(Cpu::Register::A, a);

        new_carry_flag ? cpu.set_flag(Cpu::Flag::Carry)
            : cpu.clear_flag(Cpu::Flag::Carry);

        cpu.clear_flag(Cpu::Flag::Zero);
        cpu.clear_flag(Cpu::Flag::Sub);
        cpu.clear_flag(Cpu::Flag::Half_Carry);
        
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction RLCA() {
    return {[](Cpu& cpu, Operand&) {
        auto a = cpu.get(Cpu::Register::A);

        is_set(a, 7) ? cpu.set_flag(Cpu::Flag::Carry) : 
            cpu.clear_flag(Cpu::Flag::Carry);

        cpu.set(Cpu::Register::A, rotate_left<uint8_t>(a, 1));

        cpu.clear_flag(Cpu::Flag::Zero);
        cpu.clear_flag(Cpu::Flag::Sub);
        cpu.clear_flag(Cpu::Flag::Half_Carry);

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction DAA() {    
    return {[](Cpu& cpu, Operand&) {

        auto a = cpu.get(Cpu::Register::A);
        if(!cpu.test_flag(Cpu::Flag::Sub)) {
            if(cpu.test_flag(Cpu::Flag::Carry) || a > 0x99) {
                a += 0x60;
                cpu.set_flag(Cpu::Flag::Carry);
            }

            if(cpu.test_flag(Cpu::Flag::Half_Carry) || (a & 0x0Fu) > 0x09) {
                a += 0x06;
            }
        } else {
            if(cpu.test_flag(Cpu::Flag::Carry)) {
                a -= 0x60;
            }
            if(cpu.test_flag(Cpu::Flag::Half_Carry)) {
                a -= 0x06;
            }
        }

        cpu.clear_flag(Cpu::Flag::Half_Carry);

        a == 0 ? cpu.set_flag(Cpu::Flag::Zero) :
            cpu.clear_flag(Cpu::Flag::Zero);

        cpu.set(Cpu::Register::A, a);

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADD_SP_R8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto distance = std::get<uint8_t>(op);

        half_carry_8bit(static_cast<uint8_t>(cpu.m_stack_ptr), distance)     ?
            cpu.set_flag(Cpu::Flag::Half_Carry)  :
            cpu.clear_flag(Cpu::Flag::Half_Carry);


        overflows_8bit(static_cast<uint8_t>(cpu.m_stack_ptr), distance)  ? 
            cpu.set_flag(Cpu::Flag::Carry)   :
            cpu.clear_flag(Cpu::Flag::Carry);


        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + static_cast<int8_t>(distance));

        cpu.clear_flag(Cpu::Flag::Zero);
        cpu.clear_flag(Cpu::Flag::Sub);

        constexpr auto cycles = 16;
        return cycles;
    }, immediate};    
}

uint8_t AND(uint8_t first, uint8_t second, uint8_t& flags) {
    
    first &= second;

    first == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    set_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));

    return first;
}

Instruction AND_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, AND(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction AND_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto a = cpu.get(Cpu::Register::A);
        const auto r = cpu.get(src);
        
        cpu.set(Cpu::Register::A, AND(a, r, cpu.get(Cpu::Register::F)));

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction AND_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, AND(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

uint8_t XOR(uint8_t first, uint8_t second, uint8_t& flags) {
    
    first ^= second;
    first == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));

    return first;
}

Instruction XOR_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, XOR(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction XOR_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {
        auto a = cpu.get(Cpu::Register::A);
        const auto r = cpu.get(src);

        a = XOR(a, r, cpu.get(Cpu::Register::F));

        cpu.set(Cpu::Register::A, a);

        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction XOR_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, XOR(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

uint8_t OR(uint8_t first, uint8_t second, uint8_t& flags) {
    
    first |= second;
    first == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));
    clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));

    return first;
}

Instruction OR_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, OR(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction OR_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {
        cpu.set(Cpu::Register::A, OR(cpu.get(Cpu::Register::A), cpu.get(src), cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction OR_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, OR(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

void CP(uint8_t first, uint8_t second, uint8_t& flags) {

    underflows_8bit(first, second)         ?
        set_bit(flags, static_cast<int>(Cpu::Flag::Carry))   :
        clear_bit(flags, static_cast<int>(Cpu::Flag::Carry));

    half_borrow_8bit(first, second)            ?
        set_bit(flags,      Cpu::to_index(Cpu::Flag::Half_Carry))  :
        clear_bit(flags,    Cpu::to_index(Cpu::Flag::Half_Carry));

    (first == second) ? 
        set_bit(flags,      Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags,    Cpu::to_index(Cpu::Flag::Zero));

    set_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
}

Instruction CP_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        CP(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction CP_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto a = cpu.get(Cpu::Register::A);
        const auto r = cpu.get(src);
        CP(a, r, cpu.get(Cpu::Register::F));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction CP_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        CP(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction PUSH_RR(std::pair<Cpu::Register, Cpu::Register> rr) {
    return {[rr](Cpu& cpu, Operand&) {
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-1), cpu.get(rr.first));
        cpu.m_memory_controller->write(static_cast<uint16_t>(cpu.m_stack_ptr-2), cpu.get(rr.second));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr - 2);
        constexpr auto cycles = 16;
        return cycles;
    }, implied};
}

Instruction POP_AF() {
    return {[](Cpu& cpu, Operand&) {
        cpu.set(Cpu::Register::F, cpu.m_memory_controller->read(cpu.m_stack_ptr) & 0xF0u);
        cpu.set(Cpu::Register::A, cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1)));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

Instruction POP_RR(std::pair<Cpu::Register, Cpu::Register> rr) {
    return {[rr](Cpu& cpu, Operand&) {
        cpu.set(rr.second, cpu.m_memory_controller->read(cpu.m_stack_ptr));
        cpu.set(rr.first, cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_stack_ptr + 1)));
        cpu.m_stack_ptr = static_cast<uint16_t>(cpu.m_stack_ptr + 2);
        constexpr auto cycles = 12;
        return cycles;
    }, implied};
}

uint8_t ADC(uint8_t first, uint8_t second, uint8_t& flags) {
    
    const auto carry_value = is_set(flags, Cpu::to_index(Cpu::Flag::Carry)) ? 1 : 0;

    half_carry_8bit(first, second)       ?
        set_bit(flags,      Cpu::to_index(Cpu::Flag::Half_Carry))          :
        clear_bit(flags,    Cpu::to_index(Cpu::Flag::Half_Carry));

    overflows_8bit(first, second)        ?
        set_bit(flags,      Cpu::to_index(Cpu::Flag::Carry))               :
        clear_bit(flags,    Cpu::to_index(Cpu::Flag::Carry));

    first = static_cast<uint8_t>(first + second);

    if(!is_set(flags, Cpu::to_index(Cpu::Flag::Half_Carry))) {
        half_carry_8bit(first, static_cast<uint8_t>(carry_value))       ?
        set_bit(flags,      Cpu::to_index(Cpu::Flag::Half_Carry))          :
        clear_bit(flags,    Cpu::to_index(Cpu::Flag::Half_Carry));
    }
    
    if(!is_set(flags, Cpu::to_index(Cpu::Flag::Carry))) {
        overflows_8bit(first, static_cast<uint8_t>(carry_value))        ?
            set_bit(flags,      Cpu::to_index(Cpu::Flag::Carry))               :
            clear_bit(flags,    Cpu::to_index(Cpu::Flag::Carry));
    }

    first = static_cast<uint8_t>(first + carry_value);

    first == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    clear_bit(flags, Cpu::to_index(Cpu::Flag::Sub));
    
    return first;
}

Instruction ADC_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, ADC(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction ADC_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto r = cpu.get(src);
        const auto a = cpu.get(Cpu::Register::A);
        cpu.set(Cpu::Register::A, ADC(a, r, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction ADC_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        cpu.set(Cpu::Register::A, ADC(cpu.get(Cpu::Register::A), value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction LDH_ADDR_A8_A() {
    return  {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        const auto address = static_cast<uint16_t>(0xFF00 + value);
        cpu.m_memory_controller->write(address, cpu.get(Cpu::Register::A));    
        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LDH_A_ADDR_A8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto address = static_cast<uint16_t>(0xFF00 + std::get<uint8_t>(op));
        cpu.set(Cpu::Register::A, cpu.m_memory_controller->read(address));             
        constexpr auto cycles = 12;
        return cycles;
    }, immediate};
}

Instruction LD_ADDR_C_A() {
    return {[](Cpu& cpu, Operand&) {        
        const auto address = static_cast<uint16_t>(0xFF00 + cpu.get(Cpu::Register::C));
        cpu.m_memory_controller->write(address, cpu.get(Cpu::Register::A));
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

uint8_t SBC(uint8_t first, uint8_t second, uint8_t& flags) {
    
    const auto carry_value = is_set(flags, Cpu::to_index(Cpu::Flag::Carry)) ? 1 : 0;

    half_borrow_8bit(first, second)            ?
        set_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry))  :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));

    underflows_8bit(first, second)         ?
        set_bit(flags, Cpu::to_index(Cpu::Flag::Carry))   :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));
    
    first = static_cast<uint8_t>(first - second);

    if(!is_set(flags, Cpu::to_index(Cpu::Flag::Half_Carry))) {
        half_borrow_8bit(first, static_cast<uint8_t>(carry_value))       ?
            set_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry))  :
            clear_bit(flags, Cpu::to_index(Cpu::Flag::Half_Carry));
    }

    if(!is_set(flags, Cpu::to_index(Cpu::Flag::Carry))) {
        underflows_8bit(first, static_cast<uint8_t>(carry_value))         ?
            set_bit(flags, Cpu::to_index(Cpu::Flag::Carry))   :
            clear_bit(flags, Cpu::to_index(Cpu::Flag::Carry));
    }

    first = static_cast<uint8_t>(first - carry_value);

    first == 0 ? set_bit(flags, Cpu::to_index(Cpu::Flag::Zero)) :
        clear_bit(flags, Cpu::to_index(Cpu::Flag::Zero));

    set_bit(flags, Cpu::to_index(Cpu::Flag::Sub));

    return first;
}

Instruction SBC_D8() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        const auto a = cpu.get(Cpu::Register::A);
        cpu.set(Cpu::Register::A, SBC(a, value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, immediate};
}

Instruction SBC_R(Cpu::Register src) {
    return {[src](Cpu& cpu, Operand&) {
        const auto a = cpu.get(Cpu::Register::A);
        const auto r = cpu.get(src);
        cpu.set(Cpu::Register::A, SBC(a, r, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}

Instruction SBC_A_ADDR_HL() {
    return {[](Cpu& cpu, Operand& op) {
        const auto value = std::get<uint8_t>(op);
        auto a = cpu.get(Cpu::Register::A);
        cpu.set(Cpu::Register::A, SBC(a, value, cpu.get(Cpu::Register::F)));
        constexpr auto cycles = 8;
        return cycles;
    }, hl_addressing};
}

Instruction PREFIX_CB() {
    return {[](Cpu& cpu, Operand&) {
        const auto cb_opcode = static_cast<CBCode>(cpu.m_memory_controller->read(static_cast<uint16_t>(cpu.m_program_counter - 1)));
        const auto instruction = fetch_cb(cb_opcode);
        auto operand = instruction.read_operand(cpu);
        return instruction.execute(cpu, operand);
    }, [](Cpu& cpu) -> Operand {
        cpu.m_program_counter += 2;
        return {static_cast<uint8_t>(0)};
    }};
}

Instruction LD_ADDR_HLD_A() {
    return {[](Cpu& cpu, Operand&) {
            
        auto address = cpu.get({Cpu::Register::H, Cpu::Register::L});
        cpu.m_memory_controller->write(address, cpu.get(Cpu::Register::A));

        address--;

        cpu.set(Cpu::Register::H, static_cast<uint8_t>(address >> 8u));
        cpu.set(Cpu::Register::L, static_cast<uint8_t>(address & 0xFFu));
        
        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction LD_A_ADDR_HLD() {
    return {[](Cpu& cpu, Operand&) {
        
        auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
        cpu.set(Cpu::Register::A, cpu.m_memory_controller->read(address));

        address--;
        cpu.set(Cpu::Register::H, static_cast<uint8_t>(address >> 8u));
        cpu.set(Cpu::Register::L, static_cast<uint8_t>(address & 0xFFu));

        constexpr auto cycles = 8;
        return cycles;
    }, implied};
}

Instruction CPL() {
    return {[](Cpu& cpu, Operand&){
        auto a = cpu.get(Cpu::Register::A);
        a ^= 0xFF;
        cpu.set(Cpu::Register::A, a);

        cpu.set_flag(Cpu::Flag::Sub);
        cpu.set_flag(Cpu::Flag::Half_Carry);
        
        constexpr auto cycles = 4;
        return cycles;
    }, implied};
}