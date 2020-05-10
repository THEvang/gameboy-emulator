#include "graphics/Pixel.h"

void Pixel_Array::set_pixel(const Screen_Position& screen_position, const Color& color) {
    m_pixels[screen_position.x + screen_position.y * screen_height] = color.red << 24 | color.green << 16 | color.blue << 8 | 0xFF;
}
    
uint32_t* Pixel_Array::data() {
    return m_pixels.data();
}