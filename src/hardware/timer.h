#pragma once
#ifndef TIMER_H
#define TIMER_H

#include "memory/mmu.h"

namespace GGB::Hardware
{
    class Timer
    {
        public:
            Timer(Mmu& mmu);

            void cycle(uint8_t cycles);

        private:
            uint32_t getTimerFrequency() const;

            Mmu& mmu;

            uint32_t dividerCycleCount = 0, timerCycleCount = 0;

            const uint16_t DIV_CYCLES = 4194304 / 16384; // CPU FREQUENCE / DIV FREQUENCY
            const uint32_t CPU_FREQUENCY = 4194304;
    };
}

#endif // TIMER_H