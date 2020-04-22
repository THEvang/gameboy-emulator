#include "graphics/Pixel.h"

void Pixel_Array::set_pixel(const Screen_Position& screen_position, const Color& color) {
    m_pixels[screen_position.x + screen_position.y * screen_height] = color.red;
    m_pixels[screen_position.x + screen_position.y * screen_height + 1] = color.green;
    m_pixels[screen_position.x + screen_position.y * screen_height + 2] = color.blue;
}
    
unsigned char* Pixel_Array::data() {
    return m_pixels.data();
}