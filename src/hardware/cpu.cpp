#include "cpu.h"
#include "../helper/string_helper.h"

Cpu::Cpu(Memory& memory) : memory(memory) 
{ 
    setPowerUpSequence();
    nextInstruction = parseNextInstruction();
}

long Cpu::cycle() 
{   
    int processedCycles = 0;
    int cycles = clock.getCatchUpCycles();
    while(cycles > 0 && (state == RUNNING || state == STEP))
    {
        currentInstruction = nextInstruction;

        pc += currentInstruction.definition.length;
        cycles -= currentInstruction.definition.executeInterpreter(this);
        processedCycles++;

        handleInterrupts();
        nextInstruction = parseNextInstruction();

        bool breakPointHit = 
                std::string(breakPoint) != "" 
                && std::string(breakPoint) == StringHelper::IntToHexString(nextInstruction.bytePosition, 4, false);
        if(state == STEP || breakPointHit) state = PAUSED;
    }   
    clock.Reset(); 
    return processedCycles;
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

void Cpu::handleInterrupts()
{
    uint16_t interruptVector = 0;
    uint8_t interruptFlag = 0;

    bool vBlankInterrupt = memory.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_V_BLANK)
                         & memory.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_V_BLANK);
    bool lcdInterrupt = memory.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_LCD)
                      & memory.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_LCD);
    bool timerInterrupt = memory.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_TIMER)
                        & memory.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_TIMER);
    bool serialInterrupt = memory.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_SERIAL)
                         & memory.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_SERIAL);
    bool joypadInterrupt = memory.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_INPUT)
                         & memory.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_INPUT);

    if(vBlankInterrupt)
    {
        interruptVector = VECTOR_V_BLANK;
        interruptFlag = INTERRUPT_V_BLANK;
    } 
    else if(lcdInterrupt)
    {
        interruptVector = VECTOR_LCD;
        interruptFlag = INTERRUPT_LCD;
    } 
    else if(timerInterrupt)
    {
        interruptVector = VECTOR_TIMER;
        interruptFlag = INTERRUPT_TIMER;
    }
    else if(serialInterrupt)
    {
        interruptVector = VECTOR_SERIAL;
        interruptFlag = INTERRUPT_SERIAL;
    }
    else if(joypadInterrupt)
    {
        interruptVector = VECTOR_INPUT;
        interruptFlag = INTERRUPT_INPUT;
    }
    
    if(interruptVector != 0 && interruptMasterFlag)
    {
        interruptMasterFlag = false;
        memory.writeIORegisterBit(REG_INTERRUPT_FLAG, interruptFlag, false);
        pushStack(pc.read());
        pc = interruptVector;
    }    
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

    addToParsedInstructions(nextInstruction);
    return nextInstruction;
}

void Cpu::addToParsedInstructions(ParsedInstruction parsedInstruction)
{
    if(parsedInstructions.size() == 500) parsedInstructions.pop_back();
    parsedInstructions.push_front(parsedInstruction);
}

void Cpu::setPowerUpSequence()
{
    memory.write(0xFF05, 0x0);   // TIMA
    memory.write(0xFF06, 0x0);   // TMA
    memory.write(0xFF07, 0x0);   // TAC
    memory.write(0xFF10, 0x80);  // NR10
    memory.write(0xFF11, 0xBF);  // NR11
    memory.write(0xFF12, 0xF3);  // NR12
    memory.write(0xFF14, 0xBF);  // NR14
    memory.write(0xFF16, 0x3F);  // NR21
    memory.write(0xFF17, 0x00);  // NR22
    memory.write(0xFF19, 0xBF);  // NR24
    memory.write(0xFF1A, 0x7F);  // NR30
    memory.write(0xFF1B, 0xFF);  // NR31
    memory.write(0xFF1C, 0x9F);  // NR32
    memory.write(0xFF1E, 0xBF);  // NR33
    memory.write(0xFF20, 0xFF);  // NR41
    memory.write(0xFF21, 0x00);  // NR42
    memory.write(0xFF22, 0x00);  // NR43
    memory.write(0xFF23, 0xBF);  // NR30
    memory.write(0xFF24, 0x77);  // NR50
    memory.write(0xFF25, 0xF3);  // NR51
    memory.write(0xFF26, 0xF1);  // NR52
    memory.write(0xFF40, 0x91);  // LCDC
    memory.write(0xFF42, 0x00);  // SCY
    memory.write(0xFF43, 0x00);  // SCX
    memory.write(0xFF45, 0x00);  // LYC
    memory.write(0xFF47, 0xFC);  // BGP
    memory.write(0xFF48, 0xFF);  // OBP0
    memory.write(0xFF49, 0xFF);  // OBP1
    memory.write(0xFF4A, 0x00);  // WY
    memory.write(0xFF4B, 0x00);  // WX
    memory.write(0xFF0F, 0x00);  // IF
    memory.write(0xFFFF, 0x00);  // IE
}