#pragma once
#ifndef GAMEBOYSCREEN_H
#define GAMEBOYSCREEN_H

#include "../opengl/screen.h"
#include "../hardware/gameboy.h"

class GameboyScreen : public Screen
{
    public:
        GameboyScreen(Gameboy& gameboy);

        void update() override;

    private:
        Gameboy& gameboy;
};

#endif // GAMEBOYSCREEN_H