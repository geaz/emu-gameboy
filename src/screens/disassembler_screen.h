#pragma once
#ifndef DISASSEMBLERSCREEN_H
#define DISASSEMBLERSCREEN_H

#include "../opengl/screen.h"

#include "../disassembler.h"
#include "../rom.h"

class DisassemblerScreen : public Screen
{   
    public:
        DisassemblerScreen(const Disassembler disassembler);

        void update() override;

        Disassembler disassembler;
};

#endif // DISASSEMBLERSCREEN_H