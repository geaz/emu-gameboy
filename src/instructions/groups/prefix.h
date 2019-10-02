#pragma once
#ifndef PREFIX_H
#define PREFIX_H

#include "../../hardware/memory/register.h"

namespace GGB::Hardware { class Cpu; };
namespace GGB::Hardware::Instructions
{
    class Rlc
    {
        public:
            static uint8_t RotateLeftAndSetFlags(Cpu* cpu, uint8_t value);

            static uint8_t Rlc00(Cpu* cpu);
            static uint8_t Rlc01(Cpu* cpu);
            static uint8_t Rlc02(Cpu* cpu);
            static uint8_t Rlc03(Cpu* cpu);
            static uint8_t Rlc04(Cpu* cpu);
            static uint8_t Rlc05(Cpu* cpu);
            static uint8_t Rlc06(Cpu* cpu);
            static uint8_t Rlc07(Cpu* cpu);
    };

    class Rrc
    {
        public:
            static uint8_t RotateRightAndSetFlags(Cpu* cpu, uint8_t value);

            static uint8_t Rrc08(Cpu* cpu);
            static uint8_t Rrc09(Cpu* cpu);
            static uint8_t Rrc0A(Cpu* cpu);
            static uint8_t Rrc0B(Cpu* cpu);
            static uint8_t Rrc0C(Cpu* cpu);
            static uint8_t Rrc0D(Cpu* cpu);
            static uint8_t Rrc0E(Cpu* cpu);
            static uint8_t Rrc0F(Cpu* cpu);
    };

    class Rl
    {
        public:
            static uint8_t RotateLeftThroughCarryAndSetFlags(Cpu* cpu, uint8_t value);

            static uint8_t Rl10(Cpu* cpu);
            static uint8_t Rl11(Cpu* cpu);
            static uint8_t Rl12(Cpu* cpu);
            static uint8_t Rl13(Cpu* cpu);
            static uint8_t Rl14(Cpu* cpu);
            static uint8_t Rl15(Cpu* cpu);
            static uint8_t Rl16(Cpu* cpu);
            static uint8_t Rl17(Cpu* cpu);
    };

    class Rr
    {
        public:
            static uint8_t RotateRightThroughCarryAndSetFlags(Cpu* cpu, uint8_t value);

            static uint8_t Rr18(Cpu* cpu);
            static uint8_t Rr19(Cpu* cpu);
            static uint8_t Rr1A(Cpu* cpu);
            static uint8_t Rr1B(Cpu* cpu);
            static uint8_t Rr1C(Cpu* cpu);
            static uint8_t Rr1D(Cpu* cpu);
            static uint8_t Rr1E(Cpu* cpu);
            static uint8_t Rr1F(Cpu* cpu);
    };

    class Sla
    {
        public:
            static uint8_t ShiftLeftAndSetFlags(Cpu* cpu, uint8_t value);

            static uint8_t Sla20(Cpu* cpu);
            static uint8_t Sla21(Cpu* cpu);
            static uint8_t Sla22(Cpu* cpu);
            static uint8_t Sla23(Cpu* cpu);
            static uint8_t Sla24(Cpu* cpu);
            static uint8_t Sla25(Cpu* cpu);
            static uint8_t Sla26(Cpu* cpu);
            static uint8_t Sla27(Cpu* cpu);
    };

    class Sra
    {
        public:
            static uint8_t ShiftRightAritmeticalAndSetFlags(Cpu* cpu, uint8_t value);

            static uint8_t Sra28(Cpu* cpu);
            static uint8_t Sra29(Cpu* cpu);
            static uint8_t Sra2A(Cpu* cpu);
            static uint8_t Sra2B(Cpu* cpu);
            static uint8_t Sra2C(Cpu* cpu);
            static uint8_t Sra2D(Cpu* cpu);
            static uint8_t Sra2E(Cpu* cpu);
            static uint8_t Sra2F(Cpu* cpu);
    };

    class Swap
    {
        public:
            static void SwapRegister(Cpu* cpu, Register<uint8_t>& reg);

            static uint8_t Swap30(Cpu* cpu);
            static uint8_t Swap31(Cpu* cpu);
            static uint8_t Swap32(Cpu* cpu);
            static uint8_t Swap33(Cpu* cpu);
            static uint8_t Swap34(Cpu* cpu);
            static uint8_t Swap35(Cpu* cpu);
            static uint8_t Swap36(Cpu* cpu);
            static uint8_t Swap37(Cpu* cpu);
    };

    class Srl
    {
        public:
            static uint8_t ShiftRightAndSetFlags(Cpu* cpu, uint8_t value);

            static uint8_t Srl38(Cpu* cpu);
            static uint8_t Srl39(Cpu* cpu);
            static uint8_t Srl3A(Cpu* cpu);
            static uint8_t Srl3B(Cpu* cpu);
            static uint8_t Srl3C(Cpu* cpu);
            static uint8_t Srl3D(Cpu* cpu);
            static uint8_t Srl3E(Cpu* cpu);
            static uint8_t Srl3F(Cpu* cpu);
    };

    class Bit
    {
        public:
            static void BitCheckAndSetFlags(Cpu* cpu, uint8_t bit, uint8_t value);

            static uint8_t Bit40(Cpu* cpu);
            static uint8_t Bit41(Cpu* cpu);
            static uint8_t Bit42(Cpu* cpu);
            static uint8_t Bit43(Cpu* cpu);
            static uint8_t Bit44(Cpu* cpu);
            static uint8_t Bit45(Cpu* cpu);
            static uint8_t Bit46(Cpu* cpu);
            static uint8_t Bit47(Cpu* cpu);
            static uint8_t Bit48(Cpu* cpu);
            static uint8_t Bit49(Cpu* cpu);
            static uint8_t Bit4A(Cpu* cpu);
            static uint8_t Bit4B(Cpu* cpu);
            static uint8_t Bit4C(Cpu* cpu);
            static uint8_t Bit4D(Cpu* cpu);
            static uint8_t Bit4E(Cpu* cpu);
            static uint8_t Bit4F(Cpu* cpu);
            static uint8_t Bit50(Cpu* cpu);
            static uint8_t Bit51(Cpu* cpu);
            static uint8_t Bit52(Cpu* cpu);
            static uint8_t Bit53(Cpu* cpu);
            static uint8_t Bit54(Cpu* cpu);
            static uint8_t Bit55(Cpu* cpu);
            static uint8_t Bit56(Cpu* cpu);
            static uint8_t Bit57(Cpu* cpu);
            static uint8_t Bit58(Cpu* cpu);
            static uint8_t Bit59(Cpu* cpu);
            static uint8_t Bit5A(Cpu* cpu);
            static uint8_t Bit5B(Cpu* cpu);
            static uint8_t Bit5C(Cpu* cpu);
            static uint8_t Bit5D(Cpu* cpu);
            static uint8_t Bit5E(Cpu* cpu);
            static uint8_t Bit5F(Cpu* cpu);
            static uint8_t Bit60(Cpu* cpu);
            static uint8_t Bit61(Cpu* cpu);
            static uint8_t Bit62(Cpu* cpu);
            static uint8_t Bit63(Cpu* cpu);
            static uint8_t Bit64(Cpu* cpu);
            static uint8_t Bit65(Cpu* cpu);
            static uint8_t Bit66(Cpu* cpu);
            static uint8_t Bit67(Cpu* cpu);
            static uint8_t Bit68(Cpu* cpu);
            static uint8_t Bit69(Cpu* cpu);
            static uint8_t Bit6A(Cpu* cpu);
            static uint8_t Bit6B(Cpu* cpu);
            static uint8_t Bit6C(Cpu* cpu);
            static uint8_t Bit6D(Cpu* cpu);
            static uint8_t Bit6E(Cpu* cpu);
            static uint8_t Bit6F(Cpu* cpu);
            static uint8_t Bit70(Cpu* cpu);
            static uint8_t Bit71(Cpu* cpu);
            static uint8_t Bit72(Cpu* cpu);
            static uint8_t Bit73(Cpu* cpu);
            static uint8_t Bit74(Cpu* cpu);
            static uint8_t Bit75(Cpu* cpu);
            static uint8_t Bit76(Cpu* cpu);
            static uint8_t Bit77(Cpu* cpu);
            static uint8_t Bit78(Cpu* cpu);
            static uint8_t Bit79(Cpu* cpu);
            static uint8_t Bit7A(Cpu* cpu);
            static uint8_t Bit7B(Cpu* cpu);
            static uint8_t Bit7C(Cpu* cpu);
            static uint8_t Bit7D(Cpu* cpu);
            static uint8_t Bit7E(Cpu* cpu);
            static uint8_t Bit7F(Cpu* cpu);
    };

    class Res
    {
        public:
            static void ResRegisterBit(Register<uint8_t>& reg, uint8_t bitNr);
            static void ResAddressBit(Cpu* cpu, uint16_t address, uint8_t bitNr);

            static uint8_t Res80(Cpu* cpu);
            static uint8_t Res81(Cpu* cpu);
            static uint8_t Res82(Cpu* cpu);
            static uint8_t Res83(Cpu* cpu);
            static uint8_t Res84(Cpu* cpu);
            static uint8_t Res85(Cpu* cpu);
            static uint8_t Res86(Cpu* cpu);
            static uint8_t Res87(Cpu* cpu);
            static uint8_t Res88(Cpu* cpu);
            static uint8_t Res89(Cpu* cpu);
            static uint8_t Res8A(Cpu* cpu);
            static uint8_t Res8B(Cpu* cpu);
            static uint8_t Res8C(Cpu* cpu);
            static uint8_t Res8D(Cpu* cpu);
            static uint8_t Res8E(Cpu* cpu);
            static uint8_t Res8F(Cpu* cpu);
            static uint8_t Res90(Cpu* cpu);
            static uint8_t Res91(Cpu* cpu);
            static uint8_t Res92(Cpu* cpu);
            static uint8_t Res93(Cpu* cpu);
            static uint8_t Res94(Cpu* cpu);
            static uint8_t Res95(Cpu* cpu);
            static uint8_t Res96(Cpu* cpu);
            static uint8_t Res97(Cpu* cpu);
            static uint8_t Res98(Cpu* cpu);
            static uint8_t Res99(Cpu* cpu);
            static uint8_t Res9A(Cpu* cpu);
            static uint8_t Res9B(Cpu* cpu);
            static uint8_t Res9C(Cpu* cpu);
            static uint8_t Res9D(Cpu* cpu);
            static uint8_t Res9E(Cpu* cpu);
            static uint8_t Res9F(Cpu* cpu);
            static uint8_t ResA0(Cpu* cpu);
            static uint8_t ResA1(Cpu* cpu);
            static uint8_t ResA2(Cpu* cpu);
            static uint8_t ResA3(Cpu* cpu);
            static uint8_t ResA4(Cpu* cpu);
            static uint8_t ResA5(Cpu* cpu);
            static uint8_t ResA6(Cpu* cpu);
            static uint8_t ResA7(Cpu* cpu);
            static uint8_t ResA8(Cpu* cpu);
            static uint8_t ResA9(Cpu* cpu);
            static uint8_t ResAA(Cpu* cpu);
            static uint8_t ResAB(Cpu* cpu);
            static uint8_t ResAC(Cpu* cpu);
            static uint8_t ResAD(Cpu* cpu);
            static uint8_t ResAE(Cpu* cpu);
            static uint8_t ResAF(Cpu* cpu);
            static uint8_t ResB0(Cpu* cpu);
            static uint8_t ResB1(Cpu* cpu);
            static uint8_t ResB2(Cpu* cpu);
            static uint8_t ResB3(Cpu* cpu);
            static uint8_t ResB4(Cpu* cpu);
            static uint8_t ResB5(Cpu* cpu);
            static uint8_t ResB6(Cpu* cpu);
            static uint8_t ResB7(Cpu* cpu);
            static uint8_t ResB8(Cpu* cpu);
            static uint8_t ResB9(Cpu* cpu);
            static uint8_t ResBA(Cpu* cpu);
            static uint8_t ResBB(Cpu* cpu);
            static uint8_t ResBC(Cpu* cpu);
            static uint8_t ResBD(Cpu* cpu);
            static uint8_t ResBE(Cpu* cpu);
            static uint8_t ResBF(Cpu* cpu);
    };

    class Set
    {
        public:
            static void SetRegisterBit(Register<uint8_t>& reg, uint8_t bitNr);
            static void SetAddressBit(Cpu* cpu, uint16_t address, uint8_t bitNr);

            static uint8_t SetC0(Cpu* cpu);
            static uint8_t SetC1(Cpu* cpu);
            static uint8_t SetC2(Cpu* cpu);
            static uint8_t SetC3(Cpu* cpu);
            static uint8_t SetC4(Cpu* cpu);
            static uint8_t SetC5(Cpu* cpu);
            static uint8_t SetC6(Cpu* cpu);
            static uint8_t SetC7(Cpu* cpu);
            static uint8_t SetC8(Cpu* cpu);
            static uint8_t SetC9(Cpu* cpu);
            static uint8_t SetCA(Cpu* cpu);
            static uint8_t SetCB(Cpu* cpu);
            static uint8_t SetCC(Cpu* cpu);
            static uint8_t SetCD(Cpu* cpu);
            static uint8_t SetCE(Cpu* cpu);
            static uint8_t SetCF(Cpu* cpu);
            static uint8_t SetD0(Cpu* cpu);
            static uint8_t SetD1(Cpu* cpu);
            static uint8_t SetD2(Cpu* cpu);
            static uint8_t SetD3(Cpu* cpu);
            static uint8_t SetD4(Cpu* cpu);
            static uint8_t SetD5(Cpu* cpu);
            static uint8_t SetD6(Cpu* cpu);
            static uint8_t SetD7(Cpu* cpu);
            static uint8_t SetD8(Cpu* cpu);
            static uint8_t SetD9(Cpu* cpu);
            static uint8_t SetDA(Cpu* cpu);
            static uint8_t SetDB(Cpu* cpu);
            static uint8_t SetDC(Cpu* cpu);
            static uint8_t SetDD(Cpu* cpu);
            static uint8_t SetDE(Cpu* cpu);
            static uint8_t SetDF(Cpu* cpu);
            static uint8_t SetE0(Cpu* cpu);
            static uint8_t SetE1(Cpu* cpu);
            static uint8_t SetE2(Cpu* cpu);
            static uint8_t SetE3(Cpu* cpu);
            static uint8_t SetE4(Cpu* cpu);
            static uint8_t SetE5(Cpu* cpu);
            static uint8_t SetE6(Cpu* cpu);
            static uint8_t SetE7(Cpu* cpu);
            static uint8_t SetE8(Cpu* cpu);
            static uint8_t SetE9(Cpu* cpu);
            static uint8_t SetEA(Cpu* cpu);
            static uint8_t SetEB(Cpu* cpu);
            static uint8_t SetEC(Cpu* cpu);
            static uint8_t SetED(Cpu* cpu);
            static uint8_t SetEE(Cpu* cpu);
            static uint8_t SetEF(Cpu* cpu);
            static uint8_t SetF0(Cpu* cpu);
            static uint8_t SetF1(Cpu* cpu);
            static uint8_t SetF2(Cpu* cpu);
            static uint8_t SetF3(Cpu* cpu);
            static uint8_t SetF4(Cpu* cpu);
            static uint8_t SetF5(Cpu* cpu);
            static uint8_t SetF6(Cpu* cpu);
            static uint8_t SetF7(Cpu* cpu);
            static uint8_t SetF8(Cpu* cpu);
            static uint8_t SetF9(Cpu* cpu);
            static uint8_t SetFA(Cpu* cpu);
            static uint8_t SetFB(Cpu* cpu);
            static uint8_t SetFC(Cpu* cpu);
            static uint8_t SetFD(Cpu* cpu);
            static uint8_t SetFE(Cpu* cpu);
            static uint8_t SetFF(Cpu* cpu);
    };
}

#endif // PREFIX_H