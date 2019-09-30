#include "cpu.h"
#include "../helper/string_helper.h"

Cpu::Cpu(Mmu& mmu) : mmu(mmu) 
{ 
    setPowerUpSequence();
    nextInstruction = parseNextInstruction();
}

uint8_t Cpu::cycle() 
{   
    if(handleInterrupts()) nextInstruction = parseNextInstruction();

    uint8_t opCycles = 0;
    if(!halted)
    {   
        currentInstruction = nextInstruction;
        pc += currentInstruction.definition.length;
        opCycles = currentInstruction.definition.executeInterpreter(this);
        nextInstruction = parseNextInstruction();
    }    

    if(state == STEP) state = PAUSED;
    return opCycles;
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
    mmu.write(sp.read() - 1, (value & 0xFF00) >> 8);
    mmu.write(sp.read() - 2, value & 0x00FF);
    sp -= 2;
}

uint16_t Cpu::popStack()
{
    uint16_t value = (mmu.read(sp.read() + 1) << 8) | mmu.read(sp.read());
    sp += 2;
    return value;
}

bool Cpu::handleInterrupts()
{
    bool handledInterrupt = false;
    uint16_t interruptVector = 0;
    uint8_t interruptFlag = 0;

    bool vBlankInterrupt = mmu.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_V_BLANK)
                         && mmu.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_V_BLANK);
    bool lcdInterrupt = mmu.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_LCD)
                      && mmu.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_LCD);
    bool timerInterrupt = mmu.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_TIMER)
                        && mmu.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_TIMER);
    bool serialInterrupt = mmu.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_SERIAL)
                         && mmu.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_SERIAL);
    bool joypadInterrupt = mmu.readIORegisterBit(REG_INTERRUPT_ENABLE, INTERRUPT_INPUT)
                         && mmu.readIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_INPUT);

    if(vBlankInterrupt)
    {
        interruptVector = VECTOR_V_BLANK;
        interruptFlag = INTERRUPT_V_BLANK;
        halted = false;
    } 
    else if(lcdInterrupt)
    {
        interruptVector = VECTOR_LCD;
        interruptFlag = INTERRUPT_LCD;
        halted = false;
    } 
    else if(timerInterrupt)
    {
        interruptVector = VECTOR_TIMER;
        interruptFlag = INTERRUPT_TIMER;
        halted = false;
    }
    else if(serialInterrupt)
    {
        interruptVector = VECTOR_SERIAL;
        interruptFlag = INTERRUPT_SERIAL;
        halted = false;
    }
    else if(joypadInterrupt)
    {
        interruptVector = VECTOR_INPUT;
        interruptFlag = INTERRUPT_INPUT;
        halted = false;
    }
    
    if(interruptVector != 0 && interruptMasterFlag)
    {
        interruptMasterFlag = false;
        mmu.writeIORegisterBit(REG_INTERRUPT_FLAG, interruptFlag, false);
        pushStack(pc.read());
        pc = interruptVector;
        handledInterrupt = true;
    }    
    return handledInterrupt;
}

ParsedInstruction Cpu::parseNextInstruction()
{
    // If the next Byte is 0xCB, then we look into the prefixSet
    // instead of the "normal" instruction set (Prefix Opcode)
    uint8_t nextByte = mmu.read(pc.read());

    ParsedInstruction nextInstruction;
    nextInstruction.bytePosition = pc.read();
    nextInstruction.parsedBytes.opcode = nextByte;
    
    if(nextByte != 0xCB)
    {
        nextInstruction.definition = instructionSet.set[nextByte];
        if(nextInstruction.definition.length >= 2) nextInstruction.parsedBytes.low = mmu.read(pc.read() + 1);
        if(nextInstruction.definition.length == 3)
        {
            nextInstruction.parsedBytes.high = mmu.read(pc.read() + 2);
            nextInstruction.parsedBytes.b16 = (nextInstruction.parsedBytes.high << 8) | nextInstruction.parsedBytes.low;
        }        
    }
    else
    {
        nextInstruction.definition = instructionSet.prefixSet[mmu.read(pc.read() + 1)];
        nextInstruction.parsedBytes.low = mmu.read(pc.read() + 1);
    }

    return nextInstruction;
}

void Cpu::setPowerUpSequence()
{
    mmu.write(0xFF00, 0xCF);  // Joypad 1100 1111 (No Buttons pressed)
    mmu.write(0xFF05, 0x0);   // TIMA
    mmu.write(0xFF06, 0x0);   // TMA
    mmu.write(0xFF07, 0x0);   // TAC
    mmu.write(0xFF10, 0x80);  // NR10
    mmu.write(0xFF11, 0xBF);  // NR11
    mmu.write(0xFF12, 0xF3);  // NR12
    mmu.write(0xFF14, 0xBF);  // NR14
    mmu.write(0xFF16, 0x3F);  // NR21
    mmu.write(0xFF17, 0x00);  // NR22
    mmu.write(0xFF19, 0xBF);  // NR24
    mmu.write(0xFF1A, 0x7F);  // NR30
    mmu.write(0xFF1B, 0xFF);  // NR31
    mmu.write(0xFF1C, 0x9F);  // NR32
    mmu.write(0xFF1E, 0xBF);  // NR33
    mmu.write(0xFF20, 0xFF);  // NR41
    mmu.write(0xFF21, 0x00);  // NR42
    mmu.write(0xFF22, 0x00);  // NR43
    mmu.write(0xFF23, 0xBF);  // NR30
    mmu.write(0xFF24, 0x77);  // NR50
    mmu.write(0xFF25, 0xF3);  // NR51
    mmu.write(0xFF26, 0xF1);  // NR52
    mmu.write(0xFF40, 0x91);  // LCDC
    mmu.write(0xFF42, 0x00);  // SCY
    mmu.write(0xFF43, 0x00);  // SCX
    mmu.write(0xFF44, 0x00);  // LY
    mmu.write(0xFF45, 0x00);  // LYC
    mmu.write(0xFF47, 0xFC);  // BGP
    mmu.write(0xFF48, 0xFF);  // OBP0
    mmu.write(0xFF49, 0xFF);  // OBP1
    mmu.write(0xFF4A, 0x00);  // WY
    mmu.write(0xFF4B, 0x00);  // WX
    mmu.write(0xFF0F, 0x00);  // IF
    mmu.write(0xFFFF, 0x00);  // IE
}