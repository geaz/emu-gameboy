#include <stdexcept>

#include "transfer.h"
#include "../../hardware/cpu.h"

uint8_t Ld::Ld01(Cpu* cpu)
{
    // Mnemonic: LD BC,d16, Length: 3
    // Cycles: 12, (Z N H C): - - - -
    cpu->bc.write(cpu->currentInstruction.parsedBytes.b16);
    return 12;
}

uint8_t Ld::Ld02(Cpu* cpu)
{
    // Mnemonic: LD (BC),A, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->bc.read(), cpu->a.read());
    return 8;
}

uint8_t Ld::Ld06(Cpu* cpu)
{
    // Mnemonic: LD B,d8, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    cpu->b = cpu->currentInstruction.parsedBytes.low;
    return 8;
}

uint8_t Ld::Ld08(Cpu* cpu)
{
    // Mnemonic: LD (a16),SP, Length: 3
    // Cycles: 20, (Z N H C): - - - -
    cpu->mmu.write(cpu->currentInstruction.parsedBytes.b16, cpu->sp.read() & 0x00FF);
    cpu->mmu.write(cpu->currentInstruction.parsedBytes.b16 + 1, (cpu->sp.read() & 0xFF00) >> 8);
    return 20;
}

uint8_t Ld::Ld0A(Cpu* cpu)
{
    // Mnemonic: LD A,(BC), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->a = cpu->mmu.read(cpu->bc.read());
    return 8;
}

uint8_t Ld::Ld0E(Cpu* cpu)
{
    // Mnemonic: LD C,d8, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    cpu->c = cpu->currentInstruction.parsedBytes.low;
    return 8;
}

uint8_t Ld::Ld11(Cpu* cpu)
{
    // Mnemonic: LD DE,d16, Length: 3
    // Cycles: 12, (Z N H C): - - - -
    cpu->de.write(cpu->currentInstruction.parsedBytes.b16);
    return 12;
}

uint8_t Ld::Ld12(Cpu* cpu)
{
    // Mnemonic: LD (DE),A, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->de.read(), cpu->a.read());
    return 8;
}

uint8_t Ld::Ld16(Cpu* cpu)
{
    // Mnemonic: LD D,d8, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    cpu->d = cpu->currentInstruction.parsedBytes.low;
    return 8;
}

uint8_t Ld::Ld1A(Cpu* cpu)
{
    // Mnemonic: LD A,(DE), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->a = cpu->mmu.read(cpu->de.read());
    return 8;
}

uint8_t Ld::Ld1E(Cpu* cpu)
{
    // Mnemonic: LD E,d8, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    cpu->e = cpu->currentInstruction.parsedBytes.low;
    return 8;
}

uint8_t Ld::Ld21(Cpu* cpu)
{
    // Mnemonic: LD HL,d16, Length: 3
    // Cycles: 12, (Z N H C): - - - -
    cpu->hl.write(cpu->currentInstruction.parsedBytes.b16);
    return 12;
}

uint8_t Ld::Ld22(Cpu* cpu)
{
    // Mnemonic: LD (HL+),A, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->a = cpu->mmu.read(cpu->hl.read());
    cpu->hl++;
    return 8;
}

uint8_t Ld::Ld26(Cpu* cpu)
{
    // Mnemonic: LD H,d8, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    cpu->h = cpu->currentInstruction.parsedBytes.low;
    return 8;
}

uint8_t Ld::Ld2A(Cpu* cpu)
{
    // Mnemonic: LD A,(HL+), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->a = cpu->mmu.read(cpu->hl.read());
    cpu->hl++;
    return 8;
}

uint8_t Ld::Ld2E(Cpu* cpu)
{
    // Mnemonic: LD L,d8, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    cpu->l = cpu->currentInstruction.parsedBytes.low;
    return 8;
}

uint8_t Ld::Ld31(Cpu* cpu)
{
    // Mnemonic: LD SP,d16, Length: 3
    // Cycles: 12, (Z N H C): - - - -
    cpu->sp = cpu->currentInstruction.parsedBytes.b16;
    return 12;
}

uint8_t Ld::Ld32(Cpu* cpu)
{
    // Mnemonic: LD (HL-),A, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->hl.read(), cpu->a.read());
    cpu->hl--;
    return 8;
}

uint8_t Ld::Ld36(Cpu* cpu)
{
    // Mnemonic: LD (HL),d8, Length: 2
    // Cycles: 12, (Z N H C): - - - -
    cpu->mmu.write(cpu->hl.read(), cpu->currentInstruction.parsedBytes.low);
    return 12;
}

uint8_t Ld::Ld3A(Cpu* cpu)
{
    // Mnemonic: LD A,(HL-), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->a = cpu->mmu.read(cpu->hl.read());
    cpu->hl--;
    return 8;
}

uint8_t Ld::Ld3E(Cpu* cpu)
{
    // Mnemonic: LD A,d8, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    cpu->a = cpu->currentInstruction.parsedBytes.low;
    return 8;
}

uint8_t Ld::Ld40(Cpu* cpu)
{
    // Mnemonic: LD B,B, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->b = cpu->b.read();
    return 4;
}

uint8_t Ld::Ld41(Cpu* cpu)
{
    // Mnemonic: LD B,C, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->b = cpu->c.read();
    return 4;
}

uint8_t Ld::Ld42(Cpu* cpu)
{
    // Mnemonic: LD B,D, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->b = cpu->d.read();
    return 4;
}

uint8_t Ld::Ld43(Cpu* cpu)
{
    // Mnemonic: LD B,E, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->b = cpu->e.read();
    return 4;
}

uint8_t Ld::Ld44(Cpu* cpu)
{
    // Mnemonic: LD B,H, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->b = cpu->h.read();
    return 4;
}

uint8_t Ld::Ld45(Cpu* cpu)
{
    // Mnemonic: LD B,L, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->b = cpu->l.read();
    return 4;
}

uint8_t Ld::Ld46(Cpu* cpu)
{
    // Mnemonic: LD B,(HL), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->b = cpu->mmu.read(cpu->hl.read());
    return 8;
}

uint8_t Ld::Ld47(Cpu* cpu)
{
    // Mnemonic: LD B,A, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->b = cpu->a.read();
    return 4;
}

uint8_t Ld::Ld48(Cpu* cpu)
{
    // Mnemonic: LD C,B, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->c = cpu->b.read();
    return 4;
}

uint8_t Ld::Ld49(Cpu* cpu)
{
    // Mnemonic: LD C,C, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->c = cpu->c.read();
    return 4;
}

uint8_t Ld::Ld4A(Cpu* cpu)
{
    // Mnemonic: LD C,D, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->c = cpu->d.read();
    return 4;
}

uint8_t Ld::Ld4B(Cpu* cpu)
{
    // Mnemonic: LD C,E, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->c = cpu->e.read();
    return 4;
}

uint8_t Ld::Ld4C(Cpu* cpu)
{
    // Mnemonic: LD C,H, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->c = cpu->h.read();
    return 4;
}

uint8_t Ld::Ld4D(Cpu* cpu)
{
    // Mnemonic: LD C,L, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->c = cpu->l.read();
    return 4;
}

uint8_t Ld::Ld4E(Cpu* cpu)
{
    // Mnemonic: LD C,(HL), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->c = cpu->mmu.read(cpu->hl.read());
    return 8;
}

uint8_t Ld::Ld4F(Cpu* cpu)
{
    // Mnemonic: LD C,A, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->c = cpu->a.read();
    return 4;
}

uint8_t Ld::Ld50(Cpu* cpu)
{
    // Mnemonic: LD D,B, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->d = cpu->b.read();
    return 4;
}

uint8_t Ld::Ld51(Cpu* cpu)
{
    // Mnemonic: LD D,C, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->d = cpu->c.read();
    return 4;
}

uint8_t Ld::Ld52(Cpu* cpu)
{
    // Mnemonic: LD D,D, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->d = cpu->d.read();
    return 4;
}

uint8_t Ld::Ld53(Cpu* cpu)
{
    // Mnemonic: LD D,E, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->d = cpu->e.read();
    return 4;
}

uint8_t Ld::Ld54(Cpu* cpu)
{
    // Mnemonic: LD D,H, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->d = cpu->h.read();
    return 4;
}

uint8_t Ld::Ld55(Cpu* cpu)
{
    // Mnemonic: LD D,L, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->d = cpu->l.read();
    return 4;
}

uint8_t Ld::Ld56(Cpu* cpu)
{
    // Mnemonic: LD D,(HL), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->d = cpu->mmu.read(cpu->hl.read());
    return 8;
}

uint8_t Ld::Ld57(Cpu* cpu)
{
    // Mnemonic: LD D,A, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->d = cpu->a.read();
    return 4;
}

uint8_t Ld::Ld58(Cpu* cpu)
{
    // Mnemonic: LD E,B, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->e = cpu->b.read();
    return 4;
}

uint8_t Ld::Ld59(Cpu* cpu)
{
    // Mnemonic: LD E,C, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->e = cpu->c.read();
    return 4;
}

uint8_t Ld::Ld5A(Cpu* cpu)
{
    // Mnemonic: LD E,D, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->e = cpu->d.read();
    return 4;
}

uint8_t Ld::Ld5B(Cpu* cpu)
{
    // Mnemonic: LD E,E, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->e = cpu->e.read();
    return 4;
}

uint8_t Ld::Ld5C(Cpu* cpu)
{
    // Mnemonic: LD E,H, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->e = cpu->h.read();
    return 4;
}

uint8_t Ld::Ld5D(Cpu* cpu)
{
    // Mnemonic: LD E,L, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->e = cpu->l.read();
    return 4;
}

uint8_t Ld::Ld5E(Cpu* cpu)
{
    // Mnemonic: LD E,(HL), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->e = cpu->mmu.read(cpu->hl.read());
    return 8;
}

uint8_t Ld::Ld5F(Cpu* cpu)
{
    // Mnemonic: LD E,A, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->e = cpu->a.read();
    return 4;
}

uint8_t Ld::Ld60(Cpu* cpu)
{
    // Mnemonic: LD H,B, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->h = cpu->b.read();
    return 4;
}

uint8_t Ld::Ld61(Cpu* cpu)
{
    // Mnemonic: LD H,C, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->h = cpu->c.read();
    return 4;
}

uint8_t Ld::Ld62(Cpu* cpu)
{
    // Mnemonic: LD H,D, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->h = cpu->d.read();
    return 4;
}

uint8_t Ld::Ld63(Cpu* cpu)
{
    // Mnemonic: LD H,E, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->h = cpu->e.read();
    return 4;
}

uint8_t Ld::Ld64(Cpu* cpu)
{
    // Mnemonic: LD H,H, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->h = cpu->h.read();
    return 4;
}

uint8_t Ld::Ld65(Cpu* cpu)
{
    // Mnemonic: LD H,L, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->h = cpu->l.read();
    return 4;
}

uint8_t Ld::Ld66(Cpu* cpu)
{
    // Mnemonic: LD H,(HL), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->h = cpu->mmu.read(cpu->hl.read());
    return 8;
}

uint8_t Ld::Ld67(Cpu* cpu)
{
    // Mnemonic: LD H,A, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->h = cpu->a.read();
    return 4;
}

uint8_t Ld::Ld68(Cpu* cpu)
{
    // Mnemonic: LD L,B, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->l = cpu->b.read();
    return 4;
}

uint8_t Ld::Ld69(Cpu* cpu)
{
    // Mnemonic: LD L,C, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->l = cpu->c.read();
    return 4;
}

uint8_t Ld::Ld6A(Cpu* cpu)
{
    // Mnemonic: LD L,D, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->l = cpu->d.read();
    return 4;
}

uint8_t Ld::Ld6B(Cpu* cpu)
{
    // Mnemonic: LD L,E, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->l = cpu->e.read();
    return 4;
}

uint8_t Ld::Ld6C(Cpu* cpu)
{
    // Mnemonic: LD L,H, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->l = cpu->h.read();
    return 4;
}

uint8_t Ld::Ld6D(Cpu* cpu)
{
    // Mnemonic: LD L,L, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->l = cpu->l.read();
    return 4;
}

uint8_t Ld::Ld6E(Cpu* cpu)
{
    // Mnemonic: LD L,(HL), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->l = cpu->mmu.read(cpu->hl.read());
    return 8;
}

uint8_t Ld::Ld6F(Cpu* cpu)
{
    // Mnemonic: LD L,A, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->l = cpu->a.read();
    return 4;
}

uint8_t Ld::Ld70(Cpu* cpu)
{
    // Mnemonic: LD (HL),B, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->hl.read(), cpu->b.read());
    return 8;
}

uint8_t Ld::Ld71(Cpu* cpu)
{
    // Mnemonic: LD (HL),C, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->hl.read(), cpu->c.read());
    return 8;
}

uint8_t Ld::Ld72(Cpu* cpu)
{
    // Mnemonic: LD (HL),D, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->hl.read(), cpu->d.read());
    return 8;
}

uint8_t Ld::Ld73(Cpu* cpu)
{
    // Mnemonic: LD (HL),E, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->hl.read(), cpu->e.read());
    return 8;
}

uint8_t Ld::Ld74(Cpu* cpu)
{
    // Mnemonic: LD (HL),H, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->hl.read(), cpu->h.read());
    return 8;
}

uint8_t Ld::Ld75(Cpu* cpu)
{
    // Mnemonic: LD (HL),L, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->hl.read(), cpu->l.read());
    return 8;
}

uint8_t Ld::Ld77(Cpu* cpu)
{
    // Mnemonic: LD (HL),A, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(cpu->hl.read(), cpu->a.read());
    return 8;
}

uint8_t Ld::Ld78(Cpu* cpu)
{
    // Mnemonic: LD A,B, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->a = cpu->b.read();
    return 4;
}

uint8_t Ld::Ld79(Cpu* cpu)
{
    // Mnemonic: LD A,C, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->a = cpu->c.read();
    return 4;
}

uint8_t Ld::Ld7A(Cpu* cpu)
{
    // Mnemonic: LD A,D, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->a = cpu->d.read();
    return 4;
}

uint8_t Ld::Ld7B(Cpu* cpu)
{
    // Mnemonic: LD A,E, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->a = cpu->e.read();
    return 4;
}

uint8_t Ld::Ld7C(Cpu* cpu)
{
    // Mnemonic: LD A,H, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->a = cpu->h.read();
    return 4;
}

uint8_t Ld::Ld7D(Cpu* cpu)
{
    // Mnemonic: LD A,L, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->a = cpu->l.read();
    return 4;
}

uint8_t Ld::Ld7E(Cpu* cpu)
{
    // Mnemonic: LD A,(HL), Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->a = cpu->mmu.read(cpu->hl.read());
    return 8;
}

uint8_t Ld::Ld7F(Cpu* cpu)
{
    // Mnemonic: LD A,A, Length: 1
    // Cycles: 4, (Z N H C): - - - -
    cpu->a = cpu->a.read();
    return 4;
}

uint8_t Ld::LdE2(Cpu* cpu)
{
    // Mnemonic: LD (C),A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    cpu->mmu.write(0xFF00 + cpu->c.read(), cpu->a.read());
    return 8;
}

uint8_t Ld::LdEA(Cpu* cpu)
{
    // Mnemonic: LD (a16),A, Length: 3
    // Cycles: 16, (Z N H C): - - - -
    cpu->mmu.write(cpu->currentInstruction.parsedBytes.b16, cpu->a.read());
    return 16;
}

uint8_t Ld::LdF2(Cpu* cpu)
{
    // Mnemonic: LD A,(C), Length: 2
    // Cycles: 8, (Z N H C): - - - -
    cpu->a = cpu->mmu.read(0xFF00 + cpu->c.read());
    return 8;
}

uint8_t Ld::LdF8(Cpu* cpu)
{
    // Mnemonic: LD HL,SP+r8, Length: 2
    // Cycles: 12, (Z N H C): 0 0 H C  
    int8_t signedValue = static_cast<int8_t>(cpu->currentInstruction.parsedBytes.low);  
    int32_t fullResult = cpu->sp.read() + signedValue;
    uint16_t result = static_cast<uint16_t>(fullResult);

    cpu->setFlag(Z_ZERO, false);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, ((cpu->sp.read() ^ signedValue ^ (fullResult & 0xFFFF)) & 0x10) == 0x10);
    cpu->setFlag(C_CARRY, ((cpu->sp.read() ^ signedValue ^ (fullResult & 0xFFFF)) & 0x100) == 0x100);

    cpu->hl.write(result);
    return 12;
}

uint8_t Ld::LdF9(Cpu* cpu)
{
    // Mnemonic: LD SP,HL, Length: 1
    // Cycles: 8, (Z N H C): - - - -
    cpu->sp = cpu->hl.read();
    return 8;
}

uint8_t Ld::LdFA(Cpu* cpu)
{
    // Mnemonic: LD A,(a16), Length: 3
    // Cycles: 16, (Z N H C): - - - -
    cpu->a = cpu->mmu.read(cpu->currentInstruction.parsedBytes.b16);
    return 16;
}

uint8_t Pop::PopC1(Cpu* cpu)
{
    // Mnemonic: POP BC, Length: 1
    // Cycles: 12, (Z N H C): - - - -
    cpu->bc.write(cpu->popStack());
    return 12;
}

uint8_t Pop::PopD1(Cpu* cpu)
{
    // Mnemonic: POP DE, Length: 1
    // Cycles: 12, (Z N H C): - - - -
    cpu->de.write(cpu->popStack());
    return 12;
}

uint8_t Pop::PopE1(Cpu* cpu)
{
    // Mnemonic: POP HL, Length: 1
    // Cycles: 12, (Z N H C): - - - -
    cpu->hl.write(cpu->popStack());
    return 12;
}

uint8_t Pop::PopF1(Cpu* cpu)
{
    // Mnemonic: POP AF, Length: 1
    // Cycles: 12, (Z N H C): Z N H C
    // On Pop AF the Bits 0-3 are ignored
    cpu->af.write(cpu->popStack() & 0xFFF0);
    return 12;
}

uint8_t Push::PushC5(Cpu* cpu)
{
    // Mnemonic: PUSH BC, Length: 1
    // Cycles: 16, (Z N H C): - - - -
    cpu->pushStack(cpu->bc.read());
    return 16;
}

uint8_t Push::PushD5(Cpu* cpu)
{
    // Mnemonic: PUSH DE, Length: 1
    // Cycles: 16, (Z N H C): - - - -
    cpu->pushStack(cpu->de.read());
    return 16;
}

uint8_t Push::PushE5(Cpu* cpu)
{
    // Mnemonic: PUSH HL, Length: 1
    // Cycles: 16, (Z N H C): - - - -
    cpu->pushStack(cpu->hl.read());
    return 16;
}

uint8_t Push::PushF5(Cpu* cpu)
{
    // Mnemonic: PUSH AF, Length: 1
    // Cycles: 16, (Z N H C): - - - -
    cpu->pushStack(cpu->af.read());
    return 16;
}

uint8_t Ldh::LdhE0(Cpu* cpu)
{
    // Mnemonic: LDH (a8),A, Length: 2
    // Cycles: 12, (Z N H C): - - - -
    cpu->mmu.write(0xFF00 + cpu->currentInstruction.parsedBytes.low, cpu->a.read());
    return 12;
}

uint8_t Ldh::LdhF0(Cpu* cpu)
{
    // Mnemonic: LDH A,(a8), Length: 2
    // Cycles: 12, (Z N H C): - - - -
    cpu->a = cpu->mmu.read(0xFF00 + cpu->currentInstruction.parsedBytes.low);
    return 12;
}

