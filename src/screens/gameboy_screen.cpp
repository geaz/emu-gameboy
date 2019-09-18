#include "gameboy_screen.h"

GameboyScreen::GameboyScreen(Gameboy& gameboy) : gameboy(gameboy)
{ }

void GameboyScreen::update()
{
    gameboy.process();
}