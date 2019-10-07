#include "clock.h"

namespace GGB::Hardware
{
    Clock::Clock()
    {   
        startPoint = std::chrono::high_resolution_clock::now();     
    }

    void Clock::start()
    {
        startPoint = std::chrono::high_resolution_clock::now(); 
        started = true;
    }

    bool Clock::shouldSleep()
    {
        started = false;    
        auto now = std::chrono::high_resolution_clock::now();
        auto chronoOne = std::chrono::nanoseconds(Const::OneFrameDurationNSec);
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - startPoint);    
        auto shouldSleep = std::chrono::duration_cast<std::chrono::nanoseconds>(chronoOne - elapsed);

        return shouldSleep.count() > 0;
    }
}