#pragma once
#include <cstdint>

class Mapper
{
public:
	Mapper(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper();
    // virtual ~Mapper() = default;

public:
	virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr)	 = 0;
	virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr)	 = 0;
	virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr)	 = 0;
	virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)	 = 0;

protected:
	uint8_t prg = 0;
	uint8_t chr = 0;
};
