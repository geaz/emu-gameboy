#pragma once
#ifndef CPU_H
#define CPU_H

#include "memory/register.hpp"
#include "memory/mmu.hpp"
#include "../instructions/instruction_set.hpp"

namespace GGB
{
    namespace Hardware
    {
        class Cpu 
        {
            public:
                Cpu(Mmu& mmu);

                uint8_t cycle();

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

                Enum::CpuState state = Enum::CpuState::PAUSED;
                Instructions::ParsedInstruction nextInstruction;
                Instructions::ParsedInstruction currentInstruction;

                Mmu& mmu;
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