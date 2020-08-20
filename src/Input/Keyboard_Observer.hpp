#pragma once

enum class Button {
    Start,
    Select,
    A,
    B,
    Up,
    Down,
    Right,
    Left
};

enum class Key_Press {
    Key_Down,
    Key_Up
};

struct Key_Input {
    Button button;
    Key_Press key_press;
};


class Keyboard_Observer {
public:
    virtual ~Keyboard_Observer() = default;
    virtual void input(Key_Input) = 0;
};