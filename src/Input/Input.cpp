#include "Input/Input.h"

std::bitset<4> Joypad_Controller::m_direction_keys = 0b1111;
std::bitset<4> Joypad_Controller::m_button_keys = 0b1111;

Joypad_Controller::Joypad_Controller(Interrupt_Handler* interrupt_handler)
    : m_interrupt_handler(interrupt_handler) {
}
    
uint8_t Joypad_Controller::read_input_as_byte(Button_Types button_type) {
    
    if(button_type == Button_Types::Direction_Key) {
        return static_cast<uint8_t>(m_direction_keys.to_ulong());
    }

    return static_cast<uint8_t>(m_button_keys.to_ulong());
}

void Joypad_Controller::press_button(const Buttons& button) {
    switch(button) {
        case Buttons::Right:
            m_direction_keys.reset(0);
            m_interrupt_handler->request_joypad_interrupt();
            break;
        case Buttons::Left:
            m_direction_keys.reset(1);
            m_interrupt_handler->request_joypad_interrupt();
            break;
        case Buttons::Up:
            m_direction_keys.reset(2);
            m_interrupt_handler->request_joypad_interrupt();
            break;
        case Buttons::Down:
            m_direction_keys.reset(3);
            m_interrupt_handler->request_joypad_interrupt();
            break;
        case Buttons::A:
            m_button_keys.reset(0);
            m_interrupt_handler->request_joypad_interrupt();
            break;
        case Buttons::B:
            m_button_keys.reset(1);
            m_interrupt_handler->request_joypad_interrupt();
            break;
        case Buttons::Select:
            m_button_keys.reset(2);
            m_interrupt_handler->request_joypad_interrupt();
            break;
        case Buttons::Start:
            m_button_keys.reset(3);
            m_interrupt_handler->request_joypad_interrupt();
            break;
    }
}

void Joypad_Controller::release_button(const Buttons& button) {
    switch(button) {
        case Buttons::Right:
            m_direction_keys.set(0);
            break;
        case Buttons::Left:
            m_direction_keys.set(1);
            break;
        case Buttons::Up:
            m_direction_keys.set(2);
            break;
        case Buttons::Down:
            m_direction_keys.set(3);
            break;
        case Buttons::A:
            m_button_keys.set(0);
            break;
        case Buttons::B:
            m_button_keys.set(1);
            break;
        case Buttons::Select:
            m_button_keys.set(2);
            break;
        case Buttons::Start:
            m_button_keys.set(3);
            break;
    }
}