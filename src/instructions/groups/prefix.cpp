#include <stdexcept>

#include "prefix.h"
#include "../../hardware/cpu.h"

/************** Rlc *******************/
uint8_t Rlc::RotateLeftAndSetFlags(Cpu* cpu, uint8_t value)
{
    uint8_t result = (value << 1) | ((value >> 7) & 0x1);    

    cpu->setFlag(Z_ZERO, result == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, false);
    cpu->setFlag(C_CARRY, ((value >> 7) & 0x1) != 0);

    return result;
}

uint8_t Rlc::Rlc00(Cpu* cpu)
{
    // Mnemonic: RLC B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->b = Rlc::RotateLeftAndSetFlags(cpu, cpu->b.read());
    return 8;
}

uint8_t Rlc::Rlc01(Cpu* cpu)
{
    // Mnemonic: RLC C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->c = Rlc::RotateLeftAndSetFlags(cpu, cpu->c.read());
    return 8;
}

uint8_t Rlc::Rlc02(Cpu* cpu)
{
    // Mnemonic: RLC D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->d = Rlc::RotateLeftAndSetFlags(cpu, cpu->d.read());
    return 8;
}

uint8_t Rlc::Rlc03(Cpu* cpu)
{
    // Mnemonic: RLC E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->e = Rlc::RotateLeftAndSetFlags(cpu, cpu->e.read());
    return 8;
}

uint8_t Rlc::Rlc04(Cpu* cpu)
{
    // Mnemonic: RLC H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->h = Rlc::RotateLeftAndSetFlags(cpu, cpu->h.read());
    return 8;
}

uint8_t Rlc::Rlc05(Cpu* cpu)
{
    // Mnemonic: RLC L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->l = Rlc::RotateLeftAndSetFlags(cpu, cpu->l.read());
    return 8;
}

uint8_t Rlc::Rlc06(Cpu* cpu)
{
    // Mnemonic: RLC (HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 0 C
    cpu->mmu.write(cpu->hl.read(), Rlc::RotateLeftAndSetFlags(cpu, cpu->mmu.read(cpu->hl.read())));
    return 16;
}

uint8_t Rlc::Rlc07(Cpu* cpu)
{
    // Mnemonic: RLC A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->a = Rlc::RotateLeftAndSetFlags(cpu, cpu->a.read());
    return 8;
}

/************** Rrc *******************/
uint8_t Rrc::RotateRightAndSetFlags(Cpu* cpu, uint8_t value)
{
    uint8_t result = ((value & 0x1) << 7) | (value >> 1);    

    cpu->setFlag(Z_ZERO, result == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, false);
    cpu->setFlag(C_CARRY, (value & 0x1) != 0);

    return result;
}

uint8_t Rrc::Rrc08(Cpu* cpu)
{
    // Mnemonic: RRC B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->b = Rrc::RotateRightAndSetFlags(cpu, cpu->b.read());
    return 8;
}

uint8_t Rrc::Rrc09(Cpu* cpu)
{
    // Mnemonic: RRC C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->c = Rrc::RotateRightAndSetFlags(cpu, cpu->c.read());
    return 8;
}

uint8_t Rrc::Rrc0A(Cpu* cpu)
{
    // Mnemonic: RRC D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->d = Rrc::RotateRightAndSetFlags(cpu, cpu->d.read());
    return 8;
}

uint8_t Rrc::Rrc0B(Cpu* cpu)
{
    // Mnemonic: RRC E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->e = Rrc::RotateRightAndSetFlags(cpu, cpu->e.read());
    return 8;
}

uint8_t Rrc::Rrc0C(Cpu* cpu)
{
    // Mnemonic: RRC H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->h = Rrc::RotateRightAndSetFlags(cpu, cpu->h.read());
    return 8;
}

uint8_t Rrc::Rrc0D(Cpu* cpu)
{
    // Mnemonic: RRC L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->l = Rrc::RotateRightAndSetFlags(cpu, cpu->l.read());
    return 8;
}

uint8_t Rrc::Rrc0E(Cpu* cpu)
{
    // Mnemonic: RRC (HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 0 C
    cpu->mmu.read(cpu->hl.read(), Rrc::RotateRightAndSetFlags(cpu, cpu->mmu.read(cpu->hl.read())));
    return 16;
}

uint8_t Rrc::Rrc0F(Cpu* cpu)
{
    // Mnemonic: RRC A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->a = Rrc::RotateRightAndSetFlags(cpu, cpu->a.read());
    return 8;
}

/************** Rl *******************/
uint8_t Rl::RotateLeftThroughCarryAndSetFlags(Cpu* cpu, uint8_t value)
{
    uint8_t carry = cpu->getFlag(C_CARRY) ? 1 : 0;
    uint8_t result = (value << 1) | carry;    

    cpu->setFlag(Z_ZERO, result == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, false);
    cpu->setFlag(C_CARRY, ((value >> 7) & 0x1) != 0);

    return result;
}

uint8_t Rl::Rl10(Cpu* cpu)
{
    // Mnemonic: RL B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->b = Rl::RotateLeftThroughCarryAndSetFlags(cpu, cpu->b.read());
    return 8;
}

uint8_t Rl::Rl11(Cpu* cpu)
{
    // Mnemonic: RL C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->c = Rl::RotateLeftThroughCarryAndSetFlags(cpu, cpu->c.read());
    return 8;
}

uint8_t Rl::Rl12(Cpu* cpu)
{
    // Mnemonic: RL D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->d = Rl::RotateLeftThroughCarryAndSetFlags(cpu, cpu->d.read());
    return 8;
}

uint8_t Rl::Rl13(Cpu* cpu)
{
    // Mnemonic: RL E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->e = Rl::RotateLeftThroughCarryAndSetFlags(cpu, cpu->e.read());
    return 8;
}

uint8_t Rl::Rl14(Cpu* cpu)
{
    // Mnemonic: RL H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->h = Rl::RotateLeftThroughCarryAndSetFlags(cpu, cpu->h.read());
    return 8;
}

uint8_t Rl::Rl15(Cpu* cpu)
{
    // Mnemonic: RL L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->l = Rl::RotateLeftThroughCarryAndSetFlags(cpu, cpu->l.read());
    return 8;
}

uint8_t Rl::Rl16(Cpu* cpu)
{
    // Mnemonic: RL (HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 0 C
    cpu->mmu.write(cpu->hl.read(), Rl::RotateLeftThroughCarryAndSetFlags(cpu, cpu->mmu.read(cpu->hl.read())));
    return 16;
}

uint8_t Rl::Rl17(Cpu* cpu)
{
    // Mnemonic: RL A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->a = Rl::RotateLeftThroughCarryAndSetFlags(cpu, cpu->a.read());
    return 8;
}

/************** Rr *******************/
uint8_t Rr::RotateRightThroughCarryAndSetFlags(Cpu* cpu, uint8_t value)
{
    uint8_t carry = cpu->getFlag(C_CARRY) ? 0x80 : 0;
    uint8_t result = carry | (value >> 1);    

    cpu->setFlag(Z_ZERO, result == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, false);
    cpu->setFlag(C_CARRY, (value & 0x1) != 0);

    return result;
}

uint8_t Rr::Rr18(Cpu* cpu)
{
    // Mnemonic: RR B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->b = Rr::RotateRightThroughCarryAndSetFlags(cpu, cpu->b.read());    
    return 8;
}

uint8_t Rr::Rr19(Cpu* cpu)
{
    // Mnemonic: RR C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->c = Rr::RotateRightThroughCarryAndSetFlags(cpu, cpu->c.read());    
    return 8;
}

uint8_t Rr::Rr1A(Cpu* cpu)
{
    // Mnemonic: RR D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->d = Rr::RotateRightThroughCarryAndSetFlags(cpu, cpu->d.read());    
    return 8;
}

uint8_t Rr::Rr1B(Cpu* cpu)
{
    // Mnemonic: RR E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->e = Rr::RotateRightThroughCarryAndSetFlags(cpu, cpu->e.read());    
    return 8;
}

uint8_t Rr::Rr1C(Cpu* cpu)
{
    // Mnemonic: RR H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->h = Rr::RotateRightThroughCarryAndSetFlags(cpu, cpu->h.read());    
    return 8;
}

uint8_t Rr::Rr1D(Cpu* cpu)
{
    // Mnemonic: RR L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->l = Rr::RotateRightThroughCarryAndSetFlags(cpu, cpu->l.read());    
    return 8;
}

uint8_t Rr::Rr1E(Cpu* cpu)
{
    // Mnemonic: RR (HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 0 C
    cpu->mmu.write(cpu->hl.read(), Rr::RotateRightThroughCarryAndSetFlags(cpu, cpu->mmu.read(cpu->hl.read())));    
    return 16;
}

uint8_t Rr::Rr1F(Cpu* cpu)
{
    // Mnemonic: RR A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->a = Rr::RotateRightThroughCarryAndSetFlags(cpu, cpu->a.read());    
    return 8;
}

/************** Sla *******************/
uint8_t Sla::ShiftLeftAndSetFlags(Cpu* cpu, uint8_t value)
{
    uint8_t result = value << 1;    

    cpu->setFlag(Z_ZERO, result == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, false);
    cpu->setFlag(C_CARRY, ((value >> 7) & 0x1) != 0);

    return result;
}

uint8_t Sla::Sla20(Cpu* cpu)
{
    // Mnemonic: SLA B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->b = Sla::ShiftLeftAndSetFlags(cpu, cpu->b.read());
    return 8;
}

uint8_t Sla::Sla21(Cpu* cpu)
{
    // Mnemonic: SLA C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->c = Sla::ShiftLeftAndSetFlags(cpu, cpu->c.read());
    return 8;
}

uint8_t Sla::Sla22(Cpu* cpu)
{
    // Mnemonic: SLA D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->d = Sla::ShiftLeftAndSetFlags(cpu, cpu->d.read());
    return 8;
}

uint8_t Sla::Sla23(Cpu* cpu)
{
    // Mnemonic: SLA E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->e = Sla::ShiftLeftAndSetFlags(cpu, cpu->e.read());
    return 8;
}

uint8_t Sla::Sla24(Cpu* cpu)
{
    // Mnemonic: SLA H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->h = Sla::ShiftLeftAndSetFlags(cpu, cpu->h.read());
    return 8;
}

uint8_t Sla::Sla25(Cpu* cpu)
{
    // Mnemonic: SLA L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->l = Sla::ShiftLeftAndSetFlags(cpu, cpu->l.read());
    return 8;
}

uint8_t Sla::Sla26(Cpu* cpu)
{
    // Mnemonic: SLA (HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 0 C
    cpu->mmu.write(cpu->hl.read(), Sla::ShiftLeftAndSetFlags(cpu, cpu->mmu.read(cpu->hl.read())));
    return 16;
}

uint8_t Sla::Sla27(Cpu* cpu)
{
    // Mnemonic: SLA A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->a = Sla::ShiftLeftAndSetFlags(cpu, cpu->a.read());
    return 8;
}

/************** Sra *******************/
uint8_t Sra::ShiftRightAritmeticalAndSetFlags(Cpu* cpu, uint8_t value)
{
    uint8_t result = (value & 0x80) | (value >> 1);    

    cpu->setFlag(Z_ZERO, result == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, false);
    cpu->setFlag(C_CARRY, ((value & 0x1) != 0));

    return result;
}

uint8_t Sra::Sra28(Cpu* cpu)
{
    // Mnemonic: SRA B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    cpu->b = Sra::ShiftRightAritmeticalAndSetFlags(cpu, cpu->b.read());
    return 8;
}

uint8_t Sra::Sra29(Cpu* cpu)
{
    // Mnemonic: SRA C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    cpu->c = Sra::ShiftRightAritmeticalAndSetFlags(cpu, cpu->c.read());
    return 8;
}

uint8_t Sra::Sra2A(Cpu* cpu)
{
    // Mnemonic: SRA D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    cpu->d = Sra::ShiftRightAritmeticalAndSetFlags(cpu, cpu->d.read());
    return 8;
}

uint8_t Sra::Sra2B(Cpu* cpu)
{
    // Mnemonic: SRA E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    cpu->e = Sra::ShiftRightAritmeticalAndSetFlags(cpu, cpu->e.read());
    return 8;
}

uint8_t Sra::Sra2C(Cpu* cpu)
{
    // Mnemonic: SRA H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    cpu->h = Sra::ShiftRightAritmeticalAndSetFlags(cpu, cpu->h.read());
    return 8;
}

uint8_t Sra::Sra2D(Cpu* cpu)
{
    // Mnemonic: SRA L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    cpu->l = Sra::ShiftRightAritmeticalAndSetFlags(cpu, cpu->l.read());
    return 8;
}

uint8_t Sra::Sra2E(Cpu* cpu)
{
    // Mnemonic: SRA (HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 0 0
    cpu->mmu.write(cpu->hl.read(), Sra::ShiftRightAritmeticalAndSetFlags(cpu, cpu->mmu.read(cpu->hl.read())));
    return 16;
}

uint8_t Sra::Sra2F(Cpu* cpu)
{
    // Mnemonic: SRA A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    cpu->a = Sra::ShiftRightAritmeticalAndSetFlags(cpu, cpu->a.read());
    return 8;
}

/************** Swap *******************/
void Swap::SwapRegister(Cpu* cpu, Register<uint8_t>& reg)
{
    uint8_t toSwap = reg.read();
    uint8_t swapped = (toSwap & 0x0F) << 4 | (toSwap & 0xF0) >> 4; 
    
    cpu->setFlag(Z_ZERO, swapped == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, false);
    cpu->setFlag(C_CARRY, false);
}

uint8_t Swap::Swap30(Cpu* cpu)
{
    // Mnemonic: SWAP B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    Swap::SwapRegister(cpu, cpu->b);
    return 8;
}

uint8_t Swap::Swap31(Cpu* cpu)
{
    // Mnemonic: SWAP C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    Swap::SwapRegister(cpu, cpu->c);
    return 8;
}

uint8_t Swap::Swap32(Cpu* cpu)
{
    // Mnemonic: SWAP D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    Swap::SwapRegister(cpu, cpu->d);
    return 8;
}

uint8_t Swap::Swap33(Cpu* cpu)
{
    // Mnemonic: SWAP E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    Swap::SwapRegister(cpu, cpu->e);
    return 8;
}

uint8_t Swap::Swap34(Cpu* cpu)
{
    // Mnemonic: SWAP H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    Swap::SwapRegister(cpu, cpu->h);
    return 8;
}

uint8_t Swap::Swap35(Cpu* cpu)
{
    // Mnemonic: SWAP L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    Swap::SwapRegister(cpu, cpu->l);
    return 8;
}

uint8_t Swap::Swap36(Cpu* cpu)
{
    // Mnemonic: SWAP (HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 0 0
    uint16_t toSwap = cpu->hl.read();
    uint16_t swapped = (toSwap & 0x00FF) << 8 | (toSwap & 0xFF00) >> 8; 
    
    cpu->setFlag(Z_ZERO, swapped == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, false);
    cpu->setFlag(C_CARRY, false);
    return 8;
}

uint8_t Swap::Swap37(Cpu* cpu)
{
    // Mnemonic: SWAP A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 0
    Swap::SwapRegister(cpu, cpu->a);
    return 8;
}

/************** SRL *******************/
uint8_t Srl::ShiftRightAndSetFlags(Cpu* cpu, uint8_t value)
{
    uint8_t result = value >> 1;

    cpu->setFlag(Z_ZERO, result == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, false);
    cpu->setFlag(C_CARRY, (value & 0x1) != 0);

    return result;
}

uint8_t Srl::Srl38(Cpu* cpu)
{
    // Mnemonic: SRL B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->b = Srl::ShiftRightAndSetFlags(cpu, cpu->b.read());
    return 8;
}

uint8_t Srl::Srl39(Cpu* cpu)
{
    // Mnemonic: SRL C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->d = Srl::ShiftRightAndSetFlags(cpu, cpu->d.read());
    return 8;
}

uint8_t Srl::Srl3A(Cpu* cpu)
{
    // Mnemonic: SRL D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->d = Srl::ShiftRightAndSetFlags(cpu, cpu->d.read());
    return 8;
}

uint8_t Srl::Srl3B(Cpu* cpu)
{
    // Mnemonic: SRL E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->e = Srl::ShiftRightAndSetFlags(cpu, cpu->e.read());
    return 8;
}

uint8_t Srl::Srl3C(Cpu* cpu)
{
    // Mnemonic: SRL H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->h = Srl::ShiftRightAndSetFlags(cpu, cpu->h.read());
    return 8;
}

uint8_t Srl::Srl3D(Cpu* cpu)
{
    // Mnemonic: SRL L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->l = Srl::ShiftRightAndSetFlags(cpu, cpu->l.read());
    return 8;
}

uint8_t Srl::Srl3E(Cpu* cpu)
{
    // Mnemonic: SRL (HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 0 C
    cpu->mmu.write(cpu->hl.read(), Srl::ShiftRightAndSetFlags(cpu, cpu->mmu.read(cpu->hl.read())));
    return 16;
}

uint8_t Srl::Srl3F(Cpu* cpu)
{
    // Mnemonic: SRL A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 0 C
    cpu->a = Srl::ShiftRightAndSetFlags(cpu, cpu->a.read());
    return 8;
}

/************** BIT *******************/
void Bit::BitCheckAndSetFlags(Cpu* cpu, uint8_t bit, uint8_t value)
{
    cpu->setFlag(Z_ZERO, ((value >> bit) & 0x1) == 0);
    cpu->setFlag(N_SUBSTRACT, false);
    cpu->setFlag(H_HALFCARRY, true);
}

uint8_t Bit::Bit40(Cpu* cpu)
{
    // Mnemonic: BIT 0,B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 0, cpu->b.read());
    return 8;
}

uint8_t Bit::Bit41(Cpu* cpu)
{
    // Mnemonic: BIT 0,C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 0, cpu->c.read());
    return 8;
}

uint8_t Bit::Bit42(Cpu* cpu)
{
    // Mnemonic: BIT 0,D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 0, cpu->d.read());
    return 8;
}

uint8_t Bit::Bit43(Cpu* cpu)
{
    // Mnemonic: BIT 0,E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 0, cpu->e.read());
    return 8;
}

uint8_t Bit::Bit44(Cpu* cpu)
{
    // Mnemonic: BIT 0,H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 0, cpu->h.read());
    return 8;
}

uint8_t Bit::Bit45(Cpu* cpu)
{
    // Mnemonic: BIT 0,L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 0, cpu->l.read());
    return 8;
}

uint8_t Bit::Bit46(Cpu* cpu)
{
    // Mnemonic: BIT 0,(HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 0, cpu->mmu.read(cpu->hl.read()));
    return 16;
}

uint8_t Bit::Bit47(Cpu* cpu)
{
    // Mnemonic: BIT 0,A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 0, cpu->a.read());
    return 8;
}

uint8_t Bit::Bit48(Cpu* cpu)
{
    // Mnemonic: BIT 1,B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 1, cpu->b.read());
    return 8;
}

uint8_t Bit::Bit49(Cpu* cpu)
{
    // Mnemonic: BIT 1,C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 1, cpu->c.read());
    return 8;
}

uint8_t Bit::Bit4A(Cpu* cpu)
{
    // Mnemonic: BIT 1,D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 1, cpu->d.read());
    return 8;
}

uint8_t Bit::Bit4B(Cpu* cpu)
{
    // Mnemonic: BIT 1,E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 1, cpu->e.read());
    return 8;
}

uint8_t Bit::Bit4C(Cpu* cpu)
{
    // Mnemonic: BIT 1,H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 1, cpu->h.read());
    return 8;
}

uint8_t Bit::Bit4D(Cpu* cpu)
{
    // Mnemonic: BIT 1,L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 1, cpu->l.read());
    return 8;
}

uint8_t Bit::Bit4E(Cpu* cpu)
{
    // Mnemonic: BIT 1,(HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 1, cpu->mmu.read(cpu->hl.read()));
    return 16;
}

uint8_t Bit::Bit4F(Cpu* cpu)
{
    // Mnemonic: BIT 1,A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 1, cpu->a.read());
    return 8;
}

uint8_t Bit::Bit50(Cpu* cpu)
{
    // Mnemonic: BIT 2,B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 2, cpu->b.read());
    return 8;
}

uint8_t Bit::Bit51(Cpu* cpu)
{
    // Mnemonic: BIT 2,C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 2, cpu->c.read());
    return 8;
}

uint8_t Bit::Bit52(Cpu* cpu)
{
    // Mnemonic: BIT 2,D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 2, cpu->d.read());
    return 8;
}

uint8_t Bit::Bit53(Cpu* cpu)
{
    // Mnemonic: BIT 2,E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 2, cpu->e.read());
    return 8;
}

uint8_t Bit::Bit54(Cpu* cpu)
{
    // Mnemonic: BIT 2,H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 2, cpu->h.read());
    return 8;
}

uint8_t Bit::Bit55(Cpu* cpu)
{
    // Mnemonic: BIT 2,L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 2, cpu->l.read());
    return 8;
}

uint8_t Bit::Bit56(Cpu* cpu)
{
    // Mnemonic: BIT 2,(HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 2, cpu->mmu.read(cpu->hl.read()));
    return 16;
}

uint8_t Bit::Bit57(Cpu* cpu)
{
    // Mnemonic: BIT 2,A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 2, cpu->a.read());
    return 8;
}

uint8_t Bit::Bit58(Cpu* cpu)
{
    // Mnemonic: BIT 3,B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 3, cpu->b.read());
    return 8;
}

uint8_t Bit::Bit59(Cpu* cpu)
{
    // Mnemonic: BIT 3,C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 3, cpu->c.read());
    return 8;
}

uint8_t Bit::Bit5A(Cpu* cpu)
{
    // Mnemonic: BIT 3,D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 3, cpu->d.read());
    return 8;
}

uint8_t Bit::Bit5B(Cpu* cpu)
{
    // Mnemonic: BIT 3,E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 3, cpu->e.read());
    return 8;
}

uint8_t Bit::Bit5C(Cpu* cpu)
{
    // Mnemonic: BIT 3,H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 3, cpu->h.read());
    return 8;
}

uint8_t Bit::Bit5D(Cpu* cpu)
{
    // Mnemonic: BIT 3,L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 3, cpu->l.read());
    return 8;
}

uint8_t Bit::Bit5E(Cpu* cpu)
{
    // Mnemonic: BIT 3,(HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 3, cpu->mmu.read(cpu->hl.read()));
    return 16;
}

uint8_t Bit::Bit5F(Cpu* cpu)
{
    // Mnemonic: BIT 3,A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 3, cpu->a.read());
    return 8;
}

uint8_t Bit::Bit60(Cpu* cpu)
{
    // Mnemonic: BIT 4,B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 4, cpu->b.read());
    return 8;
}

uint8_t Bit::Bit61(Cpu* cpu)
{
    // Mnemonic: BIT 4,C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 4, cpu->c.read());
    return 8;
}

uint8_t Bit::Bit62(Cpu* cpu)
{
    // Mnemonic: BIT 4,D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 4, cpu->d.read());
    return 8;
}

uint8_t Bit::Bit63(Cpu* cpu)
{
    // Mnemonic: BIT 4,E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 4, cpu->e.read());
    return 8;
}

uint8_t Bit::Bit64(Cpu* cpu)
{
    // Mnemonic: BIT 4,H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 4, cpu->h.read());
    return 8;
}

uint8_t Bit::Bit65(Cpu* cpu)
{
    // Mnemonic: BIT 4,L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 4, cpu->l.read());
    return 8;
}

uint8_t Bit::Bit66(Cpu* cpu)
{
    // Mnemonic: BIT 4,(HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 4, cpu->mmu.read(cpu->hl.read()));
    return 8;
}

uint8_t Bit::Bit67(Cpu* cpu)
{
    // Mnemonic: BIT 4,A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 4, cpu->a.read());
    return 8;
}

uint8_t Bit::Bit68(Cpu* cpu)
{
    // Mnemonic: BIT 5,B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 5, cpu->b.read());
    return 8;
}

uint8_t Bit::Bit69(Cpu* cpu)
{
    // Mnemonic: BIT 5,C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 5, cpu->d.read());
    return 8;
}

uint8_t Bit::Bit6A(Cpu* cpu)
{
    // Mnemonic: BIT 5,D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 5, cpu->d.read());
    return 8;
}

uint8_t Bit::Bit6B(Cpu* cpu)
{
    // Mnemonic: BIT 5,E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 5, cpu->e.read());
    return 8;
}

uint8_t Bit::Bit6C(Cpu* cpu)
{
    // Mnemonic: BIT 5,H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 5, cpu->h.read());
    return 8;
}

uint8_t Bit::Bit6D(Cpu* cpu)
{
    // Mnemonic: BIT 5,L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 5, cpu->l.read());
    return 8;
}

uint8_t Bit::Bit6E(Cpu* cpu)
{
    // Mnemonic: BIT 5,(HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 5, cpu->mmu.read(cpu->hl.read()));
    return 8;
}

uint8_t Bit::Bit6F(Cpu* cpu)
{
    // Mnemonic: BIT 5,A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 5, cpu->a.read());
    return 8;
}

uint8_t Bit::Bit70(Cpu* cpu)
{
    // Mnemonic: BIT 6,B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 6, cpu->b.read());
    return 8;
}

uint8_t Bit::Bit71(Cpu* cpu)
{
    // Mnemonic: BIT 6,C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 6, cpu->c.read());
    return 8;
}

uint8_t Bit::Bit72(Cpu* cpu)
{
    // Mnemonic: BIT 6,D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 6, cpu->d.read());
    return 8;
}

uint8_t Bit::Bit73(Cpu* cpu)
{
    // Mnemonic: BIT 6,E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 6, cpu->e.read());
    return 8;
}

uint8_t Bit::Bit74(Cpu* cpu)
{
    // Mnemonic: BIT 6,H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 6, cpu->h.read());
    return 8;
}

uint8_t Bit::Bit75(Cpu* cpu)
{
    // Mnemonic: BIT 6,L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 6, cpu->l.read());
    return 8;
}

uint8_t Bit::Bit76(Cpu* cpu)
{
    // Mnemonic: BIT 6,(HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 6, cpu->mmu.read(cpu->hl.read()));
    return 16;
}

uint8_t Bit::Bit77(Cpu* cpu)
{
    // Mnemonic: BIT 6,A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 6, cpu->a.read());
    return 8;
}

uint8_t Bit::Bit78(Cpu* cpu)
{
    // Mnemonic: BIT 7,B, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 7, cpu->b.read());
    return 8;
}

uint8_t Bit::Bit79(Cpu* cpu)
{
    // Mnemonic: BIT 7,C, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 7, cpu->c.read());
    return 8;
}

uint8_t Bit::Bit7A(Cpu* cpu)
{
    // Mnemonic: BIT 7,D, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 7, cpu->d.read());
    return 8;
}

uint8_t Bit::Bit7B(Cpu* cpu)
{
    // Mnemonic: BIT 7,E, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 7, cpu->e.read());
    return 8;
}

uint8_t Bit::Bit7C(Cpu* cpu)
{
    // Mnemonic: BIT 7,H, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 7, cpu->h.read());
    return 8;
}

uint8_t Bit::Bit7D(Cpu* cpu)
{
    // Mnemonic: BIT 7,L, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 7, cpu->l.read());
    return 8;
}

uint8_t Bit::Bit7E(Cpu* cpu)
{
    // Mnemonic: BIT 7,(HL), Length: 2
    // Cycles: 16, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 7, cpu->mmu.read(cpu->hl.read()));
    return 16;
}

uint8_t Bit::Bit7F(Cpu* cpu)
{
    // Mnemonic: BIT 7,A, Length: 2
    // Cycles: 8, (Z N H C): Z 0 1 -
    Bit::BitCheckAndSetFlags(cpu, 7, cpu->a.read());
    return 8;
}

/************** RES *******************/
void Res::ResRegisterBit(Register<uint8_t>& reg, uint8_t bitNr)
{
    reg = (reg.read() & ~(0x1 << bitNr)); 
}

void Res::ResAddressBit(Cpu* cpu, uint16_t address, uint8_t bitNr)
{
    cpu->mmu.write(address, cpu->mmu.read(address) & ~(0x1 << bitNr));
}

uint8_t Res::Res80(Cpu* cpu)
{
    // Mnemonic: RES 0,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->b, 0);
    return 8;
}

uint8_t Res::Res81(Cpu* cpu)
{
    // Mnemonic: RES 0,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->c, 0);
    return 8;
}

uint8_t Res::Res82(Cpu* cpu)
{
    // Mnemonic: RES 0,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->d, 0);
    return 8;
}

uint8_t Res::Res83(Cpu* cpu)
{
    // Mnemonic: RES 0,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->e, 0);
    return 8;
}

uint8_t Res::Res84(Cpu* cpu)
{
    // Mnemonic: RES 0,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->h, 0);
    return 8;
}

uint8_t Res::Res85(Cpu* cpu)
{
    // Mnemonic: RES 0,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->l, 0);
    return 8;
}

uint8_t Res::Res86(Cpu* cpu)
{
    // Mnemonic: RES 0,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Res::ResAddressBit(cpu, cpu->hl.read(), 0);
    return 16;
}

uint8_t Res::Res87(Cpu* cpu)
{
    // Mnemonic: RES 0,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->a, 0);
    return 8;
}

uint8_t Res::Res88(Cpu* cpu)
{
    // Mnemonic: RES 1,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->b, 1);
    return 8;
}

uint8_t Res::Res89(Cpu* cpu)
{
    // Mnemonic: RES 1,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->c, 1);
    return 8;
}

uint8_t Res::Res8A(Cpu* cpu)
{
    // Mnemonic: RES 1,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->d, 1);
    return 8;
}

uint8_t Res::Res8B(Cpu* cpu)
{
    // Mnemonic: RES 1,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->e, 1);
    return 8;
}

uint8_t Res::Res8C(Cpu* cpu)
{
    // Mnemonic: RES 1,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->h, 1);
    return 8;
}

uint8_t Res::Res8D(Cpu* cpu)
{
    // Mnemonic: RES 1,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->l, 1);
    return 8;
}

uint8_t Res::Res8E(Cpu* cpu)
{
    // Mnemonic: RES 1,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Res::ResAddressBit(cpu, cpu->hl.read(), 1);
    return 16;
}

uint8_t Res::Res8F(Cpu* cpu)
{
    // Mnemonic: RES 1,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->a, 1);
    return 8;
}

uint8_t Res::Res90(Cpu* cpu)
{
    // Mnemonic: RES 2,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->b, 2);
    return 8;
}

uint8_t Res::Res91(Cpu* cpu)
{
    // Mnemonic: RES 2,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->c, 2);
    return 8;
}

uint8_t Res::Res92(Cpu* cpu)
{
    // Mnemonic: RES 2,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->d, 2);
    return 8;
}

uint8_t Res::Res93(Cpu* cpu)
{
    // Mnemonic: RES 2,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->e, 2);
    return 8;
}

uint8_t Res::Res94(Cpu* cpu)
{
    // Mnemonic: RES 2,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->h, 2);
    return 8;
}

uint8_t Res::Res95(Cpu* cpu)
{
    // Mnemonic: RES 2,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->l, 2);
    return 8;
}

uint8_t Res::Res96(Cpu* cpu)
{
    // Mnemonic: RES 2,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Res::ResAddressBit(cpu, cpu->hl.read(), 2);
    return 16;
}

uint8_t Res::Res97(Cpu* cpu)
{
    // Mnemonic: RES 2,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->a, 2);
    return 8;
}

uint8_t Res::Res98(Cpu* cpu)
{
    // Mnemonic: RES 3,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->b, 3);
    return 8;
}

uint8_t Res::Res99(Cpu* cpu)
{
    // Mnemonic: RES 3,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->c, 3);
    return 8;
}

uint8_t Res::Res9A(Cpu* cpu)
{
    // Mnemonic: RES 3,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->d, 3);
    return 8;
}

uint8_t Res::Res9B(Cpu* cpu)
{
    // Mnemonic: RES 3,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->e, 3);
    return 8;
}

uint8_t Res::Res9C(Cpu* cpu)
{
    // Mnemonic: RES 3,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->h, 3);
    return 8;
}

uint8_t Res::Res9D(Cpu* cpu)
{
    // Mnemonic: RES 3,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->l, 3);
    return 8;
}

uint8_t Res::Res9E(Cpu* cpu)
{
    // Mnemonic: RES 3,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Res::ResAddressBit(cpu, cpu->hl.read(), 3);
    return 16;
}

uint8_t Res::Res9F(Cpu* cpu)
{
    // Mnemonic: RES 3,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->a, 3);
    return 8;
}

uint8_t Res::ResA0(Cpu* cpu)
{
    // Mnemonic: RES 4,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->b, 4);
    return 8;
}

uint8_t Res::ResA1(Cpu* cpu)
{
    // Mnemonic: RES 4,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->c, 4);
    return 8;
}

uint8_t Res::ResA2(Cpu* cpu)
{
    // Mnemonic: RES 4,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->d, 4);
    return 8;
}

uint8_t Res::ResA3(Cpu* cpu)
{
    // Mnemonic: RES 4,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->e, 4);
    return 8;
}

uint8_t Res::ResA4(Cpu* cpu)
{
    // Mnemonic: RES 4,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->h, 4);
    return 8;
}

uint8_t Res::ResA5(Cpu* cpu)
{
    // Mnemonic: RES 4,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->l, 4);
    return 8;
}

uint8_t Res::ResA6(Cpu* cpu)
{
    // Mnemonic: RES 4,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Res::ResAddressBit(cpu, cpu->hl.read(), 4);
    return 16;
}

uint8_t Res::ResA7(Cpu* cpu)
{
    // Mnemonic: RES 4,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->a, 4);
    return 8;
}

uint8_t Res::ResA8(Cpu* cpu)
{
    // Mnemonic: RES 5,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->b, 5);
    return 8;
}

uint8_t Res::ResA9(Cpu* cpu)
{
    // Mnemonic: RES 5,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
     Res::ResRegisterBit(cpu->c, 5);
    return 8;
}

uint8_t Res::ResAA(Cpu* cpu)
{
    // Mnemonic: RES 5,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
     Res::ResRegisterBit(cpu->d, 5);
    return 8;
}

uint8_t Res::ResAB(Cpu* cpu)
{
    // Mnemonic: RES 5,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
     Res::ResRegisterBit(cpu->e, 5);
    return 8;
}

uint8_t Res::ResAC(Cpu* cpu)
{
    // Mnemonic: RES 5,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
     Res::ResRegisterBit(cpu->h, 5);
    return 8;
}

uint8_t Res::ResAD(Cpu* cpu)
{
    // Mnemonic: RES 5,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
     Res::ResRegisterBit(cpu->l, 5);
    return 8;
}

uint8_t Res::ResAE(Cpu* cpu)
{
    // Mnemonic: RES 5,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Res::ResAddressBit(cpu, cpu->hl.read(), 5);
    return 16;
}

uint8_t Res::ResAF(Cpu* cpu)
{
    // Mnemonic: RES 5,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
     Res::ResRegisterBit(cpu->a, 5);
    return 8;
}

uint8_t Res::ResB0(Cpu* cpu)
{
    // Mnemonic: RES 6,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->b, 6);
    return 8;
}

uint8_t Res::ResB1(Cpu* cpu)
{
    // Mnemonic: RES 6,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->c, 6);
    return 8;
}

uint8_t Res::ResB2(Cpu* cpu)
{
    // Mnemonic: RES 6,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->d, 6);
    return 8;
}

uint8_t Res::ResB3(Cpu* cpu)
{
    // Mnemonic: RES 6,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->e, 6);
    return 8;
}

uint8_t Res::ResB4(Cpu* cpu)
{
    // Mnemonic: RES 6,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->h, 6);
    return 8;
}

uint8_t Res::ResB5(Cpu* cpu)
{
    // Mnemonic: RES 6,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->l, 6);
    return 8;
}

uint8_t Res::ResB6(Cpu* cpu)
{
    // Mnemonic: RES 6,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Res::ResAddressBit(cpu, cpu->hl.read(), 6);
    return 16;
}

uint8_t Res::ResB7(Cpu* cpu)
{
    // Mnemonic: RES 6,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->a, 6);
    return 8;
}

uint8_t Res::ResB8(Cpu* cpu)
{
    // Mnemonic: RES 7,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->b, 7);
    return 8;
}

uint8_t Res::ResB9(Cpu* cpu)
{
    // Mnemonic: RES 7,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->c, 7);
    return 8;
}

uint8_t Res::ResBA(Cpu* cpu)
{
    // Mnemonic: RES 7,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->d, 7);
    return 8;
}

uint8_t Res::ResBB(Cpu* cpu)
{
    // Mnemonic: RES 7,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->e, 7);
    return 8;
}

uint8_t Res::ResBC(Cpu* cpu)
{
    // Mnemonic: RES 7,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->h, 7);
    return 8;
}

uint8_t Res::ResBD(Cpu* cpu)
{
    // Mnemonic: RES 7,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->l, 7);
    return 8;
}

uint8_t Res::ResBE(Cpu* cpu)
{
    // Mnemonic: RES 7,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Res::ResAddressBit(cpu, cpu->hl.read(), 7);
    return 16;
}

uint8_t Res::ResBF(Cpu* cpu)
{
    // Mnemonic: RES 7,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Res::ResRegisterBit(cpu->a, 7);
    return 8;
}

/************** SET *******************/
void Set::SetRegisterBit(Register<uint8_t>& reg, uint8_t bitNr)
{
    reg = reg.read() | (0x1 << bitNr); 
}

void Set::SetAddressBit(Cpu* cpu, uint16_t address, uint8_t bitNr)
{
    cpu->mmu.write(address, cpu->mmu.read(address) | (0x1 << bitNr));
}

uint8_t Set::SetC0(Cpu* cpu)
{
    // Mnemonic: SET 0,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->b, 0);
    return 8;
}

uint8_t Set::SetC1(Cpu* cpu)
{
    // Mnemonic: SET 0,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->c, 0);
    return 8;
}

uint8_t Set::SetC2(Cpu* cpu)
{
    // Mnemonic: SET 0,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->d, 0);
    return 8;
}

uint8_t Set::SetC3(Cpu* cpu)
{
    // Mnemonic: SET 0,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->e, 0);
    return 8;
}

uint8_t Set::SetC4(Cpu* cpu)
{
    // Mnemonic: SET 0,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->h, 0);
    return 8;
}

uint8_t Set::SetC5(Cpu* cpu)
{
    // Mnemonic: SET 0,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->l, 0);
    return 8;
}

uint8_t Set::SetC6(Cpu* cpu)
{
    // Mnemonic: SET 0,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Set::SetAddressBit(cpu, cpu->hl.read(), 0);
    return 16;
}

uint8_t Set::SetC7(Cpu* cpu)
{
    // Mnemonic: SET 0,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->a, 0);
    return 8;
}

uint8_t Set::SetC8(Cpu* cpu)
{
    // Mnemonic: SET 1,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->b, 1);
    return 8;
}

uint8_t Set::SetC9(Cpu* cpu)
{
    // Mnemonic: SET 1,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->c, 1);
    return 8;
}

uint8_t Set::SetCA(Cpu* cpu)
{
    // Mnemonic: SET 1,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->d, 1);
    return 8;
}

uint8_t Set::SetCB(Cpu* cpu)
{
    // Mnemonic: SET 1,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->e, 1);
    return 8;
}

uint8_t Set::SetCC(Cpu* cpu)
{
    // Mnemonic: SET 1,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->h, 1);
    return 8;
}

uint8_t Set::SetCD(Cpu* cpu)
{
    // Mnemonic: SET 1,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->l, 1);
    return 8;
}

uint8_t Set::SetCE(Cpu* cpu)
{
    // Mnemonic: SET 1,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Set::SetAddressBit(cpu, cpu->hl.read(), 1);
    return 16;
}

uint8_t Set::SetCF(Cpu* cpu)
{
    // Mnemonic: SET 1,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->a, 1);
    return 8;
}

uint8_t Set::SetD0(Cpu* cpu)
{
    // Mnemonic: SET 2,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->b, 2);
    return 8;
}

uint8_t Set::SetD1(Cpu* cpu)
{
    // Mnemonic: SET 2,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->c, 2);
    return 8;
}

uint8_t Set::SetD2(Cpu* cpu)
{
    // Mnemonic: SET 2,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->d, 2);
    return 8;
}

uint8_t Set::SetD3(Cpu* cpu)
{
    // Mnemonic: SET 2,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->e, 2);
    return 8;
}

uint8_t Set::SetD4(Cpu* cpu)
{
    // Mnemonic: SET 2,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->h, 2);
    return 8;
}

uint8_t Set::SetD5(Cpu* cpu)
{
    // Mnemonic: SET 2,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->l, 2);
    return 8;
}

uint8_t Set::SetD6(Cpu* cpu)
{
    // Mnemonic: SET 2,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Set::SetAddressBit(cpu, cpu->hl.read(), 2);
    return 16;
}

uint8_t Set::SetD7(Cpu* cpu)
{
    // Mnemonic: SET 2,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->a, 2);
    return 8;
}

uint8_t Set::SetD8(Cpu* cpu)
{
    // Mnemonic: SET 3,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->b, 3);
    return 8;
}

uint8_t Set::SetD9(Cpu* cpu)
{
    // Mnemonic: SET 3,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->c, 3);
    return 8;
}

uint8_t Set::SetDA(Cpu* cpu)
{
    // Mnemonic: SET 3,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->d, 3);
    return 8;
}

uint8_t Set::SetDB(Cpu* cpu)
{
    // Mnemonic: SET 3,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->e, 3);
    return 8;
}

uint8_t Set::SetDC(Cpu* cpu)
{
    // Mnemonic: SET 3,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->h, 3);
    return 8;
}

uint8_t Set::SetDD(Cpu* cpu)
{
    // Mnemonic: SET 3,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->l, 3);
    return 8;
}

uint8_t Set::SetDE(Cpu* cpu)
{
    // Mnemonic: SET 3,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Set::SetAddressBit(cpu, cpu->hl.read(), 3);
    return 16;
}

uint8_t Set::SetDF(Cpu* cpu)
{
    // Mnemonic: SET 3,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->a, 3);
    return 8;
}

uint8_t Set::SetE0(Cpu* cpu)
{
    // Mnemonic: SET 4,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->b, 4);
    return 8;
}

uint8_t Set::SetE1(Cpu* cpu)
{
    // Mnemonic: SET 4,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->c, 4);
    return 8;
}

uint8_t Set::SetE2(Cpu* cpu)
{
    // Mnemonic: SET 4,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->d, 4);
    return 8;
}

uint8_t Set::SetE3(Cpu* cpu)
{
    // Mnemonic: SET 4,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->e, 4);
    return 8;
}

uint8_t Set::SetE4(Cpu* cpu)
{
    // Mnemonic: SET 4,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->h, 4);
    return 8;
}

uint8_t Set::SetE5(Cpu* cpu)
{
    // Mnemonic: SET 4,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->l, 4);
    return 8;
}

uint8_t Set::SetE6(Cpu* cpu)
{
    // Mnemonic: SET 4,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Set::SetAddressBit(cpu, cpu->hl.read(), 4);
    return 16;
}

uint8_t Set::SetE7(Cpu* cpu)
{
    // Mnemonic: SET 4,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->a, 4);
    return 8;
}

uint8_t Set::SetE8(Cpu* cpu)
{
    // Mnemonic: SET 5,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->b, 5);
    return 8;
}

uint8_t Set::SetE9(Cpu* cpu)
{
    // Mnemonic: SET 5,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->c, 5);
    return 8;
}

uint8_t Set::SetEA(Cpu* cpu)
{
    // Mnemonic: SET 5,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->d, 5);
    return 8;
}

uint8_t Set::SetEB(Cpu* cpu)
{
    // Mnemonic: SET 5,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->e, 5);
    return 8;
}

uint8_t Set::SetEC(Cpu* cpu)
{
    // Mnemonic: SET 5,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->h, 5);
    return 8;
}

uint8_t Set::SetED(Cpu* cpu)
{
    // Mnemonic: SET 5,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->l, 5);
    return 8;
}

uint8_t Set::SetEE(Cpu* cpu)
{
    // Mnemonic: SET 5,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Set::SetAddressBit(cpu, cpu->hl.read(), 5);
    return 16;
}

uint8_t Set::SetEF(Cpu* cpu)
{
    // Mnemonic: SET 5,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->a, 5);
    return 8;
}

uint8_t Set::SetF0(Cpu* cpu)
{
    // Mnemonic: SET 6,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->b, 6);
    return 8;
}

uint8_t Set::SetF1(Cpu* cpu)
{
    // Mnemonic: SET 6,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->c, 6);
    return 8;
}

uint8_t Set::SetF2(Cpu* cpu)
{
    // Mnemonic: SET 6,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->d, 6);
    return 8;
}

uint8_t Set::SetF3(Cpu* cpu)
{
    // Mnemonic: SET 6,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->e, 6);
    return 8;
}

uint8_t Set::SetF4(Cpu* cpu)
{
    // Mnemonic: SET 6,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->h, 6);
    return 8;
}

uint8_t Set::SetF5(Cpu* cpu)
{
    // Mnemonic: SET 6,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->l, 6);
    return 8;
}

uint8_t Set::SetF6(Cpu* cpu)
{
    // Mnemonic: SET 6,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Set::SetAddressBit(cpu, cpu->hl.read(), 6);
    return 16;
}

uint8_t Set::SetF7(Cpu* cpu)
{
    // Mnemonic: SET 6,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->a, 6);
    return 8;
}

uint8_t Set::SetF8(Cpu* cpu)
{
    // Mnemonic: SET 7,B, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->b, 7);
    return 8;
}

uint8_t Set::SetF9(Cpu* cpu)
{
    // Mnemonic: SET 7,C, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->c, 7);
    return 8;
}

uint8_t Set::SetFA(Cpu* cpu)
{
    // Mnemonic: SET 7,D, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->d, 7);
    return 8;
}

uint8_t Set::SetFB(Cpu* cpu)
{
    // Mnemonic: SET 7,E, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->e, 7);
    return 8;
}

uint8_t Set::SetFC(Cpu* cpu)
{
    // Mnemonic: SET 7,H, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->h, 7);
    return 8;
}

uint8_t Set::SetFD(Cpu* cpu)
{
    // Mnemonic: SET 7,L, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->l, 7);
    return 8;
}

uint8_t Set::SetFE(Cpu* cpu)
{
    // Mnemonic: SET 7,(HL), Length: 2
    // Cycles: 16, (Z N H C): - - - -
    Set::SetAddressBit(cpu, cpu->hl.read(), 7);
    return 16;
}

uint8_t Set::SetFF(Cpu* cpu)
{
    // Mnemonic: SET 7,A, Length: 2
    // Cycles: 8, (Z N H C): - - - -
    Set::SetRegisterBit(cpu->a, 7);
    return 8;
}

