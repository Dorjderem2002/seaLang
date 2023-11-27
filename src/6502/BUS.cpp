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
    ram[addr] = data;
}

uint8_t BUS::read(uint16_t addr, bool readOnly) 
{
    return ram[addr];
}