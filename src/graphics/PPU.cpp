#include "graphics/PPU.h"
#include "BitOperations.h"

PPU::PPU(MemoryBankController* memory_controller)
    : m_memory_controller(memory_controller)
    , m_interrupt_handler(m_memory_controller)
    , m_lcd_control(m_memory_controller)
    , m_lcd_status(m_memory_controller, m_lcd_control)
    , m_pixels()
{}

void PPU::step(int cycles) {

    auto current_scanline = m_memory_controller->read(scanline_address);
    m_lcd_status.set_status(m_scanline_counter);

    if(!m_lcd_control.lcd_display_enabled()) {
        return;
    }

    m_scanline_counter -= cycles;

    if(m_scanline_counter <= 0) {

        m_scanline_counter = 456;
        
        current_scanline++;
        m_memory_controller->raw()->write(scanline_address, current_scanline);

        if(current_scanline == 144) {
            m_interrupt_handler.request_v_blank_interrupt();
        } else if (current_scanline > 153) {
            m_memory_controller->raw()->write(scanline_address, 0);
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

    const auto scroll_y = m_memory_controller->read(scroll_y_address);
    const auto scroll_x = m_memory_controller->read(scroll_x_address);
    const auto window_y = m_memory_controller->read(window_scroll_y_address);
    const auto window_x = m_memory_controller->read(window_scroll_x_address) - 7;
    const auto scanline = m_memory_controller->read(scanline_address);

    auto using_window = false;
    if(m_lcd_control.window_display_enabled()) {
        using_window = window_y <= scanline;
    }

    const auto tile_data_start_address = m_lcd_control.tile_data_start_address();
    const auto tile_map_start_address = using_window ? m_lcd_control.window_tile_map_start_address() :
        m_lcd_control.background_tile_map_start_address();

    const auto y_pos = using_window ? scanline - window_y : 
        scroll_y + scanline;

    constexpr auto horizontal_pixels = 160;
    for(int pixel = 0; pixel < horizontal_pixels; pixel++) {

        auto x_pos = scroll_x + pixel;
        if(using_window) {
            if(pixel >= window_x) {
                x_pos = pixel - window_x;
            }
        }

        const auto tile_column = x_pos / 8;
        const auto tile_row = (y_pos / 8) * 32; 
        const auto tile_map_address = tile_map_start_address + tile_row + tile_column;

        int tile_number = 0;
        if(m_lcd_control.tile_data_signed()) {
            tile_number = static_cast<int8_t>( m_memory_controller->read(tile_map_address));
        } else {
            tile_number = m_memory_controller->read(tile_map_address);
        }

        auto tile_data_address = tile_data_start_address;
        tile_data_address += m_lcd_control.tile_data_signed() ? (tile_number+128)*16 : tile_number * 16;
       
        const auto line = (y_pos % 8) * 2;
        const auto data_1 = m_memory_controller->read(tile_data_address + line);
        const auto data_2 = m_memory_controller->read(tile_data_address + line + 1);

        auto color_bit = x_pos % 8;
        color_bit -= 7;
        color_bit *= -1;

        const auto color_1 = is_set(data_1, color_bit);
        const auto color_2 = is_set(data_2, color_bit);
        
        auto color_id = 0;
        color_id = color_2 << 1; 
        color_id |= color_1;

        Color pixel_color = get_color(color_id, 0xFF47);
        m_pixels.set_pixel({pixel, scanline}, pixel_color);
    }
}

void PPU::draw_sprites() {

  bool use8x16 = false;
  if(m_lcd_control.sprite_size()) {
    use8x16 = true ;
  }

   for (int sprite = 0 ; sprite < 40; sprite++)
   {
     // sprite occupies 4 bytes in the sprite attributes table
     const auto index = sprite*4 ;
     const auto yPos = m_memory_controller->read(0xFE00+index) - 16;
     const auto xPos = m_memory_controller->read(0xFE00+index+1)-8;
     const auto tileLocation = m_memory_controller->read(0xFE00+index+2) ;
     const auto attributes = m_memory_controller->read(0xFE00+index+3) ;

     bool yFlip = is_set(attributes,6) ;
     bool xFlip = is_set(attributes,5) ;

     int scanline = m_memory_controller->read(0xFF44);

    auto ysize = use8x16 ? 16 : 8;

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
       const auto dataAddress = (0x8000 + (tileLocation * 16)) + line ;
       const auto data1 = m_memory_controller->read( dataAddress ) ;
       const auto data2 = m_memory_controller->read( dataAddress +1 ) ;

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
         colourNum +=  is_set(data2,colourbit) ? 2 : 0;
         colourNum += is_set(data1,colourbit) ? 1 : 0;

        const auto colourAddress = is_set(attributes,4) ? 0xFF49 : 0xFF48;
        const auto col = get_color(colourNum, colourAddress);

        //  // white is transparent for sprites.
        //  if (col == Color{0x00, 0x00, 0x00}) {
        //    continue ;
        //  }

         int xPix = 0 - tilePixel ;
         xPix += 7 ;

         int pixel = xPos+xPix ;

         // sanity check
         if ((scanline<0)||(scanline>143)||(pixel<0)||(pixel>159))
         {
           continue;
         }
            m_pixels.set_pixel({pixel, scanline}, col);

     }
   }
}
}

Color PPU::get_color(int color_id, uint16_t palette_address) {
    const auto palette = m_memory_controller->read(palette_address);
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
    int color = 0;
    color = is_set(palette, hi_bit) << 1;
    color |= is_set(palette, lo_bit);

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

int PPU::tile_number(const Screen_Position& screen_position) const {
    
    const auto tile_row = (screen_position.y / pixels_in_tile) * horizontal_tiles;
    const auto tile_column = screen_position.x / pixels_in_tile;
    return tile_row + tile_column;
}

uint16_t PPU::tile_data_address(int tile_identifier_address) const {

    const auto tile_identifier = m_lcd_control.tile_data_signed() ? static_cast<int8_t>(m_memory_controller->read(tile_identifier_address)) :
        m_memory_controller->read(tile_identifier_address);

    const auto tile_data_start_address = m_lcd_control.tile_data_signed() ? 0x8800 : 0x9C00;
    const auto tile_data_offset = m_lcd_control.tile_data_signed() ? ((tile_identifier + 128) * 16) : tile_identifier * 16; 

    return tile_data_start_address + tile_data_offset;
}