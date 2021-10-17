#include "PPU.h"
#include <stdlib.h>
#include <assert.h>

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

        uint8_t current_scanline = mc->read(mc, g_scanline_address);    

        if(current_scanline == 144) {
            gb_request_interrupt(mc, Interrupts_V_Blank);
        } else if (current_scanline > 153) {
            mc->memory[g_scanline_address] = 0;
        } else if (current_scanline < 144) {
            gb_draw_scanline(ppu, mc);
        }
        current_scanline++;
        mc->memory[g_scanline_address] = current_scanline;
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
    const uint8_t window_x = mc->memory[window_scroll_x_address] -  7;
    const uint8_t scanline = mc->memory[g_scanline_address];

    bool using_window = gb_window_display_enabled(mc) && window_y <= scanline;

    const uint16_t tile_map_start_address = using_window ? gb_window_tile_map_start_address(mc) :
        gb_background_tile_map_start_address(mc);
    
    const uint16_t tile_data_start_addr = gb_tile_data_start_address(mc);

    const uint8_t y_pos = using_window ? (uint8_t) (scanline - window_y) : 
        (uint8_t) (scroll_y + scanline);

    const uint16_t tile_row = (uint16_t) ( (uint8_t) ((y_pos / 8)) * 32); 

    for(uint8_t pixel = 0; pixel < 160; pixel++) {

        uint8_t x_pos = scroll_x + pixel;
        if(using_window) {
            if(pixel >= window_x) {
                x_pos = (uint8_t) (pixel - window_x);
            }
        }

        const uint16_t tile_column = (uint16_t) ((x_pos / 8));
        const uint16_t tile_map_address = (uint16_t) (tile_map_start_address + tile_row + tile_column);

        uint16_t tile_data_address = tile_data_start_addr;

        if(gb_tile_data_signed(mc)) {
            int8_t tile_number = (int8_t) mc->read(mc, tile_map_address);
            tile_data_address += (int16_t) (tile_number * 16);
        } else {
            uint8_t tile_number = mc->read(mc, tile_map_address);
            tile_data_address += (uint16_t) (tile_number * 16);
        }

        assert(tile_data_address >= 0x8000 && tile_data_address <= 0x97FF);
        uint8_t line = (uint8_t) ((y_pos % 8) * 2);
        const uint8_t data_1 = mc->read(mc, (uint16_t) (tile_data_address + line));
        const uint8_t data_2 = mc->read(mc, (uint16_t) (tile_data_address + line + 1));

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

int compare_x_pos(const void* p, const void* q) {

    Sprite_Attribute x = *(const Sprite_Attribute*) p;
    Sprite_Attribute y = *(const Sprite_Attribute*) q;
    
    if(x.x_pos < y.x_pos) {
        return -1;
    } else if (x.x_pos > y.y_pos) {
        return 1;
    }

    return 0;
}

void gb_draw_sprites(PPU* ppu, MemoryBankController* mc) {

    int y_size = gb_sprite_size(mc) ? 16 : 8;
    uint8_t scanline = mc->memory[g_scanline_address];

    Sprite_Attribute sprites[10];
    int n_sprites = 0;
    //The Gameboy can only draw 10 sprites. So we find the first 10 that is visible
    for(uint16_t oam_address = 0xFE00; oam_address <= 0xFE9F  && n_sprites < 10; oam_address += 0x04) {

        const uint8_t y_pos = mc->memory[oam_address] - 16;
        
        if ((scanline >= y_pos) && (scanline < (y_pos + y_size))) {
            sprites[n_sprites].y_pos = y_pos;
            sprites[n_sprites].x_pos =  mc->memory[oam_address + 1] - 8;
            sprites[n_sprites].tile_location =  mc->memory[oam_address + 2];
            sprites[n_sprites].attributes =  mc->memory[oam_address + 3];
            n_sprites++;
        }
    }

    qsort(sprites, n_sprites, sizeof(Sprite_Attribute), compare_x_pos);

    for (int sprite = n_sprites-1; sprite >= 0; sprite--) {

        bool yFlip = sprites[sprite].attributes & Y_FLIP;
        bool xFlip = sprites[sprite].attributes & X_FLIP;
            
        int line = scanline - sprites[sprite].y_pos;

        // read the sprite in backwards in the y axis
        if (yFlip) {
            line -= y_size ;
            line *= -1 ;
        }

        line *= 2; // same as for tiles
        uint16_t data_address = 0x8000 + (sprites[sprite].tile_location * 16) + line;
        assert(data_address <= 0x8FFF);

        const uint8_t data_1 = mc->read(mc,  data_address);
        const uint8_t data_2 = mc->read(mc, ++data_address);

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

            const uint16_t palette_address = (sprites[sprite].attributes & PALETTE_NUMBER) ? 0xFF49 : 0xFF48;
            Color col = gb_get_color(color_index, palette_address, mc);

            // white is transparent for sprites.
            if (col.blue == 0xFF && col.red == 0xFF && col.green == 0xFF) {
                continue;
            }
            
            int xPix = 0 - tilePixel;
            xPix += 7 ;
            int pixel = sprites[sprite].x_pos + xPix;
            set_pixel(&(ppu->screen), (Screen_Position) {.x = (uint8_t)(pixel), .y = scanline}, col);
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