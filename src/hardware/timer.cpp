#include <chrono>
#include "timer.h"

namespace GGB::Hardware
{
    Timer::Timer(Mmu& mmu) : mmu(mmu) { }

    void Timer::cycle(uint8_t cycles)
    {    
        using Enums::IO_REGISTER, Enums::INTERRUPT_FLAG, Enums::TIMER_FLAG;

        dividerCycleCount += cycles;
        if(dividerCycleCount > DIV_CYCLES)
        {
            mmu.rawWrite(IO_REGISTER::REG_DIVIDER, (uint8_t) (mmu.read(IO_REGISTER::REG_DIVIDER) + 1));
            dividerCycleCount -= DIV_CYCLES;
        }

        if(mmu.readIORegisterBit(IO_REGISTER::REG_TAC, TIMER_FLAG::TIMER_STOP))
        {
            timerCycleCount += cycles;
            uint32_t timerCycles = timerCycleCount / (CPU_FREQUENCY / getTimerFrequency());
            timerCycleCount %= (CPU_FREQUENCY / getTimerFrequency());

            uint32_t timerValue = mmu.readIORegister(IO_REGISTER::REG_TIMA) + timerCycles;
            if(timerValue > 0xFF) 
            {
                mmu.write(IO_REGISTER::REG_TIMA, mmu.readIORegister(IO_REGISTER::REG_TMA));
                mmu.writeIORegisterBit(IO_REGISTER::REG_INTERRUPT_FLAG, INTERRUPT_FLAG::TIMER, true);
            }
            else
            {
                mmu.write(IO_REGISTER::REG_TIMA, timerValue);
            }   
        }        
    }

    uint32_t Timer::getTimerFrequency() const
    {
        uint32_t frequency = 0;
        uint8_t regTac = mmu.readIORegister(Enums::IO_REGISTER::REG_TAC);
        uint8_t setFrequency = (regTac & Enums::TIMER_FLAG::CLOCK_SELECT_HIGH) | (regTac & Enums::TIMER_FLAG::CLOCK_SELECT_LOW);
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
}