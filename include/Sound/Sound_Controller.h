#include "Memory/Memory_Controller.h"
#include "SDL2/SDL_audio.h"

class Sound_Controller {
public:
    Sound_Controller(MemoryBankController* memory_controller);

    
private:

    static const uint16_t channel_control_address = 0xFF24;
    static const uint16_t sound_terminal_select_address = 0xFF25;
    static const uint16_t sound_on_off_address = 0xFF26;  

};


class Tone_And_Sweep {

};

class Tone {

};