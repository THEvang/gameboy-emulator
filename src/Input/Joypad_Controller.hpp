#pragma once 

#include <bitset>
#include <cstdint>

#include "Keyboard_Observer.hpp"

enum class Button_Types {
    Direction_Key,
    Button_Key
};

class Interrupt_Handler;

class Joypad_Controller : public Keyboard_Observer {
public:
  
    explicit Joypad_Controller(Interrupt_Handler* interrupt_handler);
    
    static uint8_t read_input_as_byte(Button_Types button_type);

    void input(Key_Input) override;

private:

    void key_down(const Button& button);
    void key_up(const Button& button);

    Interrupt_Handler* m_interrupt_handler;

    static std::bitset<4> m_direction_keys;
    static std::bitset<4> m_button_keys;
};
