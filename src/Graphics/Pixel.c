#include "Graphics/Pixel.h"

void set_pixel(Pixel_Array* arr, Screen_Position screen_position, Color color) {

    uint8_t y_pos = screen_position.y;
    uint8_t x_pos = screen_position.x;

    int index = x_pos + y_pos * GB_SCREEN_WIDTH;

    arr->pixels[index] = (uint32_t) (color.red << 24u | color.green << 16u | color.blue << 8u | 0xFFu);
}