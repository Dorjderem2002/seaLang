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
    else if (addr >= 0x4016 && addr <= 0x4017)
	{
		controller_state[addr & 0x0001] = controller[addr & 0x0001];
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
    else if (addr >= 0x4016 && addr <= 0x4017)
	{
		data = (controller_state[addr & 0x0001] & 0x80) > 0;
		controller_state[addr & 0x0001] <<= 1;
	}

	return data;
}

void BUS::reset()
{
    cart->reset();
	cpu.reset();
    ppu.reset();
	sysCounter = 0;
}

void BUS::clock()
{
    // smallest unit of cycle
	ppu.clock();

    // cpu cycle is once per 3 ppu cycles
	if (sysCounter % 3 == 0)
	{
		cpu.clock();
	}

    if (ppu.nmi)
	{
		ppu.nmi = false;
		cpu.nmi();
	}

	sysCounter++;
}

void BUS::insertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cart = cartridge;
	ppu.connectCartridge(cartridge);
}