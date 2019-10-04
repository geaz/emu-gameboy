#include <stdexcept>
#include "aritmetic.h"
#include "../../hardware/cpu.h"

using GGB::Enums::CPU_FLAG;

namespace GGB::Hardware::Instructions
{
    /************** Inc *******************/
    void Inc::IncRegister(Cpu* cpu, Register<uint8_t>& reg)
    {
        reg++;
        cpu->setFlag(CPU_FLAG::Z_ZERO, reg.read() == 0);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (reg.read() & 0x0F) == 0x00);
    }

    uint8_t Inc::Inc03(Cpu* cpu)
    {
        // Mnemonic: INC BC, Length: 1
        // Cycles: 8, (Z N H C): - - - -
        cpu->bc++;
        return 8;
    }

    uint8_t Inc::Inc04(Cpu* cpu)
    {
        // Mnemonic: INC B, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H -
        Inc::IncRegister(cpu, cpu->b);
        return 4;
    }

    uint8_t Inc::Inc0C(Cpu* cpu)
    {
        // Mnemonic: INC C, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H -
        Inc::IncRegister(cpu, cpu->c);
        return 4;
    }

    uint8_t Inc::Inc13(Cpu* cpu)
    {
        // Mnemonic: INC DE, Length: 1
        // Cycles: 8, (Z N H C): - - - -
        cpu->de++;
        return 8;
    }

    uint8_t Inc::Inc14(Cpu* cpu)
    {
        // Mnemonic: INC D, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H -
        Inc::IncRegister(cpu, cpu->d);
        return 4;
    }

    uint8_t Inc::Inc1C(Cpu* cpu)
    {
        // Mnemonic: INC E, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H -
        Inc::IncRegister(cpu, cpu->e);
        return 4;
    }

    uint8_t Inc::Inc23(Cpu* cpu)
    {
        // Mnemonic: INC HL, Length: 1
        // Cycles: 8, (Z N H C): - - - -
        cpu->hl++;
        return 8;
    }

    uint8_t Inc::Inc24(Cpu* cpu)
    {
        // Mnemonic: INC H, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H -
        Inc::IncRegister(cpu, cpu->h);
        return 4;
    }

    uint8_t Inc::Inc2C(Cpu* cpu)
    {
        // Mnemonic: INC L, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H -
        Inc::IncRegister(cpu, cpu->l);
        return 4;
    }

    uint8_t Inc::Inc33(Cpu* cpu)
    {
        // Mnemonic: INC SP, Length: 1
        // Cycles: 8, (Z N H C): - - - -
        cpu->sp++;
        return 8;
    }

    uint8_t Inc::Inc34(Cpu* cpu)
    {
        // Mnemonic: INC (HL), Length: 1
        // Cycles: 12, (Z N H C): Z 0 H -
        uint16_t address = cpu->hl.read();
        uint8_t result = cpu->mmu.read(address) + 1;

        cpu->mmu.write(address, result);
        cpu->setFlag(CPU_FLAG::Z_ZERO, result == 0);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (result & 0x0F) == 0x00);
        return 12;
    }

    uint8_t Inc::Inc3C(Cpu* cpu)
    {
        // Mnemonic: INC A, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H -
        Inc::IncRegister(cpu, cpu->a);
        return 4;
    }


    /************** Dec *******************/
    void Dec::DecRegister(Cpu* cpu, Register<uint8_t>& reg)
    {
        reg--;
        cpu->setFlag(CPU_FLAG::Z_ZERO, reg.read() == 0);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, true);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (reg.read() & 0x0F) == 0x0F);
    }

    uint8_t Dec::Dec05(Cpu* cpu)
    {
        // Mnemonic: DEC B, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H -
        Dec::DecRegister(cpu, cpu->b);
        return 4;
    }

    uint8_t Dec::Dec0B(Cpu* cpu)
    {
        // Mnemonic: DEC BC, Length: 1
        // Cycles: 8, (Z N H C): - - - -
        cpu->bc--;
        return 8;
    }

    uint8_t Dec::Dec0D(Cpu* cpu)
    {
        // Mnemonic: DEC C, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H -
        Dec::DecRegister(cpu, cpu->c);
        return 4;
    }

    uint8_t Dec::Dec15(Cpu* cpu)
    {
        // Mnemonic: DEC D, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H -
        Dec::DecRegister(cpu, cpu->d);
        return 4;
    }

    uint8_t Dec::Dec1B(Cpu* cpu)
    {
        // Mnemonic: DEC DE, Length: 1
        // Cycles: 8, (Z N H C): - - - -
        cpu->de--;
        return 8;
    }

    uint8_t Dec::Dec1D(Cpu* cpu)
    {
        // Mnemonic: DEC E, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H -
        Dec::DecRegister(cpu, cpu->e);
        return 4;
    }

    uint8_t Dec::Dec25(Cpu* cpu)
    {
        // Mnemonic: DEC H, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H -
        Dec::DecRegister(cpu, cpu->h);
        return 4;
    }

    uint8_t Dec::Dec2B(Cpu* cpu)
    {
        // Mnemonic: DEC HL, Length: 1
        // Cycles: 8, (Z N H C): - - - -
        cpu->hl--;
        return 8;
    }

    uint8_t Dec::Dec2D(Cpu* cpu)
    {
        // Mnemonic: DEC L, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H -
        Dec::DecRegister(cpu, cpu->l);
        return 4;
    }

    uint8_t Dec::Dec35(Cpu* cpu)
    {
        // Mnemonic: DEC (HL), Length: 1
        // Cycles: 12, (Z N H C): Z 1 H -
        uint16_t address = cpu->hl.read();
        uint8_t result = cpu->mmu.read(address) - 1;

        cpu->mmu.write(address, result);
        cpu->setFlag(CPU_FLAG::Z_ZERO, result == 0);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, true);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (result & 0x0F) == 0x0F);
        return 12;
    }

    uint8_t Dec::Dec3B(Cpu* cpu)
    {
        // Mnemonic: DEC SP, Length: 1
        // Cycles: 8, (Z N H C): - - - -
        cpu->sp--;
        return 8;
    }

    uint8_t Dec::Dec3D(Cpu* cpu)
    {
        // Mnemonic: DEC A, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H -
        Dec::DecRegister(cpu, cpu->a);
        return 4;
    }


    /************** Add *******************/
    void Add::AddToRegisterPair(Cpu* cpu, RegisterPair& storeIn, uint16_t value)
    {
        uint32_t fullResult = storeIn.read() + value;
        uint16_t result = static_cast<uint16_t>(fullResult); 

        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (storeIn.read() ^ value ^ (fullResult & 0xFFFF)) & 0x1000);
        cpu->setFlag(CPU_FLAG::C_CARRY, fullResult > 0xFFFF);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);

        storeIn.write(result);
    }

    void Add::AddToRegister(Cpu* cpu, Register<uint8_t>& storeIn, uint8_t value)
    {
        uint16_t fullResult = storeIn.read() + value;
        uint8_t result = static_cast<uint8_t>(fullResult);

        // We only take the first 4 bits of each value and add them
        // If the result is bigger than 4 bits, we got a half carry!
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (storeIn.read() & 0xF) + (value & 0xF) > 0xF);
        cpu->setFlag(CPU_FLAG::C_CARRY, fullResult > 0xFF);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::Z_ZERO, result == 0);

        storeIn = result;
    }

    uint8_t Add::Add09(Cpu* cpu)
    {
        // Mnemonic: ADD HL,BC, Length: 1
        // Cycles: 8, (Z N H C): - 0 H C
        Add::AddToRegisterPair(cpu, cpu->hl, cpu->bc.read());
        return 8;
    }

    uint8_t Add::Add19(Cpu* cpu)
    {
        // Mnemonic: ADD HL,DE, Length: 1
        // Cycles: 8, (Z N H C): - 0 H C
        Add::AddToRegisterPair(cpu, cpu->hl, cpu->de.read());
        return 8;
    }

    uint8_t Add::Add29(Cpu* cpu)
    {
        // Mnemonic: ADD HL,HL, Length: 1
        // Cycles: 8, (Z N H C): - 0 H C
        Add::AddToRegisterPair(cpu, cpu->hl, cpu->hl.read());
        return 8;
    }

    uint8_t Add::Add39(Cpu* cpu)
    {
        // Mnemonic: ADD HL,SP, Length: 1
        // Cycles: 8, (Z N H C): - 0 H C
        Add::AddToRegisterPair(cpu, cpu->hl, cpu->sp.read());
        return 8;
    }

    uint8_t Add::Add80(Cpu* cpu)
    {
        // Mnemonic: ADD A,B, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Add::AddToRegister(cpu, cpu->a, cpu->b.read());
        return 4;
    }

    uint8_t Add::Add81(Cpu* cpu)
    {
        // Mnemonic: ADD A,C, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Add::AddToRegister(cpu, cpu->a, cpu->c.read());
        return 4;
    }

    uint8_t Add::Add82(Cpu* cpu)
    {
        // Mnemonic: ADD A,D, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Add::AddToRegister(cpu, cpu->a, cpu->d.read());
        return 4;
    }

    uint8_t Add::Add83(Cpu* cpu)
    {
        // Mnemonic: ADD A,E, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Add::AddToRegister(cpu, cpu->a, cpu->e.read());
        return 4;
    }

    uint8_t Add::Add84(Cpu* cpu)
    {
        // Mnemonic: ADD A,H, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Add::AddToRegister(cpu, cpu->a, cpu->h.read());
        return 4;
    }

    uint8_t Add::Add85(Cpu* cpu)
    {
        // Mnemonic: ADD A,L, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Add::AddToRegister(cpu, cpu->a, cpu->l.read());
        return 4;
    }

    uint8_t Add::Add86(Cpu* cpu)
    {
        // Mnemonic: ADD A,(HL), Length: 1
        // Cycles: 8, (Z N H C): Z 0 H C
        Add::AddToRegister(cpu, cpu->a, cpu->mmu.read(cpu->hl.read()));
        return 8;
    }

    uint8_t Add::Add87(Cpu* cpu)
    {
        // Mnemonic: ADD A,A, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Add::AddToRegister(cpu, cpu->a, cpu->a.read());
        return 4;
    }

    uint8_t Add::AddC6(Cpu* cpu)
    {
        // Mnemonic: ADD A,d8, Length: 2
        // Cycles: 8, (Z N H C): Z 0 H C
        Add::AddToRegister(cpu, cpu->a, cpu->currentInstruction.parsedBytes.low);
        return 8;
    }

    uint8_t Add::AddE8(Cpu* cpu)
    {
        // Mnemonic: ADD SP,r8, Length: 2
        // Cycles: 16, (Z N H C): 0 0 H C
        int8_t signedValue = static_cast<int8_t>(cpu->currentInstruction.parsedBytes.low);  
        int32_t fullResult = cpu->sp.read() + signedValue;
        uint16_t result = static_cast<uint16_t>(fullResult);

        cpu->setFlag(CPU_FLAG::Z_ZERO, false);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, ((cpu->sp.read() ^ signedValue ^ (fullResult & 0xFFFF)) & 0x10) == 0x10);
        cpu->setFlag(CPU_FLAG::C_CARRY, ((cpu->sp.read() ^ signedValue ^ (fullResult & 0xFFFF)) & 0x100) == 0x100);

        cpu->sp = result;
        return 16;
    }

    uint8_t Daa::Daa27(Cpu* cpu)
    {
        // Mnemonic: DAA, Length: 1
        // Cycles: 4, (Z N H C): Z - 0 C
        int32_t result = cpu->a.read();
        if(cpu->getFlag(CPU_FLAG::N_SUBSTRACT))
        {
            if(cpu->getFlag(CPU_FLAG::H_HALFCARRY))
            {
                result -= 6;
            }
            if(cpu->getFlag(CPU_FLAG::C_CARRY))
            {
                result -= 0x60;
            }
        }
        else
        {
            if(cpu->getFlag(CPU_FLAG::H_HALFCARRY) || (cpu->a.read() & 0x0F) > 9)
            {
                result += 6;
            }
            if(cpu->getFlag(CPU_FLAG::C_CARRY) || result > 0x9F)
            {
                result += 0x60;
            }
        }
        cpu->a = static_cast<uint8_t>(result);
        if(result > 0xFF) cpu->setFlag(CPU_FLAG::C_CARRY, true);
        cpu->setFlag(CPU_FLAG::Z_ZERO, cpu->a.read() == 0);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, false);    
        return 4;
    }

    uint8_t Cpl::Cpl2F(Cpu* cpu)
    {
        // Mnemonic: CPL, Length: 1
        // Cycles: 4, (Z N H C): - 1 1 -
        cpu->a = ~cpu->a.read();
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, true);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, true);
        return 4;
    }

    uint8_t Scf::Scf37(Cpu* cpu)
    {
        // Mnemonic: SCF, Length: 1
        // Cycles: 4, (Z N H C): - 0 0 1
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, false);
        cpu->setFlag(CPU_FLAG::C_CARRY, true);
        return 4;
    }

    uint8_t Ccf::Ccf3F(Cpu* cpu)
    {
        // Mnemonic: CCF, Length: 1
        // Cycles: 4, (Z N H C): - 0 0 C
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, false);
        cpu->setFlag(CPU_FLAG::C_CARRY, !cpu->getFlag(CPU_FLAG::C_CARRY));
        return 4;
    }

    /************** Adc *******************/
    void Adc::AdcToRegister(Cpu* cpu, Register<uint8_t>& storeIn, uint8_t value)
    {
        uint16_t fullResult = storeIn.read() + value + cpu->getFlag(CPU_FLAG::C_CARRY);
        uint8_t result = static_cast<uint8_t>(fullResult);

        // We only take the first 4 bits of each value and add them
        // If the result is bigger than 4 bits, we got a half carry!
        cpu->setFlag(CPU_FLAG::Z_ZERO, result == 0);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (storeIn.read() & 0xF) + (value & 0xF) + cpu->getFlag(CPU_FLAG::C_CARRY) > 0xF);
        cpu->setFlag(CPU_FLAG::C_CARRY, fullResult > 0xFF);

        storeIn = result;
    }

    uint8_t Adc::Adc88(Cpu* cpu)
    {
        // Mnemonic: ADC A,B, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Adc::AdcToRegister(cpu, cpu->a, cpu->b.read());
        return 4;
    }

    uint8_t Adc::Adc89(Cpu* cpu)
    {
        // Mnemonic: ADC A,C, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Adc::AdcToRegister(cpu, cpu->a, cpu->c.read());
        return 4;
    }

    uint8_t Adc::Adc8A(Cpu* cpu)
    {
        // Mnemonic: ADC A,D, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Adc::AdcToRegister(cpu, cpu->a, cpu->d.read());
        return 4;
    }

    uint8_t Adc::Adc8B(Cpu* cpu)
    {
        // Mnemonic: ADC A,E, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Adc::AdcToRegister(cpu, cpu->a, cpu->e.read());
        return 4;
    }

    uint8_t Adc::Adc8C(Cpu* cpu)
    {
        // Mnemonic: ADC A,H, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Adc::AdcToRegister(cpu, cpu->a, cpu->h.read());
        return 4;
    }

    uint8_t Adc::Adc8D(Cpu* cpu)
    {
        // Mnemonic: ADC A,L, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Adc::AdcToRegister(cpu, cpu->a, cpu->l.read());
        return 4;
    }

    uint8_t Adc::Adc8E(Cpu* cpu)
    {
        // Mnemonic: ADC A,(HL), Length: 1
        // Cycles: 8, (Z N H C): Z 0 H C
        Adc::AdcToRegister(cpu, cpu->a, cpu->mmu.read(cpu->hl.read()));
        return 8;
    }

    uint8_t Adc::Adc8F(Cpu* cpu)
    {
        // Mnemonic: ADC A,A, Length: 1
        // Cycles: 4, (Z N H C): Z 0 H C
        Adc::AdcToRegister(cpu, cpu->a, cpu->a.read());
        return 4;
    }

    uint8_t Adc::AdcCE(Cpu* cpu)
    {
        // Mnemonic: ADC A,d8, Length: 2
        // Cycles: 8, (Z N H C): Z 0 H C
        Adc::AdcToRegister(cpu, cpu->a, cpu->currentInstruction.parsedBytes.low);
        return 8;
    }

    /************** Sub *******************/
    void Sub::SubToRegister(Cpu* cpu, Register<uint8_t>& storeIn, uint8_t value)
    {
        uint8_t result = storeIn.read() - value;

        // We only take the first 4 bits of each value and sub them
        // If the result is smaller than 0, we got a half carry!
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (storeIn.read() & 0xF) - (value & 0xF) < 0);
        cpu->setFlag(CPU_FLAG::C_CARRY, storeIn.read() < value);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, true);
        cpu->setFlag(CPU_FLAG::Z_ZERO, result == 0);

        storeIn = result;
    }

    uint8_t Sub::Sub90(Cpu* cpu)
    {
        // Mnemonic: SUB B, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sub::SubToRegister(cpu, cpu->a, cpu->b.read());
        return 4;
    }

    uint8_t Sub::Sub91(Cpu* cpu)
    {
        // Mnemonic: SUB C, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sub::SubToRegister(cpu, cpu->a, cpu->c.read());
        return 4;
    }

    uint8_t Sub::Sub92(Cpu* cpu)
    {
        // Mnemonic: SUB D, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sub::SubToRegister(cpu, cpu->a, cpu->d.read());
        return 4;
    }

    uint8_t Sub::Sub93(Cpu* cpu)
    {
        // Mnemonic: SUB E, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sub::SubToRegister(cpu, cpu->a, cpu->e.read());
        return 4;
    }

    uint8_t Sub::Sub94(Cpu* cpu)
    {
        // Mnemonic: SUB H, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sub::SubToRegister(cpu, cpu->a, cpu->h.read());
        return 4;
    }

    uint8_t Sub::Sub95(Cpu* cpu)
    {
        // Mnemonic: SUB L, Length: 1
        Sub::SubToRegister(cpu, cpu->a, cpu->l.read());
        return 4;
    }

    uint8_t Sub::Sub96(Cpu* cpu)
    {
        // Mnemonic: SUB (HL), Length: 1
        // Cycles: 8, (Z N H C): Z 1 H C
        Sub::SubToRegister(cpu, cpu->a, cpu->mmu.read(cpu->hl.read()));
        return 8;
    }

    uint8_t Sub::Sub97(Cpu* cpu)
    {
        // Mnemonic: SUB A, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sub::SubToRegister(cpu, cpu->a, cpu->a.read());
        return 4;
    }

    uint8_t Sub::SubD6(Cpu* cpu)
    {
        // Mnemonic: SUB d8, Length: 2
        // Cycles: 8, (Z N H C): Z 1 H C
        Sub::SubToRegister(cpu, cpu->a, cpu->currentInstruction.parsedBytes.low);
        return 8;
    }

    /************** Sbc *******************/
    void Sbc::SbcToRegister(Cpu* cpu, Register<uint8_t>& storeIn, uint8_t value)
    {
        int32_t fullResult = storeIn.read() - value - cpu->getFlag(CPU_FLAG::C_CARRY);
        uint8_t result = static_cast<uint8_t>(fullResult);

        cpu->setFlag(CPU_FLAG::Z_ZERO, result == 0);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, true);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (storeIn.read() & 0xF) - (value & 0xF) - cpu->getFlag(CPU_FLAG::C_CARRY) < 0);
        cpu->setFlag(CPU_FLAG::C_CARRY, fullResult < 0);

        storeIn = result;
    }

    uint8_t Sbc::Sbc98(Cpu* cpu)
    {
        // Mnemonic: SBC A,B, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sbc::SbcToRegister(cpu, cpu->a, cpu->b.read());
        return 4;
    }

    uint8_t Sbc::Sbc99(Cpu* cpu)
    {
        // Mnemonic: SBC A,C, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sbc::SbcToRegister(cpu, cpu->a, cpu->c.read());
        return 4;
    }

    uint8_t Sbc::Sbc9A(Cpu* cpu)
    {
        // Mnemonic: SBC A,D, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sbc::SbcToRegister(cpu, cpu->a, cpu->d.read());
        return 4;
    }

    uint8_t Sbc::Sbc9B(Cpu* cpu)
    {
        // Mnemonic: SBC A,E, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sbc::SbcToRegister(cpu, cpu->a, cpu->e.read());
        return 4;
    }

    uint8_t Sbc::Sbc9C(Cpu* cpu)
    {
        // Mnemonic: SBC A,H, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sbc::SbcToRegister(cpu, cpu->a, cpu->h.read());
        return 4;
    }

    uint8_t Sbc::Sbc9D(Cpu* cpu)
    {
        // Mnemonic: SBC A,L, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sbc::SbcToRegister(cpu, cpu->a, cpu->l.read());
        return 4;
    }

    uint8_t Sbc::Sbc9E(Cpu* cpu)
    {
        // Mnemonic: SBC A,(HL), Length: 1
        // Cycles: 8, (Z N H C): Z 1 H C
        Sbc::SbcToRegister(cpu, cpu->a, cpu->mmu.read(cpu->hl.read()));
        return 8;
    }

    uint8_t Sbc::Sbc9F(Cpu* cpu)
    {
        // Mnemonic: SBC A,A, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Sbc::SbcToRegister(cpu, cpu->a, cpu->a.read());
        return 4;
    }

    uint8_t Sbc::SbcDE(Cpu* cpu)
    {
        // Mnemonic: SBC A,d8, Length: 2
        // Cycles: 8, (Z N H C): Z 1 H C
        Sbc::SbcToRegister(cpu, cpu->a, cpu->currentInstruction.parsedBytes.low);
        return 8;
    }

    /************** And *******************/
    void And::AndAcc(Cpu* cpu, uint8_t value)
    {
        cpu->a = cpu->a.read() & value;

        cpu->setFlag(CPU_FLAG::Z_ZERO, cpu->a.read() == 0);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, true);
        cpu->setFlag(CPU_FLAG::C_CARRY, false);
    }

    uint8_t And::AndA0(Cpu* cpu)
    {
        // Mnemonic: AND B, Length: 1
        // Cycles: 4, (Z N H C): Z 0 1 0
        And::AndAcc(cpu, cpu->b.read());
        return 4;
    }

    uint8_t And::AndA1(Cpu* cpu)
    {
        // Mnemonic: AND C, Length: 1
        // Cycles: 4, (Z N H C): Z 0 1 0
        And::AndAcc(cpu, cpu->c.read());
        return 4;
    }

    uint8_t And::AndA2(Cpu* cpu)
    {
        // Mnemonic: AND D, Length: 1
        // Cycles: 4, (Z N H C): Z 0 1 0
        And::AndAcc(cpu, cpu->d.read());
        return 4;
    }

    uint8_t And::AndA3(Cpu* cpu)
    {
        // Mnemonic: AND E, Length: 1
        // Cycles: 4, (Z N H C): Z 0 1 0
        And::AndAcc(cpu, cpu->e.read());
        return 4;
    }

    uint8_t And::AndA4(Cpu* cpu)
    {
        // Mnemonic: AND H, Length: 1
        // Cycles: 4, (Z N H C): Z 0 1 0
        And::AndAcc(cpu, cpu->h.read());
        return 4;
    }

    uint8_t And::AndA5(Cpu* cpu)
    {
        // Mnemonic: AND L, Length: 1
        // Cycles: 4, (Z N H C): Z 0 1 0
        And::AndAcc(cpu, cpu->l.read());
        return 4;
    }

    uint8_t And::AndA6(Cpu* cpu)
    {
        // Mnemonic: AND (HL), Length: 1
        // Cycles: 8, (Z N H C): Z 0 1 0
        And::AndAcc(cpu, cpu->mmu.read(cpu->hl.read()));
        return 8;
    }

    uint8_t And::AndA7(Cpu* cpu)
    {
        // Mnemonic: AND A, Length: 1
        // Cycles: 4, (Z N H C): Z 0 1 0
        And::AndAcc(cpu, cpu->a.read());
        return 4;
    }

    uint8_t And::AndE6(Cpu* cpu)
    {
        // Mnemonic: AND d8, Length: 2
        // Cycles: 8, (Z N H C): Z 0 1 0
        And::AndAcc(cpu, cpu->currentInstruction.parsedBytes.low);
        return 8;
    }

    /************** Xor *******************/
    void Xor::XorAcc(Cpu* cpu, uint8_t value)
    {
        cpu->a = cpu->a.read() ^ value;

        cpu->setFlag(CPU_FLAG::Z_ZERO, cpu->a.read() == 0);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, false);
        cpu->setFlag(CPU_FLAG::C_CARRY, false);
    }

    uint8_t Xor::XorA8(Cpu* cpu)
    {
        // Mnemonic: XOR B, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Xor::XorAcc(cpu, cpu->b.read());
        return 4;
    }

    uint8_t Xor::XorA9(Cpu* cpu)
    {
        // Mnemonic: XOR C, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Xor::XorAcc(cpu, cpu->c.read());
        return 4;
    }

    uint8_t Xor::XorAA(Cpu* cpu)
    {
        // Mnemonic: XOR D, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Xor::XorAcc(cpu, cpu->d.read());
        return 4;
    }

    uint8_t Xor::XorAB(Cpu* cpu)
    {
        // Mnemonic: XOR E, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Xor::XorAcc(cpu, cpu->e.read());
        return 4;
    }

    uint8_t Xor::XorAC(Cpu* cpu)
    {
        // Mnemonic: XOR H, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Xor::XorAcc(cpu, cpu->h.read());
        return 4;
    }

    uint8_t Xor::XorAD(Cpu* cpu)
    {
        // Mnemonic: XOR L, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Xor::XorAcc(cpu, cpu->l.read());
        return 4;
    }

    uint8_t Xor::XorAE(Cpu* cpu)
    {
        // Mnemonic: XOR (HL), Length: 1
        // Cycles: 8, (Z N H C): Z 0 0 0
        Xor::XorAcc(cpu, cpu->mmu.read(cpu->hl.read()));
        return 8;
    }

    uint8_t Xor::XorAF(Cpu* cpu)
    {
        // Mnemonic: XOR A, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Xor::XorAcc(cpu, cpu->a.read());
        return 4;
    }

    uint8_t Xor::XorEE(Cpu* cpu)
    {
        // Mnemonic: XOR d8, Length: 2
        // Cycles: 8, (Z N H C): Z 0 0 0
        Xor::XorAcc(cpu, cpu->currentInstruction.parsedBytes.low);
        return 8;
    }

    /************** Or *******************/
    void Or::OrAcc(Cpu* cpu, uint8_t value)
    {
        cpu->a = cpu->a.read() | value;

        cpu->setFlag(CPU_FLAG::Z_ZERO, cpu->a.read() == 0);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, false);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, false);
        cpu->setFlag(CPU_FLAG::C_CARRY, false);
    }

    uint8_t Or::OrB0(Cpu* cpu)
    {
        // Mnemonic: OR B, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Or::OrAcc(cpu, cpu->b.read());
        return 4;
    }

    uint8_t Or::OrB1(Cpu* cpu)
    {
        // Mnemonic: OR C, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Or::OrAcc(cpu, cpu->c.read());
        return 4;
    }

    uint8_t Or::OrB2(Cpu* cpu)
    {
        // Mnemonic: OR D, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Or::OrAcc(cpu, cpu->d.read());
        return 4;
    }

    uint8_t Or::OrB3(Cpu* cpu)
    {
        // Mnemonic: OR E, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Or::OrAcc(cpu, cpu->e.read());
        return 4;
    }

    uint8_t Or::OrB4(Cpu* cpu)
    {
        // Mnemonic: OR H, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Or::OrAcc(cpu, cpu->h.read());
        return 4;
    }

    uint8_t Or::OrB5(Cpu* cpu)
    {
        // Mnemonic: OR L, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Or::OrAcc(cpu, cpu->l.read());
        return 4;
    }

    uint8_t Or::OrB6(Cpu* cpu)
    {
        // Mnemonic: OR (HL), Length: 1
        // Cycles: 8, (Z N H C): Z 0 0 0
        Or::OrAcc(cpu, cpu->mmu.read(cpu->hl.read()));
        return 8;
    }

    uint8_t Or::OrB7(Cpu* cpu)
    {
        // Mnemonic: OR A, Length: 1
        // Cycles: 4, (Z N H C): Z 0 0 0
        Or::OrAcc(cpu, cpu->a.read());
        return 4;
    }

    uint8_t Or::OrF6(Cpu* cpu)
    {
        // Mnemonic: OR d8, Length: 2
        // Cycles: 8, (Z N H C): Z 0 0 0
        Or::OrAcc(cpu, cpu->currentInstruction.parsedBytes.low);
        return 8;
    }

    /************** CP *******************/
    void Cp::CpAcc(Cpu* cpu, uint8_t value)
    {
        cpu->setFlag(CPU_FLAG::Z_ZERO, cpu->a.read() == value);
        cpu->setFlag(CPU_FLAG::N_SUBSTRACT, true);
        cpu->setFlag(CPU_FLAG::H_HALFCARRY, (cpu->a.read() & 0xF) - (value & 0xF) < 0);
        cpu->setFlag(CPU_FLAG::C_CARRY, cpu->a.read() < value);
    }

    uint8_t Cp::CpB8(Cpu* cpu)
    {
        // Mnemonic: CP B, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Cp::CpAcc(cpu, cpu->b.read());
        return 4;
    }

    uint8_t Cp::CpB9(Cpu* cpu)
    {
        // Mnemonic: CP C, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Cp::CpAcc(cpu, cpu->c.read());
        return 4;
    }

    uint8_t Cp::CpBA(Cpu* cpu)
    {
        // Mnemonic: CP D, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Cp::CpAcc(cpu, cpu->d.read());
        return 4;
    }

    uint8_t Cp::CpBB(Cpu* cpu)
    {
        // Mnemonic: CP E, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Cp::CpAcc(cpu, cpu->e.read());
        return 4;
    }

    uint8_t Cp::CpBC(Cpu* cpu)
    {
        // Mnemonic: CP H, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Cp::CpAcc(cpu, cpu->h.read());
        return 4;
    }

    uint8_t Cp::CpBD(Cpu* cpu)
    {
        // Mnemonic: CP L, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Cp::CpAcc(cpu, cpu->l.read());
        return 4;
    }

    uint8_t Cp::CpBE(Cpu* cpu)
    {
        // Mnemonic: CP (HL), Length: 1
        // Cycles: 8, (Z N H C): Z 1 H C
        Cp::CpAcc(cpu, cpu->mmu.read(cpu->hl.read()));
        return 8;
    }

    uint8_t Cp::CpBF(Cpu* cpu)
    {
        // Mnemonic: CP A, Length: 1
        // Cycles: 4, (Z N H C): Z 1 H C
        Cp::CpAcc(cpu, cpu->a.read());
        return 4;
    }

    uint8_t Cp::CpFE(Cpu* cpu)
    {
        // Mnemonic: CP d8, Length: 2
        // Cycles: 8, (Z N H C): Z 1 H C
        Cp::CpAcc(cpu, cpu->currentInstruction.parsedBytes.low);
        return 8;
    }
}