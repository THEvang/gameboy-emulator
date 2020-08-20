#pragma once

#include <array>
#include <GL/gl.h>

struct Screen_Position {
    uint8_t x = 0;
    uint8_t y = 0;
};

struct Color {  
    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;
};

class Pixel_Array {
public:

    void set_pixel(const Screen_Position& screen_position, const Color& color);    
    uint32_t const* data();

private:
    static const std::size_t screen_width = 160;
    static const std::size_t screen_height = 144;
    std::array<GLuint, screen_height*screen_width> m_pixels;
};

