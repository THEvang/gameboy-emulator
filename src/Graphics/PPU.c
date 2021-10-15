#include "PPU.h"
#include <stdlib.h>

#include "LCD_Control.h"
#include "LCD_Status.h"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"
#include "Cpu/Interrupts.h"

void gb_ppu_step(PPU* ppu, MemoryBankController* mc, int cycles) {

    gb_set_status(mc, &(ppu->scanline_counter));
    if(!gb_lcd_display_enabled(mc)) {
        return;
    }

    ppu->scanline_counter -= cycles;

    if(ppu->scanline_counter <= 0) {

        ppu->scanline_counter = 456;

        uint8_t current_scanline = gb_read(mc, g_scanline_address);    
        current_scanline++;
        mc->memory[g_scanline_address] = current_scanline;

        if(current_scanline == 144) {
            gb_request_interrupt(mc, Interrupts_V_Blank);
        } else if (current_scanline > 153) {
            mc->memory[g_scanline_address] = 0;
        } else if (current_scanline < 144) {
            gb_draw_scanline(ppu, mc);
        }
    }
}

void gb_draw_scanline(PPU* ppu, MemoryBankController* mc) {

    if(gb_background_display_enabled(mc)) {
        gb_draw_background(ppu, mc);
    }

    if(gb_sprite_display_enabled(mc)) {
        gb_draw_sprites(ppu, mc);
    }
}

void gb_draw_background(PPU* ppu, MemoryBankController* mc) {

    const uint16_t scroll_y_address = 0xFF42; 
    const uint16_t scroll_x_address = 0xFF43;
    const uint16_t window_scroll_y_address = 0xFF4A;
    const uint16_t window_scroll_x_address = 0xFF4B;

    const uint8_t scroll_y = mc->memory[scroll_y_address];
    const uint8_t scroll_x = mc->memory[scroll_x_address];
    const uint8_t window_y = mc->memory[window_scroll_y_address];
    const uint8_t window_x = (uint8_t) (mc->memory[window_scroll_x_address] - (uint8_t) 7);
    const uint8_t scanline = mc->memory[g_scanline_address];

    bool using_window = false;
    if(gb_window_display_enabled(mc)) {
        using_window = window_y <= scanline;
    }

    const uint16_t tile_map_start_address = using_window ? gb_window_tile_map_start_address(mc) :
        gb_background_tile_map_start_address(mc);

    const uint8_t y_pos = using_window ? (uint8_t) (scanline - window_y) : 
        (uint8_t) (scroll_y + scanline);

    const uint16_t tile_row = (uint16_t) ( (uint8_t) ((y_pos / 8)) * 32); 

    for(uint8_t pixel = 0; pixel < 160; pixel++) {

        uint8_t x_pos = (uint8_t) (scroll_x + pixel);
        if(using_window) {
            if(pixel >= window_x) {
                x_pos = (uint8_t) (pixel - window_x);
            }
        }

        const uint16_t tile_column = (uint16_t) ((x_pos / 8));
        const uint16_t tile_map_address = (uint16_t) (tile_map_start_address + tile_row + tile_column);

        const uint16_t tile_data_start_addr = gb_tile_data_start_address(mc);
        uint16_t tile_data_address = tile_data_start_addr;

        if(gb_tile_data_signed(mc)) {
            int8_t tile_number = (int8_t) gb_read(mc, tile_map_address);
            tile_data_address += (int16_t) (tile_number * 16);

        } else {
            uint16_t tile_number = gb_read(mc, tile_map_address);
            tile_data_address += (uint16_t) (tile_number * 16);
        }

        uint8_t line = (uint8_t) ((y_pos % 8) * 2);
        const uint8_t data_1 = gb_read(mc, (uint16_t) (tile_data_address + line));
        const uint8_t data_2 = gb_read(mc, (uint16_t) (tile_data_address + line + 1));

        int color_bit = x_pos % 8;
        color_bit -= 7;
        color_bit *= -1;

        const uint8_t color_1 = test_bit_8bit(data_1, color_bit) ? 1 : 0;
        const uint8_t color_2 = test_bit_8bit(data_2, color_bit) ? 1 : 0;
        
        uint8_t color_index = (color_2 << 1u) | color_1;
    
        Color pixel_color = gb_get_color(color_index, 0xFF47, mc);
        set_pixel(&(ppu->screen) , (Screen_Position) {.x = pixel, .y = scanline}, pixel_color);
    }
}

void gb_draw_sprites(PPU* ppu, MemoryBankController* mc) {

    bool use8x16 = false;
    if(gb_sprite_size(mc)) {
        use8x16 = true;
    }
    
   for (int sprite = 0; sprite < 40; sprite++) {
    
        // sprite occupies 4 bytes in the sprite attributes table
        const uint8_t sprite_index = (uint8_t) (sprite * 4);
        const uint8_t yPos = (uint8_t) (gb_read(mc, (uint16_t) (0xFE00 + sprite_index)) - 16);
        const uint8_t xPos = (uint8_t) (gb_read(mc, (uint16_t) (0xFE00 + sprite_index + 1)) - 8);
        const uint8_t tileLocation = gb_read(mc, (uint16_t) (0xFE00 + sprite_index + 2));
        const uint8_t attributes = gb_read(mc, (uint16_t) (0xFE00 + sprite_index + 3));

        bool yFlip = test_bit_8bit(attributes, 6);
        bool xFlip = test_bit_8bit(attributes, 5);

        uint8_t scanline = gb_read(mc, g_scanline_address);

        int ysize = use8x16 ? 16 : 8;

        // does this sprite intercept with the scanline?
        if ((scanline >= yPos) && (scanline < (yPos + ysize))) {
            
            int line = scanline - yPos;

            // read the sprite in backwards in the y axis
            if (yFlip) {
                line -= ysize ;
                line *= -1 ;
            }

            line *= 2; // same as for tiles
            const uint16_t dataAddress = (uint16_t) ((0x8000 + (tileLocation * 16)) + line);
            const uint8_t data_1 = gb_read(mc,  dataAddress ) ;
            const uint8_t data_2 = gb_read(mc, (uint16_t) (dataAddress +1)) ;

            // its easier to read in from right to left as pixel 0 is
            // bit 7 in the colour data, pixel 1 is bit 6 etc...
            for (int tilePixel = 7; tilePixel >= 0; tilePixel--) {
                
                int color_bit = tilePixel;
                // read the sprite in backwards for the x axis
                if (xFlip) {
                        color_bit -= 7;
                        color_bit *= -1;
                }

                // the rest is the same as for tiles
                const uint8_t color_1 = test_bit_8bit(data_1, color_bit) ? 1 : 0;
                const uint8_t color_2 = test_bit_8bit(data_2, color_bit) ? 1 : 0;
                uint8_t color_index = (color_2 << 1u) | color_1;

                const uint16_t palette_address = test_bit_8bit(attributes, 4) ? 0xFF49 : 0xFF48;
                Color col = gb_get_color(color_index, palette_address, mc);

                // white is transparent for sprites.
                if (col.blue == 0xFF && col.red == 0xFF && col.green == 0xFF) {
                    continue;
                }
                
                int xPix = 0 - tilePixel;
                xPix += 7 ;
                int pixel = xPos + xPix;
                set_pixel(&(ppu->screen), (Screen_Position) {.x = (uint8_t)(pixel), .y = scanline}, col);
            }
        }
    }
}

Color gb_get_color(uint8_t color_index, uint16_t palette_address, MemoryBankController* mc) {
    
    const uint8_t palette = mc->memory[palette_address];
    uint8_t mask = 0x03;
    uint8_t color =  (uint8_t) (palette >> (color_index * 2)) & mask;

    static Color colors[4] = {
        {.red = 0xFF, .green = 0xFF, .blue = 0xFF, .alpha = 0xFF},
        {.red = 0xA9, .green = 0xA9, .blue = 0xA9, .alpha = 0xFF},
        {.red = 0x54, .green = 0x54, .blue = 0x54, .alpha = 0xFF},
        {.red = 0x00, .green = 0x00, .blue = 0x00, .alpha = 0xFF}
    };

    return colors[color];
 }