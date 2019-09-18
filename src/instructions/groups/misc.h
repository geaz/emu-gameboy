#pragma once
#ifndef MISC_H
#define MISC_H
class Cpu;

class Nop
{
    public:
        static uint8_t Nop00(Cpu* cpu);
};

class Rlca
{
    public:
        static uint8_t Rlca07(Cpu* cpu);
};

class Rrca
{
    public:
        static uint8_t Rrca0F(Cpu* cpu);
};

class Stop
{
    public:
        static uint8_t Stop10(Cpu* cpu);
};

class Rla
{
    public:
        static uint8_t Rla17(Cpu* cpu);
};

class Rra
{
    public:
        static uint8_t Rra1F(Cpu* cpu);
};

class Halt
{
    public:
        static uint8_t Halt76(Cpu* cpu);
};

class Di
{
    public:
        static uint8_t DiF3(Cpu* cpu);
};

class Ei
{
    public:
        static uint8_t EiFB(Cpu* cpu);
};

#endif // MISC_H