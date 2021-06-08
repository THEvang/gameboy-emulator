#include "Cpu/Interrupt_Handler.hpp"

#include "Memory/Memory_Controller.hpp"
#include "Cpu/Cpu.hpp"
#include "Utilities/BitOperations.hpp"

Interrupt_Handler::Interrupt_Handler(MemoryBankController* memory_controller)
    : m_memory_bank_controller(memory_controller)
{}

int Interrupt_Handler::interrupts(Cpu& cpu) {

    auto handle = [this](Cpu& cpu, Interrupts interrupt) -> bool {
        if(is_enabled(interrupt) && is_requested(interrupt)) {
            const auto vector = get_vector(interrupt);
            call(cpu, vector);
            clear(interrupt);
            cpu.interrupts_enabled = false;
            return true;
        }
        return false;
    };

    for(auto i = 0; i <= static_cast<int>(Interrupts::Joypad); i++) {
        if(handle(cpu, static_cast<Interrupts>(i))) {
            return 20;
        };
    }

    return  4;
}

void Interrupt_Handler::request(Interrupts interrupt) {
    auto interrupt_request = m_memory_bank_controller->read(interrupt_request_address);
    set_bit(interrupt_request, static_cast<int>(interrupt));
    m_memory_bank_controller->write(interrupt_request_address, interrupt_request);
}

void Interrupt_Handler::clear(Interrupts interrupt) {
    auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    clear_bit(request_register, static_cast<int>(interrupt));
    m_memory_bank_controller->write(interrupt_request_address, request_register);
}

bool Interrupt_Handler::should_exit_halt() {

    const auto interrupt_requests = m_memory_bank_controller->read(interrupt_request_address);
    const auto interrupts_enabled = m_memory_bank_controller->read(interrupt_enabled_address);

    return (static_cast<uint8_t>(interrupt_requests & interrupts_enabled) & 0x1FU) == 0;
}

bool Interrupt_Handler::is_requested(Interrupts interrupt) const {
    const auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    return test_bit_8bit(request_register, static_cast<int>(interrupt));
}

bool Interrupt_Handler::is_enabled(Interrupts interrupt) const {
    const auto interrupt_enable_register = m_memory_bank_controller->read(interrupt_enabled_address);
    return test_bit_8bit(interrupt_enable_register, static_cast<int>(interrupt));
}

void Interrupt_Handler::call(Cpu& cpu, uint8_t interrupt_vector) {

    const auto pc_low = static_cast<uint8_t>(cpu.program_counter & 0xFFU);
    const auto pc_high = static_cast<uint8_t>(cpu.program_counter >> 8U);
    m_memory_bank_controller->write(static_cast<uint16_t>(cpu.stack_ptr - 1), pc_high);
    m_memory_bank_controller->write(static_cast<uint16_t>(cpu.stack_ptr - 2), pc_low);
    cpu.stack_ptr = static_cast<uint16_t>(cpu.stack_ptr - 2);
    cpu.program_counter = static_cast<uint16_t>(interrupt_vector);
}

uint16_t Interrupt_Handler::get_vector(Interrupts interrupt) const {
    switch(interrupt) {
        case Interrupts::V_Blank:
            return 0x40;
        case Interrupts::LCD_STAT:
            return 0x48;
        case Interrupts::Timer:
            return 0x50;
        case Interrupts::Serial:
            return 0x58;
        case Interrupts::Joypad:
            return 0x60;
    }
}