#include "cpu.h"

Cpu::Cpu(Memory& memory) : memory(memory) 
{ 
    pc = 0x100;
    nextInstruction = parseNextInstruction();
}

void Cpu::cycle() 
{   
    currentInstruction = nextInstruction;

    currentInstruction.definition.executeInterpreter(this);
    pc += currentInstruction.definition.length;
    
    nextInstruction = parseNextInstruction();
}

ParsedInstruction Cpu::parseNextInstruction()
{
    Instruction instruction = instructionSet.set[memory.read(pc.get())];

    int opcode = 0;
    for(int j = instruction.length - 1; j >= 0; j--)
    {
        uint8_t singleByte = memory.read(pc.get());
        opcode = opcode | singleByte << (j * 8);
    }

    return { opcode, pc.get(), instruction };
}