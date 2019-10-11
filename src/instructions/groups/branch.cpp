#include <stdexcept>
#include "branch.hpp"
#include "../../hardware/cpu.hpp"

namespace GGB::Hardware::Instructions
{
    using GGB::Enum::CpuFlag;

    uint8_t Jr::Jr18(Cpu* cpu)
    {
        // Mnemonic: JR r8, Length: 2
        // Cycles: 12, (Z N H C): - - - -
        cpu->pc += static_cast<int8_t>(cpu->currentInstruction.parsedBytes.low);
        return 12;
    }

    uint8_t Jr::Jr20(Cpu* cpu)
    {
        // Mnemonic: JR NZ,r8, Length: 2
        // Cycles: 12/8, (Z N H C): - - - -
        bool zeroFlag = cpu->f.readBit((uint8_t)CpuFlag::Z_ZERO);
        if(!zeroFlag) cpu->pc += static_cast<int8_t>(cpu->currentInstruction.parsedBytes.low);    
        return !zeroFlag ? 12 : 8;
    }

    uint8_t Jr::Jr28(Cpu* cpu)
    {
        // Mnemonic: JR Z,r8, Length: 2
        // Cycles: 12/8, (Z N H C): - - - -
        bool zeroFlag = cpu->f.readBit((uint8_t)CpuFlag::Z_ZERO);
        if(zeroFlag) cpu->pc += static_cast<int8_t>(cpu->currentInstruction.parsedBytes.low);
        return zeroFlag ? 12 : 8;
    }

    uint8_t Jr::Jr30(Cpu* cpu)
    {
        // Mnemonic: JR NC,r8, Length: 2
        // Cycles: 12/8, (Z N H C): - - - -
        bool carryFlag = cpu->f.readBit((uint8_t)CpuFlag::C_CARRY);
        if(!carryFlag) cpu->pc += static_cast<int8_t>(cpu->currentInstruction.parsedBytes.low);
        return !carryFlag ? 12 : 8;
    }

    uint8_t Jr::Jr38(Cpu* cpu)
    {
        // Mnemonic: JR C,r8, Length: 2
        // Cycles: 12/8, (Z N H C): - - - -
        bool carryFlag = cpu->f.readBit((uint8_t)CpuFlag::C_CARRY);
        if(carryFlag) cpu->pc += static_cast<int8_t>(cpu->currentInstruction.parsedBytes.low);
        return carryFlag ? 12 : 8;
    }

    uint8_t Ret::RetC0(Cpu* cpu)
    {
        // Mnemonic: RET NZ, Length: 1
        // Cycles: 20/8, (Z N H C): - - - -
        bool zeroFlag = cpu->f.readBit((uint8_t)CpuFlag::Z_ZERO);
        if(!zeroFlag) cpu->pc = cpu->popStack();
        return !zeroFlag ? 20 : 8;
    }

    uint8_t Ret::RetC8(Cpu* cpu)
    {
        // Mnemonic: RET Z, Length: 1
        // Cycles: 20/8, (Z N H C): - - - -
        bool zeroFlag = cpu->f.readBit((uint8_t)CpuFlag::Z_ZERO);
        if(zeroFlag) cpu->pc = cpu->popStack();
        return zeroFlag ? 20 : 8;
    }

    uint8_t Ret::RetC9(Cpu* cpu)
    {
        // Mnemonic: RET, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pc = cpu->popStack();
        return 16;
    }

    uint8_t Ret::RetD0(Cpu* cpu)
    {
        // Mnemonic: RET NC, Length: 1
        // Cycles: 20/8, (Z N H C): - - - -
        bool carryFlag = cpu->f.readBit((uint8_t)CpuFlag::C_CARRY);
        if(!carryFlag) cpu->pc = cpu->popStack();
        return !carryFlag ? 20 : 8;
    }

    uint8_t Ret::RetD8(Cpu* cpu)
    {
        // Mnemonic: RET C, Length: 1
        // Cycles: 20/8, (Z N H C): - - - -
        bool carryFlag = cpu->f.readBit((uint8_t)CpuFlag::C_CARRY);
        if(carryFlag) cpu->pc = cpu->popStack();
        return carryFlag ? 20 : 8;
    }

    uint8_t Jp::JpC2(Cpu* cpu)
    {
        // Mnemonic: JP NZ,a16, Length: 3
        // Cycles: 16/12, (Z N H C): - - - -
        bool zeroFlag = cpu->f.readBit((uint8_t)CpuFlag::Z_ZERO);
        if(!zeroFlag) cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        return !zeroFlag ? 16 : 12;
    }

    uint8_t Jp::JpC3(Cpu* cpu)
    {
        // Mnemonic: JP a16, Length: 3
        // Cycles: 16, (Z N H C): - - - -
        cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        return 16;
    }

    uint8_t Jp::JpCA(Cpu* cpu)
    {
        // Mnemonic: JP Z,a16, Length: 3
        // Cycles: 16/12, (Z N H C): - - - -
        bool zeroFlag = cpu->f.readBit((uint8_t)CpuFlag::Z_ZERO);
        if(zeroFlag) cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        return zeroFlag ? 16 : 12;
    }

    uint8_t Jp::JpD2(Cpu* cpu)
    {
        // Mnemonic: JP NC,a16, Length: 3
        // Cycles: 16/12, (Z N H C): - - - -
        bool carryFlag = cpu->f.readBit((uint8_t)CpuFlag::C_CARRY);
        if(!carryFlag) cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        return !carryFlag ? 16 : 12;
    }

    uint8_t Jp::JpDA(Cpu* cpu)
    {
        // Mnemonic: JP C,a16, Length: 3
        // Cycles: 16/12, (Z N H C): - - - -
        bool carryFlag = cpu->f.readBit((uint8_t)CpuFlag::C_CARRY);
        if(carryFlag) cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        return carryFlag ? 16 : 12;
    }

    uint8_t Jp::JpE9(Cpu* cpu)
    {
        // Mnemonic: JP (HL), Length: 1
        // Cycles: 4, (Z N H C): - - - -
        cpu->pc = cpu->hl.read();
        return 4;
    }

    uint8_t Call::CallC4(Cpu* cpu)
    {
        // Mnemonic: CALL NZ,a16, Length: 3
        // Cycles: 24/12, (Z N H C): - - - -
        bool zeroFlag = cpu->f.readBit((uint8_t)CpuFlag::Z_ZERO);
        if(!zeroFlag) 
        {
            cpu->pushStack(cpu->pc.read()); 
            cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        }
        return !zeroFlag ? 24 : 12;
    }

    uint8_t Call::CallCC(Cpu* cpu)
    {
        // Mnemonic: CALL Z,a16, Length: 3
        // Cycles: 24/12, (Z N H C): - - - -
        bool zeroFlag = cpu->f.readBit((uint8_t)CpuFlag::Z_ZERO);
        if(zeroFlag)
        {
            cpu->pushStack(cpu->pc.read()); 
            cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        }
        return zeroFlag ? 24 : 12;
    }

    uint8_t Call::CallCD(Cpu* cpu)
    {
        // Mnemonic: CALL a16, Length: 3
        // Cycles: 24, (Z N H C): - - - -
        cpu->pushStack(cpu->pc.read()); 
        cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        return 24;
    }

    uint8_t Call::CallD4(Cpu* cpu)
    {
        // Mnemonic: CALL NC,a16, Length: 3
        // Cycles: 24/12, (Z N H C): - - - -
        bool carryFlag = cpu->f.readBit((uint8_t)CpuFlag::C_CARRY);
        if(!carryFlag) 
        {
            cpu->pushStack(cpu->pc.read()); 
            cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        }
        return !carryFlag ? 24 : 12;
    }

    uint8_t Call::CallDC(Cpu* cpu)
    {
        // Mnemonic: CALL C,a16, Length: 3
        // Cycles: 24/12, (Z N H C): - - - -
        bool carryFlag = cpu->f.readBit((uint8_t)CpuFlag::C_CARRY);
        if(carryFlag)
        {
            cpu->pushStack(cpu->pc.read()); 
            cpu->pc = cpu->currentInstruction.parsedBytes.b16;
        }
        return carryFlag ? 24 : 12;
    }

    /************** Rst *******************/
    uint8_t Rst::RstC7(Cpu* cpu)
    {
        // Mnemonic: RST 00H, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pushStack(cpu->pc.read());
        cpu->pc = 0x0;
        return 16;
    }

    uint8_t Rst::RstCF(Cpu* cpu)
    {
        // Mnemonic: RST 08H, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pushStack(cpu->pc.read());
        cpu->pc = 0x08;
        return 16;
    }

    uint8_t Rst::RstD7(Cpu* cpu)
    {
        // Mnemonic: RST 10H, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pushStack(cpu->pc.read());
        cpu->pc = 0x10;
        return 16;
    }

    uint8_t Rst::RstDF(Cpu* cpu)
    {
        // Mnemonic: RST 18H, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pushStack(cpu->pc.read());
        cpu->pc = 0x18;
        return 16;
    }

    uint8_t Rst::RstE7(Cpu* cpu)
    {
        // Mnemonic: RST 20H, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pushStack(cpu->pc.read());
        cpu->pc = 0x20;
        return 16;
    }

    uint8_t Rst::RstEF(Cpu* cpu)
    {
        // Mnemonic: RST 28H, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pushStack(cpu->pc.read());
        cpu->pc = 0x28;
        return 16;
    }

    uint8_t Rst::RstF7(Cpu* cpu)
    {
        // Mnemonic: RST 30H, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pushStack(cpu->pc.read());
        cpu->pc = 0x30;
        return 16;
    }

    uint8_t Rst::RstFF(Cpu* cpu)
    {
        // Mnemonic: RST 38H, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pushStack(cpu->pc.read());
        cpu->pc = 0x38;
        return 16;
    }

    uint8_t Reti::RetiD9(Cpu* cpu)
    {
        // Mnemonic: RETI, Length: 1
        // Cycles: 16, (Z N H C): - - - -
        cpu->pc = cpu->popStack();
        cpu->interruptMasterFlag = true;
        return 16;
    }
}