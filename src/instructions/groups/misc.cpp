#include <stdexcept>

#include "misc.h"
#include "../../hardware/cpu.h"

uint8_t Nop::Nop00(Cpu* cpu)
{
    // Mnemonic: NOP, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    return 4;
}

uint8_t Rlca::Rlca07(Cpu* cpu)
{
    // Mnemonic: RLCA, Length: 1
    // Cycles: 4, (Z N H C): 0 0 0 C
    throw std::runtime_error("Not implemented! (Rlca07)");
    return 0;
}

uint8_t Rrca::Rrca0F(Cpu* cpu)
{
    // Mnemonic: RRCA, Length: 1
    // Cycles: 4, (Z N H C): 0 0 0 C
    throw std::runtime_error("Not implemented! (Rrca0F)");
    return 0;
}

uint8_t Stop::Stop10(Cpu* cpu)
{
    // Mnemonic: STOP 0, Length: 2
    // Cycles: 4, (Z N H C): - - - -
    throw std::runtime_error("Not implemented! (Stop10)");
    return 0;
}

uint8_t Rla::Rla17(Cpu* cpu)
{
    // Mnemonic: RLA, Length: 1
    // Cycles: 4, (Z N H C): 0 0 0 C
    throw std::runtime_error("Not implemented! (Rla17)");
    return 0;
}

uint8_t Rra::Rra1F(Cpu* cpu)
{
    // Mnemonic: RRA, Length: 1
    // Cycles: 4, (Z N H C): 0 0 0 C
    throw std::runtime_error("Not implemented! (Rra1F)");
    return 0;
}

uint8_t Halt::Halt76(Cpu* cpu)
{
    // Mnemonic: HALT, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    throw std::runtime_error("Not implemented! (Halt76)");
    return 0;
}

uint8_t Di::DiF3(Cpu* cpu)
{
    // Mnemonic: DI, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->interruptsEnabled = false;
    return 4;
}

uint8_t Ei::EiFB(Cpu* cpu)
{
    // Mnemonic: EI, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->interruptsEnabled = true;
    return 4;
}

