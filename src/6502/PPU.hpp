#pragma once
#include <cstdint>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Cartridge.hpp"

class PPU
{
public:
    PPU();
    ~PPU();

private:
    uint8_t tblName[2][1024];
    uint8_t tblPattern[2][4096];
    uint8_t tblPalette[32];

private:
    sf::Color palScreen[0x40];
    sf::VertexArray screen;
    sf::VertexArray nameTable[2];
	sf::VertexArray patternTable[2];

    void setPixel(int x, int y, sf::Color color, sf::VertexArray &spr);
    void addVertex(int x, int y, sf::VertexArray &spr);

public:
    int pixelSize = 3;
    int width = 768;
    int height = 720;
    sf::VertexArray &getScreen();
    sf::VertexArray &getNameTable(uint8_t i);
    sf::VertexArray &getPatternTable(uint8_t i, uint8_t palette);

    sf::Color &getColourFromPaletteRam(uint8_t palette, uint8_t pixel);
    bool frame_complete = false;

private:
    union
    {
        struct
        {
            uint8_t unused : 5;
            uint8_t sprite_overflow : 1;
            uint8_t sprite_zero_hit : 1;
            uint8_t vertical_blank : 1;
        };

        uint8_t reg;
    } status;

    union
    {
        struct
        {
            uint8_t grayscale : 1;
            uint8_t render_background_left : 1;
            uint8_t render_sprites_left : 1;
            uint8_t render_background : 1;
            uint8_t render_sprites : 1;
            uint8_t enhance_red : 1;
            uint8_t enhance_green : 1;
            uint8_t enhance_blue : 1;
        };

        uint8_t reg;
    } mask;

    union PPUCTRL
    {
        struct
        {
            uint8_t nametable_x : 1;
            uint8_t nametable_y : 1;
            uint8_t increment_mode : 1;
            uint8_t pattern_sprite : 1;
            uint8_t pattern_background : 1;
            uint8_t sprite_size : 1;
            uint8_t slave_mode : 1; // unused
            uint8_t enable_nmi : 1;
        };

        uint8_t reg;
    } control;

    union loopy_register
    {
        // Credit to Loopy for working this out :D
        struct
        {

            uint16_t coarse_x : 5;
            uint16_t coarse_y : 5;
            uint16_t nametable_x : 1;
            uint16_t nametable_y : 1;
            uint16_t fine_y : 3;
            uint16_t unused : 1;
        };

        uint16_t reg = 0x0000;
    };

    loopy_register vram_addr; // Active "pointer" address into nametable to extract background tile info
    loopy_register tram_addr; // Temporary store of information to be "transferred" into "pointer" at various times

    // Pixel offset horizontally
    uint8_t fine_x = 0x00;

    // Internal communications
    uint8_t address_latch = 0x00;
    uint8_t ppu_data_buffer = 0x00;

    // Pixel "dot" position information
    int16_t scanline = 0;
    int16_t cycle = 0;

    // Background rendering
    uint8_t bg_next_tile_id = 0x00;
    uint8_t bg_next_tile_attrib = 0x00;
    uint8_t bg_next_tile_lsb = 0x00;
    uint8_t bg_next_tile_msb = 0x00;
    uint16_t bg_shifter_pattern_lo = 0x0000;
    uint16_t bg_shifter_pattern_hi = 0x0000;
    uint16_t bg_shifter_attrib_lo = 0x0000;
    uint16_t bg_shifter_attrib_hi = 0x0000;

public:
    uint8_t cpuRead(uint16_t addr, bool rdonly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

    uint8_t ppuRead(uint16_t addr, bool rdonly = false);
    void ppuWrite(uint16_t addr, uint8_t data);

private:
    std::shared_ptr<Cartridge> cart;

public:
    void connectCartridge(const std::shared_ptr<Cartridge> &cartridge);
    void clock();
    void reset();
    bool nmi = false;
};
