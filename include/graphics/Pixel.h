#include <array>

struct Screen_Position {
    int x = 0;
    int y = 0;
};

struct Color {  
    unsigned char red = 255;
    unsigned char green = 0;
    unsigned char blue = 0;
    unsigned char alpha = 0;
};

class Pixel_Array {
public:

    void set_pixel(const Screen_Position& screen_position, const Color& color);    
    unsigned char* data();

private:
    static const int screen_width = 160;
    static const int screen_height = 144;
    std::array<unsigned char, screen_height*screen_width*3> m_pixels;
};

