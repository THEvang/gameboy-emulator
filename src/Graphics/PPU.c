#include "PPU.h"

#include "LCD_Control.h"
#include "LCD_Status.h"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"
#include "Cpu/Interrupts.h"

void gb_ppu_step(PPU* ppu, int cycles) {

    set_status(ppu->memory_controller, &(ppu->scanline_counter));
    if(!lcd_display_enabled(ppu->memory_controller)) {
        return;
    }

    ppu->scanline_counter -= cycles;

    if(ppu->scanline_counter <= 0) {

        ppu->scanline_counter = 456;

        uint8_t current_scanline = gb_read(ppu->memory_controller, g_scanline_address);    
        current_scanline++;
        ppu->memory_controller->memory[g_scanline_address] = current_scanline;

        if(current_scanline == 144) {
            request_interrupt(ppu->memory_controller, Interrupts_V_Blank);
        } else if (current_scanline > 153) {
            ppu->memory_controller->memory[g_scanline_address] = 0;
        } else if (current_scanline < 144) {
            gb_draw_scanline(ppu, ppu->memory_controller);
        }
    }
}

void gb_draw_scanline(PPU* ppu, MemoryBankController* mc) {

    if(background_display_enabled(mc)) {
        gb_draw_background(ppu, mc);
    }

    if(sprite_display_eanbled(mc)) {
        gb_draw_sprites(ppu, mc);
    }
}

void gb_draw_background(PPU* ppu, MemoryBankController* mc) {

    const uint16_t scroll_y_address = 0xFF42; 
    const uint16_t scroll_x_address = 0xFF43;
    const uint16_t window_scroll_y_address = 0xFF4A;
    const uint16_t window_scroll_x_address = 0xFF4B;

    const uint8_t scroll_y = gb_read(mc, scroll_y_address);
    const uint8_t scroll_x = gb_read(mc, scroll_x_address);
    const uint8_t window_y = gb_read(mc, window_scroll_y_address);
    const uint8_t window_x = (uint8_t) (gb_read(mc, window_scroll_x_address) - (uint8_t) 7);
    const uint8_t scanline = gb_read(mc, g_scanline_address);

    bool using_window = false;
    if(window_display_enabled(mc)) {
        using_window = window_y <= scanline;
    }

    const uint16_t tile_data_start_addr = tile_data_start_address(mc);
    const uint16_t tile_map_start_address = using_window ? window_tile_map_start_address(mc) :
        background_tile_map_start_address(mc);

    const uint8_t y_pos = using_window ? (uint8_t)(scanline - window_y) : 
        (uint8_t) (scroll_y + scanline);

    const uint16_t tile_row = (uint16_t) ( (uint8_t) ((y_pos / 8)) * 32); 

    const uint8_t horizontal_pixels = 160;
    for(uint8_t pixel = 0; pixel < horizontal_pixels; pixel++) {

        uint8_t x_pos = (uint8_t) (scroll_x + pixel);
        if(using_window) {
            if(pixel >= window_x) {
                x_pos = (uint8_t) (pixel - window_x);
            }
        }

        const uint16_t tile_column = (uint16_t) ((x_pos / 8));
        const uint16_t tile_map_address = (uint16_t) (tile_map_start_address + tile_row + tile_column);

        uint16_t tile_data_address = tile_data_start_addr;

        if(tile_data_signed(mc)) {
            const int8_t tile_number = (int8_t) gb_read(mc, tile_map_address);
            tile_data_address = (uint16_t) (tile_data_address + (tile_number + 128) * 16);

        } else {
            const uint8_t tile_number = gb_read(mc, tile_map_address);
            tile_data_address = (uint16_t) (tile_number * 16 + tile_data_address);
        }

        uint8_t line = (uint8_t) ((y_pos % 8) * 2);
        const uint8_t data_1 = gb_read(mc, (uint16_t) (tile_data_address + line));
        const uint8_t data_2 = gb_read(mc, (uint16_t) (tile_data_address + line + 1));

        uint8_t color_bit = x_pos % 8;
        color_bit -= 7;
        color_bit *= -1;

        const uint8_t color_1 = test_bit_8bit(data_1, color_bit) ? 1 : 0;
        const uint8_t color_2 = test_bit_8bit(data_2, color_bit) ? 1 : 0;
        
        uint8_t color_id = 0;
        color_id = (uint8_t) (color_2 << 1U); 
        color_id |= color_1;

        Color pixel_color = gb_get_color(color_id, 0xFF47, mc);
        set_pixel(&(ppu->screen) , (Screen_Position) {.x = pixel, .y = scanline}, pixel_color);
    }
}

void gb_draw_sprites(PPU* ppu, MemoryBankController* mc) {

    bool use8x16 = false;
    if(sprite_size(mc)) {
        use8x16 = true;
    }
    
   for (int sprite = 0 ; sprite < 40; sprite++)
   {
    
    // sprite occupies 4 bytes in the sprite attributes table
    const uint8_t index = (uint8_t) sprite * 4;
    const uint8_t yPos = (uint8_t) (gb_read(mc, (uint16_t) (0xFE00+index)) - 16);
    const uint8_t xPos = (uint8_t) (gb_read(mc, (uint16_t) (0xFE00+index+1)) - 8);
    const uint8_t tileLocation = gb_read(mc, (uint16_t) (0xFE00 + index + 2));
    const uint8_t attributes = gb_read(mc, (uint16_t) (0xFE00 + index + 3));

    bool yFlip = test_bit_8bit(attributes,6) ;
    bool xFlip = test_bit_8bit(attributes,5) ;

    uint8_t scanline = gb_read(mc, g_scanline_address);

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
       const uint16_t dataAddress = (uint16_t) ((0x8000 + (tileLocation * 16)) + line);
       const uint8_t data1 = gb_read(mc,  dataAddress ) ;
       const uint8_t data2 = gb_read(mc, (uint16_t) (dataAddress +1)) ;

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
        const Color col = gb_get_color((uint8_t) (colourNum), colourAddress, mc);

         // white is transparent for sprites.
         if (col.blue == 0xFF && col.red == 0xFF && col.green == 0xFF) {
           continue;
         }
        
            int xPix = 0 - tilePixel ;
            xPix += 7 ;
            int pixel = xPos+xPix ;
            set_pixel(&(ppu->screen), (Screen_Position) {.x = (uint8_t)(pixel), .y =scanline}, col);
            }
        }
    }
}

Color gb_get_color(uint8_t color_id, uint16_t palette_address, MemoryBankController* mc) {
    
    const uint8_t palette = gb_read(mc, palette_address);
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
     case 0: return (Color) {.red = 0xFF, .green = 0xFF, .blue = 0xFF};
     case 1: return (Color) {.red = 0xCC, .green = 0xCC, .blue = 0xCC}; 
     case 2: return (Color) {.red = 0x77, .green = 0x77, .blue = 0x77};
     case 3: return (Color) {.red = 0x00, .green = 0x00, .blue = 0x00};
     default: return (Color) {.red = 0xDD, .green = 0xDD, .blue = 0xDD};
   }
}