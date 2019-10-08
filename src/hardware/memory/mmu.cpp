#include <stdexcept>
#include <cstring>
#include "mmu.h"
#include "../video/tile_list.h"

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
            if(currentPpuMode == Enum::LcdMode::Transfer && address >= 0x8000 && address <= 0x9FFF)
                return 0xFF;
            else if((currentPpuMode == Enum::LcdMode::Transfer || currentPpuMode == Enum::LcdMode::Oam)
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
        lastWriteEvent = { address, value, std::chrono::high_resolution_clock::now() };

        // If writing to LDCY I/O register, reset it
        if(address == Const::AddrRegLcdY) memory[address] = 0;
        // If writing to the Timer Divider, it also reset the internal clock!
        else if(address == Const::AddrRegDivider)
        {
            memory[Const::AddrRegInternalClockLow] = 0;
            memory[address] = 0;
        }
        // If written to DMA start a DMA transfer to OAM
        else if(address == Const::AddrRegDma) executeDmaTransfer(value);    
        // If writing to the pad register for setting bit 4 & 5
        // Preserver Lower Bits (= Button pressed atm)
        // 0x30 = 0011 0000
        else if(address == Const::AddrRegInput) 
            memory[Const::AddrRegInput] = (value & 0x30) | (memory[Const::AddrRegInput] & 0xCF);
        // If writing to the lcd status register
        // Preserver Lower two Bits (= current lcd mode (read only))
        // 0x03 = 0000 0011
        // 0x7C = 0111 1100
        else if(address == Const::AddrRegLcdStatus) 
            memory[Const::AddrRegLcdStatus] = (value & 0x7C) | (memory[Const::AddrRegLcdStatus] & 0x03);
        // If writing into this range, change the rom bank in the cartridge
        else if(address >= Const::AddrCartSwitchTriggerStart && address <= Const::AddrCartSwitchTriggerEnd) 
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
        memory[Const::AddrRegDma] = value;
        uint16_t startAddress = value << 8;

        for (int i = 0x0; i <= 0x9F; i++) 
        {
            uint16_t copyFrom = startAddress + i;
            uint16_t copyTo = 0xFE00 + i;

            uint8_t copyValue = read(copyFrom, true);
            rawWrite(copyTo, copyValue);
        }
    }

    bool Mmu::readIORegisterBit(const uint16_t reg, const uint8_t flag, const bool ppuAccess) const 
    { 
        return read(reg, ppuAccess) & flag; 
    }

    void Mmu::writeIORegisterBit(const uint16_t reg, const uint8_t flag, const bool value) 
    { 
        if(value) memory[reg] |= flag; 
        else memory[reg] &= ~flag; 
    }

    Enum::LcdMode Mmu::readLcdMode() const
    {
        return currentPpuMode;
    }

    void Mmu::writeLcdMode(const Enum::LcdMode lcdMode)
    {
        uint8_t lcdModeValue = static_cast<uint8_t>(lcdMode);
        writeIORegisterBit(Const::AddrRegLcdStatus, Const::FlagLcdStatusModeHigh, (lcdModeValue >> 1) & 0x1);
        writeIORegisterBit(Const::AddrRegLcdStatus, Const::FlagLcdStatusModeLow, lcdModeValue & 0x1);
        currentPpuMode = lcdMode;
    }
}