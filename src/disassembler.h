#pragma once
#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <vector>
#include <optional>
#include <map>

#include "rom.h"
#include "instructions/instruction_set.h"

class Disassembler
{
    public: 
        bool nextInstruction();

        void parseRom(Rom rom);    
        unsigned long getBytePosition();
        unsigned long getInstructionPosition();
        unsigned long getInstructionCount();

        ParsedInstruction currentInstruction;
        std::vector<ParsedInstruction> parsedInstructions;

    private:
        InstructionSet instructionSet;
        std::optional<Rom> currentRom;
        unsigned long instructionPosition = 0;
        unsigned long bytePosition = 0;
};

#endif // DISASSEMBLER_H