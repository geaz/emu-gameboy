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

    private:
        Gameboy& gameboy;
        Shader pixelShader;
        unsigned int VBO, VAO, EBO;

        void updateDisplay();
        void drawPixelAt(const int x, const int y);
        void drawRect(float vertices[], unsigned int indices[], int sizeofVertices, int sizeofIndices);
};

#endif // GAMEBOYSCREEN_H