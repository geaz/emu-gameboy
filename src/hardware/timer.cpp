#include <chrono>
#include "timer.h"

Timer::Timer(Mmu& mmu) : mmu(mmu) { }

void Timer::cycle(uint8_t cycles)
{    
    dividerCycleCount += cycles;
    uint16_t dividerCycles = dividerCycleCount / (CPU_FREQUENCY / DIV_FREQUENCY);
    dividerCycleCount %= (CPU_FREQUENCY / DIV_FREQUENCY);

    mmu.rawWrite(REG_DIVIDER, (uint8_t) (mmu.read(REG_DIVIDER) + dividerCycles));

    if(mmu.readIORegisterBit(REG_TAC, TIMER_STOP))
    {
        timerCycleCount += cycles;
        uint32_t timerCycles = timerCycleCount / (CPU_FREQUENCY / getTimerFrequency());
        timerCycleCount %= (CPU_FREQUENCY / getTimerFrequency());

        uint32_t timerValue = mmu.readIORegister(REG_TIMA) + timerCycles;
        if(timerValue > 0xFF) 
        {
            mmu.write(REG_TIMA, mmu.readIORegister(REG_TMA));
            mmu.writeIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_TIMER, true);
        }
        else
        {
            mmu.write(REG_TIMA, timerValue);
        }   
    }        
}

uint32_t Timer::getTimerFrequency() const
{
    uint32_t frequency = 0;
    uint8_t regTac = mmu.readIORegister(REG_TAC);
    uint8_t setFrequency = (regTac & CLOCK_SELECT_HIGH) | (regTac & CLOCK_SELECT_LOW);
    switch(setFrequency)
    {
        case 0:
            frequency = 4096;
            break;
        case 1:
            frequency = 262144;
            break;
        case 2:
            frequency = 65536;
            break;
        case 3:
            frequency = 16384;
            break;
    }
    return frequency;
}