#include "BUS.hpp"
#include <iostream>

using namespace std;

BUS::BUS()
{
    for (auto &i : ram) i = 0x00;
    
    cpu->connectBus(this);
}

void BUS::write(uint16_t addr, uint8_t data) 
{
    ram[addr] = data;
}

uint8_t BUS::read(uint16_t addr, bool readOnly) 
{
    return ram[addr];
}