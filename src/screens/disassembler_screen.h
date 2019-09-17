#pragma once
#ifndef DISASSEMBLERSCREEN_H
#define DISASSEMBLERSCREEN_H

#include "../opengl/structs.h"
#include "../opengl/screen.h"

#include "../disassembler.h"
#include "../rom.h"

class DisassemblerScreen : public Screen
{   
    public:
        DisassemblerScreen(Rom rom);

        void update() override;

        Rom rom;
        Disassembler disassembler;

    private:        
        Color offBlack = { 50, 50, 50, 255 };
        Color gray = { 160, 160, 160, 255 };
        Color blue = { 17, 90, 198, 255 };
        Color orange = { 255, 165, 0, 255};
        Color red = { 255, 0, 0, 255 };
};

#endif // DISASSEMBLERSCREEN_H