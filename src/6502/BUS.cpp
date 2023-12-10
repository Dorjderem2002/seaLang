#include "BUS.hpp"
#include <iostream>

using namespace std;

BUS::BUS()
{
    cpu.connectBus(this);
    for (auto &i : ram) i = 0x00;
}

void BUS::write(uint16_t addr, uint8_t data) 
{
    if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		ram[addr & 0x07FF] = data;

	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		ppu.cpuWrite(addr & 0x0007, data);
	}
}

uint8_t BUS::read(uint16_t addr, bool readOnly) 
{
    uint8_t data = 0x00;	
    if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		data = ram[addr & 0x07FF];
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		data = ppu.cpuRead(addr & 0x0007, readOnly);
	}

	return data;
}

void BUS::reset()
{
	cpu.reset();
	sysCounter = 0;
}

void BUS::clock()
{
	ppu.clock();
	if (sysCounter % 3 == 0)
	{
		cpu.clock();
	}

	sysCounter++;
}