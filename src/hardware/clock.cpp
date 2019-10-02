#include <chrono>
#include "clock.h"

Clock::Clock(uint32_t frequency) : frequency(frequency) { }

uint32_t Clock::getCatchUpCycles() 
{
    if(lastCycle == -1) lastCycle = getNowMs();
    uint64_t nowMs = getNowMs();
    uint32_t cycles = (uint32_t) (nowMs - lastCycle) * frequency / 1000;
    
    lastCycle = nowMs;
    return cycles;
}

uint64_t Clock::getNowMs()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
}