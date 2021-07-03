#pragma once

#include "Memory/Memory_Controller.h"
#include "Utilities/BitOperations.h"
#include <SDL2/SDL.h>

typedef struct Square_Wave {
    float duty;
    double freq;
    double length;
    double time;
} Square_Wave;

typedef struct Wave_Ram {
    uint8_t data[0x1F];
    float freq;
} Wave_Ram;

typedef struct Sound_Channels {
    Square_Wave channel_2;
} Sound_Channels;


Square_Wave gb_sound_channel_2_update_wave(MemoryBankController* mc);
gb_sound_channel_3_update_wave_ram(MemoryBankController* mc, Wave_Ram* ram);

void gb_generate_square_wave(Square_Wave* wave, uint8_t* stream, int len, double dt);
void gb_audio_callback(void* user_data, Uint8* stream, int len);
void gb_play_sound_channel_2(MemoryBankController* mc, Sound_Channels* sound_channels);