#include <chrono>
#include "clock.h"

Clock::Clock(long frequency) : frequency(frequency) { }

void Clock::Reset() { lastCycle = getNowMs(); }

long Clock::getCatchUpCycles() 
{
    long long nowMs = getNowMs();
    long cycles = (int) (nowMs - lastCycle) * frequency / 1000;
    return cycles;
}

long long Clock::getNowMs()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
}