#include "cpu.h"

Cpu::Cpu(Memory& memory) : memory(memory) 
{ 
    pc = 0x100;
    nextInstruction = parseNextInstruction();
}

void Cpu::cycle() 
{   
    int cycles = clock.getCatchUpCycles();
    while(cycles > 0 && (state == RUNNING || state == STEP))
    {
        currentInstruction = nextInstruction;

        pc += currentInstruction.definition.length;
        cycles -= currentInstruction.definition.executeInterpreter(this);

        nextInstruction = parseNextInstruction();
        if(state == STEP) state = PAUSED;
    }   
    clock.Reset(); 
}

bool Cpu::getFlag(Flag flag)
{
    return f.readBit(flag);
}

void Cpu::setFlag(Flag flag, bool value)
{
    return f.writeBit(flag, value);
}

void Cpu::pushStack(uint16_t value)
{
    memory.write(sp.read() - 1, (value & 0xFF00) >> 8);
    memory.write(sp.read() - 2, value & 0x00FF);
    sp -= 2;
}

uint16_t Cpu::popStack()
{
    uint16_t value = (memory.read(sp.read() + 1) << 8) | memory.read(sp.read());
    sp += 2;
    return value;
}

ParsedInstruction Cpu::parseNextInstruction()
{
    // If the next Byte is 0xCB, then we look into the prefixSet
    // instead of the "normal" instruction set (Prefix Opcode)
    uint8_t nextByte = memory.read(pc.read());

    ParsedInstruction nextInstruction;
    nextInstruction.bytePosition = pc.read();
    nextInstruction.parsedBytes.opcode = nextByte;
    
    if(nextByte != 0xCB)
    {
        nextInstruction.definition = instructionSet.set[nextByte];
        if(nextInstruction.definition.length >= 2) nextInstruction.parsedBytes.low = memory.read(pc.read() + 1);
        if(nextInstruction.definition.length == 3)
        {
            nextInstruction.parsedBytes.high = memory.read(pc.read() + 2);
            nextInstruction.parsedBytes.b16 = (nextInstruction.parsedBytes.high << 8) | nextInstruction.parsedBytes.low;
        }        
    }
    else
    {
        nextInstruction.definition = instructionSet.prefixSet[memory.read(pc.read() + 1)];
        nextInstruction.parsedBytes.low = memory.read(pc.read() + 1);
    }

    addToParsedInstruction(nextInstruction);
    return nextInstruction;
}

void Cpu::addToParsedInstruction(ParsedInstruction parsedInstruction)
{
    if(parsedInstructions.size() == 100) parsedInstructions.pop_back();
    parsedInstructions.push_front(parsedInstruction);
}