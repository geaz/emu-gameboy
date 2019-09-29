#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opengl/window.h"
#include "hardware/gameboy.h"
#include "hardware/cartridge.h"
#include "screens/cpu_screen.h"
#include "screens/instruction_screen.h"
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

    Window window("Gameboy", 810, 488); // Gameboy Display: 160x144
    window.setClearColor(255, 255, 255, 255);
    
    CpuScreen cpuScreen(gameboy.cpu);
    GameboyScreen gameboyScreen(gameboy);   
    ComponentsScreen componentsScreen(gameboy.mmu, cartridge); 
    InstructionScreen instructionScreen(gameboy.cpu);

    window.addScreen(&componentsScreen);
    window.addScreen(&cpuScreen);
    window.addScreen(&gameboyScreen);
    window.addScreen(&instructionScreen);
    window.startLoop();
}
