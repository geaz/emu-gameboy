#include "cpu.h"

Cpu::Cpu(Cartridge& cartridge) : cartridge(cartridge) 
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
    Instruction instruction = instructionSet.set[cartridge.getDataAt(pc.get())];

    int k = 0;
    int opcode = 0;
    for(uint8_t j = instruction.length - 1; j >= 0; j--)
    {
        uint8_t singleByte = cartridge.getDataAt(pc.get());
        opcode = opcode | singleByte << (j * 8);
        k++;
    }

    return { opcode, pc.get(), instruction };
}