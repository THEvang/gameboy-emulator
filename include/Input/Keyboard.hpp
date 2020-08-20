#pragma once

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>
#include <queue>
#include <SDL2/SDL_events.h>

#include "Keyboard_Observer.hpp"

class Keyboard_Queue {
public:

    using Key_Map = std::map<SDL_Keycode, Button>;

    Keyboard_Queue(const Key_Map& key_map);
    Keyboard_Queue();

    void push(const Key_Input& button);

    Key_Input front() const;
    void pop();
    bool empty() const;

    Key_Map key_map;
    
private:

    std::queue<Key_Input> m_input_queue;
};


int keyboard_filter(void* user_data, SDL_Event* event);

class Keyboard_Emitter {
public:

    using Observer_Handle = int;

    Keyboard_Emitter() = default;

    Observer_Handle add_observer(Keyboard_Observer* observer);

    void remove_observer(Observer_Handle handle);

    void emitt();

    Keyboard_Queue* get_queue();

private:

    Observer_Handle m_next_handle = 0;
    std::map<Observer_Handle, Keyboard_Observer*> m_observers;

    Keyboard_Queue m_input_queue;
};

#endif