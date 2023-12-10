#pragma once

#include <cstdint>

#include "CPU.hpp"
#include "PPU.hpp"

class BUS
{
public:
    BUS();
    uint8_t read(uint16_t addr, bool readOnly = false);
    void write(uint16_t addr, uint8_t data);
    void reset();
	void clock();

    uint32_t sysCounter = 0;

    CPU cpu;
    PPU ppu;
    std::shared_ptr<Cartridge> cart;
private:
    uint8_t ram[64 * 1024];
};