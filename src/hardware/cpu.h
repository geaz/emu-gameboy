#pragma once
#ifndef CPU_H
#define CPU_H

#include "../instructions/instruction_set.h"
#include "cartridge.h"
#include "register.h"

enum CpuState
{
    PAUSED,
    RUNNING,
    INTERRUPT,
    ERROR
};

class Cpu 
{
    public:
        Cpu(Cartridge& cartridge);

        void cycle();

        // Start Values taken from Pandocs - Power Up Sequence
        Register<short> pc = Register<short>("pc", 0x0100);
        Register<short> sp = Register<short>("sp", 0xFFFE);
        Register<unsigned char> a = Register<unsigned char>("a", 0x01);
        Register<unsigned char> f = Register<unsigned char>("f", 0xB0);
        Register<unsigned char> b = Register<unsigned char>("b", 0x00);
        Register<unsigned char> c = Register<unsigned char>("c", 0x13);
        Register<unsigned char> d = Register<unsigned char>("d", 0x00);
        Register<unsigned char> e = Register<unsigned char>("e", 0xD8);
        Register<unsigned char> h = Register<unsigned char>("h", 0x01);
        Register<unsigned char> l = Register<unsigned char>("l", 0x4D);

        Cartridge& cartridge;

        CpuState state = PAUSED;
        ParsedInstruction currentInstruction;
        ParsedInstruction nextInstruction;

    private:
        ParsedInstruction parseNextInstruction();

        InstructionSet instructionSet;
};

#endif // CPU_H