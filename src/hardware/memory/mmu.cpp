#include <stdexcept>
#include <cstring>
#include "mmu.h"

namespace GGB::Hardware
{
    Mmu::Mmu(Cartridge& cartridge) : cartridge(cartridge) { }

    uint8_t Mmu::read(const uint16_t address, const bool ppuAccess) const 
    {     
        // VRAM Access through the PPU. CPU is not allowed to access it directly.
        // PPU Mode has to be checked, wether the CPU is currently allowed to access it
        // ppuAccess is able to overwrite this behaviour. This way it is possible 
        // for the debugging tools and the PPU to read memory during each state
        if(!ppuAccess)
        {
            if(currentPpuMode == Enums::LCD_MODE::TRANSFER && address >= 0x8000 && address <= 0x9FFF)
                return 0xFF;
            else if((currentPpuMode == Enums::LCD_MODE::TRANSFER || currentPpuMode == Enums::LCD_MODE::OAM)
                    && address >= 0xFE00 && address <= 0xFE9F)
                return 0xFF;
        }    

        // Cartridge Bank 0
        if(address >= 0x000 && address <= 0x3FFF)
            return cartridge.read(address);    
        // Cartridge Bank 1..NN
        else if(address >= 0x4000 && address <= 0x7FFF)
            return cartridge.read(address);    
        else
            return memory[address];     
    }

    void Mmu::write(const uint16_t address, const uint8_t value) 
    {
        // VRAM Access through the PPU. CPU is not allowed to access it directly.
        // PPU Mode has to be checked, weather the CPU is currently allowed to write.
        // Any attempt to write during the forbidden modes will keep the memory unchanged.
        // PPU components are using the rawWrite method to overwrite this behaviour.
        if(currentPpuMode == Enums::LCD_MODE::TRANSFER && address >= 0x8000 && address <= 0x9FFF) return;
        else if((currentPpuMode == Enums::LCD_MODE::TRANSFER || currentPpuMode == Enums::LCD_MODE::OAM)
                && address >= 0xFE00 && address <= 0xFE9F) return;   

        using Enums::IO_REGISTER;
        // If writing to LDCY I/O register, reset it
        if(address == IO_REGISTER::REG_LCD_Y) memory[address] = 0;
        // If writing to the Timer Divider, reset it
        else if(address == IO_REGISTER::REG_DIVIDER) memory[address] = 0;
        // If written to DMA start a DMA transfer to OAM
        else if(address == IO_REGISTER::REG_DMA) executeDmaTransfer(value);    
        // If writing to the pad register for setting bit 4 & 5
        // Preserver Lower Bits (= Button pressed atm)
        // 0x30 = 0011 0000
        else if(address == IO_REGISTER::REG_PAD) 
            memory[IO_REGISTER::REG_PAD] = (value & 0x30) | (memory[IO_REGISTER::REG_PAD] & 0xCF);
        // If writing to the lcd status register
        // Preserver Lower two Bits (= current lcd mode (read only))
        // 0x03 = 0000 0011
        // 0x7C = 0111 1100
        else if(address == IO_REGISTER::REG_LCD_STATUS) 
            memory[IO_REGISTER::REG_LCD_STATUS] = (value & 0x7C) | (memory[IO_REGISTER::REG_LCD_STATUS] & 0x03);
        // If writing into this range, change the rom bank in the cartridge
        else if(address >= (uint16_t)Enums::CARTRIDGE_FLAG::SWITCH_BANK_TRIGGER_START
        && address <= (uint16_t)Enums::CARTRIDGE_FLAG::SWITCH_BANK_TRIGGER_END) 
            cartridge.selectRomBank(value);
        else memory[address] = value; 
    }

    void Mmu::rawWrite(const uint16_t address, const uint8_t value) 
    {
        memory[address] = value;
    }

    void Mmu::executeDmaTransfer(const uint8_t value)
    {
        // DMA has a higher priority than PPU modes
        // Thats why we do rawWrites/rawReads here.
        memory[Enums::IO_REGISTER::REG_DMA] = value;
        uint16_t startAddress = value << 8;

        for (int i = 0x0; i <= 0x9F; i++) 
        {
            uint16_t copyFrom = startAddress + i;
            uint16_t copyTo = 0xFE00 + i;

            uint8_t copyValue = read(copyFrom, true);
            rawWrite(copyTo, copyValue);
        }
    }

    bool Mmu::readIORegisterBit(const Enums::IO_REGISTER reg, const uint8_t flag, const bool ppuAccess) const 
    { 
        return read(reg, ppuAccess) & flag; 
    }

    uint8_t Mmu::readIORegister(const Enums::IO_REGISTER reg, const bool ppuAccess) const 
    {
        return read(reg, ppuAccess); 
    }

    void Mmu::writeIORegisterBit(const Enums::IO_REGISTER reg, const uint8_t flag, const bool value) 
    { 
        if(value) memory[reg] |= flag; 
        else memory[reg] &= ~flag; 
    }

    Enums::LCD_MODE Mmu::readLcdMode() const
    {
        return currentPpuMode;
    }

    void Mmu::writeLcdMode(const Enums::LCD_MODE lcdMode)
    {
        using Enums::IO_REGISTER, Enums::LCD_STATUS_FLAG;
        writeIORegisterBit(IO_REGISTER::REG_LCD_STATUS, LCD_STATUS_FLAG::MODE_HIGH, (lcdMode >> 1) & 0x1);
        writeIORegisterBit(IO_REGISTER::REG_LCD_STATUS, LCD_STATUS_FLAG::MODE_LOW, lcdMode & 0x1);
        currentPpuMode = lcdMode;
    }

    uint32_t Mmu::getSize() const 
    { 
        return memorySize; 
    }
}