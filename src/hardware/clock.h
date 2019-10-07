#pragma once
#ifndef CLOCK_H
#define CLOCK_H

#include <cstdint>
#include <chrono>
#include "cpu.h"
#include "video/ppu.h"

namespace GGB::Hardware
{
    class Clock
    {
        public:
            Clock();

            void start();
            bool shouldSleep();

            bool started = false;

        private:         
            std::chrono::time_point<std::chrono::high_resolution_clock> startPoint;
    };
}

#endif