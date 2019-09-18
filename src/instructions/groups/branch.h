#pragma once
#ifndef BRANCH_H
#define BRANCH_H
class Cpu;

class Jr
{
    public:
        static unsigned char Jr18(Cpu* cpu);
        static unsigned char Jr20(Cpu* cpu);
        static unsigned char Jr28(Cpu* cpu);
        static unsigned char Jr30(Cpu* cpu);
        static unsigned char Jr38(Cpu* cpu);
};

class Ret
{
    public:
        static unsigned char RetC0(Cpu* cpu);
        static unsigned char RetC8(Cpu* cpu);
        static unsigned char RetC9(Cpu* cpu);
        static unsigned char RetD0(Cpu* cpu);
        static unsigned char RetD8(Cpu* cpu);
};

class Jp
{
    public:
        static unsigned char JpC2(Cpu* cpu);
        static unsigned char JpC3(Cpu* cpu);
        static unsigned char JpCA(Cpu* cpu);
        static unsigned char JpD2(Cpu* cpu);
        static unsigned char JpDA(Cpu* cpu);
        static unsigned char JpE9(Cpu* cpu);
};

class Call
{
    public:
        static unsigned char CallC4(Cpu* cpu);
        static unsigned char CallCC(Cpu* cpu);
        static unsigned char CallCD(Cpu* cpu);
        static unsigned char CallD4(Cpu* cpu);
        static unsigned char CallDC(Cpu* cpu);
};

class Rst
{
    public:
        static unsigned char RstC7(Cpu* cpu);
        static unsigned char RstCF(Cpu* cpu);
        static unsigned char RstD7(Cpu* cpu);
        static unsigned char RstDF(Cpu* cpu);
        static unsigned char RstE7(Cpu* cpu);
        static unsigned char RstEF(Cpu* cpu);
        static unsigned char RstF7(Cpu* cpu);
        static unsigned char RstFF(Cpu* cpu);
};

class Reti
{
    public:
        static unsigned char RetiD9(Cpu* cpu);
};

#endif // BRANCH_H