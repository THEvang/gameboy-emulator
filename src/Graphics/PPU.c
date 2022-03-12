#include "PPU.h"
#include <stdlib.h>
#include <assert.h>

#include "LCD_Control.h"
#include "LCD_Status.h"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"
#include "Cpu/Interrupts.h"

void gb_ppu_step(PPU* ppu, MemoryBankController* mc, int cycles) {

    bool lcd_display_enabled = mc->memory[LCD_CONTROL_ADDRESS] & LCD_ENABLED;
    if(!lcd_display_enabled) {
        return;
    }

    gb_set_status(mc, &ppu->scanline_counter);

    ppu->scanline_counter -= cycles;

    if(ppu->scanline_counter <= 0) {

        ppu->scanline_counter = 456;

        uint8_t scanline = mc->memory[LY];

        if(scanline == 144) {
            gb_request_interrupt(mc, Interrupts_V_Blank);
            mc->memory[LY]++;
        } else if (scanline > 153) {
            mc->memory[LY] = 0;
        } else if (scanline < 144) {
            gb_draw_scanline(ppu, mc);
            mc->memory[LY]++;
        } else {
            mc->memory[LY]++;
        }
    }
}

void gb_draw_scanline(PPU* ppu, MemoryBankController* mc) {

    bool draw_background = mc->memory[LCD_CONTROL_ADDRESS] & BACKGROUND_DISPLAY;
    if(draw_background) {
        gb_draw_background(ppu, mc);
    } 

    bool draw_sprites = mc->memory[LCD_CONTROL_ADDRESS] & SPRITE_DISPLAY;
    if(draw_sprites) {
        gb_draw_sprites(ppu, mc);
    }
}

void gb_draw_background(PPU* ppu, MemoryBankController* mc) {

    const uint8_t scroll_y = mc->memory[SCY];
    const uint8_t scroll_x = mc->memory[SCX];
    const uint8_t window_y = mc->memory[WY];
    const uint8_t window_x = (uint8_t) (mc->memory[WX] - 7);
    const uint8_t scanline = mc->memory[LY];
    assert(scanline <= 153);

    bool using_window = mc->memory[LCD_CONTROL_ADDRESS] & WINDOW_DISPLAY_ENABLE 
        && window_y <= scanline;

    for (int pixel_x = 0; pixel_x < 160; pixel_x++) {

        using_window = using_window && pixel_x >= window_x;

        uint8_t x_pos = using_window ? (uint8_t) (pixel_x - window_x):
            (uint8_t) (scroll_x + pixel_x);
        
        uint8_t y_pos = using_window ? (uint8_t) (scanline - window_y):
           (uint8_t) (scanline + scroll_y);

        uint16_t tilemap_address = using_window ? gb_window_tile_map_start_address(mc) :
            gb_background_tile_map_start_address(mc);

        tilemap_address += (uint16_t) (x_pos / 8) + (uint16_t) ((y_pos / 8) * 32);
        assert(tilemap_address >= 0x9800 && tilemap_address <= 0x9FFF);

        uint16_t tile_data_address = gb_tile_data_start_address(mc);
        if(gb_tile_data_signed(mc)) {
            int8_t tile_number = (int8_t) mc->read(mc, tilemap_address);
            tile_data_address += (uint16_t) (tile_number * 16);
        } else {
            uint8_t tile_number = mc->read(mc, tilemap_address);
            tile_data_address += (uint16_t) (tile_number * 16);
        }

        tile_data_address += (y_pos % 8) * 2;
        assert(tile_data_address >= 0x8000 && tile_data_address <= 0x97FF);
        uint8_t tiledata_low = mc->read(mc, tile_data_address++);
        uint8_t tiledata_high = mc->read(mc, tile_data_address);

        int color_bit = x_pos % 8;
        color_bit -= 7;
        color_bit *= -1;

        const uint8_t color_1 = test_bit_8bit(tiledata_low, color_bit) ? 1 : 0;
        const uint8_t color_2 = test_bit_8bit(tiledata_high, color_bit) ? 1 : 0;

        uint8_t color_index = (uint8_t) ((color_2 << 1u) | color_1);
        
        Color pixel_color = gb_get_color(color_index, 0xFF47, mc);
        gb_set_pixel(ppu->screen_buffer , (Point) {.x = pixel_x, .y = scanline}, pixel_color);
    }
}

int compare_x_pos(const void* p, const void* q) {

    Sprite_Attribute a = *(const Sprite_Attribute*) p;
    Sprite_Attribute b = *(const Sprite_Attribute*) q;
    
    if(a.x_pos < b.x_pos) {
        return -1;
    } else if (a.x_pos > b.y_pos) {
        return 1;
    }

    if(a.oam_address < b.oam_address) {
        return -1;
    } 
    
    return 1;
}

void gb_draw_sprites(PPU* ppu, MemoryBankController* mc) {

    int y_size = gb_sprite_size(mc) ? 16 : 8;
    uint8_t size_mask = gb_sprite_size(mc) ? 0b11111110 : 0xFF;
    uint8_t scanline = mc->memory[LY];

    Sprite_Attribute sprites[40];
    int n_sprites = 0;
    //The Gameboy can only draw 10 sprites. So we find the first 10 that is visible
    for(uint16_t oam_address = 0xFE00; oam_address <= 0xFE9F; oam_address += 0x04) {

        const uint8_t y_pos = (uint8_t) (mc->memory[oam_address] - 16);
        
        if ((scanline >= y_pos) && (scanline < (y_pos + y_size))) {
            sprites[n_sprites].y_pos = y_pos;
            sprites[n_sprites].x_pos =  (uint8_t) (mc->memory[oam_address + 1] - 8);
            sprites[n_sprites].tile_location =  mc->memory[oam_address + 2] & size_mask;
            sprites[n_sprites].attributes =  mc->memory[oam_address + 3];
            sprites[n_sprites].oam_address = oam_address;
            n_sprites++;
        }
    }

    qsort(sprites, n_sprites, sizeof(Sprite_Attribute), compare_x_pos);

    for (int sprite = 0; sprite < n_sprites; sprite++) {

        bool yFlip = sprites[sprite].attributes & Y_FLIP;
        bool xFlip = sprites[sprite].attributes & X_FLIP;
            
        int line = scanline - sprites[sprite].y_pos;

        // read the sprite in backwards in the y axis
        if (yFlip) {
            line -= y_size ;
            line *= -1 ;
        }

        line *= 2; // same as for tiles
        uint16_t data_address = (uint16_t) (0x8000 + (sprites[sprite].tile_location * 16) + line);
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
            uint8_t color_index = (uint8_t) ((color_2 << 1u) | color_1);

            const uint16_t palette_address = (sprites[sprite].attributes & PALETTE_NUMBER) ? 0xFF49 : 0xFF48;
            Color col = gb_get_color(color_index, palette_address, mc);

            // white is transparent for sprites.
            if (col.blue == 0xFF && col.red == 0xFF && col.green == 0xFF) {
                continue;
            }
            
            int xPix = 0 - tilePixel;
            xPix += 7 ;
            int pixel = sprites[sprite].x_pos + xPix;
            gb_set_pixel(&ppu->screen_buffer, (Point) {.x = (uint8_t)(pixel), .y = scanline}, col);
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

 void gb_set_pixel(PPU* ppu, Point screen_position, Color color) {

    uint8_t y_pos = screen_position.y;
    uint8_t x_pos = screen_position.x;

    int index = x_pos + y_pos * GB_SCREEN_WIDTH;

    ppu->screen_buffer[index] = (uint32_t) (color.red << 24u | color.green << 16u | color.blue << 8u | color.alpha);
}