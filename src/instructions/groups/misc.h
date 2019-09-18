#pragma once
#ifndef MISC_H
#define MISC_H
class Cpu;

class Nop
{
    public:
        static unsigned char Nop00(Cpu* cpu);
};

class Rlca
{
    public:
        static unsigned char Rlca07(Cpu* cpu);
};

class Rrca
{
    public:
        static unsigned char Rrca0F(Cpu* cpu);
};

class Stop
{
    public:
        static unsigned char Stop10(Cpu* cpu);
};

class Rla
{
    public:
        static unsigned char Rla17(Cpu* cpu);
};

class Rra
{
    public:
        static unsigned char Rra1F(Cpu* cpu);
};

class Halt
{
    public:
        static unsigned char Halt76(Cpu* cpu);
};

class Di
{
    public:
        static unsigned char DiF3(Cpu* cpu);
};

class Ei
{
    public:
        static unsigned char EiFB(Cpu* cpu);
};

#endif // MISC_H