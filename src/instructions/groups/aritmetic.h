#pragma once
#ifndef ARITMETIC_H
#define ARITMETIC_H
class Cpu;

class Inc
{
    public:
        static unsigned char Inc03(Cpu* cpu);
        static unsigned char Inc04(Cpu* cpu);
        static unsigned char Inc0C(Cpu* cpu);
        static unsigned char Inc13(Cpu* cpu);
        static unsigned char Inc14(Cpu* cpu);
        static unsigned char Inc1C(Cpu* cpu);
        static unsigned char Inc23(Cpu* cpu);
        static unsigned char Inc24(Cpu* cpu);
        static unsigned char Inc2C(Cpu* cpu);
        static unsigned char Inc33(Cpu* cpu);
        static unsigned char Inc34(Cpu* cpu);
        static unsigned char Inc3C(Cpu* cpu);
};

class Dec
{
    public:
        static unsigned char Dec05(Cpu* cpu);
        static unsigned char Dec0B(Cpu* cpu);
        static unsigned char Dec0D(Cpu* cpu);
        static unsigned char Dec15(Cpu* cpu);
        static unsigned char Dec1B(Cpu* cpu);
        static unsigned char Dec1D(Cpu* cpu);
        static unsigned char Dec25(Cpu* cpu);
        static unsigned char Dec2B(Cpu* cpu);
        static unsigned char Dec2D(Cpu* cpu);
        static unsigned char Dec35(Cpu* cpu);
        static unsigned char Dec3B(Cpu* cpu);
        static unsigned char Dec3D(Cpu* cpu);
};

class Add
{
    public:
        static unsigned char Add09(Cpu* cpu);
        static unsigned char Add19(Cpu* cpu);
        static unsigned char Add29(Cpu* cpu);
        static unsigned char Add39(Cpu* cpu);
        static unsigned char Add80(Cpu* cpu);
        static unsigned char Add81(Cpu* cpu);
        static unsigned char Add82(Cpu* cpu);
        static unsigned char Add83(Cpu* cpu);
        static unsigned char Add84(Cpu* cpu);
        static unsigned char Add85(Cpu* cpu);
        static unsigned char Add86(Cpu* cpu);
        static unsigned char Add87(Cpu* cpu);
        static unsigned char AddC6(Cpu* cpu);
        static unsigned char AddE8(Cpu* cpu);
};

class Daa
{
    public:
        static unsigned char Daa27(Cpu* cpu);
};

class Cpl
{
    public:
        static unsigned char Cpl2F(Cpu* cpu);
};

class Scf
{
    public:
        static unsigned char Scf37(Cpu* cpu);
};

class Ccf
{
    public:
        static unsigned char Ccf3F(Cpu* cpu);
};

class Adc
{
    public:
        static unsigned char Adc88(Cpu* cpu);
        static unsigned char Adc89(Cpu* cpu);
        static unsigned char Adc8A(Cpu* cpu);
        static unsigned char Adc8B(Cpu* cpu);
        static unsigned char Adc8C(Cpu* cpu);
        static unsigned char Adc8D(Cpu* cpu);
        static unsigned char Adc8E(Cpu* cpu);
        static unsigned char Adc8F(Cpu* cpu);
        static unsigned char AdcCE(Cpu* cpu);
};

class Sub
{
    public:
        static unsigned char Sub90(Cpu* cpu);
        static unsigned char Sub91(Cpu* cpu);
        static unsigned char Sub92(Cpu* cpu);
        static unsigned char Sub93(Cpu* cpu);
        static unsigned char Sub94(Cpu* cpu);
        static unsigned char Sub95(Cpu* cpu);
        static unsigned char Sub96(Cpu* cpu);
        static unsigned char Sub97(Cpu* cpu);
        static unsigned char SubD6(Cpu* cpu);
};

class Sbc
{
    public:
        static unsigned char Sbc98(Cpu* cpu);
        static unsigned char Sbc99(Cpu* cpu);
        static unsigned char Sbc9A(Cpu* cpu);
        static unsigned char Sbc9B(Cpu* cpu);
        static unsigned char Sbc9C(Cpu* cpu);
        static unsigned char Sbc9D(Cpu* cpu);
        static unsigned char Sbc9E(Cpu* cpu);
        static unsigned char Sbc9F(Cpu* cpu);
        static unsigned char SbcDE(Cpu* cpu);
};

class And
{
    public:
        static unsigned char AndA0(Cpu* cpu);
        static unsigned char AndA1(Cpu* cpu);
        static unsigned char AndA2(Cpu* cpu);
        static unsigned char AndA3(Cpu* cpu);
        static unsigned char AndA4(Cpu* cpu);
        static unsigned char AndA5(Cpu* cpu);
        static unsigned char AndA6(Cpu* cpu);
        static unsigned char AndA7(Cpu* cpu);
        static unsigned char AndE6(Cpu* cpu);
};

class Xor
{
    public:
        static unsigned char XorA8(Cpu* cpu);
        static unsigned char XorA9(Cpu* cpu);
        static unsigned char XorAA(Cpu* cpu);
        static unsigned char XorAB(Cpu* cpu);
        static unsigned char XorAC(Cpu* cpu);
        static unsigned char XorAD(Cpu* cpu);
        static unsigned char XorAE(Cpu* cpu);
        static unsigned char XorAF(Cpu* cpu);
        static unsigned char XorEE(Cpu* cpu);
};

class Or
{
    public:
        static unsigned char OrB0(Cpu* cpu);
        static unsigned char OrB1(Cpu* cpu);
        static unsigned char OrB2(Cpu* cpu);
        static unsigned char OrB3(Cpu* cpu);
        static unsigned char OrB4(Cpu* cpu);
        static unsigned char OrB5(Cpu* cpu);
        static unsigned char OrB6(Cpu* cpu);
        static unsigned char OrB7(Cpu* cpu);
        static unsigned char OrF6(Cpu* cpu);
};

class Cp
{
    public:
        static unsigned char CpB8(Cpu* cpu);
        static unsigned char CpB9(Cpu* cpu);
        static unsigned char CpBA(Cpu* cpu);
        static unsigned char CpBB(Cpu* cpu);
        static unsigned char CpBC(Cpu* cpu);
        static unsigned char CpBD(Cpu* cpu);
        static unsigned char CpBE(Cpu* cpu);
        static unsigned char CpBF(Cpu* cpu);
        static unsigned char CpFE(Cpu* cpu);
};

#endif // ARITMETIC_H