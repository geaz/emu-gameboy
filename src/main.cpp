#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opengl/window.h"
#include "hardware/gameboy.h"
#include "hardware/cartridge.h"
#include "screens/misc_screen.h"
#include "screens/cpu_screen.h"
#include "screens/cartridge_screen.h"
#include "screens/gameboy_screen.h"

int main(int argc, char** args) {
    if(argc < 2)
    {
        std::cout << "Please enter a rom path as argument!";
        return 0;
    }

    Cartridge cartridge(args[1]);
    Gameboy gameboy(cartridge);

    Window window("Gameboy", 680, 548);
    window.setClearColor(224, 248, 208, 255);
    
    MiscScreen miscScreen;
    CpuScreen cpuScreen(gameboy.cpu);
    CartridgeScreen cartridgeScreen(gameboy.cartridge); 
    GameboyScreen gameboyScreen(gameboy);   

    window.addScreen(&miscScreen);
    window.addScreen(&cartridgeScreen);
    window.addScreen(&cpuScreen);
    window.addScreen(&gameboyScreen);
    window.startLoop();
}
