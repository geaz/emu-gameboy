#pragma once
#ifndef CLOCK_H
#define CLOCK_H

 #include <cstdint>

class Clock
{
    public:
        Clock(uint32_t frequency);

        void Reset();
        uint32_t getCatchUpCycles();

        uint32_t frequency;

    private:
        uint64_t getNowMs();

        uint64_t lastCycle = -1;
};

#endif