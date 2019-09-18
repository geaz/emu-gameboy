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
        Register<uint16_t> pc = Register<uint16_t>("pc", 0x0100);
        Register<uint16_t> sp = Register<uint16_t>("sp", 0xFFFE);
        Register<uint8_t> a = Register<uint8_t>("a", 0x01);
        Register<uint8_t> f = Register<uint8_t>("f", 0xB0);
        Register<uint8_t> b = Register<uint8_t>("b", 0x00);
        Register<uint8_t> c = Register<uint8_t>("c", 0x13);
        Register<uint8_t> d = Register<uint8_t>("d", 0x00);
        Register<uint8_t> e = Register<uint8_t>("e", 0xD8);
        Register<uint8_t> h = Register<uint8_t>("h", 0x01);
        Register<uint8_t> l = Register<uint8_t>("l", 0x4D);

        Cartridge& cartridge;

        CpuState state = PAUSED;
        ParsedInstruction currentInstruction;
        ParsedInstruction nextInstruction;

    private:
        ParsedInstruction parseNextInstruction();

        InstructionSet instructionSet;
};

#endif // CPU_H