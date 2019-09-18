#pragma once
#ifndef TRANSFER_H
#define TRANSFER_H
class Cpu;

class Ld
{
    public:
        static unsigned char Ld01(Cpu* cpu);
        static unsigned char Ld02(Cpu* cpu);
        static unsigned char Ld06(Cpu* cpu);
        static unsigned char Ld08(Cpu* cpu);
        static unsigned char Ld0A(Cpu* cpu);
        static unsigned char Ld0E(Cpu* cpu);
        static unsigned char Ld11(Cpu* cpu);
        static unsigned char Ld12(Cpu* cpu);
        static unsigned char Ld16(Cpu* cpu);
        static unsigned char Ld1A(Cpu* cpu);
        static unsigned char Ld1E(Cpu* cpu);
        static unsigned char Ld21(Cpu* cpu);
        static unsigned char Ld22(Cpu* cpu);
        static unsigned char Ld26(Cpu* cpu);
        static unsigned char Ld2A(Cpu* cpu);
        static unsigned char Ld2E(Cpu* cpu);
        static unsigned char Ld31(Cpu* cpu);
        static unsigned char Ld32(Cpu* cpu);
        static unsigned char Ld36(Cpu* cpu);
        static unsigned char Ld3A(Cpu* cpu);
        static unsigned char Ld3E(Cpu* cpu);
        static unsigned char Ld40(Cpu* cpu);
        static unsigned char Ld41(Cpu* cpu);
        static unsigned char Ld42(Cpu* cpu);
        static unsigned char Ld43(Cpu* cpu);
        static unsigned char Ld44(Cpu* cpu);
        static unsigned char Ld45(Cpu* cpu);
        static unsigned char Ld46(Cpu* cpu);
        static unsigned char Ld47(Cpu* cpu);
        static unsigned char Ld48(Cpu* cpu);
        static unsigned char Ld49(Cpu* cpu);
        static unsigned char Ld4A(Cpu* cpu);
        static unsigned char Ld4B(Cpu* cpu);
        static unsigned char Ld4C(Cpu* cpu);
        static unsigned char Ld4D(Cpu* cpu);
        static unsigned char Ld4E(Cpu* cpu);
        static unsigned char Ld4F(Cpu* cpu);
        static unsigned char Ld50(Cpu* cpu);
        static unsigned char Ld51(Cpu* cpu);
        static unsigned char Ld52(Cpu* cpu);
        static unsigned char Ld53(Cpu* cpu);
        static unsigned char Ld54(Cpu* cpu);
        static unsigned char Ld55(Cpu* cpu);
        static unsigned char Ld56(Cpu* cpu);
        static unsigned char Ld57(Cpu* cpu);
        static unsigned char Ld58(Cpu* cpu);
        static unsigned char Ld59(Cpu* cpu);
        static unsigned char Ld5A(Cpu* cpu);
        static unsigned char Ld5B(Cpu* cpu);
        static unsigned char Ld5C(Cpu* cpu);
        static unsigned char Ld5D(Cpu* cpu);
        static unsigned char Ld5E(Cpu* cpu);
        static unsigned char Ld5F(Cpu* cpu);
        static unsigned char Ld60(Cpu* cpu);
        static unsigned char Ld61(Cpu* cpu);
        static unsigned char Ld62(Cpu* cpu);
        static unsigned char Ld63(Cpu* cpu);
        static unsigned char Ld64(Cpu* cpu);
        static unsigned char Ld65(Cpu* cpu);
        static unsigned char Ld66(Cpu* cpu);
        static unsigned char Ld67(Cpu* cpu);
        static unsigned char Ld68(Cpu* cpu);
        static unsigned char Ld69(Cpu* cpu);
        static unsigned char Ld6A(Cpu* cpu);
        static unsigned char Ld6B(Cpu* cpu);
        static unsigned char Ld6C(Cpu* cpu);
        static unsigned char Ld6D(Cpu* cpu);
        static unsigned char Ld6E(Cpu* cpu);
        static unsigned char Ld6F(Cpu* cpu);
        static unsigned char Ld70(Cpu* cpu);
        static unsigned char Ld71(Cpu* cpu);
        static unsigned char Ld72(Cpu* cpu);
        static unsigned char Ld73(Cpu* cpu);
        static unsigned char Ld74(Cpu* cpu);
        static unsigned char Ld75(Cpu* cpu);
        static unsigned char Ld77(Cpu* cpu);
        static unsigned char Ld78(Cpu* cpu);
        static unsigned char Ld79(Cpu* cpu);
        static unsigned char Ld7A(Cpu* cpu);
        static unsigned char Ld7B(Cpu* cpu);
        static unsigned char Ld7C(Cpu* cpu);
        static unsigned char Ld7D(Cpu* cpu);
        static unsigned char Ld7E(Cpu* cpu);
        static unsigned char Ld7F(Cpu* cpu);
        static unsigned char LdE2(Cpu* cpu);
        static unsigned char LdEA(Cpu* cpu);
        static unsigned char LdF2(Cpu* cpu);
        static unsigned char LdF8(Cpu* cpu);
        static unsigned char LdF9(Cpu* cpu);
        static unsigned char LdFA(Cpu* cpu);
};

class Pop
{
    public:
        static unsigned char PopC1(Cpu* cpu);
        static unsigned char PopD1(Cpu* cpu);
        static unsigned char PopE1(Cpu* cpu);
        static unsigned char PopF1(Cpu* cpu);
};

class Push
{
    public:
        static unsigned char PushC5(Cpu* cpu);
        static unsigned char PushD5(Cpu* cpu);
        static unsigned char PushE5(Cpu* cpu);
        static unsigned char PushF5(Cpu* cpu);
};

class Ldh
{
    public:
        static unsigned char LdhE0(Cpu* cpu);
        static unsigned char LdhF0(Cpu* cpu);
};

#endif // TRANSFER_H