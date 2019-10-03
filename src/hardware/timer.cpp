#include <chrono>
#include "timer.h"

namespace GGB::Hardware
{
    Timer::Timer(Mmu& mmu) : mmu(mmu) { }

    void Timer::cycle(uint8_t cycles)
    {    
        using Enums::IO_REGISTER, Enums::INTERRUPT_FLAG, Enums::TIMER_FLAG;

        uint8_t regDivider = mmu.read(IO_REGISTER::REG_DIVIDER);

        dividerCycleCount += cycles;
        if(dividerCycleCount >= DIV_CYCLES)
        {
            mmu.rawWrite(IO_REGISTER::REG_DIVIDER, (uint8_t) (regDivider + 1));
            dividerCycleCount -= DIV_CYCLES;
        }

        if(mmu.readIORegisterBit(IO_REGISTER::REG_TAC, TIMER_FLAG::TIMER_START))
        {
            timerCycleCount += cycles;
            uint32_t currentCyclesPerTick = CPU_FREQUENCY / getTimerFrequency();
            if(timerCycleCount >= currentCyclesPerTick)
            {
                uint32_t timerValue = mmu.readIORegister(IO_REGISTER::REG_TIMA) + 1;
                // Reset if, DIV got a reset
                if(oldRegDivider != 0xFF && regDivider == 0x00)
                {
                    mmu.write(IO_REGISTER::REG_TIMA, 0);
                }
                else if(timerValue > 0xFF) 
                {
                    mmu.write(IO_REGISTER::REG_TIMA, mmu.readIORegister(IO_REGISTER::REG_TMA));
                    mmu.writeIORegisterBit(IO_REGISTER::REG_INTERRUPT_FLAG, INTERRUPT_FLAG::TIMER, true);
                }
                else
                {
                    mmu.write(IO_REGISTER::REG_TIMA, timerValue);
                }   
                timerCycleCount -= currentCyclesPerTick;
            }                 
            oldRegDivider = regDivider;       
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