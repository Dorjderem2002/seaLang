#include "PPU.hpp"

#include <iostream>

PPU::PPU()
{
    std::cout << "PPU initialized" << std::endl;
    palScreen[0x00] = sf::Color(84, 84, 84);
    palScreen[0x01] = sf::Color(0, 30, 116);
    palScreen[0x02] = sf::Color(8, 16, 144);
    palScreen[0x03] = sf::Color(48, 0, 136);
    palScreen[0x04] = sf::Color(68, 0, 100);
    palScreen[0x05] = sf::Color(92, 0, 48);
    palScreen[0x06] = sf::Color(84, 4, 0);
    palScreen[0x07] = sf::Color(60, 24, 0);
    palScreen[0x08] = sf::Color(32, 42, 0);
    palScreen[0x09] = sf::Color(8, 58, 0);
    palScreen[0x0A] = sf::Color(0, 64, 0);
    palScreen[0x0B] = sf::Color(0, 60, 0);
    palScreen[0x0C] = sf::Color(0, 50, 60);
    palScreen[0x0D] = sf::Color(0, 0, 0);
    palScreen[0x0E] = sf::Color(0, 0, 0);
    palScreen[0x0F] = sf::Color(0, 0, 0);

    palScreen[0x10] = sf::Color(152, 150, 152);
    palScreen[0x11] = sf::Color(8, 76, 196);
    palScreen[0x12] = sf::Color(48, 50, 236);
    palScreen[0x13] = sf::Color(92, 30, 228);
    palScreen[0x14] = sf::Color(136, 20, 176);
    palScreen[0x15] = sf::Color(160, 20, 100);
    palScreen[0x16] = sf::Color(152, 34, 32);
    palScreen[0x17] = sf::Color(120, 60, 0);
    palScreen[0x18] = sf::Color(84, 90, 0);
    palScreen[0x19] = sf::Color(40, 114, 0);
    palScreen[0x1A] = sf::Color(8, 124, 0);
    palScreen[0x1B] = sf::Color(0, 118, 40);
    palScreen[0x1C] = sf::Color(0, 102, 120);
    palScreen[0x1D] = sf::Color(0, 0, 0);
    palScreen[0x1E] = sf::Color(0, 0, 0);
    palScreen[0x1F] = sf::Color(0, 0, 0);

    palScreen[0x20] = sf::Color(236, 238, 236);
    palScreen[0x21] = sf::Color(76, 154, 236);
    palScreen[0x22] = sf::Color(120, 124, 236);
    palScreen[0x23] = sf::Color(176, 98, 236);
    palScreen[0x24] = sf::Color(228, 84, 236);
    palScreen[0x25] = sf::Color(236, 88, 180);
    palScreen[0x26] = sf::Color(236, 106, 100);
    palScreen[0x27] = sf::Color(212, 136, 32);
    palScreen[0x28] = sf::Color(160, 170, 0);
    palScreen[0x29] = sf::Color(116, 196, 0);
    palScreen[0x2A] = sf::Color(76, 208, 32);
    palScreen[0x2B] = sf::Color(56, 204, 108);
    palScreen[0x2C] = sf::Color(56, 180, 204);
    palScreen[0x2D] = sf::Color(60, 60, 60);
    palScreen[0x2E] = sf::Color(0, 0, 0);
    palScreen[0x2F] = sf::Color(0, 0, 0);

    palScreen[0x30] = sf::Color(236, 238, 236);
    palScreen[0x31] = sf::Color(168, 204, 236);
    palScreen[0x32] = sf::Color(188, 188, 236);
    palScreen[0x33] = sf::Color(212, 178, 236);
    palScreen[0x34] = sf::Color(236, 174, 236);
    palScreen[0x35] = sf::Color(236, 174, 212);
    palScreen[0x36] = sf::Color(236, 180, 176);
    palScreen[0x37] = sf::Color(228, 196, 144);
    palScreen[0x38] = sf::Color(204, 210, 120);
    palScreen[0x39] = sf::Color(180, 222, 120);
    palScreen[0x3A] = sf::Color(168, 226, 144);
    palScreen[0x3B] = sf::Color(152, 226, 180);
    palScreen[0x3C] = sf::Color(160, 214, 228);
    palScreen[0x3D] = sf::Color(160, 162, 160);
    palScreen[0x3E] = sf::Color(0, 0, 0);
    palScreen[0x3F] = sf::Color(0, 0, 0);

    screen = sf::VertexArray(sf::Triangles, 3);
    for (int y = 0; y < height; y += pixelSize)
    {
        for (int x = 0; x < width; x += pixelSize)
        {
            addVertex(x, y);
        }
    }
}

PPU::~PPU()
{
}

sf::VertexArray &PPU::getScreen()
{
    return screen;
}

uint8_t PPU::cpuRead(uint16_t addr, bool rdonly)
{
    uint8_t data = 0x00;

    switch (addr)
    {
    case 0x0000: // Control
        break;
    case 0x0001: // Mask
        break;
    case 0x0002: // Status
        break;
    case 0x0003: // OAM Address
        break;
    case 0x0004: // OAM Data
        break;
    case 0x0005: // Scroll
        break;
    case 0x0006: // PPU Address
        break;
    case 0x0007: // PPU Data
        break;
    }

    return data;
}

void PPU::cpuWrite(uint16_t addr, uint8_t data)
{
    switch (addr)
    {
    case 0x0000: // Control
        break;
    case 0x0001: // Mask
        break;
    case 0x0002: // Status
        break;
    case 0x0003: // OAM Address
        break;
    case 0x0004: // OAM Data
        break;
    case 0x0005: // Scroll
        break;
    case 0x0006: // PPU Address
        break;
    case 0x0007: // PPU Data
        break;
    }
}

uint8_t PPU::ppuRead(uint16_t addr, bool rdonly)
{
    uint8_t data = 0x00;
    addr &= 0x3FFF;

    if (cart->ppuRead(addr, data))
    {
    }

    return data;
}

void PPU::ppuWrite(uint16_t addr, uint8_t data)
{
    addr &= 0x3FFF;

    if (cart->ppuWrite(addr, data))
    {
    }
}

void PPU::connectCartridge(const std::shared_ptr<Cartridge> &cartridge)
{
    this->cart = cartridge;
}

void PPU::clock()
{
    setPixel(cycle - 1, scanline, palScreen[(rand() % 2) ? 0x3F : 0x30]);
    cycle++;
    if (cycle >= 341)
    {
        cycle = 0;
        scanline++;
        if (scanline >= 261)
        {
            scanline = -1;
            frame_complete = true;
        }
    }
}

void PPU::setPixel(int x, int y, sf::Color color)
{
    int len = width / 3;
    int pixelIndex = (y * len + x) * 6;
    for (int i = 0; i < 6; i++)
    {
        screen[pixelIndex + i].color = color;
    }
}

void PPU::addVertex(int x, int y)
{
    sf::Vector2f topLeft(x, y);
    // Calculate the top-right corner of the pixel
    sf::Vector2f topRight(x + pixelSize, y);

    // Calculate the bottom-right corner of the pixel
    sf::Vector2f bottomRight(x + pixelSize, y + pixelSize);

    // Calculate the bottom-left corner of the pixel
    sf::Vector2f bottomLeft(x, y + pixelSize);

    // Add the vertices for the first triangle
    screen.append(sf::Vertex(topLeft, sf::Color::White));
    screen.append(sf::Vertex(topRight, sf::Color::White));
    screen.append(sf::Vertex(bottomRight, sf::Color::White));

    // Add the vertices for the second triangle
    screen.append(sf::Vertex(topLeft, sf::Color::White));
    screen.append(sf::Vertex(bottomRight, sf::Color::White));
    screen.append(sf::Vertex(bottomLeft, sf::Color::White));
}