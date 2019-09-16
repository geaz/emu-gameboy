#include <iostream>

#include "disassembler.h"
#include "instructions/instruction_set.h"

bool Disassembler::nextInstruction()
{
    bool next = false;
    if(instructionPosition < getInstructionCount())
    {
        bytePosition += currentInstruction.definition.length;
        currentInstruction = parsedInstructions[++instructionPosition];
        next = true;
    }
    return next;
}

void Disassembler::parseRom(Rom rom)
{
    parsedInstructions.clear();
    currentRom = rom;
    bytePosition = 0;
    instructionPosition = 0;

    int instructionCount = 0;
    for(int bytePosition = 0; bytePosition < (int) rom.romSize; bytePosition++)
    {
        if(instructionSet.set.find((unsigned char)rom.romData[bytePosition]) != instructionSet.set.end())
        {   
            // First get the instruction for the current bytePosition
            Instruction instruction = instructionSet.set[(unsigned char)rom.romData[bytePosition]];

            // Not every instruction is just one byte long
            // Thats why we also get the next x bytes (instruction.length)
            // and combine all retrieved bytes to one single opcode
            int k = 0;
            int opcode = 0;
            for(short j = instruction.length - 1; j >= 0; j--)
            {
                unsigned char singleByte = (unsigned char) rom.romData[bytePosition+k];
                opcode = opcode | singleByte << (j * 8);
                k++;
            }
            parsedInstructions.push_back({ opcode, instructionCount, bytePosition, instruction });

            bytePosition += instruction.length - 1;
            instructionCount++;
        }
    }
    currentInstruction = parsedInstructions[instructionPosition];
}

unsigned long Disassembler::getBytePosition() { return bytePosition; }
unsigned long Disassembler::getInstructionPosition() { return instructionPosition; }
unsigned long Disassembler::getInstructionCount() { return parsedInstructions.size(); }