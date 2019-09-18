#include <stdexcept>

#include "branch.h"
#include "../../hardware/cpu.h"

uint8_t Jr::Jr18(Cpu* cpu)
{
    // Mnemonic: JR r8
    // Cycles: 12
    throw std::runtime_error("Not implemented! (Jr18)");
    return 0;
}

uint8_t Jr::Jr20(Cpu* cpu)
{
    // Mnemonic: JR NZ,r8
    // Cycles: 12/8
    throw std::runtime_error("Not implemented! (Jr20)");
    return 0;
}

uint8_t Jr::Jr28(Cpu* cpu)
{
    // Mnemonic: JR Z,r8
    // Cycles: 12/8
    throw std::runtime_error("Not implemented! (Jr28)");
    return 0;
}

uint8_t Jr::Jr30(Cpu* cpu)
{
    // Mnemonic: JR NC,r8
    // Cycles: 12/8
    throw std::runtime_error("Not implemented! (Jr30)");
    return 0;
}

uint8_t Jr::Jr38(Cpu* cpu)
{
    // Mnemonic: JR C,r8
    // Cycles: 12/8
    throw std::runtime_error("Not implemented! (Jr38)");
    return 0;
}

uint8_t Ret::RetC0(Cpu* cpu)
{
    // Mnemonic: RET NZ
    // Cycles: 20/8
    throw std::runtime_error("Not implemented! (RetC0)");
    return 0;
}

uint8_t Ret::RetC8(Cpu* cpu)
{
    // Mnemonic: RET Z
    // Cycles: 20/8
    throw std::runtime_error("Not implemented! (RetC8)");
    return 0;
}

uint8_t Ret::RetC9(Cpu* cpu)
{
    // Mnemonic: RET
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RetC9)");
    return 0;
}

uint8_t Ret::RetD0(Cpu* cpu)
{
    // Mnemonic: RET NC
    // Cycles: 20/8
    throw std::runtime_error("Not implemented! (RetD0)");
    return 0;
}

uint8_t Ret::RetD8(Cpu* cpu)
{
    // Mnemonic: RET C
    // Cycles: 20/8
    throw std::runtime_error("Not implemented! (RetD8)");
    return 0;
}

uint8_t Jp::JpC2(Cpu* cpu)
{
    // Mnemonic: JP NZ,a16
    // Cycles: 16/12
    throw std::runtime_error("Not implemented! (JpC2)");
    return 0;
}

uint8_t Jp::JpC3(Cpu* cpu)
{
    // Mnemonic: JP a16
    // Cycles: 16
    throw std::runtime_error("Not implemented! (JpC3)");
    return 0;
}

uint8_t Jp::JpCA(Cpu* cpu)
{
    // Mnemonic: JP Z,a16
    // Cycles: 16/12
    throw std::runtime_error("Not implemented! (JpCA)");
    return 0;
}

uint8_t Jp::JpD2(Cpu* cpu)
{
    // Mnemonic: JP NC,a16
    // Cycles: 16/12
    throw std::runtime_error("Not implemented! (JpD2)");
    return 0;
}

uint8_t Jp::JpDA(Cpu* cpu)
{
    // Mnemonic: JP C,a16
    // Cycles: 16/12
    throw std::runtime_error("Not implemented! (JpDA)");
    return 0;
}

uint8_t Jp::JpE9(Cpu* cpu)
{
    // Mnemonic: JP (HL)
    // Cycles: 4
    throw std::runtime_error("Not implemented! (JpE9)");
    return 0;
}

uint8_t Call::CallC4(Cpu* cpu)
{
    // Mnemonic: CALL NZ,a16
    // Cycles: 24/12
    throw std::runtime_error("Not implemented! (CallC4)");
    return 0;
}

uint8_t Call::CallCC(Cpu* cpu)
{
    // Mnemonic: CALL Z,a16
    // Cycles: 24/12
    throw std::runtime_error("Not implemented! (CallCC)");
    return 0;
}

uint8_t Call::CallCD(Cpu* cpu)
{
    // Mnemonic: CALL a16
    // Cycles: 24
    throw std::runtime_error("Not implemented! (CallCD)");
    return 0;
}

uint8_t Call::CallD4(Cpu* cpu)
{
    // Mnemonic: CALL NC,a16
    // Cycles: 24/12
    throw std::runtime_error("Not implemented! (CallD4)");
    return 0;
}

uint8_t Call::CallDC(Cpu* cpu)
{
    // Mnemonic: CALL C,a16
    // Cycles: 24/12
    throw std::runtime_error("Not implemented! (CallDC)");
    return 0;
}

uint8_t Rst::RstC7(Cpu* cpu)
{
    // Mnemonic: RST 00H
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RstC7)");
    return 0;
}

uint8_t Rst::RstCF(Cpu* cpu)
{
    // Mnemonic: RST 08H
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RstCF)");
    return 0;
}

uint8_t Rst::RstD7(Cpu* cpu)
{
    // Mnemonic: RST 10H
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RstD7)");
    return 0;
}

uint8_t Rst::RstDF(Cpu* cpu)
{
    // Mnemonic: RST 18H
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RstDF)");
    return 0;
}

uint8_t Rst::RstE7(Cpu* cpu)
{
    // Mnemonic: RST 20H
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RstE7)");
    return 0;
}

uint8_t Rst::RstEF(Cpu* cpu)
{
    // Mnemonic: RST 28H
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RstEF)");
    return 0;
}

uint8_t Rst::RstF7(Cpu* cpu)
{
    // Mnemonic: RST 30H
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RstF7)");
    return 0;
}

uint8_t Rst::RstFF(Cpu* cpu)
{
    // Mnemonic: RST 38H
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RstFF)");
    return 0;
}

uint8_t Reti::RetiD9(Cpu* cpu)
{
    // Mnemonic: RETI
    // Cycles: 16
    throw std::runtime_error("Not implemented! (RetiD9)");
    return 0;
}

