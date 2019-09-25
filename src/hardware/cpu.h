#pragma once
#ifndef CPU_H
#define CPU_H

#include <deque>

#include "helper/clock.h"
#include "memory.h"
#include "register.h"
#include "../instructions/instruction_set.h"

enum CpuState
{
    STEP,
    PAUSED,
    RUNNING,
    INTERRUPT,
    ERROR
};

enum Flag
{
    Z_ZERO = 7,
    N_SUBSTRACT = 6,
    H_HALFCARRY = 5,
    C_CARRY =4
};

class Cpu 
{
    public:
        Cpu(Memory& memory);

        long cycle();

        bool getFlag(Flag flag);
        void setFlag(Flag flag, bool value);

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

        CpuState state = PAUSED;
        ParsedInstruction nextInstruction;
        ParsedInstruction currentInstruction;
        std::deque<ParsedInstruction> parsedInstructions;

        Memory& memory;
        char breakPoint[5] = "";
        Clock clock = Clock(4194304); // Hz
        bool interruptMasterFlag = false;

    private:
        void handleInterrupts();
        void setPowerUpSequence();
        ParsedInstruction parseNextInstruction();
        void addToParsedInstructions(ParsedInstruction parsedInstruction);

        InstructionSet instructionSet;
};

#endif // CPU_H