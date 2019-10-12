#pragma once
#ifndef ENVELOPECOMPONENT_H
#define ENVELOPECOMPONENT_H

#include <cstdint>

namespace GGB::Hardware::Audio
{
    class EnvelopeComponent
    {
        public:
            void setEnvelope(uint8_t ticks, uint8_t startVolume, bool increasing) 
            { 
                envelopeTicks = ticks;
                envelopeVolume = startVolume;
                isEnvelopeIncreasing = increasing;

                elapsedTicks = 0;
            }

            void tick() 
            {
                // No envelope operation, if the the envelope ticks are zero
                if(envelopeTicks == 0) return;
                
                // We are waiting until the elapsed ticks are equal
                // to the evelope tick length. As soon as this happens
                // we increase/decrease the current volume and reset the tick counter
                elapsedTicks ++;
                elapsedTicks %= envelopeTicks;
                if(elapsedTicks == 0)
                {
                    if(!isEnvelopeIncreasing && envelopeVolume != 0)
                        envelopeVolume--;
                    else if(isEnvelopeIncreasing && envelopeVolume != 15)
                        envelopeVolume++;
                }
            }

            uint8_t getVolume() { return envelopeVolume; }

        private:
            uint8_t envelopeTicks = 0;
            uint8_t envelopeVolume = 0;
            bool isEnvelopeIncreasing = false;
            
            uint8_t elapsedTicks = 0;
    };
}

#endif // ENVELOPECOMPONENT_H