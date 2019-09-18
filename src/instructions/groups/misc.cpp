#include <stdexcept>

#include "misc.h"
#include "../../hardware/cpu.h"

unsigned char Nop::Nop00(Cpu* cpu)
{
    // Mnemonic: NOP
    // Cycles: 4
    return 4;
}

unsigned char Rlca::Rlca07(Cpu* cpu)
{
    // Mnemonic: RLCA
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rrca::Rrca0F(Cpu* cpu)
{
    // Mnemonic: RRCA
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Stop::Stop10(Cpu* cpu)
{
    // Mnemonic: STOP 0
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rla::Rla17(Cpu* cpu)
{
    // Mnemonic: RLA
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rra::Rra1F(Cpu* cpu)
{
    // Mnemonic: RRA
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Halt::Halt76(Cpu* cpu)
{
    // Mnemonic: HALT
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Di::DiF3(Cpu* cpu)
{
    // Mnemonic: DI
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Ei::EiFB(Cpu* cpu)
{
    // Mnemonic: EI
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

