#include "Sound.h"
#include <math.h>

void gb_generate_square_wave(Square_Wave* wave, Uint8* stream, int len, double dt) {
    
    float* fstream = (float*) stream;
    for (int i = 0; i < len / sizeof(float); i++) {
        float value = sin(2.0 * M_PI * wave->freq * wave->time);
        fstream[i] = value;
        wave->time += dt;
    }
}

void gb_audio_callback(void* user_data, Uint8* stream, int len) {

    Sound_Channels* channels = (Sound_Channels*) user_data;

    double time_step = 1.0F / 44100.0F;
    gb_generate_square_wave(&(channels->channel_2), stream, len, time_step);

}

Square_Wave gb_sound_channel_2_update_wave(MemoryBankController* mc) {

    uint8_t NR21 = gb_read(mc, 0xFF16);
    
    uint8_t duty_data = (NR21 & 0xC0) > 6;
    float duty = 0.5;
    switch(duty_data) {
        case 0:
            duty = 0.125;
            break;
        case 1:
            duty = 0.25;
            break;
        case 3:
            duty = 0.75;
            break;
        case 2:
        default:
            duty = 0.5;
            break;
    }

    uint8_t length_data = (NR21 & 0x1F);
    float length = (64.0F - length_data) / 256.0F;


    uint8_t NR23 = gb_read(mc, 0xFF18);
    uint8_t NR24 = gb_read(mc, 0xFF19);

    uint16_t freq_data = (uint16_t) ((NR24 & 0x07) << 8) | NR23;
    float freq = 131072.0F / (2048.0F - freq_data);

    Square_Wave wave;
    wave.freq = freq;
    wave.duty = duty;
    wave.length = length;
    wave.time = 0;

    return wave;
}

void gb_play_sound_channel_2(MemoryBankController* mc, Sound_Channels* sound_channels) {

    uint8_t NR24 = gb_read(mc, 0xFF19);
    if(NR24 & 0x80) {
        sound_channels->channel_2 = gb_sound_channel_2_update_wave(mc);
    }

}


gb_sound_channel_3_update_wave_ram(MemoryBankController* mc, Wave_Ram* ram) {

    for (int i = 0; i < 0x1F; i++) {
        ram->data[i] = gb_read(mc, 0xF30 + i);
    }

}

void gb_play_sound(MemoryBankController* mc) {


    
}