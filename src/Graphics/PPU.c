#include "PPU.h"
#include <stdlib.h>
#include <assert.h>

#include "LCD_Control.h"
#include "LCD_Status.h"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"
#include "Cpu/Interrupts.h"
#include "Registers.h"

void gb_ppu_step(PPU* ppu, MemoryBankController* mc, int cycles) {

    bool lcd_display_enabled = mc->memory[LCDC] & LCD_ENABLED;
    if(!lcd_display_enabled) {
        mc->memory[LY] = 0;
        mc->memory[STAT] &= (uint8_t) ~0x03;
        ppu->scanline_counter = 456;
        return;
    }

    gb_set_status(mc, &ppu->scanline_counter);

    ppu->scanline_counter -= cycles;

    if(ppu->scanline_counter <= 0) {

        ppu->scanline_counter = 456;

        uint8_t scanline = mc->memory[LY];

        if (scanline < 144) {
            gb_draw_scanline(ppu, mc);
        }

        scanline++;

        if(scanline == 144) {
            gb_request_interrupt(mc, Interrupts_V_Blank);
        } else if (scanline > 153) {
            scanline = 0;
        }

        mc->memory[LY] = scanline;
    }
}

void gb_draw_scanline(PPU* ppu, MemoryBankController* mc) {

    bool draw_background = mc->memory[LCDC] & BACKGROUND_DISPLAY;
    if(draw_background) {
        gb_draw_background(ppu, mc);
    } else {
        //With the background disabled the line is blank
        const uint8_t scanline = mc->memory[LY];
        for (int pixel_x = 0; pixel_x < GB_SCREEN_WIDTH; pixel_x++) {
            ppu->bg_color_index[pixel_x] = 0;
            gb_set_color(ppu, (Point) {.x = pixel_x, .y = scanline}, ppu->palette[0]);
        }
    }

    bool draw_sprites = mc->memory[LCDC] & SPRITE_DISPLAY;
    if(draw_sprites) {
        gb_draw_sprites(ppu, mc);
    }
}

void gb_draw_background(PPU* ppu, MemoryBankController* mc) {

    const uint8_t scroll_y = mc->memory[SCY];
    const uint8_t scroll_x = mc->memory[SCX];
    const uint8_t window_y = mc->memory[WY];
    const int window_x = mc->memory[WX] - 7;
    const uint8_t scanline = mc->memory[LY];
    assert(scanline <= 153);

    bool using_window = mc->memory[LCDC] & WINDOW_DISPLAY_ENABLE 
        && window_y <= scanline;

    for (int pixel_x = 0; pixel_x < GB_SCREEN_WIDTH; pixel_x++) {

        const bool window_pixel = using_window && pixel_x >= window_x;

        uint8_t x_pos = window_pixel ? (uint8_t) (pixel_x - window_x):
            (uint8_t) (scroll_x + pixel_x);
        
        uint8_t y_pos = window_pixel ? (uint8_t) (scanline - window_y):
           (uint8_t) (scanline + scroll_y);

        uint16_t tilemap_address = window_pixel ? gb_window_tile_map_start_address(mc) :
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
        ppu->bg_color_index[pixel_x] = color_index;
        
        uint32_t pixel_color = gb_get_color(color_index, BGP, mc, ppu);
        gb_set_color(ppu, (Point) {.x = pixel_x, .y = scanline}, pixel_color);
    }
}

int compare_x_pos(const void* p, const void* q) {

    Sprite_Attribute a = *(const Sprite_Attribute*) p;
    Sprite_Attribute b = *(const Sprite_Attribute*) q;
    
    if(a.x_pos < b.x_pos) {
        return -1;
    } else if (a.x_pos > b.x_pos) {
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
    int scanline = mc->memory[LY];

    Sprite_Attribute sprites[10];
    int n_sprites = 0;
    //The Gameboy can only draw 10 sprites per line. So we find the first 10 that is visible
    for(uint16_t oam_address = 0xFE00; oam_address <= 0xFE9F && n_sprites < 10; oam_address += 0x04) {

        const int y_pos = mc->memory[oam_address] - 16;

        if ((scanline >= y_pos) && (scanline < (y_pos + y_size))) {
            sprites[n_sprites].y_pos = y_pos;
            sprites[n_sprites].x_pos = mc->memory[oam_address + 1] - 8;
            sprites[n_sprites].tile_location =  mc->memory[oam_address + 2] & size_mask;
            sprites[n_sprites].attributes =  mc->memory[oam_address + 3];
            sprites[n_sprites].oam_address = oam_address;
            n_sprites++;
        }
    }

    qsort(sprites, (size_t) n_sprites, sizeof(Sprite_Attribute), compare_x_pos);

    // Sprites with a lower x position (then lower oam address) have priority,
    // so they are drawn last
    for (int sprite = n_sprites - 1; sprite >= 0; sprite--) {

        bool yFlip = sprites[sprite].attributes & Y_FLIP;
        bool xFlip = sprites[sprite].attributes & X_FLIP;
        bool behind_background = sprites[sprite].attributes & BG_AND_WINDOW_OVER_OBJECT;

        int line = scanline - sprites[sprite].y_pos;

        // read the sprite in backwards in the y axis
        if (yFlip) {
            line = y_size - 1 - line;
        }

        line *= 2; // same as for tiles
        uint16_t data_address = (uint16_t) (0x8000 + (sprites[sprite].tile_location * 16) + line);

        const uint8_t data_1 = mc->read(mc,  data_address);
        const uint8_t data_2 = mc->read(mc, ++data_address);

        const uint16_t palette_address = (sprites[sprite].attributes & PALETTE_NUMBER) ? OBP1 : OBP0;

        // pixel 0 is bit 7 in the colour data, pixel 1 is bit 6 etc...
        for (int tile_pixel = 0; tile_pixel < 8; tile_pixel++) {

            const int pixel = sprites[sprite].x_pos + tile_pixel;
            if (pixel < 0 || pixel >= GB_SCREEN_WIDTH) {
                continue;
            }

            // read the sprite in backwards for the x axis
            const int color_bit = xFlip ? tile_pixel : 7 - tile_pixel;

            const uint8_t color_1 = test_bit_8bit(data_1, color_bit) ? 1 : 0;
            const uint8_t color_2 = test_bit_8bit(data_2, color_bit) ? 1 : 0;
            uint8_t color_index = (uint8_t) ((color_2 << 1u) | color_1);

            // color 0 is transparent for sprites.
            if (color_index == 0) {
                continue;
            }

            if (behind_background && ppu->bg_color_index[pixel] != 0) {
                continue;
            }

            uint32_t col = gb_get_color(color_index, palette_address, mc, ppu);
            gb_set_color(ppu, (Point) {.x = pixel, .y = scanline}, col);
        }
    }
}

uint32_t gb_get_color(uint8_t color_index, uint16_t palette_address, MemoryBankController* mc, PPU* ppu) {
    
    const uint8_t palette = mc->memory[palette_address];
    uint8_t mask = 0x03;
    uint8_t color =  (uint8_t) (palette >> (color_index * 2)) & mask;
    return ppu->palette[color];
}

 void gb_set_color(PPU* ppu, Point screen_coordinates, uint32_t color) {

    int y_pos = screen_coordinates.y;
    int x_pos = screen_coordinates.x;

    int index = x_pos + y_pos * GB_SCREEN_WIDTH;
    ppu->screen_buffer[index] = color;
}