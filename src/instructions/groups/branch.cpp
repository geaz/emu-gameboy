#include <stdexcept>

#include "branch.h"
#include "../../hardware/cpu.h"

unsigned char Jr::Jr18(Cpu* cpu)
{
    // Mnemonic: JR r8
    // Cycles: 12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jr::Jr20(Cpu* cpu)
{
    // Mnemonic: JR NZ,r8
    // Cycles: 12/8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jr::Jr28(Cpu* cpu)
{
    // Mnemonic: JR Z,r8
    // Cycles: 12/8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jr::Jr30(Cpu* cpu)
{
    // Mnemonic: JR NC,r8
    // Cycles: 12/8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jr::Jr38(Cpu* cpu)
{
    // Mnemonic: JR C,r8
    // Cycles: 12/8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Ret::RetC0(Cpu* cpu)
{
    // Mnemonic: RET NZ
    // Cycles: 20/8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Ret::RetC8(Cpu* cpu)
{
    // Mnemonic: RET Z
    // Cycles: 20/8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Ret::RetC9(Cpu* cpu)
{
    // Mnemonic: RET
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Ret::RetD0(Cpu* cpu)
{
    // Mnemonic: RET NC
    // Cycles: 20/8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Ret::RetD8(Cpu* cpu)
{
    // Mnemonic: RET C
    // Cycles: 20/8
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jp::JpC2(Cpu* cpu)
{
    // Mnemonic: JP NZ,a16
    // Cycles: 16/12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jp::JpC3(Cpu* cpu)
{
    // Mnemonic: JP a16
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jp::JpCA(Cpu* cpu)
{
    // Mnemonic: JP Z,a16
    // Cycles: 16/12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jp::JpD2(Cpu* cpu)
{
    // Mnemonic: JP NC,a16
    // Cycles: 16/12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jp::JpDA(Cpu* cpu)
{
    // Mnemonic: JP C,a16
    // Cycles: 16/12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Jp::JpE9(Cpu* cpu)
{
    // Mnemonic: JP (HL)
    // Cycles: 4
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Call::CallC4(Cpu* cpu)
{
    // Mnemonic: CALL NZ,a16
    // Cycles: 24/12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Call::CallCC(Cpu* cpu)
{
    // Mnemonic: CALL Z,a16
    // Cycles: 24/12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Call::CallCD(Cpu* cpu)
{
    // Mnemonic: CALL a16
    // Cycles: 24
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Call::CallD4(Cpu* cpu)
{
    // Mnemonic: CALL NC,a16
    // Cycles: 24/12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Call::CallDC(Cpu* cpu)
{
    // Mnemonic: CALL C,a16
    // Cycles: 24/12
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rst::RstC7(Cpu* cpu)
{
    // Mnemonic: RST 00H
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rst::RstCF(Cpu* cpu)
{
    // Mnemonic: RST 08H
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rst::RstD7(Cpu* cpu)
{
    // Mnemonic: RST 10H
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rst::RstDF(Cpu* cpu)
{
    // Mnemonic: RST 18H
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rst::RstE7(Cpu* cpu)
{
    // Mnemonic: RST 20H
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rst::RstEF(Cpu* cpu)
{
    // Mnemonic: RST 28H
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rst::RstF7(Cpu* cpu)
{
    // Mnemonic: RST 30H
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Rst::RstFF(Cpu* cpu)
{
    // Mnemonic: RST 38H
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

unsigned char Reti::RetiD9(Cpu* cpu)
{
    // Mnemonic: RETI
    // Cycles: 16
    throw std::runtime_error("Not implemented!");
    return 0;
}

