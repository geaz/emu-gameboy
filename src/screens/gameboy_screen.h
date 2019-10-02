#pragma once
#ifndef GAMEBOYSCREEN_H
#define GAMEBOYSCREEN_H

#include "../opengl/screen.h"
#include "../opengl/resource_manager.h"
#include "../hardware/gameboy.h"

namespace GGB
{
    /**
     * The GameBoyScreen emulates the display of the Game Boy and is
     * responsible for the update of the CPU by calling the 'cycle' method
     * of the Game Boy.
     **/
    class GameBoyScreen : public OpenGL::Screen
    {
        public:
            GameBoyScreen(GameBoy& gameBoy);

            void update() override;
            void handleKeys(const int key, const int scancode, const int action, const int mods) override;

        private:
            void renderBackground();
            void renderSprites();
            void renderTexture(GLuint* data);

            GameBoy& gameBoy;
            OpenGL::Shader textureShader;
            unsigned int VBO, VAO, EBO, texture;
            
            uint32_t glColorBlack = ((0x2D << 24) |(0x1B << 16) | (0x0 << 8) | (0xFF << 0));
            uint32_t glColorWhite = ((0xC4 << 24) |(0xF0 << 16) | (0xC2 << 8) | (0xFF << 0));
            uint32_t glColorDarkGray = ((0x1E << 24) |(0x60 << 16) | (0x6E << 8) | (0xFF << 0));
            uint32_t glColorLightGray = ((0x5A << 24) |(0xB9 << 16) | (0xA8 << 8) | (0xFF << 0));
            uint32_t glColorTransparent = ((0x00 << 24) |(0x00 << 16) | (0x00 << 8) | (0x00 << 0));
    };
}

#endif // GAMEBOYSCREEN_H