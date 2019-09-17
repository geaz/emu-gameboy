#pragma once
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <map>
#include <string>
#include <functional>

struct Instruction
{
    short length;                                   // Byte Length of the Instruction
    std::function<std::string (int)> getMnemonic;   // Method which returns the mnemonic for the given opcode
};

struct ParsedInstruction
{
    int bytes;
    int number;
    int bytePosition;
    Instruction definition;
};

class InstructionGroup
{
    public:
        std::map<unsigned char, Instruction> group;        

    protected:
        /**
         * 16-bit instructions are constructed in this way:
         * Byte 1: Instruction Code
         * Byte 2: Low-Order Address
         * Byte 3: High-Order Address
         * 
         * Therefore it is necessary to switch the bytes in a 16-bit instruction code
         * to get the correct address.
         */
        int getAddrFrom16Bit(int opcode)
        {
            return ((opcode & 0x00FF) << 8) | ((opcode & 0xFF00) >> 8);
        }
};

#endif // INSTRUCTION_H