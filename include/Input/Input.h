#pragma once

#include <bitset>

class Interrupt_Handler;

enum class Button_Types {
    Direction_Key,
    Button_Key
};

enum class Buttons {
    Start,
    Select,
    A,
    B,
    Up,
    Down,
    Right,
    Left
};

class Joypad_Controller {
public:
  
    explicit Joypad_Controller(Interrupt_Handler* interrupt_handler);
    
    static uint8_t read_input_as_byte(Button_Types button_type);
    void press_button(const Buttons& button);
    void release_button(const Buttons& button);

private:

    Interrupt_Handler* m_interrupt_handler;

    static std::bitset<4> m_direction_keys;
    static std::bitset<4> m_button_keys;
};