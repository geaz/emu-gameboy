#pragma once
#ifndef GAMEBOYSCREEN_H
#define GAMEBOYSCREEN_H

#include "../opengl/screen.h"
#include "../opengl/resource_manager.h"
#include "../hardware/gameboy.h"

class GameboyScreen : public Screen
{
    public:
        GameboyScreen(Gameboy& gameboy);

        void update() override;
        void handleKeys(const int key, const int scancode, const int action, const int mods) override;

    private:
        Gameboy& gameboy;
        Shader textureShader;
        unsigned int VBO, VAO, EBO, texture;
        
        uint32_t colorBlack = ((0x2D << 24) |(0x1B << 16) | (0x0 << 8) | (0xFF << 0));
        uint32_t colorWhite = ((0xC4 << 24) |(0xF0 << 16) | (0xC2 << 8) | (0xFF << 0));
        uint32_t colorDarkGray = ((0x1E << 24) |(0x60 << 16) | (0x6E << 8) | (0xFF << 0));
        uint32_t colorLightGray = ((0x5A << 24) |(0xB9 << 16) | (0xA8 << 8) | (0xFF << 0));
        uint32_t colorTransparent = ((0x00 << 24) |(0x00 << 16) | (0x00 << 8) | (0x00 << 0));

        void renderBackground();
};

#endif // GAMEBOYSCREEN_H