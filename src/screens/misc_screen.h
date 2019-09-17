#pragma once
#ifndef MISCSCREEN_H
#define MISCSCREEN_H

#include "../opengl/structs.h"
#include "../opengl/screen.h"

#include "../disassembler.h"
#include "../rom.h"

class MiscScreen : public Screen
{   
    public:
        MiscScreen(const Disassembler disassembler);

        void update() override;

        Disassembler disassembler;
};

#endif // MISCSCREEN_H