#pragma once
#ifndef BRANCH_H
#define BRANCH_H
class Cpu;

class Jr
{
    public:
        static uint8_t Jr18(Cpu* cpu);
        static uint8_t Jr20(Cpu* cpu);
        static uint8_t Jr28(Cpu* cpu);
        static uint8_t Jr30(Cpu* cpu);
        static uint8_t Jr38(Cpu* cpu);
};

class Ret
{
    public:
        static uint8_t RetC0(Cpu* cpu);
        static uint8_t RetC8(Cpu* cpu);
        static uint8_t RetC9(Cpu* cpu);
        static uint8_t RetD0(Cpu* cpu);
        static uint8_t RetD8(Cpu* cpu);
};

class Jp
{
    public:
        static uint8_t JpC2(Cpu* cpu);
        static uint8_t JpC3(Cpu* cpu);
        static uint8_t JpCA(Cpu* cpu);
        static uint8_t JpD2(Cpu* cpu);
        static uint8_t JpDA(Cpu* cpu);
        static uint8_t JpE9(Cpu* cpu);
};

class Call
{
    public:
        static uint8_t CallC4(Cpu* cpu);
        static uint8_t CallCC(Cpu* cpu);
        static uint8_t CallCD(Cpu* cpu);
        static uint8_t CallD4(Cpu* cpu);
        static uint8_t CallDC(Cpu* cpu);
};

class Rst
{
    public:
        static uint8_t RstC7(Cpu* cpu);
        static uint8_t RstCF(Cpu* cpu);
        static uint8_t RstD7(Cpu* cpu);
        static uint8_t RstDF(Cpu* cpu);
        static uint8_t RstE7(Cpu* cpu);
        static uint8_t RstEF(Cpu* cpu);
        static uint8_t RstF7(Cpu* cpu);
        static uint8_t RstFF(Cpu* cpu);
};

class Reti
{
    public:
        static uint8_t RetiD9(Cpu* cpu);
};

#endif // BRANCH_H