#include <chrono>
#include "timer.h"
#include "cpu.h"
#include "memory/mmu.h"

namespace GGB::Hardware
{
    Timer::Timer(Mmu& mmu) : mmu(mmu) { }

    void Timer::cycle(uint8_t cycles)
    {    
        using Enums::IO_REGISTER, Enums::INTERRUPT_FLAG, Enums::TIMER_FLAG;        

        // Read internal clock from memory
        // The upper 8 bits of the interal clock are the Timer Divider
        // Because we add the cycles to the complete internal clock, we don't
        // have to handle the divider register serperatly. It will get incremented
        // at the correct rate, if we just increment the internal clock.
        uint16_t internalClock = (mmu.readIORegister(IO_REGISTER::REG_DIVIDER) << 8) 
            | mmu.readIORegister(IO_REGISTER::REG_INTERNAL_CLOCK_LOW);
        internalClock += cycles;

        // Write new value to internal clock
        mmu.rawWrite(IO_REGISTER::REG_DIVIDER, (internalClock & 0xFF00) >> 8);
        mmu.rawWrite(IO_REGISTER::REG_INTERNAL_CLOCK_LOW, internalClock & 0x00FF);

        handleTima(cycles, internalClock);
    }

    /*
    * The TIMA increment can be get from the internal clock by, 
    * selecting the corresponding bit for each cycle. If this bit overflows
    * the TIMA increments.
    * 
    * For more information see: The Cycle-Accurate Game Boy Docs (Timer Chapter)
    */
    void Timer::handleTima(uint8_t cycles, uint16_t internalClock)
    {
        using Enums::IO_REGISTER, Enums::INTERRUPT_FLAG, Enums::TIMER_FLAG;

        // Reset the timer, if the frequency changed
        uint32_t currentFrequency = getTimerFrequency();
        if(oldFrequency != currentFrequency)
        {
            mmu.write(IO_REGISTER::REG_TIMA, 0);
            oldFrequency = currentFrequency;
        }

        if(mmu.readIORegisterBit(IO_REGISTER::REG_TAC, TIMER_FLAG::TIMER_START))
        {
            uint16_t previousClock = internalClock - cycles;
            uint16_t bitToSelect = Constants::CPU_CYCLES / currentFrequency;
            bool previousPulse = previousClock & bitToSelect;

            for(int clock = previousClock + 1; clock <= internalClock; clock++)
            {
                // Handle pending overflows, triggered by previous loops
                handleOverflow();
                bool currentPulse = clock & bitToSelect;
                if(currentPulse != previousPulse)
                {                    
                    previousPulse = currentPulse;
                    uint8_t timerValue = mmu.readIORegister(IO_REGISTER::REG_TIMA) + 1;
                    pendingOverflow = timerValue == 0x00;
                    mmu.write(IO_REGISTER::REG_TIMA, timerValue);          
                }
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

    void Timer::handleOverflow()
    {
        using Enums::IO_REGISTER, Enums::INTERRUPT_FLAG, Enums::TIMER_FLAG;
        if(pendingOverflow)
        {
            pendingOverflow = false;
            mmu.write(IO_REGISTER::REG_TIMA, mmu.readIORegister(IO_REGISTER::REG_TMA));
            mmu.writeIORegisterBit(IO_REGISTER::REG_INTERRUPT_FLAG, INTERRUPT_FLAG::TIMER, true);
        }
    }
}