#include "PPU.hpp"

#include <iostream>

PPU::PPU()
{
    palScreen[0x00] = sf::Color(84, 84, 84);
    palScreen[0x01] = sf::Color(0, 30, 116);
    palScreen[0x02] = sf::Color(8, 16, 144);
    palScreen[0x03] = sf::Color(48, 0, 136);
    palScreen[0x04] = sf::Color(68, 0, 100);
    palScreen[0x05] = sf::Color(92, 0, 48);
    palScreen[0x06] = sf::Color(84, 4, 0);
    palScreen[0x07] = sf::Color(60, 24, 0);
    palScreen[0x08] = sf::Color(32, 42, 0);
    palScreen[0x09] = sf::Color(8, 58, 0);
    palScreen[0x0A] = sf::Color(0, 64, 0);
    palScreen[0x0B] = sf::Color(0, 60, 0);
    palScreen[0x0C] = sf::Color(0, 50, 60);
    palScreen[0x0D] = sf::Color(0, 0, 0);
    palScreen[0x0E] = sf::Color(0, 0, 0);
    palScreen[0x0F] = sf::Color(0, 0, 0);

    palScreen[0x10] = sf::Color(152, 150, 152);
    palScreen[0x11] = sf::Color(8, 76, 196);
    palScreen[0x12] = sf::Color(48, 50, 236);
    palScreen[0x13] = sf::Color(92, 30, 228);
    palScreen[0x14] = sf::Color(136, 20, 176);
    palScreen[0x15] = sf::Color(160, 20, 100);
    palScreen[0x16] = sf::Color(152, 34, 32);
    palScreen[0x17] = sf::Color(120, 60, 0);
    palScreen[0x18] = sf::Color(84, 90, 0);
    palScreen[0x19] = sf::Color(40, 114, 0);
    palScreen[0x1A] = sf::Color(8, 124, 0);
    palScreen[0x1B] = sf::Color(0, 118, 40);
    palScreen[0x1C] = sf::Color(0, 102, 120);
    palScreen[0x1D] = sf::Color(0, 0, 0);
    palScreen[0x1E] = sf::Color(0, 0, 0);
    palScreen[0x1F] = sf::Color(0, 0, 0);

    palScreen[0x20] = sf::Color(236, 238, 236);
    palScreen[0x21] = sf::Color(76, 154, 236);
    palScreen[0x22] = sf::Color(120, 124, 236);
    palScreen[0x23] = sf::Color(176, 98, 236);
    palScreen[0x24] = sf::Color(228, 84, 236);
    palScreen[0x25] = sf::Color(236, 88, 180);
    palScreen[0x26] = sf::Color(236, 106, 100);
    palScreen[0x27] = sf::Color(212, 136, 32);
    palScreen[0x28] = sf::Color(160, 170, 0);
    palScreen[0x29] = sf::Color(116, 196, 0);
    palScreen[0x2A] = sf::Color(76, 208, 32);
    palScreen[0x2B] = sf::Color(56, 204, 108);
    palScreen[0x2C] = sf::Color(56, 180, 204);
    palScreen[0x2D] = sf::Color(60, 60, 60);
    palScreen[0x2E] = sf::Color(0, 0, 0);
    palScreen[0x2F] = sf::Color(0, 0, 0);

    palScreen[0x30] = sf::Color(236, 238, 236);
    palScreen[0x31] = sf::Color(168, 204, 236);
    palScreen[0x32] = sf::Color(188, 188, 236);
    palScreen[0x33] = sf::Color(212, 178, 236);
    palScreen[0x34] = sf::Color(236, 174, 236);
    palScreen[0x35] = sf::Color(236, 174, 212);
    palScreen[0x36] = sf::Color(236, 180, 176);
    palScreen[0x37] = sf::Color(228, 196, 144);
    palScreen[0x38] = sf::Color(204, 210, 120);
    palScreen[0x39] = sf::Color(180, 222, 120);
    palScreen[0x3A] = sf::Color(168, 226, 144);
    palScreen[0x3B] = sf::Color(152, 226, 180);
    palScreen[0x3C] = sf::Color(160, 214, 228);
    palScreen[0x3D] = sf::Color(160, 162, 160);
    palScreen[0x3E] = sf::Color(0, 0, 0);
    palScreen[0x3F] = sf::Color(0, 0, 0);

    screen = sf::VertexArray(sf::Triangles, 3);
    nameTable[0] = sf::VertexArray(sf::Triangles, 3);
    nameTable[1] = sf::VertexArray(sf::Triangles, 3);
    patternTable[0] = sf::VertexArray(sf::Triangles, 3);
    patternTable[1] = sf::VertexArray(sf::Triangles, 3);

    for (int y = 0; y < height; y += pixelSize)
    {
        for (int x = 0; x < width; x += pixelSize)
        {
            addVertex(x, y, screen);
            addVertex(x, y, nameTable[0]);
            addVertex(x, y, nameTable[1]);
            addVertex(x, y, patternTable[0]);
            addVertex(x, y, patternTable[1]);
        }
    }
    std::cout << "PPU initialized" << std::endl;
}

PPU::~PPU()
{
}

sf::VertexArray &PPU::getScreen()
{
    return screen;
}

sf::VertexArray &PPU::getPatternTable(uint8_t i, uint8_t palette)
{
    for (uint16_t nTileY = 0; nTileY < 16; nTileY++)
    {
        for (uint16_t nTileX = 0; nTileX < 16; nTileX++)
        {
            uint16_t nOffset = nTileY * 256 + nTileX * 16;
            for (uint16_t row = 0; row < 8; row++)
            {
                uint8_t tile_lsb = ppuRead(i * 0x1000 + nOffset + row + 0x0000);
                uint8_t tile_msb = ppuRead(i * 0x1000 + nOffset + row + 0x0008);

                for (uint16_t col = 0; col < 8; col++)
                {
                    uint8_t pixel = (tile_lsb & 0x01) + (tile_msb & 0x01);
                    tile_lsb >>= 1;
                    tile_msb >>= 1;
                    int x = nTileX * 8 + (7 - col);
                    int y = nTileY * 8 + row;
                    sf::Color c = getColourFromPaletteRam(palette, pixel);
                    setPixel(x, y, c, patternTable[i]);
                }
            }
        }
    }
    return patternTable[i];
}

sf::Color &PPU::getColourFromPaletteRam(uint8_t palette, uint8_t pixel)
{
    // "0x3F00"       - Offset into PPU addressable range where palettes are stored
    // "palette << 2" - Each palette is 4 bytes in size
    // "pixel"        - Each pixel index is either 0, 1, 2 or 3
    // "& 0x3F"       - Stops us reading beyond the bounds of the palScreen array
    return palScreen[ppuRead(0x3F00 + (palette << 2) + pixel) & 0x3F];
}

sf::VertexArray &PPU::getNameTable(uint8_t i)
{
    return nameTable[i];
}

uint8_t PPU::cpuRead(uint16_t addr, bool rdonly)
{
    uint8_t data = 0x00;
    if (rdonly)
    {
        switch (addr)
        {
        case 0x0000: // Control
            break;
        case 0x0001: // Mask
            break;
        case 0x0002: // Status
            break;
        case 0x0003: // OAM Address
            break;
        case 0x0004: // OAM Data
            break;
        case 0x0005: // Scroll
            break;
        case 0x0006: // PPU Address
            break;
        case 0x0007: // PPU Data
            break;
        }
    }

    else
    {
        switch (addr)
        {
        case 0x0000:
            break;
        case 0x0001:
            break;
        case 0x0002:
            data = (status.reg & 0xE0) | (ppu_data_buffer & 0x1F);
            status.vertical_blank = 0;
            address_latch = 0;
            break;
        case 0x0003:
            break;
        case 0x0004:
            break;
        case 0x0005:
            break;
        case 0x0006:
            break;
        case 0x0007:
            data = ppu_data_buffer;
            ppu_data_buffer = ppuRead(vram_addr.reg);
            if (vram_addr.reg >= 0x3F00)
                data = ppu_data_buffer;
            vram_addr.reg += (control.increment_mode ? 32 : 1);
            break;
        }
    }

    return data;
}

void PPU::cpuWrite(uint16_t addr, uint8_t data)
{
    switch (addr)
    {
    // Control
    case 0x0000:
        control.reg = data;
        tram_addr.nametable_x = control.nametable_x;
        tram_addr.nametable_y = control.nametable_y;
        break;
    // Mask
    case 0x0001:
        mask.reg = data;
        break;
    // Status
    case 0x0002:
        break;
    // OAM Address
    case 0x0003:
        break;
    // OAM Data
    case 0x0004:
        break;
    // Scroll
    case 0x0005:
        if (address_latch == 0)
        {
            fine_x = data & 0x07;
            tram_addr.coarse_x = data >> 3;
            address_latch = 1;
        }
        else
        {
            tram_addr.fine_y = data & 0x07;
            tram_addr.coarse_y = data >> 3;
            address_latch = 0;
        }
        break;
    // PPU Address
    case 0x0006:
        if (address_latch == 0)
        {
            tram_addr.reg = (uint16_t)((data & 0x3F) << 8) | (tram_addr.reg & 0x00FF);
            address_latch = 1;
        }
        else
        {
            tram_addr.reg = (tram_addr.reg & 0xFF00) | data;
            vram_addr = tram_addr;
            address_latch = 0;
        }
        break;
    // PPU Data
    case 0x0007: 
        ppuWrite(vram_addr.reg, data);
        vram_addr.reg += (control.increment_mode ? 32 : 1);
        break;
    }
}

uint8_t PPU::ppuRead(uint16_t addr, bool rdonly)
{
    uint8_t data = 0x00;
	addr &= 0x3FFF;

	if (cart->ppuRead(addr, data))
	{

	}
	else if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		// If the cartridge cant map the address, have
		// a physical location ready here
		data = tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF];
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF)
	{
		addr &= 0x0FFF;

		if (cart->mirror == Cartridge::MIRROR::VERTICAL)
		{
			// Vertical
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[1][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
		}
		else if (cart->mirror == Cartridge::MIRROR::HORIZONTAL)
		{
			// Horizontal
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[1][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
		}
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF)
	{
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		data = tblPalette[addr] & (mask.grayscale ? 0x30 : 0x3F);
	}

	return data;
}

void PPU::ppuWrite(uint16_t addr, uint8_t data)
{
    addr &= 0x3FFF;

	if (cart->ppuWrite(addr, data))
	{

	}
	else if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF)
	{
		addr &= 0x0FFF;
		if (cart->mirror == Cartridge::MIRROR::VERTICAL)
		{
			// Vertical
			if (addr >= 0x0000 && addr <= 0x03FF)
				tblName[0][addr & 0x03FF] = data;
			if (addr >= 0x0400 && addr <= 0x07FF)
				tblName[1][addr & 0x03FF] = data;
			if (addr >= 0x0800 && addr <= 0x0BFF)
				tblName[0][addr & 0x03FF] = data;
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				tblName[1][addr & 0x03FF] = data;
		}
		else if (cart->mirror == Cartridge::MIRROR::HORIZONTAL)
		{
			// Horizontal
			if (addr >= 0x0000 && addr <= 0x03FF)
				tblName[0][addr & 0x03FF] = data;
			if (addr >= 0x0400 && addr <= 0x07FF)
				tblName[0][addr & 0x03FF] = data;
			if (addr >= 0x0800 && addr <= 0x0BFF)
				tblName[1][addr & 0x03FF] = data;
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				tblName[1][addr & 0x03FF] = data;
		}
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF)
	{
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		tblPalette[addr] = data;
	}
}

void PPU::connectCartridge(const std::shared_ptr<Cartridge> &cartridge)
{
    this->cart = cartridge;
}

void PPU::clock()
{
	auto IncrementScrollX = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			if (vram_addr.coarse_x == 31)
			{
				vram_addr.coarse_x = 0;
				vram_addr.nametable_x = ~vram_addr.nametable_x;
			}
			else
			{
				vram_addr.coarse_x++;
			}
		}
	};
	auto IncrementScrollY = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			if (vram_addr.fine_y < 7)
			{
				vram_addr.fine_y++;
			}
			else
			{
				vram_addr.fine_y = 0;
				if (vram_addr.coarse_y == 29)
				{
					vram_addr.coarse_y = 0;
					vram_addr.nametable_y = ~vram_addr.nametable_y;
				}
				else if (vram_addr.coarse_y == 31)
				{
					vram_addr.coarse_y = 0;
				}
				else
				{
					vram_addr.coarse_y++;
				}
			}
		}
	};
	auto TransferAddressX = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			vram_addr.nametable_x = tram_addr.nametable_x;
			vram_addr.coarse_x    = tram_addr.coarse_x;
		}
	};
	auto TransferAddressY = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			vram_addr.fine_y      = tram_addr.fine_y;
			vram_addr.nametable_y = tram_addr.nametable_y;
			vram_addr.coarse_y    = tram_addr.coarse_y;
		}
	};
	auto LoadBackgroundShifters = [&]()
	{	
		bg_shifter_pattern_lo = (bg_shifter_pattern_lo & 0xFF00) | bg_next_tile_lsb;
		bg_shifter_pattern_hi = (bg_shifter_pattern_hi & 0xFF00) | bg_next_tile_msb;

		bg_shifter_attrib_lo  = (bg_shifter_attrib_lo & 0xFF00) | ((bg_next_tile_attrib & 0b01) ? 0xFF : 0x00);
		bg_shifter_attrib_hi  = (bg_shifter_attrib_hi & 0xFF00) | ((bg_next_tile_attrib & 0b10) ? 0xFF : 0x00);
	};

	auto UpdateShifters = [&]()
	{
		if (mask.render_background)
		{
			bg_shifter_pattern_lo <<= 1;
			bg_shifter_pattern_hi <<= 1;

			bg_shifter_attrib_lo <<= 1;
			bg_shifter_attrib_hi <<= 1;
		}
	};

	if (scanline >= -1 && scanline < 240)
	{		
		if (scanline == 0 && cycle == 0)
		{
			cycle = 1;
		}

		if (scanline == -1 && cycle == 1)
		{
			status.vertical_blank = 0;
		}


		if ((cycle >= 2 && cycle < 258) || (cycle >= 321 && cycle < 338))
		{
			UpdateShifters();
			switch ((cycle - 1) % 8)
			{
			case 0:
				LoadBackgroundShifters();

				bg_next_tile_id = ppuRead(0x2000 | (vram_addr.reg & 0x0FFF));
				break;
			case 2:			
				bg_next_tile_attrib = ppuRead(0x23C0 | (vram_addr.nametable_y << 11) 
					                                 | (vram_addr.nametable_x << 10) 
					                                 | ((vram_addr.coarse_y >> 2) << 3) 
					                                 | (vram_addr.coarse_x >> 2));
				
				
				if (vram_addr.coarse_y & 0x02) bg_next_tile_attrib >>= 4;
				if (vram_addr.coarse_x & 0x02) bg_next_tile_attrib >>= 2;
				bg_next_tile_attrib &= 0x03;
				break;
			case 4: 
				bg_next_tile_lsb = ppuRead((control.pattern_background << 12) 
					                       + ((uint16_t)bg_next_tile_id << 4) 
					                       + (vram_addr.fine_y) + 0);

				break;
			case 6:
				bg_next_tile_msb = ppuRead((control.pattern_background << 12)
					                       + ((uint16_t)bg_next_tile_id << 4)
					                       + (vram_addr.fine_y) + 8);
				break;
			case 7:
				IncrementScrollX();
				break;
			}
		}
		if (cycle == 256)
		{
			IncrementScrollY();
		}
		if (cycle == 257)
		{
			LoadBackgroundShifters();
			TransferAddressX();
		}
		if (cycle == 338 || cycle == 340)
		{
			bg_next_tile_id = ppuRead(0x2000 | (vram_addr.reg & 0x0FFF));
		}

		if (scanline == -1 && cycle >= 280 && cycle < 305)
		{
			TransferAddressY();
		}
	}

	if (scanline == 240)
	{
	}

	if (scanline >= 241 && scanline < 261)
	{
		if (scanline == 241 && cycle == 1)
		{
			status.vertical_blank = 1;
			if (control.enable_nmi) 
				nmi = true;
		}
	}

	uint8_t bg_pixel = 0x00;   
	uint8_t bg_palette = 0x00; 
	if (mask.render_background)
	{
		uint16_t bit_mux = 0x8000 >> fine_x;
		uint8_t p0_pixel = (bg_shifter_pattern_lo & bit_mux) > 0;
		uint8_t p1_pixel = (bg_shifter_pattern_hi & bit_mux) > 0;
		bg_pixel = (p1_pixel << 1) | p0_pixel;
		uint8_t bg_pal0 = (bg_shifter_attrib_lo & bit_mux) > 0;
		uint8_t bg_pal1 = (bg_shifter_attrib_hi & bit_mux) > 0;
		bg_palette = (bg_pal1 << 1) | bg_pal0;
	}

    setPixel(cycle - 1, scanline, getColourFromPaletteRam(bg_palette, bg_pixel), screen);
    cycle++;
    if (cycle >= 341)
    {
        cycle = 0;
        scanline++;
        if (scanline >= 261)
        {
            scanline = -1;
            frame_complete = true;
        }
    }
}

void PPU::reset()
{
    fine_x = 0x00;
    address_latch = 0x00;
    ppu_data_buffer = 0x00;
    scanline = 0;
    cycle = 0;
    bg_next_tile_id = 0x00;
    bg_next_tile_attrib = 0x00;
    bg_next_tile_lsb = 0x00;
    bg_next_tile_msb = 0x00;
    bg_shifter_pattern_lo = 0x0000;
    bg_shifter_pattern_hi = 0x0000;
    bg_shifter_attrib_lo = 0x0000;
    bg_shifter_attrib_hi = 0x0000;
    status.reg = 0x00;
    mask.reg = 0x00;
    control.reg = 0x00;
    vram_addr.reg = 0x0000;
    tram_addr.reg = 0x0000;
}

void PPU::setPixel(int x, int y, sf::Color color, sf::VertexArray &spr)
{
    int len = width / 3;
    int pixelIndex = (y * len + x) * 6;
    for (int i = 0; i < 6; i++)
    {
        spr[pixelIndex + i].color = color;
    }
}

void PPU::addVertex(int x, int y, sf::VertexArray &spr)
{
    sf::Vector2f topLeft(x, y);
    // Calculate the top-right corner of the pixel
    sf::Vector2f topRight(x + pixelSize, y);

    // Calculate the bottom-right corner of the pixel
    sf::Vector2f bottomRight(x + pixelSize, y + pixelSize);

    // Calculate the bottom-left corner of the pixel
    sf::Vector2f bottomLeft(x, y + pixelSize);

    // Add the vertices for the first triangle
    spr.append(sf::Vertex(topLeft, sf::Color::White));
    spr.append(sf::Vertex(topRight, sf::Color::White));
    spr.append(sf::Vertex(bottomRight, sf::Color::White));

    // Add the vertices for the second triangle
    spr.append(sf::Vertex(topLeft, sf::Color::White));
    spr.append(sf::Vertex(bottomRight, sf::Color::White));
    spr.append(sf::Vertex(bottomLeft, sf::Color::White));
}