#include <chrono>
#include "timer.hpp"
#include "cpu.hpp"
#include "memory/mmu.hpp"

namespace GGB::Hardware
{
    Timer::Timer(Mmu& mmu) : mmu(mmu) { }

    void Timer::cycle(uint8_t cycles)
    {    
        // Read internal clock from memory
        // The upper 8 bits of the interal clock are the Timer Divider
        // Because we add the cycles to the complete internal clock, we don't
        // have to handle the divider register serperatly. It will get incremented
        // at the correct rate, if we just increment the internal clock.
        uint16_t internalClock = (mmu.read(Const::AddrRegDivider) << 8) 
            | mmu.read(Const::AddrRegInternalClockLow);
        internalClock += cycles;

        // Write new value to internal clock
        mmu.rawWrite(Const::AddrRegDivider, (internalClock & 0xFF00) >> 8);
        mmu.rawWrite(Const::AddrRegInternalClockLow, internalClock & 0x00FF);

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
        if(!mmu.readIORegisterBit(Const::AddrRegTAC, Const::FlagTimerStart))
            timaStarted = false;
        else if(mmu.readIORegisterBit(Const::AddrRegTAC, Const::FlagTimerStart))
        {
            // If the timer just stared, we will save the clock count at start
            // This way we don't increment the timer to early, because the internal
            // clock may be not zero at this time.
            uint32_t previousClock = internalClock - cycles;
            if(!timaStarted)
            {
                timaStarted = true;
                timaStartClock = internalClock;
                // The timer just started in the processed t-cycles
                // So just handle the last t-cycle
                previousClock = internalClock - 1;
            }
                    
            uint16_t bitToSelect = (Const::CyclesCpu / getTimerFrequency()) >> 1;
            for(int clock = previousClock + 1; clock <= internalClock; clock++)
            {
                // Handle pending overflows, triggered by previous loops
                handleOverflow();
                bool currentPulse = clock & bitToSelect;
                if(lastVisiblePulse && !currentPulse)
                {                    
                    uint8_t timerValue = mmu.read(Const::AddrRegTIMA) + 1;
                    pendingOverflow = timerValue == 0x00;
                    mmu.write(Const::AddrRegTIMA, timerValue);          
                }
                lastVisiblePulse = currentPulse;
            }               
        }  
    }
    
    uint32_t Timer::getTimerFrequency() const
    {
        uint32_t frequency = 0;
        uint8_t regTac = mmu.read(Const::AddrRegTAC);
        uint8_t setFrequency = regTac & Const::FlagTimerClockMode;
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
        if(pendingOverflow)
        {
            pendingOverflow = false;
            mmu.write(Const::AddrRegTIMA, mmu.read(Const::AddrRegTMA));
            mmu.writeIORegisterBit(Const::AddrRegInterruptFlag, Const::FlagInterruptTimer, true);
        }
    }
}