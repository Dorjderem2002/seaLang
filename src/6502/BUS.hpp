#include <cstdint>

#include "CPU.hpp"

class BUS
{
public:
    BUS();
    uint8_t read(uint16_t addr, bool readOnly = false);
    void write(uint16_t addr, uint8_t data);

    
private:
    uint8_t ram[64 * 1024];
    CPU cpu;
};