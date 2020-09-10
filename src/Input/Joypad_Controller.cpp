#include "Input/Joypad_Controller.hpp"
#include "Cpu/Interrupt_Handler.hpp"

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

void Joypad_Controller::key_down(const Button& button) {
    switch(button) {
        case Button::Right:
            m_direction_keys.reset(0);
            m_interrupt_handler->request(Interrupts::Joypad);
            break;
        case Button::Left:
            m_direction_keys.reset(1);
            m_interrupt_handler->request(Interrupts::Joypad);
            break;
        case Button::Up:
            m_direction_keys.reset(2);
            m_interrupt_handler->request(Interrupts::Joypad);
            break;
        case Button::Down:
            m_direction_keys.reset(3);
            m_interrupt_handler->request(Interrupts::Joypad);
            break;
        case Button::A:
            m_button_keys.reset(0);
            m_interrupt_handler->request(Interrupts::Joypad);
            break;
        case Button::B:
            m_button_keys.reset(1);
            m_interrupt_handler->request(Interrupts::Joypad);
            break;
        case Button::Select:
            m_button_keys.reset(2);
            m_interrupt_handler->request(Interrupts::Joypad);
            break;
        case Button::Start:
            m_button_keys.reset(3);
            m_interrupt_handler->request(Interrupts::Joypad);
            break;
    }
}

void Joypad_Controller::key_up(const Button& button) {
    switch(button) {
        case Button::Right:
            m_direction_keys.set(0);
            break;
        case Button::Left:
            m_direction_keys.set(1);
            break;
        case Button::Up:
            m_direction_keys.set(2);
            break;
        case Button::Down:
            m_direction_keys.set(3);
            break;
        case Button::A:
            m_button_keys.set(0);
            break;
        case Button::B:
            m_button_keys.set(1);
            break;
        case Button::Select:
            m_button_keys.set(2);
            break;
        case Button::Start:
            m_button_keys.set(3);
            break;
    }
}


void Joypad_Controller::input(Key_Input input) {
    switch(input.key_press) {
        case Key_Press::Key_Down:
            key_down(input.button);
            break;
        case Key_Press::Key_Up:
            key_up(input.button);
            break;
    }
}