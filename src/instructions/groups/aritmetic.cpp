#include <stdexcept>

#include "aritmetic.h"
#include "../../hardware/cpu.h"

unsigned char Inc::Inc03(Cpu* cpu)
{
    // Mnemonic: INC BC
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc04(Cpu* cpu)
{
    // Mnemonic: INC B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc0C(Cpu* cpu)
{
    // Mnemonic: INC C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc13(Cpu* cpu)
{
    // Mnemonic: INC DE
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc14(Cpu* cpu)
{
    // Mnemonic: INC D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc1C(Cpu* cpu)
{
    // Mnemonic: INC E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc23(Cpu* cpu)
{
    // Mnemonic: INC HL
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc24(Cpu* cpu)
{
    // Mnemonic: INC H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc2C(Cpu* cpu)
{
    // Mnemonic: INC L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc33(Cpu* cpu)
{
    // Mnemonic: INC SP
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc34(Cpu* cpu)
{
    // Mnemonic: INC (HL)
    // Cycles: 12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Inc::Inc3C(Cpu* cpu)
{
    // Mnemonic: INC A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec05(Cpu* cpu)
{
    // Mnemonic: DEC B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec0B(Cpu* cpu)
{
    // Mnemonic: DEC BC
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec0D(Cpu* cpu)
{
    // Mnemonic: DEC C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec15(Cpu* cpu)
{
    // Mnemonic: DEC D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec1B(Cpu* cpu)
{
    // Mnemonic: DEC DE
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec1D(Cpu* cpu)
{
    // Mnemonic: DEC E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec25(Cpu* cpu)
{
    // Mnemonic: DEC H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec2B(Cpu* cpu)
{
    // Mnemonic: DEC HL
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec2D(Cpu* cpu)
{
    // Mnemonic: DEC L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec35(Cpu* cpu)
{
    // Mnemonic: DEC (HL)
    // Cycles: 12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec3B(Cpu* cpu)
{
    // Mnemonic: DEC SP
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Dec::Dec3D(Cpu* cpu)
{
    // Mnemonic: DEC A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add09(Cpu* cpu)
{
    // Mnemonic: ADD HL,BC
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add19(Cpu* cpu)
{
    // Mnemonic: ADD HL,DE
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add29(Cpu* cpu)
{
    // Mnemonic: ADD HL,HL
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add39(Cpu* cpu)
{
    // Mnemonic: ADD HL,SP
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add80(Cpu* cpu)
{
    // Mnemonic: ADD A,B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add81(Cpu* cpu)
{
    // Mnemonic: ADD A,C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add82(Cpu* cpu)
{
    // Mnemonic: ADD A,D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add83(Cpu* cpu)
{
    // Mnemonic: ADD A,E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add84(Cpu* cpu)
{
    // Mnemonic: ADD A,H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add85(Cpu* cpu)
{
    // Mnemonic: ADD A,L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add86(Cpu* cpu)
{
    // Mnemonic: ADD A,(HL)
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::Add87(Cpu* cpu)
{
    // Mnemonic: ADD A,A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::AddC6(Cpu* cpu)
{
    // Mnemonic: ADD A,d8
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Add::AddE8(Cpu* cpu)
{
    // Mnemonic: ADD SP,r8
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Daa::Daa27(Cpu* cpu)
{
    // Mnemonic: DAA
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cpl::Cpl2F(Cpu* cpu)
{
    // Mnemonic: CPL
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Scf::Scf37(Cpu* cpu)
{
    // Mnemonic: SCF
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Ccf::Ccf3F(Cpu* cpu)
{
    // Mnemonic: CCF
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Adc::Adc88(Cpu* cpu)
{
    // Mnemonic: ADC A,B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Adc::Adc89(Cpu* cpu)
{
    // Mnemonic: ADC A,C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Adc::Adc8A(Cpu* cpu)
{
    // Mnemonic: ADC A,D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Adc::Adc8B(Cpu* cpu)
{
    // Mnemonic: ADC A,E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Adc::Adc8C(Cpu* cpu)
{
    // Mnemonic: ADC A,H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Adc::Adc8D(Cpu* cpu)
{
    // Mnemonic: ADC A,L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Adc::Adc8E(Cpu* cpu)
{
    // Mnemonic: ADC A,(HL)
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Adc::Adc8F(Cpu* cpu)
{
    // Mnemonic: ADC A,A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Adc::AdcCE(Cpu* cpu)
{
    // Mnemonic: ADC A,d8
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sub::Sub90(Cpu* cpu)
{
    // Mnemonic: SUB B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sub::Sub91(Cpu* cpu)
{
    // Mnemonic: SUB C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sub::Sub92(Cpu* cpu)
{
    // Mnemonic: SUB D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sub::Sub93(Cpu* cpu)
{
    // Mnemonic: SUB E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sub::Sub94(Cpu* cpu)
{
    // Mnemonic: SUB H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sub::Sub95(Cpu* cpu)
{
    // Mnemonic: SUB L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sub::Sub96(Cpu* cpu)
{
    // Mnemonic: SUB (HL)
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sub::Sub97(Cpu* cpu)
{
    // Mnemonic: SUB A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sub::SubD6(Cpu* cpu)
{
    // Mnemonic: SUB d8
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sbc::Sbc98(Cpu* cpu)
{
    // Mnemonic: SBC A,B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sbc::Sbc99(Cpu* cpu)
{
    // Mnemonic: SBC A,C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sbc::Sbc9A(Cpu* cpu)
{
    // Mnemonic: SBC A,D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sbc::Sbc9B(Cpu* cpu)
{
    // Mnemonic: SBC A,E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sbc::Sbc9C(Cpu* cpu)
{
    // Mnemonic: SBC A,H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sbc::Sbc9D(Cpu* cpu)
{
    // Mnemonic: SBC A,L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sbc::Sbc9E(Cpu* cpu)
{
    // Mnemonic: SBC A,(HL)
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sbc::Sbc9F(Cpu* cpu)
{
    // Mnemonic: SBC A,A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Sbc::SbcDE(Cpu* cpu)
{
    // Mnemonic: SBC A,d8
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char And::AndA0(Cpu* cpu)
{
    // Mnemonic: AND B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char And::AndA1(Cpu* cpu)
{
    // Mnemonic: AND C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char And::AndA2(Cpu* cpu)
{
    // Mnemonic: AND D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char And::AndA3(Cpu* cpu)
{
    // Mnemonic: AND E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char And::AndA4(Cpu* cpu)
{
    // Mnemonic: AND H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char And::AndA5(Cpu* cpu)
{
    // Mnemonic: AND L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char And::AndA6(Cpu* cpu)
{
    // Mnemonic: AND (HL)
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char And::AndA7(Cpu* cpu)
{
    // Mnemonic: AND A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char And::AndE6(Cpu* cpu)
{
    // Mnemonic: AND d8
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Xor::XorA8(Cpu* cpu)
{
    // Mnemonic: XOR B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Xor::XorA9(Cpu* cpu)
{
    // Mnemonic: XOR C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Xor::XorAA(Cpu* cpu)
{
    // Mnemonic: XOR D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Xor::XorAB(Cpu* cpu)
{
    // Mnemonic: XOR E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Xor::XorAC(Cpu* cpu)
{
    // Mnemonic: XOR H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Xor::XorAD(Cpu* cpu)
{
    // Mnemonic: XOR L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Xor::XorAE(Cpu* cpu)
{
    // Mnemonic: XOR (HL)
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Xor::XorAF(Cpu* cpu)
{
    // Mnemonic: XOR A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Xor::XorEE(Cpu* cpu)
{
    // Mnemonic: XOR d8
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Or::OrB0(Cpu* cpu)
{
    // Mnemonic: OR B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Or::OrB1(Cpu* cpu)
{
    // Mnemonic: OR C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Or::OrB2(Cpu* cpu)
{
    // Mnemonic: OR D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Or::OrB3(Cpu* cpu)
{
    // Mnemonic: OR E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Or::OrB4(Cpu* cpu)
{
    // Mnemonic: OR H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Or::OrB5(Cpu* cpu)
{
    // Mnemonic: OR L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Or::OrB6(Cpu* cpu)
{
    // Mnemonic: OR (HL)
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Or::OrB7(Cpu* cpu)
{
    // Mnemonic: OR A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Or::OrF6(Cpu* cpu)
{
    // Mnemonic: OR d8
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cp::CpB8(Cpu* cpu)
{
    // Mnemonic: CP B
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cp::CpB9(Cpu* cpu)
{
    // Mnemonic: CP C
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cp::CpBA(Cpu* cpu)
{
    // Mnemonic: CP D
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cp::CpBB(Cpu* cpu)
{
    // Mnemonic: CP E
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cp::CpBC(Cpu* cpu)
{
    // Mnemonic: CP H
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cp::CpBD(Cpu* cpu)
{
    // Mnemonic: CP L
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cp::CpBE(Cpu* cpu)
{
    // Mnemonic: CP (HL)
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cp::CpBF(Cpu* cpu)
{
    // Mnemonic: CP A
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Cp::CpFE(Cpu* cpu)
{
    // Mnemonic: CP d8
    // Cycles: 8
    throw std::runtime_error("Not implemented!");
    return 0;
}

