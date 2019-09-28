#pragma once
#ifndef ARITMETIC_H
#define ARITMETIC_H

#include "../../hardware/memory/register.h"
class Cpu;

class Inc
{
    public:
        static void IncRegister(Cpu* cpu, Register<uint8_t>& reg);

        static uint8_t Inc03(Cpu* cpu);
        static uint8_t Inc04(Cpu* cpu);
        static uint8_t Inc0C(Cpu* cpu);
        static uint8_t Inc13(Cpu* cpu);
        static uint8_t Inc14(Cpu* cpu);
        static uint8_t Inc1C(Cpu* cpu);
        static uint8_t Inc23(Cpu* cpu);
        static uint8_t Inc24(Cpu* cpu);
        static uint8_t Inc2C(Cpu* cpu);
        static uint8_t Inc33(Cpu* cpu);
        static uint8_t Inc34(Cpu* cpu);
        static uint8_t Inc3C(Cpu* cpu);
};

class Dec
{
    public:
        static void DecRegister(Cpu* cpu, Register<uint8_t>& reg);

        static uint8_t Dec05(Cpu* cpu);
        static uint8_t Dec0B(Cpu* cpu);
        static uint8_t Dec0D(Cpu* cpu);
        static uint8_t Dec15(Cpu* cpu);
        static uint8_t Dec1B(Cpu* cpu);
        static uint8_t Dec1D(Cpu* cpu);
        static uint8_t Dec25(Cpu* cpu);
        static uint8_t Dec2B(Cpu* cpu);
        static uint8_t Dec2D(Cpu* cpu);
        static uint8_t Dec35(Cpu* cpu);
        static uint8_t Dec3B(Cpu* cpu);
        static uint8_t Dec3D(Cpu* cpu);
};

class Add
{
    public:
        static void AddToRegisterPair(Cpu* cpu, RegisterPair& storeIn, uint16_t value);
        static void AddToRegister(Cpu* cpu, Register<uint8_t>& storeIn, uint8_t value);

        static uint8_t Add09(Cpu* cpu);
        static uint8_t Add19(Cpu* cpu);
        static uint8_t Add29(Cpu* cpu);
        static uint8_t Add39(Cpu* cpu);
        static uint8_t Add80(Cpu* cpu);
        static uint8_t Add81(Cpu* cpu);
        static uint8_t Add82(Cpu* cpu);
        static uint8_t Add83(Cpu* cpu);
        static uint8_t Add84(Cpu* cpu);
        static uint8_t Add85(Cpu* cpu);
        static uint8_t Add86(Cpu* cpu);
        static uint8_t Add87(Cpu* cpu);
        static uint8_t AddC6(Cpu* cpu);
        static uint8_t AddE8(Cpu* cpu);
};

class Daa
{
    public:
        static uint8_t Daa27(Cpu* cpu);
};

class Cpl
{
    public:
        static uint8_t Cpl2F(Cpu* cpu);
};

class Scf
{
    public:
        static uint8_t Scf37(Cpu* cpu);
};

class Ccf
{
    public:
        static uint8_t Ccf3F(Cpu* cpu);
};

class Adc
{
    public:
        static void AdcToRegister(Cpu* cpu, Register<uint8_t>& storeIn, uint8_t value);

        static uint8_t Adc88(Cpu* cpu);
        static uint8_t Adc89(Cpu* cpu);
        static uint8_t Adc8A(Cpu* cpu);
        static uint8_t Adc8B(Cpu* cpu);
        static uint8_t Adc8C(Cpu* cpu);
        static uint8_t Adc8D(Cpu* cpu);
        static uint8_t Adc8E(Cpu* cpu);
        static uint8_t Adc8F(Cpu* cpu);
        static uint8_t AdcCE(Cpu* cpu);
};

class Sub
{
    public:
        static void SubToRegister(Cpu* cpu, Register<uint8_t>& storeIn, uint8_t value);

        static uint8_t Sub90(Cpu* cpu);
        static uint8_t Sub91(Cpu* cpu);
        static uint8_t Sub92(Cpu* cpu);
        static uint8_t Sub93(Cpu* cpu);
        static uint8_t Sub94(Cpu* cpu);
        static uint8_t Sub95(Cpu* cpu);
        static uint8_t Sub96(Cpu* cpu);
        static uint8_t Sub97(Cpu* cpu);
        static uint8_t SubD6(Cpu* cpu);
};

class Sbc
{
    public:
        static uint8_t Sbc98(Cpu* cpu);
        static uint8_t Sbc99(Cpu* cpu);
        static uint8_t Sbc9A(Cpu* cpu);
        static uint8_t Sbc9B(Cpu* cpu);
        static uint8_t Sbc9C(Cpu* cpu);
        static uint8_t Sbc9D(Cpu* cpu);
        static uint8_t Sbc9E(Cpu* cpu);
        static uint8_t Sbc9F(Cpu* cpu);
        static uint8_t SbcDE(Cpu* cpu);
};

class And
{
    public:
        static void AndAcc(Cpu* cpu, uint8_t value);

        static uint8_t AndA0(Cpu* cpu);
        static uint8_t AndA1(Cpu* cpu);
        static uint8_t AndA2(Cpu* cpu);
        static uint8_t AndA3(Cpu* cpu);
        static uint8_t AndA4(Cpu* cpu);
        static uint8_t AndA5(Cpu* cpu);
        static uint8_t AndA6(Cpu* cpu);
        static uint8_t AndA7(Cpu* cpu);
        static uint8_t AndE6(Cpu* cpu);
};

class Xor
{
    public:
        static void XorAcc(Cpu* cpu, uint8_t value);

        static uint8_t XorA8(Cpu* cpu);
        static uint8_t XorA9(Cpu* cpu);
        static uint8_t XorAA(Cpu* cpu);
        static uint8_t XorAB(Cpu* cpu);
        static uint8_t XorAC(Cpu* cpu);
        static uint8_t XorAD(Cpu* cpu);
        static uint8_t XorAE(Cpu* cpu);
        static uint8_t XorAF(Cpu* cpu);
        static uint8_t XorEE(Cpu* cpu);
};

class Or
{
    public:
        static void OrAcc(Cpu* cpu, uint8_t value);

        static uint8_t OrB0(Cpu* cpu);
        static uint8_t OrB1(Cpu* cpu);
        static uint8_t OrB2(Cpu* cpu);
        static uint8_t OrB3(Cpu* cpu);
        static uint8_t OrB4(Cpu* cpu);
        static uint8_t OrB5(Cpu* cpu);
        static uint8_t OrB6(Cpu* cpu);
        static uint8_t OrB7(Cpu* cpu);
        static uint8_t OrF6(Cpu* cpu);
};

class Cp
{
    public:
        static void CpAcc(Cpu* cpu, uint8_t value);

        static uint8_t CpB8(Cpu* cpu);
        static uint8_t CpB9(Cpu* cpu);
        static uint8_t CpBA(Cpu* cpu);
        static uint8_t CpBB(Cpu* cpu);
        static uint8_t CpBC(Cpu* cpu);
        static uint8_t CpBD(Cpu* cpu);
        static uint8_t CpBE(Cpu* cpu);
        static uint8_t CpBF(Cpu* cpu);
        static uint8_t CpFE(Cpu* cpu);
};

#endif // ARITMETIC_H