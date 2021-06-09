#include "Graphics/PPU.hpp"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.hpp"

PPU::PPU(MemoryBankController* memory_controller)
    : m_memory_controller(memory_controller)
    , m_interrupt_handler(m_memory_controller)
    , m_lcd_control(m_memory_controller)
    , m_lcd_status(m_memory_controller, m_lcd_control)
{}

void PPU::step(int cycles) {

    m_lcd_status.set_status(m_scanline_counter);
    if(!m_lcd_control.lcd_display_enabled()) {
        return;
    }

    m_scanline_counter -= cycles;

    if(m_scanline_counter <= 0) {

        m_scanline_counter = 456;

        auto current_scanline = read(m_memory_controller, scanline_address);    
        current_scanline++;
        m_memory_controller->memory[scanline_address] = current_scanline;

        if(current_scanline == 144) {
            m_interrupt_handler.request(Interrupts::V_Blank);
        } else if (current_scanline > 153) {
            m_memory_controller->memory[scanline_address] = 0;
        } else if (current_scanline < 144) {
            draw_scanline();
        }
    }
}

void PPU::draw_scanline() {

    if(m_lcd_control.background_display_enabled()) {
        draw_background();
    }

    if(m_lcd_control.sprite_display_eanbled()) {
        draw_sprites();
    }
}

void PPU::draw_background() {

    const auto scroll_y = read(m_memory_controller, scroll_y_address);
    const auto scroll_x = read(m_memory_controller, scroll_x_address);
    const auto window_y = read(m_memory_controller, window_scroll_y_address);
    const auto window_x = static_cast<uint8_t>(read(m_memory_controller, window_scroll_x_address) - static_cast<uint8_t>(7));
    const auto scanline = read(m_memory_controller, scanline_address);

    auto using_window = false;
    if(m_lcd_control.window_display_enabled()) {
        using_window = window_y <= scanline;
    }

    const auto tile_data_start_address = m_lcd_control.tile_data_start_address();
    const auto tile_map_start_address = using_window ? m_lcd_control.window_tile_map_start_address() :
        m_lcd_control.background_tile_map_start_address();

    const auto y_pos = using_window ? static_cast<uint8_t>(scanline - window_y) : 
        static_cast<uint8_t>(scroll_y + scanline);

    const auto tile_row = static_cast<uint16_t>(static_cast<uint8_t>((y_pos / 8)) * 32); 

    constexpr uint8_t horizontal_pixels = 160;
    for(uint8_t pixel = 0; pixel < horizontal_pixels; pixel++) {

        auto x_pos = static_cast<uint8_t>(scroll_x + pixel);
        if(using_window) {
            if(pixel >= window_x) {
                x_pos = static_cast<uint8_t>(pixel - window_x);
            }
        }

        const auto tile_column = static_cast<uint16_t>((x_pos / 8));
        const auto tile_map_address = static_cast<uint16_t>(tile_map_start_address + tile_row + tile_column);

        uint16_t tile_data_address = tile_data_start_address;

        if(m_lcd_control.tile_data_signed()) {
            const auto tile_number = static_cast<int8_t>( read(m_memory_controller, tile_map_address));
            tile_data_address = static_cast<uint16_t>(tile_data_address + (tile_number + 128) * 16);

        } else {
            const auto tile_number = read(m_memory_controller, tile_map_address);
            tile_data_address = static_cast<uint16_t>(tile_number * 16 + tile_data_address);
        }

        auto line = static_cast<uint8_t>((y_pos % 8) * 2);
        const auto data_1 = read(m_memory_controller, static_cast<uint16_t>(tile_data_address + line));
        const auto data_2 = read(m_memory_controller, static_cast<uint16_t>(tile_data_address + line + 1));

        auto color_bit = x_pos % 8;
        color_bit -= 7;
        color_bit *= -1;

        const uint8_t color_1 = test_bit_8bit(data_1, color_bit) ? 1 : 0;
        const uint8_t color_2 = test_bit_8bit(data_2, color_bit) ? 1 : 0;
        
        uint8_t color_id = 0;
        color_id = static_cast<uint8_t>(color_2 << 1U); 
        color_id |= color_1;

        Color pixel_color = get_color(color_id, 0xFF47);
        screen.set_pixel({pixel, scanline}, pixel_color);
    }
}

void PPU::draw_sprites() {

    bool use8x16 = false;
    if(m_lcd_control.sprite_size()) {
        use8x16 = true;
    }

    Screen_Position positions[40];
    
   for (int sprite = 0 ; sprite < 40; sprite++)
   {
    
    // sprite occupies 4 bytes in the sprite attributes table
    const auto index = static_cast<uint8_t>(sprite*4);
    const auto yPos = static_cast<uint8_t>(read(m_memory_controller, static_cast<uint16_t>(0xFE00+index)) - 16);
    const auto xPos = static_cast<uint8_t>(read(m_memory_controller, static_cast<uint16_t>(0xFE00+index+1)) - 8);
    const auto tileLocation = read(m_memory_controller, static_cast<uint16_t>(0xFE00+index+2));
    const auto attributes = read(m_memory_controller, static_cast<uint16_t>(0xFE00+index+3));

    bool yFlip = test_bit_8bit(attributes,6) ;
    bool xFlip = test_bit_8bit(attributes,5) ;

    auto scanline = read(m_memory_controller, scanline_address);

    int ysize = use8x16 ? 16 : 8;

     // does this sprite intercept with the scanline?
     if ((scanline >= yPos) && (scanline < (yPos+ysize)))
     {
       int line = scanline - yPos ;

       // read the sprite in backwards in the y axis
       if (yFlip)
       {
         line -= ysize ;
         line *= -1 ;
       }

       line *= 2; // same as for tiles
       const auto dataAddress = static_cast<uint16_t>((0x8000 + (tileLocation * 16)) + line);
       const auto data1 = read(m_memory_controller,  dataAddress ) ;
       const auto data2 = read(m_memory_controller, static_cast<uint16_t>(dataAddress +1)) ;

       // its easier to read in from right to left as pixel 0 is
       // bit 7 in the colour data, pixel 1 is bit 6 etc...
       for (int tilePixel = 7; tilePixel >= 0; tilePixel--)
       {
        int colourbit = tilePixel ;
        // read the sprite in backwards for the x axis
        if (xFlip)
        {
        colourbit -= 7 ;
        colourbit *= -1 ;
        }

        // the rest is the same as for tiles
        int colourNum = 0;
        colourNum +=  test_bit_8bit(data2, colourbit) ? 2 : 0;
        colourNum += test_bit_8bit(data1, colourbit) ? 1 : 0;

        const uint16_t colourAddress = test_bit_8bit(attributes,4) ? 0xFF49 : 0xFF48;
        const auto col = get_color(static_cast<uint8_t>(colourNum), colourAddress);

         // white is transparent for sprites.
         if (col.blue == 0xFF && col.red == 0xFF && col.green == 0xFF) {
           continue;
         }
        
            int xPix = 0 - tilePixel ;
            xPix += 7 ;
            int pixel = xPos+xPix ;
            screen.set_pixel({static_cast<uint8_t>(pixel), scanline}, col);
            }
        }
    }
}

Color PPU::get_color(uint8_t color_id, uint16_t palette_address) {
    
    const uint8_t palette = read(m_memory_controller, palette_address);
    int hi_bit = 0;
    int lo_bit = 0;

    switch (color_id)
    {
        case 0: hi_bit = 1 ; lo_bit = 0 ;break ;
        case 1: hi_bit = 3 ; lo_bit = 2 ;break ;
        case 2: hi_bit = 5 ; lo_bit = 4 ;break ;
        case 3: hi_bit = 7 ; lo_bit = 6 ;break ;
    }

    // use the palette to get the colour
    uint8_t color = 0;
    color = (uint8_t) ((unsigned int)(test_bit_8bit(palette, hi_bit)) << 1U);
    color = (uint8_t) (color | (unsigned int)(test_bit_8bit(palette, lo_bit)));

   // convert the game colour to emulator colour
   switch (color)
   {
     case 0: return {0xFF, 0xFF, 0xFF};
     case 1: return {0xCC, 0xCC, 0xCC}; 
     case 2: return {0x77, 0x77, 0x77};
     case 3: return {0x00, 0x00, 0x00};
     default: return {0xDD, 0xDD, 0xDD};
   }
}