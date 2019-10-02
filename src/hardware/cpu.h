#pragma once
#ifndef CPU_H
#define CPU_H

#include "clock.h"
#include "memory/register.h"
#include "memory/mmu.h"
#include "../instructions/instruction_set.h"

namespace GGB
{
    namespace Enums
    {
        enum class CPU_STATE { STEP, PAUSED, RUNNING, INTERRUPT, ERROR };
        enum class CPU_FLAG { Z_ZERO = 7, N_SUBSTRACT = 6, H_HALFCARRY = 5, C_CARRY = 4 };  
    }

    namespace Hardware
    {
        class Cpu 
        {
            public:
                Cpu(Mmu& mmu);

                uint8_t cycle();

                bool getFlag(Enums::CPU_FLAG flag);
                void setFlag(Enums::CPU_FLAG flag, bool value);

                void pushStack(uint16_t value);
                uint16_t popStack();

                // Start Values taken from Pandocs - Power Up Sequence
                Register<uint16_t> pc = Register<uint16_t>(0x0100);
                Register<uint16_t> sp = Register<uint16_t>(0xFFFE);
                Register<uint8_t> a = Register<uint8_t>(0x01);
                Register<uint8_t> f = Register<uint8_t>(0xB0);
                Register<uint8_t> b = Register<uint8_t>(0x00);
                Register<uint8_t> c = Register<uint8_t>(0x13);
                Register<uint8_t> d = Register<uint8_t>(0x00);
                Register<uint8_t> e = Register<uint8_t>(0xD8);
                Register<uint8_t> h = Register<uint8_t>(0x01);
                Register<uint8_t> l = Register<uint8_t>(0x4D);

                RegisterPair af = RegisterPair(a, f);
                RegisterPair bc = RegisterPair(b, c);
                RegisterPair de = RegisterPair(d, e);
                RegisterPair hl = RegisterPair(h, l);

                Enums::CPU_STATE state = Enums::CPU_STATE::PAUSED;
                Instructions::ParsedInstruction nextInstruction;
                Instructions::ParsedInstruction currentInstruction;

                Mmu& mmu;
                Clock clock = Clock(4194304); // Hz
                bool interruptMasterFlag = false, halted = false;

            private:
                bool handleInterrupts();
                void setPowerUpSequence();
                Instructions::ParsedInstruction parseNextInstruction();
                void addToParsedInstructions(Instructions::ParsedInstruction parsedInstruction);

                Instructions::InstructionSet instructionSet;
        };
    }
}

#endif // CPU_H