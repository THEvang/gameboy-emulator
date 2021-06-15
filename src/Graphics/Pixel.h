#pragma once

#include <stdint.h>

#define GB_SCREEN_WIDTH 160
#define GB_SCREEN_HEIGHT 144

typedef struct Screen_Position {
    uint8_t x;
    uint8_t y;
} Screen_Position;

typedef struct Color {  
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Color;

typedef struct Pixel_Array {
    uint32_t pixels[GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT];
} Pixel_Array;

void set_pixel(Pixel_Array* arr, Screen_Position screen_position, Color color);