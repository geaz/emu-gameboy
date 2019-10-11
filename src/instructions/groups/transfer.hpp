#pragma once
#ifndef TRANSFER_H
#define TRANSFER_H

namespace GGB::Hardware { class Cpu; };
namespace GGB::Hardware::Instructions
{
    class Ld
    {
        public:
            static uint8_t Ld01(Cpu* cpu);
            static uint8_t Ld02(Cpu* cpu);
            static uint8_t Ld06(Cpu* cpu);
            static uint8_t Ld08(Cpu* cpu);
            static uint8_t Ld0A(Cpu* cpu);
            static uint8_t Ld0E(Cpu* cpu);
            static uint8_t Ld11(Cpu* cpu);
            static uint8_t Ld12(Cpu* cpu);
            static uint8_t Ld16(Cpu* cpu);
            static uint8_t Ld1A(Cpu* cpu);
            static uint8_t Ld1E(Cpu* cpu);
            static uint8_t Ld21(Cpu* cpu);
            static uint8_t Ld22(Cpu* cpu);
            static uint8_t Ld26(Cpu* cpu);
            static uint8_t Ld2A(Cpu* cpu);
            static uint8_t Ld2E(Cpu* cpu);
            static uint8_t Ld31(Cpu* cpu);
            static uint8_t Ld32(Cpu* cpu);
            static uint8_t Ld36(Cpu* cpu);
            static uint8_t Ld3A(Cpu* cpu);
            static uint8_t Ld3E(Cpu* cpu);
            static uint8_t Ld40(Cpu* cpu);
            static uint8_t Ld41(Cpu* cpu);
            static uint8_t Ld42(Cpu* cpu);
            static uint8_t Ld43(Cpu* cpu);
            static uint8_t Ld44(Cpu* cpu);
            static uint8_t Ld45(Cpu* cpu);
            static uint8_t Ld46(Cpu* cpu);
            static uint8_t Ld47(Cpu* cpu);
            static uint8_t Ld48(Cpu* cpu);
            static uint8_t Ld49(Cpu* cpu);
            static uint8_t Ld4A(Cpu* cpu);
            static uint8_t Ld4B(Cpu* cpu);
            static uint8_t Ld4C(Cpu* cpu);
            static uint8_t Ld4D(Cpu* cpu);
            static uint8_t Ld4E(Cpu* cpu);
            static uint8_t Ld4F(Cpu* cpu);
            static uint8_t Ld50(Cpu* cpu);
            static uint8_t Ld51(Cpu* cpu);
            static uint8_t Ld52(Cpu* cpu);
            static uint8_t Ld53(Cpu* cpu);
            static uint8_t Ld54(Cpu* cpu);
            static uint8_t Ld55(Cpu* cpu);
            static uint8_t Ld56(Cpu* cpu);
            static uint8_t Ld57(Cpu* cpu);
            static uint8_t Ld58(Cpu* cpu);
            static uint8_t Ld59(Cpu* cpu);
            static uint8_t Ld5A(Cpu* cpu);
            static uint8_t Ld5B(Cpu* cpu);
            static uint8_t Ld5C(Cpu* cpu);
            static uint8_t Ld5D(Cpu* cpu);
            static uint8_t Ld5E(Cpu* cpu);
            static uint8_t Ld5F(Cpu* cpu);
            static uint8_t Ld60(Cpu* cpu);
            static uint8_t Ld61(Cpu* cpu);
            static uint8_t Ld62(Cpu* cpu);
            static uint8_t Ld63(Cpu* cpu);
            static uint8_t Ld64(Cpu* cpu);
            static uint8_t Ld65(Cpu* cpu);
            static uint8_t Ld66(Cpu* cpu);
            static uint8_t Ld67(Cpu* cpu);
            static uint8_t Ld68(Cpu* cpu);
            static uint8_t Ld69(Cpu* cpu);
            static uint8_t Ld6A(Cpu* cpu);
            static uint8_t Ld6B(Cpu* cpu);
            static uint8_t Ld6C(Cpu* cpu);
            static uint8_t Ld6D(Cpu* cpu);
            static uint8_t Ld6E(Cpu* cpu);
            static uint8_t Ld6F(Cpu* cpu);
            static uint8_t Ld70(Cpu* cpu);
            static uint8_t Ld71(Cpu* cpu);
            static uint8_t Ld72(Cpu* cpu);
            static uint8_t Ld73(Cpu* cpu);
            static uint8_t Ld74(Cpu* cpu);
            static uint8_t Ld75(Cpu* cpu);
            static uint8_t Ld77(Cpu* cpu);
            static uint8_t Ld78(Cpu* cpu);
            static uint8_t Ld79(Cpu* cpu);
            static uint8_t Ld7A(Cpu* cpu);
            static uint8_t Ld7B(Cpu* cpu);
            static uint8_t Ld7C(Cpu* cpu);
            static uint8_t Ld7D(Cpu* cpu);
            static uint8_t Ld7E(Cpu* cpu);
            static uint8_t Ld7F(Cpu* cpu);
            static uint8_t LdE2(Cpu* cpu);
            static uint8_t LdEA(Cpu* cpu);
            static uint8_t LdF2(Cpu* cpu);
            static uint8_t LdF8(Cpu* cpu);
            static uint8_t LdF9(Cpu* cpu);
            static uint8_t LdFA(Cpu* cpu);
    };

    class Pop
    {
        public:
            static uint8_t PopC1(Cpu* cpu);
            static uint8_t PopD1(Cpu* cpu);
            static uint8_t PopE1(Cpu* cpu);
            static uint8_t PopF1(Cpu* cpu);
    };

    class Push
    {
        public:
            static uint8_t PushC5(Cpu* cpu);
            static uint8_t PushD5(Cpu* cpu);
            static uint8_t PushE5(Cpu* cpu);
            static uint8_t PushF5(Cpu* cpu);
    };

    class Ldh
    {
        public:
            static uint8_t LdhE0(Cpu* cpu);
            static uint8_t LdhF0(Cpu* cpu);
    };
}

#endif // TRANSFER_H