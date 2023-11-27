#include "CPU.hpp"
#include "BUS.hpp"

#include <iostream>

CPU::CPU()
{
    tableOp = new INSTRUCTION[256]
    {
            {"BRK", &CPU::BRK, &CPU::IMM, 7},
            {"ORA", &CPU::ORA, &CPU::IZX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"???", &CPU::NOP, &CPU::IMP, 3},
            {"ORA", &CPU::ORA, &CPU::ZP0, 3},
            {"ASL", &CPU::ASL, &CPU::ZP0, 5},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"PHP", &CPU::PHP, &CPU::IMP, 3},
            {"ORA", &CPU::ORA, &CPU::IMM, 2},
            {"ASL", &CPU::ASL, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"ORA", &CPU::ORA, &CPU::ABS, 4},
            {"ASL", &CPU::ASL, &CPU::ABS, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"BPL", &CPU::BPL, &CPU::REL, 2},
            {"ORA", &CPU::ORA, &CPU::IZY, 5},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"ORA", &CPU::ORA, &CPU::ZPX, 4},
            {"ASL", &CPU::ASL, &CPU::ZPX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"CLC", &CPU::CLC, &CPU::IMP, 2},
            {"ORA", &CPU::ORA, &CPU::ABY, 4},
            {"???", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"ORA", &CPU::ORA, &CPU::ABX, 4},
            {"ASL", &CPU::ASL, &CPU::ABX, 7},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"JSR", &CPU::JSR, &CPU::ABS, 6},
            {"AND", &CPU::AND, &CPU::IZX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"BIT", &CPU::BIT, &CPU::ZP0, 3},
            {"AND", &CPU::AND, &CPU::ZP0, 3},
            {"ROL", &CPU::ROL, &CPU::ZP0, 5},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"PLP", &CPU::PLP, &CPU::IMP, 4},
            {"AND", &CPU::AND, &CPU::IMM, 2},
            {"ROL", &CPU::ROL, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"BIT", &CPU::BIT, &CPU::ABS, 4},
            {"AND", &CPU::AND, &CPU::ABS, 4},
            {"ROL", &CPU::ROL, &CPU::ABS, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"BMI", &CPU::BMI, &CPU::REL, 2},
            {"AND", &CPU::AND, &CPU::IZY, 5},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"AND", &CPU::AND, &CPU::ZPX, 4},
            {"ROL", &CPU::ROL, &CPU::ZPX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"SEC", &CPU::SEC, &CPU::IMP, 2},
            {"AND", &CPU::AND, &CPU::ABY, 4},
            {"???", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"AND", &CPU::AND, &CPU::ABX, 4},
            {"ROL", &CPU::ROL, &CPU::ABX, 7},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"RTI", &CPU::RTI, &CPU::IMP, 6},
            {"EOR", &CPU::EOR, &CPU::IZX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"???", &CPU::NOP, &CPU::IMP, 3},
            {"EOR", &CPU::EOR, &CPU::ZP0, 3},
            {"LSR", &CPU::LSR, &CPU::ZP0, 5},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"PHA", &CPU::PHA, &CPU::IMP, 3},
            {"EOR", &CPU::EOR, &CPU::IMM, 2},
            {"LSR", &CPU::LSR, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"JMP", &CPU::JMP, &CPU::ABS, 3},
            {"EOR", &CPU::EOR, &CPU::ABS, 4},
            {"LSR", &CPU::LSR, &CPU::ABS, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"BVC", &CPU::BVC, &CPU::REL, 2},
            {"EOR", &CPU::EOR, &CPU::IZY, 5},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"EOR", &CPU::EOR, &CPU::ZPX, 4},
            {"LSR", &CPU::LSR, &CPU::ZPX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"CLI", &CPU::CLI, &CPU::IMP, 2},
            {"EOR", &CPU::EOR, &CPU::ABY, 4},
            {"???", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"EOR", &CPU::EOR, &CPU::ABX, 4},
            {"LSR", &CPU::LSR, &CPU::ABX, 7},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"RTS", &CPU::RTS, &CPU::IMP, 6},
            {"ADC", &CPU::ADC, &CPU::IZX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"???", &CPU::NOP, &CPU::IMP, 3},
            {"ADC", &CPU::ADC, &CPU::ZP0, 3},
            {"ROR", &CPU::ROR, &CPU::ZP0, 5},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"PLA", &CPU::PLA, &CPU::IMP, 4},
            {"ADC", &CPU::ADC, &CPU::IMM, 2},
            {"ROR", &CPU::ROR, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"JMP", &CPU::JMP, &CPU::IND, 5},
            {"ADC", &CPU::ADC, &CPU::ABS, 4},
            {"ROR", &CPU::ROR, &CPU::ABS, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"BVS", &CPU::BVS, &CPU::REL, 2},
            {"ADC", &CPU::ADC, &CPU::IZY, 5},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"ADC", &CPU::ADC, &CPU::ZPX, 4},
            {"ROR", &CPU::ROR, &CPU::ZPX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"SEI", &CPU::SEI, &CPU::IMP, 2},
            {"ADC", &CPU::ADC, &CPU::ABY, 4},
            {"???", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"ADC", &CPU::ADC, &CPU::ABX, 4},
            {"ROR", &CPU::ROR, &CPU::ABX, 7},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"???", &CPU::NOP, &CPU::IMP, 2},
            {"STA", &CPU::STA, &CPU::IZX, 6},
            {"???", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"STY", &CPU::STY, &CPU::ZP0, 3},
            {"STA", &CPU::STA, &CPU::ZP0, 3},
            {"STX", &CPU::STX, &CPU::ZP0, 3},
            {"???", &CPU::SUS, &CPU::IMP, 3},
            {"DEY", &CPU::DEY, &CPU::IMP, 2},
            {"???", &CPU::NOP, &CPU::IMP, 2},
            {"TXA", &CPU::TXA, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"STY", &CPU::STY, &CPU::ABS, 4},
            {"STA", &CPU::STA, &CPU::ABS, 4},
            {"STX", &CPU::STX, &CPU::ABS, 4},
            {"???", &CPU::SUS, &CPU::IMP, 4},
            {"BCC", &CPU::BCC, &CPU::REL, 2},
            {"STA", &CPU::STA, &CPU::IZY, 6},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"STY", &CPU::STY, &CPU::ZPX, 4},
            {"STA", &CPU::STA, &CPU::ZPX, 4},
            {"STX", &CPU::STX, &CPU::ZPY, 4},
            {"???", &CPU::SUS, &CPU::IMP, 4},
            {"TYA", &CPU::TYA, &CPU::IMP, 2},
            {"STA", &CPU::STA, &CPU::ABY, 5},
            {"TXS", &CPU::TXS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"???", &CPU::NOP, &CPU::IMP, 5},
            {"STA", &CPU::STA, &CPU::ABX, 5},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"LDY", &CPU::LDY, &CPU::IMM, 2},
            {"LDA", &CPU::LDA, &CPU::IZX, 6},
            {"LDX", &CPU::LDX, &CPU::IMM, 2},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"LDY", &CPU::LDY, &CPU::ZP0, 3},
            {"LDA", &CPU::LDA, &CPU::ZP0, 3},
            {"LDX", &CPU::LDX, &CPU::ZP0, 3},
            {"???", &CPU::SUS, &CPU::IMP, 3},
            {"TAY", &CPU::TAY, &CPU::IMP, 2},
            {"LDA", &CPU::LDA, &CPU::IMM, 2},
            {"TAX", &CPU::TAX, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"LDY", &CPU::LDY, &CPU::ABS, 4},
            {"LDA", &CPU::LDA, &CPU::ABS, 4},
            {"LDX", &CPU::LDX, &CPU::ABS, 4},
            {"???", &CPU::SUS, &CPU::IMP, 4},
            {"BCS", &CPU::BCS, &CPU::REL, 2},
            {"LDA", &CPU::LDA, &CPU::IZY, 5},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"LDY", &CPU::LDY, &CPU::ZPX, 4},
            {"LDA", &CPU::LDA, &CPU::ZPX, 4},
            {"LDX", &CPU::LDX, &CPU::ZPY, 4},
            {"???", &CPU::SUS, &CPU::IMP, 4},
            {"CLV", &CPU::CLV, &CPU::IMP, 2},
            {"LDA", &CPU::LDA, &CPU::ABY, 4},
            {"TSX", &CPU::TSX, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 4},
            {"LDY", &CPU::LDY, &CPU::ABX, 4},
            {"LDA", &CPU::LDA, &CPU::ABX, 4},
            {"LDX", &CPU::LDX, &CPU::ABY, 4},
            {"???", &CPU::SUS, &CPU::IMP, 4},
            {"CPY", &CPU::CPY, &CPU::IMM, 2},
            {"CMP", &CPU::CMP, &CPU::IZX, 6},
            {"???", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"CPY", &CPU::CPY, &CPU::ZP0, 3},
            {"CMP", &CPU::CMP, &CPU::ZP0, 3},
            {"DEC", &CPU::DEC, &CPU::ZP0, 5},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"INY", &CPU::INY, &CPU::IMP, 2},
            {"CMP", &CPU::CMP, &CPU::IMM, 2},
            {"DEX", &CPU::DEX, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"CPY", &CPU::CPY, &CPU::ABS, 4},
            {"CMP", &CPU::CMP, &CPU::ABS, 4},
            {"DEC", &CPU::DEC, &CPU::ABS, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"BNE", &CPU::BNE, &CPU::REL, 2},
            {"CMP", &CPU::CMP, &CPU::IZY, 5},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"CMP", &CPU::CMP, &CPU::ZPX, 4},
            {"DEC", &CPU::DEC, &CPU::ZPX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"CLD", &CPU::CLD, &CPU::IMP, 2},
            {"CMP", &CPU::CMP, &CPU::ABY, 4},
            {"NOP", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"CMP", &CPU::CMP, &CPU::ABX, 4},
            {"DEC", &CPU::DEC, &CPU::ABX, 7},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"CPX", &CPU::CPX, &CPU::IMM, 2},
            {"SBC", &CPU::SBC, &CPU::IZX, 6},
            {"???", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"CPX", &CPU::CPX, &CPU::ZP0, 3},
            {"SBC", &CPU::SBC, &CPU::ZP0, 3},
            {"INC", &CPU::INC, &CPU::ZP0, 5},
            {"???", &CPU::SUS, &CPU::IMP, 5},
            {"INX", &CPU::INX, &CPU::IMP, 2},
            {"SBC", &CPU::SBC, &CPU::IMM, 2},
            {"NOP", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SBC, &CPU::IMP, 2},
            {"CPX", &CPU::CPX, &CPU::ABS, 4},
            {"SBC", &CPU::SBC, &CPU::ABS, 4},
            {"INC", &CPU::INC, &CPU::ABS, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"BEQ", &CPU::BEQ, &CPU::REL, 2},
            {"SBC", &CPU::SBC, &CPU::IZY, 5},
            {"???", &CPU::SUS, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 8},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"SBC", &CPU::SBC, &CPU::ZPX, 4},
            {"INC", &CPU::INC, &CPU::ZPX, 6},
            {"???", &CPU::SUS, &CPU::IMP, 6},
            {"SED", &CPU::SED, &CPU::IMP, 2},
            {"SBC", &CPU::SBC, &CPU::ABY, 4},
            {"NOP", &CPU::NOP, &CPU::IMP, 2},
            {"???", &CPU::SUS, &CPU::IMP, 7},
            {"???", &CPU::NOP, &CPU::IMP, 4},
            {"SBC", &CPU::SBC, &CPU::ABX, 4},
            {"INC", &CPU::INC, &CPU::ABX, 7},
            {"???", &CPU::SUS, &CPU::IMP, 7},
        };
}

void CPU::connectBus(BUS *newBus)
{
    std::cout<<"Bus connected"<<std::endl;
    bus = newBus;
}

uint8_t CPU::read(uint16_t addr)
{
    return bus->read(addr);
}

void CPU::write(uint16_t addr, uint8_t data)
{
    bus->write(addr, data);
}

void CPU::clock()
{
    if(cycles == 0)
    {
        opcode = read(pc++);
        cycles = tableOp[opcode].cycles;
        uint8_t addCycleAddr = (this->*tableOp[opcode].addrmode)();
        uint8_t addCycleOp =(this->*tableOp[opcode].operate)();
        cycles += (addCycleAddr & addCycleOp);
    }
    cycles--;
}

uint8_t CPU::getFlag(FLAGS f)
{
	return ((statRegister & f) > 0) ? 1 : 0;
}

void CPU::setFlag(FLAGS f, bool v)
{
	if (v)
		statRegister |= f;
	else
		statRegister &= ~f;
}

uint8_t CPU::IMP()
{
    fetched = accRegister;
    return 0;
}

uint8_t CPU::IMM() 
{
    addr_abs = pc++;
    return 0;
}

uint8_t CPU::ZP0()
{
    addr_abs = read(pc++);
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t CPU::ZPX()
{
    addr_abs = read(pc++) + xRegister;
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t CPU::ZPY()
{
    addr_abs = read(pc++) + yRegister;
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t CPU::ABS()
{
    uint16_t lo = read(pc++);
    uint16_t hi = read(pc++);
    addr_abs = (hi << 8) | lo;
    return 0;
}

uint8_t CPU::ABX()
{
    uint16_t low = read(pc++);
    uint16_t high = read(pc++);
    addr_abs = (high << 8) | low;
    addr_abs += xRegister;

    if((addr_abs & 0xFF00) != (high << 8))
        return 1;
    return 0;
}

uint8_t CPU::ABY()
{
    uint16_t low = read(pc++);
    uint16_t high = read(pc++);
    addr_abs = (high << 8) | low;
    addr_abs += yRegister;

    if((addr_abs & 0xFF00) != (high << 8))
        return 1;
    return 0;
}

uint8_t CPU::IND()
{
	uint16_t ptr_low = read(pc++);
	uint16_t ptr_high = read(pc++);
	uint16_t ptr = (ptr_high << 8) | ptr_low;

	if (ptr_low == 0x00FF)
		addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
	else
		addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
	return 0;
}

uint8_t CPU::IZX()
{
	uint16_t t = read(pc++);
    uint16_t low = read((t + (uint16_t)xRegister) & 0x00FF);
    uint16_t high = read((t + (uint16_t)xRegister + 1) & 0x00FF);

	addr_abs = (high << 8) | low;
	return 0;
}

uint8_t CPU::IZY()
{
    uint16_t t = read(pc++);
    uint16_t low = read(t & 0x00FF);
    uint16_t high = read((t + 1) & 0x00FF);

	addr_abs = (high << 8) | low;
    addr_abs += yRegister;

    if((addr_abs & 0xFF00) != (high << 8))
        return 1;
	return 0;
}

uint8_t CPU::REL()
{
    addr_rel = read(pc++);
    if(addr_rel & 0x80)
        addr_rel |= 0xFF00;
    return 0;
}

uint8_t CPU::fetch()
{
    if(!(tableOp[opcode].addrmode == &CPU::IMP))
        fetched = read(addr_abs);
    return fetched;
}

uint8_t CPU::AND()
{
    fetch();
    accRegister &= fetched;
    setFlag(Z, accRegister == 0x00);
    setFlag(N, accRegister & 0x80);
    return 1;
}

uint8_t CPU::BCS()
{
    if(getFlag(C))
    {
        cycles++;
        addr_abs = pc + addr_rel;
        if((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;
        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU::BCC()
{
	if (getFlag(C) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;
		
		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		
		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BEQ()
{
	if (getFlag(Z) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BIT()
{
	fetch();
	temp = accRegister & fetched;
	setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, fetched & (1 << 7));
	setFlag(V, fetched & (1 << 6));
	return 0;
}

uint8_t CPU::BMI()
{
	if (getFlag(N) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BNE()
{
	if (getFlag(Z) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BPL()
{
	if (getFlag(N) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BRK()
{
	pc++;
	
    setFlag(I, 1);
	write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
	stackPtr--;
	write(0x0100 + stackPtr, pc & 0x00FF);
	stackPtr--;

	setFlag(B, 1);
	write(0x0100 + stackPtr, statRegister);
	stackPtr--;
	setFlag(B, 0);

	pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
	return 0;
}

uint8_t CPU::BVC()
{
	if (getFlag(V) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BVS()
{
	if (getFlag(V) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::CLC()
{
    setFlag(C, false);
    return 0;
}

uint8_t CPU::CLD()
{
    setFlag(D, false);
    return 0;
}

uint8_t CPU::CLI()
{
	setFlag(I, false);
	return 0;
}

uint8_t CPU::CLV()
{
	setFlag(V, false);
	return 0;
}

uint8_t CPU::CMP()
{
	fetch();
	temp = (uint16_t)accRegister - (uint16_t)fetched;
	setFlag(C, accRegister >= fetched);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 1;
}

uint8_t CPU::CPX()
{
	fetch();
	temp = (uint16_t)xRegister - (uint16_t)fetched;
	setFlag(C, xRegister >= fetched);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 0;
}

uint8_t CPU::CPY()
{
	fetch();
	temp = (uint16_t)yRegister - (uint16_t)fetched;
	setFlag(C, yRegister >= fetched);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 0;
}

uint8_t CPU::DEC()
{
	fetch();
	temp = fetched - 1;
	write(addr_abs, temp & 0x00FF);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 0;
}

uint8_t CPU::DEX()
{
	xRegister--;
	setFlag(Z, xRegister == 0x00);
	setFlag(N, xRegister & 0x80);
	return 0;
}

uint8_t CPU::DEY()
{
	yRegister--;
	setFlag(Z, yRegister == 0x00);
	setFlag(N, yRegister & 0x80);
	return 0;
}

uint8_t CPU::EOR()
{
	fetch();
	accRegister = accRegister ^ fetched;	
	setFlag(Z, accRegister == 0x00);
	setFlag(N, accRegister & 0x80);
	return 1;
}

uint8_t CPU::INC()
{
	fetch();
	temp = fetched + 1;
	write(addr_abs, temp & 0x00FF);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 0;
}

uint8_t CPU::INX()
{
	xRegister++;
	setFlag(Z, xRegister == 0x00);
	setFlag(N, xRegister & 0x80);
	return 0;
}

uint8_t CPU::INY()
{
	yRegister++;
	setFlag(Z, yRegister == 0x00);
	setFlag(N, yRegister & 0x80);
	return 0;
}

uint8_t CPU::JMP()
{
	pc = addr_abs;
	return 0;
}

uint8_t CPU::JSR()
{
	pc--;

	write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
	stackPtr--;
	write(0x0100 + stackPtr, pc & 0x00FF);
	stackPtr--;

	pc = addr_abs;
	return 0;
}

uint8_t CPU::LDA()
{
	fetch();
	accRegister = fetched;
	setFlag(Z, accRegister == 0x00);
	setFlag(N, accRegister & 0x80);
	return 1;
}

uint8_t CPU::LDX()
{
	fetch();
	xRegister = fetched;
	setFlag(Z, xRegister == 0x00);
	setFlag(N, xRegister & 0x80);
	return 1;
}

uint8_t CPU::LDY()
{
	fetch();
	yRegister = fetched;
	setFlag(Z, yRegister == 0x00);
	setFlag(N, yRegister & 0x80);
	return 1;
}

uint8_t CPU::LSR()
{
	fetch();
	setFlag(C, fetched & 0x0001);
	temp = fetched >> 1;	
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	if (tableOp[opcode].addrmode == &CPU::IMP)
		accRegister = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t CPU::NOP()
{
	switch (opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}

uint8_t CPU::ORA()
{
	fetch();
	accRegister = accRegister | fetched;
	setFlag(Z, accRegister == 0x00);
	setFlag(N, accRegister & 0x80);
	return 1;
}


uint8_t CPU::ADC()
{
	fetch();
	temp = (uint16_t)accRegister + (uint16_t)fetched + (uint16_t)getFlag(C);
	setFlag(C, temp > 255);
	setFlag(Z, (temp & 0x00FF) == 0);
	setFlag(V, (~((uint16_t)accRegister ^ (uint16_t)fetched) & ((uint16_t)accRegister ^ (uint16_t)temp)) & 0x0080);
	setFlag(N, temp & 0x80);
	accRegister = temp & 0x00FF;
	return 1;
}

uint8_t CPU::SBC()
{
	fetch();
	uint16_t value = ((uint16_t)fetched) ^ 0x00FF;
	
	// Notice this is exactly the same as addition from here!
	temp = (uint16_t)accRegister + value + (uint16_t)getFlag(C);
	setFlag(C, temp & 0xFF00);
	setFlag(Z, ((temp & 0x00FF) == 0));
	setFlag(V, (temp ^ (uint16_t)accRegister) & (temp ^ value) & 0x0080);
	setFlag(N, temp & 0x0080);
	accRegister = temp & 0x00FF;
	return 1;
}

uint8_t CPU::PHA()
{
    write(0x0100 + stackPtr, accRegister);
    stackPtr--;
    return 0;
}

uint8_t CPU::PLA()
{
    stackPtr++;
    accRegister = read(0x0100 + stackPtr);
    setFlag(Z, accRegister == 0x00);
    setFlag(N, accRegister & 0x80);
    return 0;
}

uint8_t CPU::PHP()
{
	write(0x0100 + stackPtr, statRegister | B | U);
	setFlag(B, 0);
	setFlag(U, 0);
	stackPtr--;
	return 0;
}

uint8_t CPU::PLP()
{
	stackPtr++;
	statRegister = read(0x0100 + stackPtr);
	setFlag(U, 1);
	return 0;
}

void CPU::reset()
{
    addr_abs = 0xFFFC;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) | lo;
	accRegister = 0;
	xRegister = 0;
	yRegister = 0;
	stackPtr = 0xFD;
	statRegister = 0x00 | U;
	addr_rel = 0x0000;
	addr_abs = 0x0000;
	fetched = 0x00;
	cycles = 8;
}

void CPU::interruptReq()
{
    if (getFlag(I) == 0)
	{
		write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
		stackPtr--;
		write(0x0100 + stackPtr, pc & 0x00FF);
		stackPtr--;

		setFlag(B, 0);
		setFlag(U, 1);
		setFlag(I, 1);
		write(0x0100 + stackPtr, statRegister);
		stackPtr--;

		addr_abs = 0xFFFE;
		uint16_t low = read(addr_abs + 0);
		uint16_t high = read(addr_abs + 1);
		pc = (high << 8) | low;
		cycles = 7;
	}
}

void CPU::nonInterruptReq()
{
	write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
	stackPtr--;
	write(0x0100 + stackPtr, pc & 0x00FF);
	stackPtr--;

	setFlag(B, 0);
	setFlag(U, 1);
	setFlag(I, 1);
	write(0x0100 + stackPtr, statRegister);
	stackPtr--;

	addr_abs = 0xFFFA;
	uint16_t low = read(addr_abs + 0);
	uint16_t high = read(addr_abs + 1);
	pc = (high << 8) | low;

	cycles = 8;
}

uint8_t CPU::ASL()
{
	fetch();
	temp = (uint16_t)fetched << 1;
	setFlag(C, (temp & 0xFF00) > 0);
	setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, temp & 0x80);
	if (tableOp[opcode].addrmode == &CPU::IMP)
		accRegister = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t CPU::ROL()
{
	fetch();
	temp = (uint16_t)(fetched << 1) | getFlag(C);
	setFlag(C, temp & 0xFF00);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	if (tableOp[opcode].addrmode == &CPU::IMP)
		accRegister = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t CPU::ROR()
{
	fetch();
	temp = (uint16_t)(getFlag(C) << 7) | (fetched >> 1);
	setFlag(C, fetched & 0x01);
	setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, temp & 0x0080);
	if (tableOp[opcode].addrmode == &CPU::IMP)
		accRegister = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t CPU::RTI()
{
	stackPtr++;
	statRegister = read(0x0100 + stackPtr);
	statRegister &= ~B;
	statRegister &= ~U;

	stackPtr++;
	pc = (uint16_t)read(0x0100 + stackPtr);
	stackPtr++;
	pc |= (uint16_t)read(0x0100 + stackPtr) << 8;
	return 0;
}

uint8_t CPU::RTS()
{
	stackPtr++;
	pc = (uint16_t)read(0x0100 + stackPtr);
	stackPtr++;
	pc |= (uint16_t)read(0x0100 + stackPtr) << 8;
	
	pc++;
	return 0;
}

uint8_t CPU::SEC()
{
	setFlag(C, true);
	return 0;
}

uint8_t CPU::SED()
{
	setFlag(D, true);
	return 0;
}

uint8_t CPU::SEI()
{
	setFlag(I, true);
	return 0;
}

uint8_t CPU::STA()
{
	write(addr_abs, accRegister);
	return 0;
}

uint8_t CPU::STX()
{
	write(addr_abs, xRegister);
	return 0;
}

uint8_t CPU::STY()
{
	write(addr_abs, yRegister);
	return 0;
}

uint8_t CPU::TAX()
{
	xRegister = accRegister;
	setFlag(Z, xRegister == 0x00);
	setFlag(N, xRegister & 0x80);
	return 0;
}

uint8_t CPU::TAY()
{
	yRegister = accRegister;
	setFlag(Z, yRegister == 0x00);
	setFlag(N, yRegister & 0x80);
	return 0;
}

uint8_t CPU::TSX()
{
	xRegister = stackPtr;
	setFlag(Z, xRegister == 0x00);
	setFlag(N, xRegister & 0x80);
	return 0;
}

uint8_t CPU::TXA()
{
	accRegister = xRegister;
	setFlag(Z, accRegister == 0x00);
	setFlag(N, accRegister & 0x80);
	return 0;
}

uint8_t CPU::TXS()
{
	stackPtr = xRegister;
	return 0;
}

uint8_t CPU::TYA()
{
	accRegister = yRegister;
	setFlag(Z, accRegister == 0x00);
	setFlag(N, accRegister & 0x80);
	return 0;
}

uint8_t CPU::SUS()
{
	return 0;
}