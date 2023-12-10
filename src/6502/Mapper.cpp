#include "Mapper.hpp"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
{
	prg = prgBanks;
	chr = chrBanks;
}


Mapper::~Mapper()
{
}