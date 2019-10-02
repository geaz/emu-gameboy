#include <stdexcept>
#include "misc.h"
#include "../../hardware/cpu.h"

using GGB::Enums::CPU_FLAG;

namespace GGB::Hardware::Instructions
{
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
        cpu->a = Rlc::RotateLeftAndSetFlags(cpu, cpu->a.read());    
        cpu->setFlag(CPU_FLAG::Z_ZERO, false);
        return 4;
    }

    uint8_t Rrca::Rrca0F(Cpu* cpu)
    {
        // Mnemonic: RRCA, Length: 1
        // Cycles: 4, (Z N H C): 0 0 0 C
        cpu->a = Rrc::RotateRightAndSetFlags(cpu, cpu->a.read());    
        cpu->setFlag(CPU_FLAG::Z_ZERO, false);
        return 4;
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
        cpu->a = Rl::RotateLeftThroughCarryAndSetFlags(cpu, cpu->a.read());    
        cpu->setFlag(CPU_FLAG::Z_ZERO, false);
        return 4;
    }

    uint8_t Rra::Rra1F(Cpu* cpu)
    {
        // Mnemonic: RRA, Length: 1
        // Cycles: 4, (Z N H C): 0 0 0 C
        cpu->a = Rr::RotateRightThroughCarryAndSetFlags(cpu, cpu->a.read());    
        cpu->setFlag(CPU_FLAG::Z_ZERO, false);
        return 4;
    }

    uint8_t Halt::Halt76(Cpu* cpu)
    {
        // Mnemonic: HALT, Length: 1
        // Cycles: 4, (Z N H C): - - - -
        cpu->halted = true;
        return 4;
    }

    uint8_t Di::DiF3(Cpu* cpu)
    {
        // Mnemonic: DI, Length: 1
        // Cycles: 4, (Z N H C): - - - -
        cpu->interruptMasterFlag = false;
        return 4;
    }

    uint8_t Ei::EiFB(Cpu* cpu)
    {
        // Mnemonic: EI, Length: 1
        // Cycles: 4, (Z N H C): - - - -
        cpu->interruptMasterFlag = true;
        return 4;
    }
}