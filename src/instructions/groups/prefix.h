#pragma once
#ifndef PREFIX_H
#define PREFIX_H
class Cpu;

class Rlc
{
    public:
        static unsigned char Rlc00(Cpu* cpu);
        static unsigned char Rlc01(Cpu* cpu);
        static unsigned char Rlc02(Cpu* cpu);
        static unsigned char Rlc03(Cpu* cpu);
        static unsigned char Rlc04(Cpu* cpu);
        static unsigned char Rlc05(Cpu* cpu);
        static unsigned char Rlc06(Cpu* cpu);
        static unsigned char Rlc07(Cpu* cpu);
};

class Rrc
{
    public:
        static unsigned char Rrc08(Cpu* cpu);
        static unsigned char Rrc09(Cpu* cpu);
        static unsigned char Rrc0A(Cpu* cpu);
        static unsigned char Rrc0B(Cpu* cpu);
        static unsigned char Rrc0C(Cpu* cpu);
        static unsigned char Rrc0D(Cpu* cpu);
        static unsigned char Rrc0E(Cpu* cpu);
        static unsigned char Rrc0F(Cpu* cpu);
};

class Rl
{
    public:
        static unsigned char Rl10(Cpu* cpu);
        static unsigned char Rl11(Cpu* cpu);
        static unsigned char Rl12(Cpu* cpu);
        static unsigned char Rl13(Cpu* cpu);
        static unsigned char Rl14(Cpu* cpu);
        static unsigned char Rl15(Cpu* cpu);
        static unsigned char Rl16(Cpu* cpu);
        static unsigned char Rl17(Cpu* cpu);
};

class Rr
{
    public:
        static unsigned char Rr18(Cpu* cpu);
        static unsigned char Rr19(Cpu* cpu);
        static unsigned char Rr1A(Cpu* cpu);
        static unsigned char Rr1B(Cpu* cpu);
        static unsigned char Rr1C(Cpu* cpu);
        static unsigned char Rr1D(Cpu* cpu);
        static unsigned char Rr1E(Cpu* cpu);
        static unsigned char Rr1F(Cpu* cpu);
};

class Sla
{
    public:
        static unsigned char Sla20(Cpu* cpu);
        static unsigned char Sla21(Cpu* cpu);
        static unsigned char Sla22(Cpu* cpu);
        static unsigned char Sla23(Cpu* cpu);
        static unsigned char Sla24(Cpu* cpu);
        static unsigned char Sla25(Cpu* cpu);
        static unsigned char Sla26(Cpu* cpu);
        static unsigned char Sla27(Cpu* cpu);
};

class Sra
{
    public:
        static unsigned char Sra28(Cpu* cpu);
        static unsigned char Sra29(Cpu* cpu);
        static unsigned char Sra2A(Cpu* cpu);
        static unsigned char Sra2B(Cpu* cpu);
        static unsigned char Sra2C(Cpu* cpu);
        static unsigned char Sra2D(Cpu* cpu);
        static unsigned char Sra2E(Cpu* cpu);
        static unsigned char Sra2F(Cpu* cpu);
};

class Swap
{
    public:
        static unsigned char Swap30(Cpu* cpu);
        static unsigned char Swap31(Cpu* cpu);
        static unsigned char Swap32(Cpu* cpu);
        static unsigned char Swap33(Cpu* cpu);
        static unsigned char Swap34(Cpu* cpu);
        static unsigned char Swap35(Cpu* cpu);
        static unsigned char Swap36(Cpu* cpu);
        static unsigned char Swap37(Cpu* cpu);
};

class Srl
{
    public:
        static unsigned char Srl38(Cpu* cpu);
        static unsigned char Srl39(Cpu* cpu);
        static unsigned char Srl3A(Cpu* cpu);
        static unsigned char Srl3B(Cpu* cpu);
        static unsigned char Srl3C(Cpu* cpu);
        static unsigned char Srl3D(Cpu* cpu);
        static unsigned char Srl3E(Cpu* cpu);
        static unsigned char Srl3F(Cpu* cpu);
};

class Bit
{
    public:
        static unsigned char Bit40(Cpu* cpu);
        static unsigned char Bit41(Cpu* cpu);
        static unsigned char Bit42(Cpu* cpu);
        static unsigned char Bit43(Cpu* cpu);
        static unsigned char Bit44(Cpu* cpu);
        static unsigned char Bit45(Cpu* cpu);
        static unsigned char Bit46(Cpu* cpu);
        static unsigned char Bit47(Cpu* cpu);
        static unsigned char Bit48(Cpu* cpu);
        static unsigned char Bit49(Cpu* cpu);
        static unsigned char Bit4A(Cpu* cpu);
        static unsigned char Bit4B(Cpu* cpu);
        static unsigned char Bit4C(Cpu* cpu);
        static unsigned char Bit4D(Cpu* cpu);
        static unsigned char Bit4E(Cpu* cpu);
        static unsigned char Bit4F(Cpu* cpu);
        static unsigned char Bit50(Cpu* cpu);
        static unsigned char Bit51(Cpu* cpu);
        static unsigned char Bit52(Cpu* cpu);
        static unsigned char Bit53(Cpu* cpu);
        static unsigned char Bit54(Cpu* cpu);
        static unsigned char Bit55(Cpu* cpu);
        static unsigned char Bit56(Cpu* cpu);
        static unsigned char Bit57(Cpu* cpu);
        static unsigned char Bit58(Cpu* cpu);
        static unsigned char Bit59(Cpu* cpu);
        static unsigned char Bit5A(Cpu* cpu);
        static unsigned char Bit5B(Cpu* cpu);
        static unsigned char Bit5C(Cpu* cpu);
        static unsigned char Bit5D(Cpu* cpu);
        static unsigned char Bit5E(Cpu* cpu);
        static unsigned char Bit5F(Cpu* cpu);
        static unsigned char Bit60(Cpu* cpu);
        static unsigned char Bit61(Cpu* cpu);
        static unsigned char Bit62(Cpu* cpu);
        static unsigned char Bit63(Cpu* cpu);
        static unsigned char Bit64(Cpu* cpu);
        static unsigned char Bit65(Cpu* cpu);
        static unsigned char Bit66(Cpu* cpu);
        static unsigned char Bit67(Cpu* cpu);
        static unsigned char Bit68(Cpu* cpu);
        static unsigned char Bit69(Cpu* cpu);
        static unsigned char Bit6A(Cpu* cpu);
        static unsigned char Bit6B(Cpu* cpu);
        static unsigned char Bit6C(Cpu* cpu);
        static unsigned char Bit6D(Cpu* cpu);
        static unsigned char Bit6E(Cpu* cpu);
        static unsigned char Bit6F(Cpu* cpu);
        static unsigned char Bit70(Cpu* cpu);
        static unsigned char Bit71(Cpu* cpu);
        static unsigned char Bit72(Cpu* cpu);
        static unsigned char Bit73(Cpu* cpu);
        static unsigned char Bit74(Cpu* cpu);
        static unsigned char Bit75(Cpu* cpu);
        static unsigned char Bit76(Cpu* cpu);
        static unsigned char Bit77(Cpu* cpu);
        static unsigned char Bit78(Cpu* cpu);
        static unsigned char Bit79(Cpu* cpu);
        static unsigned char Bit7A(Cpu* cpu);
        static unsigned char Bit7B(Cpu* cpu);
        static unsigned char Bit7C(Cpu* cpu);
        static unsigned char Bit7D(Cpu* cpu);
        static unsigned char Bit7E(Cpu* cpu);
        static unsigned char Bit7F(Cpu* cpu);
};

class Res
{
    public:
        static unsigned char Res80(Cpu* cpu);
        static unsigned char Res81(Cpu* cpu);
        static unsigned char Res82(Cpu* cpu);
        static unsigned char Res83(Cpu* cpu);
        static unsigned char Res84(Cpu* cpu);
        static unsigned char Res85(Cpu* cpu);
        static unsigned char Res86(Cpu* cpu);
        static unsigned char Res87(Cpu* cpu);
        static unsigned char Res88(Cpu* cpu);
        static unsigned char Res89(Cpu* cpu);
        static unsigned char Res8A(Cpu* cpu);
        static unsigned char Res8B(Cpu* cpu);
        static unsigned char Res8C(Cpu* cpu);
        static unsigned char Res8D(Cpu* cpu);
        static unsigned char Res8E(Cpu* cpu);
        static unsigned char Res8F(Cpu* cpu);
        static unsigned char Res90(Cpu* cpu);
        static unsigned char Res91(Cpu* cpu);
        static unsigned char Res92(Cpu* cpu);
        static unsigned char Res93(Cpu* cpu);
        static unsigned char Res94(Cpu* cpu);
        static unsigned char Res95(Cpu* cpu);
        static unsigned char Res96(Cpu* cpu);
        static unsigned char Res97(Cpu* cpu);
        static unsigned char Res98(Cpu* cpu);
        static unsigned char Res99(Cpu* cpu);
        static unsigned char Res9A(Cpu* cpu);
        static unsigned char Res9B(Cpu* cpu);
        static unsigned char Res9C(Cpu* cpu);
        static unsigned char Res9D(Cpu* cpu);
        static unsigned char Res9E(Cpu* cpu);
        static unsigned char Res9F(Cpu* cpu);
        static unsigned char ResA0(Cpu* cpu);
        static unsigned char ResA1(Cpu* cpu);
        static unsigned char ResA2(Cpu* cpu);
        static unsigned char ResA3(Cpu* cpu);
        static unsigned char ResA4(Cpu* cpu);
        static unsigned char ResA5(Cpu* cpu);
        static unsigned char ResA6(Cpu* cpu);
        static unsigned char ResA7(Cpu* cpu);
        static unsigned char ResA8(Cpu* cpu);
        static unsigned char ResA9(Cpu* cpu);
        static unsigned char ResAA(Cpu* cpu);
        static unsigned char ResAB(Cpu* cpu);
        static unsigned char ResAC(Cpu* cpu);
        static unsigned char ResAD(Cpu* cpu);
        static unsigned char ResAE(Cpu* cpu);
        static unsigned char ResAF(Cpu* cpu);
        static unsigned char ResB0(Cpu* cpu);
        static unsigned char ResB1(Cpu* cpu);
        static unsigned char ResB2(Cpu* cpu);
        static unsigned char ResB3(Cpu* cpu);
        static unsigned char ResB4(Cpu* cpu);
        static unsigned char ResB5(Cpu* cpu);
        static unsigned char ResB6(Cpu* cpu);
        static unsigned char ResB7(Cpu* cpu);
        static unsigned char ResB8(Cpu* cpu);
        static unsigned char ResB9(Cpu* cpu);
        static unsigned char ResBA(Cpu* cpu);
        static unsigned char ResBB(Cpu* cpu);
        static unsigned char ResBC(Cpu* cpu);
        static unsigned char ResBD(Cpu* cpu);
        static unsigned char ResBE(Cpu* cpu);
        static unsigned char ResBF(Cpu* cpu);
};

class Set
{
    public:
        static unsigned char SetC0(Cpu* cpu);
        static unsigned char SetC1(Cpu* cpu);
        static unsigned char SetC2(Cpu* cpu);
        static unsigned char SetC3(Cpu* cpu);
        static unsigned char SetC4(Cpu* cpu);
        static unsigned char SetC5(Cpu* cpu);
        static unsigned char SetC6(Cpu* cpu);
        static unsigned char SetC7(Cpu* cpu);
        static unsigned char SetC8(Cpu* cpu);
        static unsigned char SetC9(Cpu* cpu);
        static unsigned char SetCA(Cpu* cpu);
        static unsigned char SetCB(Cpu* cpu);
        static unsigned char SetCC(Cpu* cpu);
        static unsigned char SetCD(Cpu* cpu);
        static unsigned char SetCE(Cpu* cpu);
        static unsigned char SetCF(Cpu* cpu);
        static unsigned char SetD0(Cpu* cpu);
        static unsigned char SetD1(Cpu* cpu);
        static unsigned char SetD2(Cpu* cpu);
        static unsigned char SetD3(Cpu* cpu);
        static unsigned char SetD4(Cpu* cpu);
        static unsigned char SetD5(Cpu* cpu);
        static unsigned char SetD6(Cpu* cpu);
        static unsigned char SetD7(Cpu* cpu);
        static unsigned char SetD8(Cpu* cpu);
        static unsigned char SetD9(Cpu* cpu);
        static unsigned char SetDA(Cpu* cpu);
        static unsigned char SetDB(Cpu* cpu);
        static unsigned char SetDC(Cpu* cpu);
        static unsigned char SetDD(Cpu* cpu);
        static unsigned char SetDE(Cpu* cpu);
        static unsigned char SetDF(Cpu* cpu);
        static unsigned char SetE0(Cpu* cpu);
        static unsigned char SetE1(Cpu* cpu);
        static unsigned char SetE2(Cpu* cpu);
        static unsigned char SetE3(Cpu* cpu);
        static unsigned char SetE4(Cpu* cpu);
        static unsigned char SetE5(Cpu* cpu);
        static unsigned char SetE6(Cpu* cpu);
        static unsigned char SetE7(Cpu* cpu);
        static unsigned char SetE8(Cpu* cpu);
        static unsigned char SetE9(Cpu* cpu);
        static unsigned char SetEA(Cpu* cpu);
        static unsigned char SetEB(Cpu* cpu);
        static unsigned char SetEC(Cpu* cpu);
        static unsigned char SetED(Cpu* cpu);
        static unsigned char SetEE(Cpu* cpu);
        static unsigned char SetEF(Cpu* cpu);
        static unsigned char SetF0(Cpu* cpu);
        static unsigned char SetF1(Cpu* cpu);
        static unsigned char SetF2(Cpu* cpu);
        static unsigned char SetF3(Cpu* cpu);
        static unsigned char SetF4(Cpu* cpu);
        static unsigned char SetF5(Cpu* cpu);
        static unsigned char SetF6(Cpu* cpu);
        static unsigned char SetF7(Cpu* cpu);
        static unsigned char SetF8(Cpu* cpu);
        static unsigned char SetF9(Cpu* cpu);
        static unsigned char SetFA(Cpu* cpu);
        static unsigned char SetFB(Cpu* cpu);
        static unsigned char SetFC(Cpu* cpu);
        static unsigned char SetFD(Cpu* cpu);
        static unsigned char SetFE(Cpu* cpu);
        static unsigned char SetFF(Cpu* cpu);
};

#endif // PREFIX_H