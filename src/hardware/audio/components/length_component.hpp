#pragma once
#ifndef LENGTHCOMPONENT_H
#define LENGTHCOMPONENT_H

#include <cstdint>

namespace GGB::Hardware::Audio
{
    class LengthComponent
    {
        public:
            void setLength(uint16_t value, bool stopAfterLength) 
            { 
                length = length == 0 ? value : length;
                lengthStop = stopAfterLength;
            }

            bool tick() 
            {
                length -= length != 0 ? 1 : 0;
                return !lengthStop || (length != 0 && lengthStop);
            }

        private:
            bool lengthStop = false;
            uint16_t length = 0;
    };
}

#endif // LENGTHCOMPONENT_H