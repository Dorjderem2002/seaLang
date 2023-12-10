#pragma once
#include "Mapper.hpp"

class Mapper_000 : public Mapper
{
public:
	Mapper_000(uint8_t prgBanks, uint8_t chrBanks);
    virtual ~Mapper_000() = default;

public:
	bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
	bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;
	bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
	bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;
};
