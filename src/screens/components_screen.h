#pragma once
#ifndef COMPONENTSSCREEN_H
#define COMPONENTSSCREEN_H

#include <map>
#include <functional>

#include "../opengl/screen.h"
#include "../hardware/memory/mmu.h"

class ComponentsScreen : public Screen
{   
    public:
        ComponentsScreen(Mmu& mmu, Cartridge& cartridge);

        void update() override;

        Mmu& mmu;
        Cartridge& cartridge;

    private:
        void drawMemoryMap(
            const std::string title, 
            const std::map<uint16_t, std::string> toolTipMap,
            const uint32_t memorySize,
            std::function<uint8_t (uint32_t)> memoryReadFunc);

        std::map<uint16_t, std::string> memoryToolTips = {
            { 0x0000, "Cartridge Bank 0 Start" },
            { 0x4000, "Cartridge Bank Switchable" },
            { 0x8000, "Video RAM Start" },
            { 0xA000, "External RAM Start" },
            { 0xC000, "Work RAM 0 Start" },
            { 0xD000, "Work RAM 1 Start" },
            { 0xE000, "Mirror Start" },
            { 0xFE00, "OAM (Sprites) Start" },            
            { 0xFF00, "I/O Registers Start" },
            { 0xFFFF, "Interrupt Enabled Flag" }
        };
        std::map<uint16_t, std::string> cartridgeToolTips = {
             { 0x0100, "Cartridge Bank 0 Start" }
        };
};

#endif // COMPONENTSSCREEN_H