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
    sf::Color palScreen[0x40];
    sf::VertexArray screen;

    void setPixel(int x, int y, sf::Color color);
    void addVertex(int x, int y);

public:
    int pixelSize = 3;
    int width = 768;
    int height = 720;
    sf::VertexArray &getScreen();
    bool frame_complete = false;

private:
    int16_t scanline = 0;
    int16_t cycle = 0;

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
};
