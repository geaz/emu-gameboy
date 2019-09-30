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
        
        void renderBackground();
};

#endif // GAMEBOYSCREEN_H