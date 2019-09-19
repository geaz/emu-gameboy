#include <stdexcept>

#include "aritmetic.h"
#include "../../hardware/cpu.h"
#include "../../hardware/register.h"


/************** Inc *******************/
void Inc::IncRegister(Cpu* cpu, Register<uint8_t>& reg)
{
    reg++;
    cpu->setFlag(Z_ZERO, reg.read() == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, (reg.read() & 0x0F) == 0x00);
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
    cpu->memory.write(address, cpu->memory.read(address) + 1);
    cpu->setFlag(Z_ZERO, false);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, (cpu->memory.read(address) & 0x0F) == 0x00);
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
    cpu->setFlag(Z_ZERO, reg.read() == 0);
    cpu->setFlag(N_SUBSTRACT, true);
    cpu->setFlag(H_HALFCARRY, (reg.read() & 0x0F) == 0x0F);
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
    uint8_t address = cpu->hl.read();
    cpu->memory.write(address, cpu->memory.read(address) - 1);
    cpu->setFlag(Z_ZERO, false);
    cpu->setFlag(N_SUBSTRACT, true);
    cpu->setFlag(H_HALFCARRY, (cpu->memory.read(address) & 0x0F) == 0x0F);
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
    uint16_t result = storeIn.read() + value;

    // We only take the first 8 bits of each value and add them
    // If the result is bigger than 8 bits, we got a half carry!
    cpu->setFlag(H_HALFCARRY, (storeIn.read() & 0xFFF) + (value & 0xFFF) > 0xFFF);
    cpu->setFlag(C_CARRY, result > 0xFFFF);
    cpu->setFlag(N_SUBSTRACT, false);

    storeIn.write(result);
}

void Add::AddToRegister(Cpu* cpu, Register<uint8_t>& storeIn, uint8_t value)
{
    uint8_t result = storeIn.read() + value;

    // We only take the first 4 bits of each value and add them
    // If the result is bigger than 4 bits, we got a half carry!
    cpu->setFlag(H_HALFCARRY, (storeIn.read() & 0xF) + (value & 0xF) > 0xF);
    cpu->setFlag(C_CARRY, result > 0xFF);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(Z_ZERO, result == 0);

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
    Add::AddToRegister(cpu, cpu->a, cpu->memory.read(cpu->hl.read()));
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
    throw std::runtime_error("Not implemented! (AddE8)");
    return 0;
}

uint8_t Daa::Daa27(Cpu* cpu)
{
    // Mnemonic: DAA, Length: 1
    // Cycles: 4, (Z N H C): Z - 0 C
    throw std::runtime_error("Not implemented! (Daa27)");
    return 0;
}

uint8_t Cpl::Cpl2F(Cpu* cpu)
{
    // Mnemonic: CPL, Length: 1
    // Cycles: 4, (Z N H C): - 1 1 -
    throw std::runtime_error("Not implemented! (Cpl2F)");
    return 0;
}

uint8_t Scf::Scf37(Cpu* cpu)
{
    // Mnemonic: SCF, Length: 1
    // Cycles: 4, (Z N H C): - 0 0 1
    throw std::runtime_error("Not implemented! (Scf37)");
    return 0;
}

uint8_t Ccf::Ccf3F(Cpu* cpu)
{
    // Mnemonic: CCF, Length: 1
    // Cycles: 4, (Z N H C): - 0 0 C
    throw std::runtime_error("Not implemented! (Ccf3F)");
    return 0;
}

uint8_t Adc::Adc88(Cpu* cpu)
{
    // Mnemonic: ADC A,B, Length: 1
    // Cycles: 4, (Z N H C): Z 0 H C
    throw std::runtime_error("Not implemented! (Adc88)");
    return 0;
}

uint8_t Adc::Adc89(Cpu* cpu)
{
    // Mnemonic: ADC A,C, Length: 1
    // Cycles: 4, (Z N H C): Z 0 H C
    throw std::runtime_error("Not implemented! (Adc89)");
    return 0;
}

uint8_t Adc::Adc8A(Cpu* cpu)
{
    // Mnemonic: ADC A,D, Length: 1
    // Cycles: 4, (Z N H C): Z 0 H C
    throw std::runtime_error("Not implemented! (Adc8A)");
    return 0;
}

uint8_t Adc::Adc8B(Cpu* cpu)
{
    // Mnemonic: ADC A,E, Length: 1
    // Cycles: 4, (Z N H C): Z 0 H C
    throw std::runtime_error("Not implemented! (Adc8B)");
    return 0;
}

uint8_t Adc::Adc8C(Cpu* cpu)
{
    // Mnemonic: ADC A,H, Length: 1
    // Cycles: 4, (Z N H C): Z 0 H C
    throw std::runtime_error("Not implemented! (Adc8C)");
    return 0;
}

uint8_t Adc::Adc8D(Cpu* cpu)
{
    // Mnemonic: ADC A,L, Length: 1
    // Cycles: 4, (Z N H C): Z 0 H C
    throw std::runtime_error("Not implemented! (Adc8D)");
    return 0;
}

uint8_t Adc::Adc8E(Cpu* cpu)
{
    // Mnemonic: ADC A,(HL), Length: 1
    // Cycles: 8, (Z N H C): Z 0 H C
    throw std::runtime_error("Not implemented! (Adc8E)");
    return 0;
}

uint8_t Adc::Adc8F(Cpu* cpu)
{
    // Mnemonic: ADC A,A, Length: 1
    // Cycles: 4, (Z N H C): Z 0 H C
    throw std::runtime_error("Not implemented! (Adc8F)");
    return 0;
}

uint8_t Adc::AdcCE(Cpu* cpu)
{
    // Mnemonic: ADC A,d8, Length: 2
    // Cycles: 8, (Z N H C): Z 0 H C
    throw std::runtime_error("Not implemented! (AdcCE)");
    return 0;
}

uint8_t Sub::Sub90(Cpu* cpu)
{
    // Mnemonic: SUB B, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sub90)");
    return 0;
}

uint8_t Sub::Sub91(Cpu* cpu)
{
    // Mnemonic: SUB C, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sub91)");
    return 0;
}

uint8_t Sub::Sub92(Cpu* cpu)
{
    // Mnemonic: SUB D, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sub92)");
    return 0;
}

uint8_t Sub::Sub93(Cpu* cpu)
{
    // Mnemonic: SUB E, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sub93)");
    return 0;
}

uint8_t Sub::Sub94(Cpu* cpu)
{
    // Mnemonic: SUB H, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sub94)");
    return 0;
}

uint8_t Sub::Sub95(Cpu* cpu)
{
    // Mnemonic: SUB L, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sub95)");
    return 0;
}

uint8_t Sub::Sub96(Cpu* cpu)
{
    // Mnemonic: SUB (HL), Length: 1
    // Cycles: 8, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sub96)");
    return 0;
}

uint8_t Sub::Sub97(Cpu* cpu)
{
    // Mnemonic: SUB A, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sub97)");
    return 0;
}

uint8_t Sub::SubD6(Cpu* cpu)
{
    // Mnemonic: SUB d8, Length: 2
    // Cycles: 8, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (SubD6)");
    return 0;
}

uint8_t Sbc::Sbc98(Cpu* cpu)
{
    // Mnemonic: SBC A,B, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sbc98)");
    return 0;
}

uint8_t Sbc::Sbc99(Cpu* cpu)
{
    // Mnemonic: SBC A,C, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sbc99)");
    return 0;
}

uint8_t Sbc::Sbc9A(Cpu* cpu)
{
    // Mnemonic: SBC A,D, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sbc9A)");
    return 0;
}

uint8_t Sbc::Sbc9B(Cpu* cpu)
{
    // Mnemonic: SBC A,E, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sbc9B)");
    return 0;
}

uint8_t Sbc::Sbc9C(Cpu* cpu)
{
    // Mnemonic: SBC A,H, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sbc9C)");
    return 0;
}

uint8_t Sbc::Sbc9D(Cpu* cpu)
{
    // Mnemonic: SBC A,L, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sbc9D)");
    return 0;
}

uint8_t Sbc::Sbc9E(Cpu* cpu)
{
    // Mnemonic: SBC A,(HL), Length: 1
    // Cycles: 8, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sbc9E)");
    return 0;
}

uint8_t Sbc::Sbc9F(Cpu* cpu)
{
    // Mnemonic: SBC A,A, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (Sbc9F)");
    return 0;
}

uint8_t Sbc::SbcDE(Cpu* cpu)
{
    // Mnemonic: SBC A,d8, Length: 2
    // Cycles: 8, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (SbcDE)");
    return 0;
}

uint8_t And::AndA0(Cpu* cpu)
{
    // Mnemonic: AND B, Length: 1
    // Cycles: 4, (Z N H C): Z 0 1 0
    throw std::runtime_error("Not implemented! (AndA0)");
    return 0;
}

uint8_t And::AndA1(Cpu* cpu)
{
    // Mnemonic: AND C, Length: 1
    // Cycles: 4, (Z N H C): Z 0 1 0
    throw std::runtime_error("Not implemented! (AndA1)");
    return 0;
}

uint8_t And::AndA2(Cpu* cpu)
{
    // Mnemonic: AND D, Length: 1
    // Cycles: 4, (Z N H C): Z 0 1 0
    throw std::runtime_error("Not implemented! (AndA2)");
    return 0;
}

uint8_t And::AndA3(Cpu* cpu)
{
    // Mnemonic: AND E, Length: 1
    // Cycles: 4, (Z N H C): Z 0 1 0
    throw std::runtime_error("Not implemented! (AndA3)");
    return 0;
}

uint8_t And::AndA4(Cpu* cpu)
{
    // Mnemonic: AND H, Length: 1
    // Cycles: 4, (Z N H C): Z 0 1 0
    throw std::runtime_error("Not implemented! (AndA4)");
    return 0;
}

uint8_t And::AndA5(Cpu* cpu)
{
    // Mnemonic: AND L, Length: 1
    // Cycles: 4, (Z N H C): Z 0 1 0
    throw std::runtime_error("Not implemented! (AndA5)");
    return 0;
}

uint8_t And::AndA6(Cpu* cpu)
{
    // Mnemonic: AND (HL), Length: 1
    // Cycles: 8, (Z N H C): Z 0 1 0
    throw std::runtime_error("Not implemented! (AndA6)");
    return 0;
}

uint8_t And::AndA7(Cpu* cpu)
{
    // Mnemonic: AND A, Length: 1
    // Cycles: 4, (Z N H C): Z 0 1 0
    throw std::runtime_error("Not implemented! (AndA7)");
    return 0;
}

uint8_t And::AndE6(Cpu* cpu)
{
    // Mnemonic: AND d8, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 0
    throw std::runtime_error("Not implemented! (AndE6)");
    return 0;
}

/************** Xor *******************/
void Xor::XorAcc(Cpu* cpu, uint8_t value)
{
    cpu->a = cpu->a.read() ^ value;

    cpu->setFlag(Z_ZERO, cpu->a.read() == 0);
    cpu->setFlag(N_SUBSTRACT, 0);
    cpu->setFlag(H_HALFCARRY, 0);
    cpu->setFlag(C_CARRY, 0);
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
    Xor::XorAcc(cpu, cpu->memory.read(cpu->hl.read()));
    return 4;
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

uint8_t Or::OrB0(Cpu* cpu)
{
    // Mnemonic: OR B, Length: 1
    // Cycles: 4, (Z N H C): Z 0 0 0
    throw std::runtime_error("Not implemented! (OrB0)");
    return 0;
}

uint8_t Or::OrB1(Cpu* cpu)
{
    // Mnemonic: OR C, Length: 1
    // Cycles: 4, (Z N H C): Z 0 0 0
    throw std::runtime_error("Not implemented! (OrB1)");
    return 0;
}

uint8_t Or::OrB2(Cpu* cpu)
{
    // Mnemonic: OR D, Length: 1
    // Cycles: 4, (Z N H C): Z 0 0 0
    throw std::runtime_error("Not implemented! (OrB2)");
    return 0;
}

uint8_t Or::OrB3(Cpu* cpu)
{
    // Mnemonic: OR E, Length: 1
    // Cycles: 4, (Z N H C): Z 0 0 0
    throw std::runtime_error("Not implemented! (OrB3)");
    return 0;
}

uint8_t Or::OrB4(Cpu* cpu)
{
    // Mnemonic: OR H, Length: 1
    // Cycles: 4, (Z N H C): Z 0 0 0
    throw std::runtime_error("Not implemented! (OrB4)");
    return 0;
}

uint8_t Or::OrB5(Cpu* cpu)
{
    // Mnemonic: OR L, Length: 1
    // Cycles: 4, (Z N H C): Z 0 0 0
    throw std::runtime_error("Not implemented! (OrB5)");
    return 0;
}

uint8_t Or::OrB6(Cpu* cpu)
{
    // Mnemonic: OR (HL), Length: 1
    // Cycles: 8, (Z N H C): Z 0 0 0
    throw std::runtime_error("Not implemented! (OrB6)");
    return 0;
}

uint8_t Or::OrB7(Cpu* cpu)
{
    // Mnemonic: OR A, Length: 1
    // Cycles: 4, (Z N H C): Z 0 0 0
    throw std::runtime_error("Not implemented! (OrB7)");
    return 0;
}

uint8_t Or::OrF6(Cpu* cpu)
{
    // Mnemonic: OR d8, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    throw std::runtime_error("Not implemented! (OrF6)");
    return 0;
}

uint8_t Cp::CpB8(Cpu* cpu)
{
    // Mnemonic: CP B, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (CpB8)");
    return 0;
}

uint8_t Cp::CpB9(Cpu* cpu)
{
    // Mnemonic: CP C, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (CpB9)");
    return 0;
}

uint8_t Cp::CpBA(Cpu* cpu)
{
    // Mnemonic: CP D, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (CpBA)");
    return 0;
}

uint8_t Cp::CpBB(Cpu* cpu)
{
    // Mnemonic: CP E, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (CpBB)");
    return 0;
}

uint8_t Cp::CpBC(Cpu* cpu)
{
    // Mnemonic: CP H, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (CpBC)");
    return 0;
}

uint8_t Cp::CpBD(Cpu* cpu)
{
    // Mnemonic: CP L, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (CpBD)");
    return 0;
}

uint8_t Cp::CpBE(Cpu* cpu)
{
    // Mnemonic: CP (HL), Length: 1
    // Cycles: 8, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (CpBE)");
    return 0;
}

uint8_t Cp::CpBF(Cpu* cpu)
{
    // Mnemonic: CP A, Length: 1
    // Cycles: 4, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (CpBF)");
    return 0;
}

uint8_t Cp::CpFE(Cpu* cpu)
{
    // Mnemonic: CP d8, Length: 2
    // Cycles: 8, (Z N H C): Z 1 H C
    throw std::runtime_error("Not implemented! (CpFE)");
    return 0;
}

