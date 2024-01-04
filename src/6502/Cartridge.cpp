#include "Cartridge.hpp"

Cartridge::Cartridge(const std::string& sFileName)
{
	struct sHeader
	{
		char name[4];
		uint8_t prg_rom_chunks;
		uint8_t chr_rom_chunks;
		uint8_t mapper1;
		uint8_t mapper2;
		uint8_t prg_ram_size;
		uint8_t tv_system1;
		uint8_t tv_system2;
		char unused[5];
	} header;

	imageValid = false;

	std::ifstream ifs;
	ifs.open(sFileName, std::ifstream::binary);
	if (ifs.is_open())
	{
		ifs.read((char*)&header, sizeof(sHeader));
		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);
		mapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;
		uint8_t nFileType = 1;

		if (nFileType == 0)
		{

		}

		if (nFileType == 1)
		{
			prgBanks = header.prg_rom_chunks;
			prgMemory.resize(prgBanks * 16384);
			ifs.read((char*)prgMemory.data(), prgMemory.size());

			chrBanks = header.chr_rom_chunks;
			if (chrBanks == 0)
			{
				chrMemory.resize(8192);
			}
			else
			{
				chrMemory.resize(chrBanks * 8192);
			}
			ifs.read((char*)chrMemory.data(), chrMemory.size());
		}

		if (nFileType == 2)
		{

		}
		switch (mapperID)
		{
		case   0: pMapper = std::make_shared<Mapper_000>(prgBanks, chrBanks); break;
		//case   2: pMapper = std::make_shared<Mapper_002>(prgBanks, chrBanks); break;
		//case   3: pMapper = std::make_shared<Mapper_003>(prgBanks, chrBanks); break;
		//case  66: pMapper = std::make_shared<Mapper_066>(prgBanks, chrBanks); break;
		}

		imageValid = true;
		ifs.close();
	}

}


Cartridge::~Cartridge()
{
}

bool Cartridge::isImageValid()
{
	return imageValid;
}

bool Cartridge::cpuRead(uint16_t addr, uint8_t &data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->cpuMapRead(addr, mapped_addr))
	{
		data = prgMemory[mapped_addr];
		return true;
	}
	else
		return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->cpuMapWrite(addr, mapped_addr, data))
	{
		prgMemory[mapped_addr] = data;
		return true;
	}
	else
		return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t & data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->ppuMapRead(addr, mapped_addr))
	{
		data = chrMemory[mapped_addr];
		return true;
	}
	else
		return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->ppuMapWrite(addr, mapped_addr))
	{
		chrMemory[mapped_addr] = data;
		return true;
	}
	else
		return false;
}


void Cartridge::reset()
{
	if (pMapper != nullptr)
		pMapper->reset();
}