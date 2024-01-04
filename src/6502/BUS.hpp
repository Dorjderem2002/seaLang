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

public:
    void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    std::shared_ptr<Cartridge> cart;

private:
    uint8_t ram[64 * 1024];
    uint8_t controller[2];
	uint8_t controller_state[2];
};