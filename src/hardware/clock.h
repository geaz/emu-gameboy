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

            // We take the VBlank to syncronize the clock
            // The gameboy refreshes the screen ~60 times per seconds (CPU_CYCLES/FRAME_CYCLES)
            // One Frame takes ~16.775.709‬ nano seconds
            const int64_t ONE_FRAME_DURATION_NSEC = 1000000000 / (GGB::Constants::CPU_CYCLES / GGB::Constants::FRAME_CYCLES);
    };
}

#endif