#include "Graphics/Pixel.h"

void Pixel_Array::set_pixel(const Screen_Position& screen_position, const Color& color) {

    auto y_pos = screen_position.y;
    auto x_pos = screen_position.x;

    auto index = x_pos + y_pos * screen_width;

    m_pixels[index] = static_cast<GLuint>(color.red << 24u | color.green << 16u | color.blue << 8u | 0xFFu);
}
    
uint32_t const* Pixel_Array::data() {
    return m_pixels.data();
}