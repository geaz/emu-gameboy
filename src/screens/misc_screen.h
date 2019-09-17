#pragma once
#ifndef MISCSCREEN_H
#define MISCSCREEN_H

#include "../opengl/structs.h"
#include "../opengl/screen.h"

#include "../rom.h"

class MiscScreen : public Screen
{   
    public:
        MiscScreen(Rom rom);

        void update() override;

        Rom rom;
};

#endif // MISCSCREEN_H