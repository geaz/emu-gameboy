#pragma once
#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
    public:
        Clock(long frequency);

        void Reset();
        long getCatchUpCycles();

        long frequency;

    private:
        long long getNowMs();

        long long lastCycle = -1;
};

#endif