#include <bitset>
#include <map>
#include <queue>
#include <SDL2/SDL_events.h>

#include "Input/Keyboard.hpp"
#include "Cpu/Interrupt_Handler.hpp"

Keyboard_Queue::Keyboard_Queue(const Key_Map& key_map) 
    : key_map(key_map) 
{

}

Keyboard_Queue::Keyboard_Queue() {
    key_map = Key_Map {
        {SDLK_z, Button::A},
        {SDLK_x, Button::B},
        {SDLK_RETURN, Button::Start},
        {SDLK_BACKSPACE, Button::Select},
        {SDLK_w, Button::Up},
        {SDLK_s, Button::Down},
        {SDLK_d, Button::Right},
        {SDLK_a, Button::Left}
    };
}

void Keyboard_Queue::push(const Key_Input& button) {
    m_input_queue.push(button);
}

Key_Input Keyboard_Queue::front() const {
    return m_input_queue.front();
}

void Keyboard_Queue::pop() {
    m_input_queue.pop();
}

bool Keyboard_Queue::empty() const {
    return m_input_queue.empty();
}

int keyboard_filter(void* user_data, SDL_Event* event) {

    if(!user_data || !event) {
        return 1;
    }

    Key_Input input;
    switch(event->type) {
        case SDL_KEYDOWN:
            input.key_press = Key_Press::Key_Down;
            break;
        case SDL_KEYUP:
            input.key_press = Key_Press::Key_Up;
            break;
        default:
            return 1;
    }


    auto keyboard_queue = static_cast<Keyboard_Queue*>(user_data);
    auto key_map = keyboard_queue->key_map;
    input.button = key_map[event->key.keysym.sym];
    
    keyboard_queue->push(input);

    return 0;
}

Keyboard_Emitter::Observer_Handle Keyboard_Emitter::add_observer(Keyboard_Observer* observer) {
    
    auto handle = m_next_handle;
    m_observers[handle] = observer;

    while(m_observers.find(m_next_handle) != m_observers.end()) {
        m_next_handle++;
    }

    return handle;
}

void Keyboard_Emitter::remove_observer(Observer_Handle handle) {
    if(auto it = m_observers.find(handle) != m_observers.end()) {
        m_next_handle = handle;
        m_observers.erase(it);
    }
}

void Keyboard_Emitter::emitt() {

    while(!m_input_queue.empty()) {
        for(auto [handle, observer] : m_observers) {
            observer->input(m_input_queue.front());
        }

        m_input_queue.pop();
    }
}

Keyboard_Queue* Keyboard_Emitter::get_queue() {
    return &m_input_queue;
}