#include "cpu.h"

Cpu::Cpu(Cartridge& cartridge) : cartridge(cartridge) 
{ 
    pc = (unsigned short) 0x100;
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
    Instruction instruction = instructionSet.set[cartridge.getDataAt(pc.get())];

    int k = 0;
    int opcode = 0;
    for(short j = instruction.length - 1; j >= 0; j--)
    {
        unsigned char singleByte = cartridge.getDataAt(pc.get());
        opcode = opcode | singleByte << (j * 8);
        k++;
    }

    return { opcode, pc.get(), instruction };
}