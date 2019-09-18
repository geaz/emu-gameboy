#include <stdexcept>

#include "misc.h"
#include "../../hardware/cpu.h"

uint8_t Nop::Nop00(Cpu* cpu)
{
    // Mnemonic: NOP
    // Cycles: 4
    throw std::runtime_error("Not implemented! (Nop00)");
    return 0;
}

uint8_t Rlca::Rlca07(Cpu* cpu)
{
    // Mnemonic: RLCA
    // Cycles: 4
    throw std::runtime_error("Not implemented! (Rlca07)");
    return 0;
}

uint8_t Rrca::Rrca0F(Cpu* cpu)
{
    // Mnemonic: RRCA
    // Cycles: 4
    throw std::runtime_error("Not implemented! (Rrca0F)");
    return 0;
}

uint8_t Stop::Stop10(Cpu* cpu)
{
    // Mnemonic: STOP 0
    // Cycles: 4
    throw std::runtime_error("Not implemented! (Stop10)");
    return 0;
}

uint8_t Rla::Rla17(Cpu* cpu)
{
    // Mnemonic: RLA
    // Cycles: 4
    throw std::runtime_error("Not implemented! (Rla17)");
    return 0;
}

uint8_t Rra::Rra1F(Cpu* cpu)
{
    // Mnemonic: RRA
    // Cycles: 4
    throw std::runtime_error("Not implemented! (Rra1F)");
    return 0;
}

uint8_t Halt::Halt76(Cpu* cpu)
{
    // Mnemonic: HALT
    // Cycles: 4
    throw std::runtime_error("Not implemented! (Halt76)");
    return 0;
}

uint8_t Di::DiF3(Cpu* cpu)
{
    // Mnemonic: DI
    // Cycles: 4
    throw std::runtime_error("Not implemented! (DiF3)");
    return 0;
}

uint8_t Ei::EiFB(Cpu* cpu)
{
    // Mnemonic: EI
    // Cycles: 4
    throw std::runtime_error("Not implemented! (EiFB)");
    return 0;
}

