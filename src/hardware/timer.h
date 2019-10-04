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
            void handleTima(uint8_t cycles, uint16_t internalClock);
            uint32_t getTimerFrequency() const;
            void handleOverflow();

            Mmu& mmu;
            uint32_t oldFrequency = 1024;
            bool lastVisiblePulse = false;
            bool pendingOverflow = false;
    };
}

#endif // TIMER_H