#pragma once
#ifndef CARTRIDGESCREEN_H
#define CARTRIDGESCREEN_H

#include "../opengl/screen.h"

#include "../hardware/cartridge.h"

class CartridgeScreen : public Screen
{   
    public:
        CartridgeScreen(Cartridge& cartridge);

        void update() override;

        Cartridge& cartridge;
};

#endif // CARTRIDGESCREEN_H