#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opengl/window.h"
#include "hardware/gameboy.h"
#include "hardware/cartridge.h"
#include "screens/debug_screen.h"
#include "screens/components_screen.h"
#include "screens/gameboy_screen.h"

int main(int argc, char** args) {
    if(argc < 2)
    {
        std::cout << "Please enter a rom path as argument!";
        return 0;
    }

    Cartridge cartridge(args[1]);
    Gameboy gameboy(cartridge);

    Window window("Gameboy", 
        gameboy.DISPLAY_WIDTH * 2, 
        (gameboy.DISPLAY_HEIGHT * 2)); // Gameboy Display: 160x144, Window Size: 2xDisplay
    window.setClearColor(255, 255, 255, 255);
    
    DebugScreen debugScreen(gameboy.cpu);
    GameboyScreen gameboyScreen(gameboy);   
    ComponentsScreen componentsScreen(gameboy.mmu, cartridge); 

    window.addScreen(&componentsScreen);
    window.addScreen(&debugScreen);
    window.addScreen(&gameboyScreen);
    window.startLoop();
}
