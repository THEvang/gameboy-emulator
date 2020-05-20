#include "Graphics/Pixel.h"

void Pixel_Array::set_pixel(const Screen_Position& screen_position, const Color& color) {

    auto y_pos = screen_position.y;
    auto x_pos = screen_position.x;

    auto index = x_pos + y_pos * screen_width;

    m_pixels[index] = color.red << 24 | color.green << 16 | color.blue << 8 | 0xFF;
}
    
uint32_t const* Pixel_Array::data() {
    return m_pixels.data();
}