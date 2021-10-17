#pragma once

#include <stdint.h>

#define GB_SCREEN_WIDTH 160
#define GB_SCREEN_HEIGHT 144

typedef struct Screen_Position {
    uint8_t x;
    uint8_t y;
} Screen_Position;

typedef struct Color {  
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha; 
} Color;

typedef enum Sprite_Attribute_Flags {
    BG_AND_WINDOW_OVER_OBJECT = 1 << 7,
    Y_FLIP = 1 << 6,
    X_FLIP = 1 << 5,
    PALETTE_NUMBER = 1 << 4
} Sprite_Attribute_Flags;

typedef struct Pixel_Array {
    uint32_t pixels[GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT];
} Pixel_Array;

void set_pixel(Pixel_Array* arr, Screen_Position screen_position, Color color);