#include "cpu/Interrupt_Handler.h"
#include "BitOperations.h"

Interrupt_Handler::Interrupt_Handler(MemoryBankController* memory_bank_controller)
    : m_memory_bank_controller(memory_bank_controller)
{}

int Interrupt_Handler::interrupts(Cpu& cpu) {

    if(v_blank_interrupt_enabled() && v_blank_interrupt_requested()) {
        call(cpu, v_blank_vector);
        clear_v_blank_request();
        cpu.m_interrupts_enabled = false;
        return 20;
    }

    if(lcd_stat_interrupt_enabled() && lcd_stat_interrupt_requested()) {
        call(cpu, lcd_stat_vector);
        clear_lcd_stat_request();
        cpu.m_interrupts_enabled = false;
        return 20;
    } 

    if(timer_interrupt_enabled() && timer_interrupt_requested()) {
        call(cpu, timer_vector);
        clear_timer_request();
        cpu.m_interrupts_enabled = false;
        return 20;
    }

    if(serial_interrupt_enabled() && serial_interrupt_requested()) {
        call(cpu, serial_vector);
        clear_serial_request();
        cpu.m_interrupts_enabled = false;
        return 20;
    }
    
    if(joypad_interrupt_enabled() && joypad_interrupt_requested()) {
        call(cpu, joypad_vector);
        clear_joypad_request();
        cpu.m_interrupts_enabled = false;
        return 20;
    }

    return 0;
}

bool Interrupt_Handler::should_exit_halt() {

    const auto interrupt_requests = m_memory_bank_controller->read(interrupt_request_address);
    const auto interrupts_enabled = m_memory_bank_controller->read(interrupt_enabled_address);

    return ((interrupt_requests & interrupts_enabled) & 0x1F) == 0;
}

void Interrupt_Handler::clear_v_blank_request() {
    auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    clear_bit(request_register, static_cast<int>(Interrupts::V_Blank));
    m_memory_bank_controller->write(interrupt_request_address, request_register);
}

void Interrupt_Handler::clear_lcd_stat_request() {
    auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    clear_bit(request_register, static_cast<int>(Interrupts::LCD_STAT));
    m_memory_bank_controller->write(interrupt_request_address, request_register);
}

void Interrupt_Handler::clear_timer_request() {
    auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    clear_bit(request_register, static_cast<int>(Interrupts::Timer));
    m_memory_bank_controller->write(interrupt_request_address, request_register);
}

void Interrupt_Handler::clear_serial_request() {
    auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    clear_bit(request_register, static_cast<int>(Interrupts::Serial));
    m_memory_bank_controller->write(interrupt_request_address, request_register);
}

void Interrupt_Handler::clear_joypad_request() {
    auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    clear_bit(request_register, static_cast<int>(Interrupts::Joypad));
    m_memory_bank_controller->write(interrupt_request_address, request_register);
}

bool Interrupt_Handler::v_blank_interrupt_requested() const {
    const auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    return is_set(request_register, static_cast<int>(Interrupts::V_Blank));
}

bool Interrupt_Handler::lcd_stat_interrupt_requested() const {
    const auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    return is_set(request_register, static_cast<int>(Interrupts::LCD_STAT));
}

bool Interrupt_Handler::timer_interrupt_requested() const {
    const auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    return is_set(request_register, static_cast<int>(Interrupts::Timer));
}

bool Interrupt_Handler::serial_interrupt_requested() const {
    const auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    return is_set(request_register, static_cast<int>(Interrupts::Serial));
}

bool Interrupt_Handler::joypad_interrupt_requested() const {
    const auto request_register = m_memory_bank_controller->read(interrupt_request_address);
    return is_set(request_register, static_cast<int>(Interrupts::Joypad));
}

bool Interrupt_Handler::v_blank_interrupt_enabled() const {
    const auto interrupt_enable_register = m_memory_bank_controller->read(interrupt_enabled_address);
    return is_set(interrupt_enable_register, static_cast<int>(Interrupts::V_Blank));
}

bool Interrupt_Handler::lcd_stat_interrupt_enabled() const {
    const auto interrupt_enable_register = m_memory_bank_controller->read(interrupt_enabled_address);
    return is_set(interrupt_enable_register, static_cast<int>(Interrupts::LCD_STAT));
}

bool Interrupt_Handler::timer_interrupt_enabled() const {
    const auto interrupt_enable_register = m_memory_bank_controller->read(interrupt_enabled_address);
    return is_set(interrupt_enable_register, static_cast<int>(Interrupts::Timer));
}

bool Interrupt_Handler::serial_interrupt_enabled() const {
    const auto interrupt_enable_register = m_memory_bank_controller->read(interrupt_enabled_address);
    return is_set(interrupt_enable_register, static_cast<int>(Interrupts::Serial));
}

bool Interrupt_Handler::joypad_interrupt_enabled() const {
    const auto interrupt_enable_register = m_memory_bank_controller->read(interrupt_enabled_address);
    return is_set(interrupt_enable_register, static_cast<int>(Interrupts::Joypad));
}

void Interrupt_Handler::call(Cpu& cpu, int interrupt_vector) {

    const auto pc_low = cpu.m_program_counter & 0xFF;
    const auto pc_high = cpu.m_program_counter >> 8;
    m_memory_bank_controller->write(cpu.m_stack_ptr - 1, pc_high);
    m_memory_bank_controller->write(cpu.m_stack_ptr - 2, pc_low);
    cpu.m_stack_ptr -= 2;
    cpu.m_program_counter = interrupt_vector;
}
