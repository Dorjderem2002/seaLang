#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

#include "Mapper_000.hpp"

class Cartridge
{
public:	
	Cartridge(const std::string& fileName);
	~Cartridge();


public:
	bool isImageValid();

	enum MIRROR
	{
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI,
	} mirror = HORIZONTAL;

private:
	bool imageValid = false;

	uint8_t mapperID = 0;
	uint8_t prgBanks = 0;
	uint8_t chrBanks = 0;

	std::vector<uint8_t> prgMemory;
	std::vector<uint8_t> chrMemory;

	std::shared_ptr<Mapper> pMapper;

public:
	bool cpuRead(uint16_t addr, uint8_t &data);
	bool cpuWrite(uint16_t addr, uint8_t data);

	bool ppuRead(uint16_t addr, uint8_t &data);
	bool ppuWrite(uint16_t addr, uint8_t data);

    void reset();
};
