#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opengl/window.hpp"
#include "hardware/gameboy.hpp"
#include "hardware/cartridge.hpp"
#include "screens/debug_screen.hpp"
#include "screens/components_screen.hpp"
#include "screens/gameboy_screen.hpp"

int main(int argc, char** args) {
    if(argc < 2)
    {
        std::cout << "Please enter a rom path as argument!";
        return 0;
    }

    GGB::Hardware::Cartridge cartridge(args[1]);
    GGB::GameBoy gameBoy(cartridge);

    OpenGL::Window window("GGB", 
        GGB::Const::LcdWidth * 2, 
        GGB::Const::LcdHeight * 2);
        
    GGB::DebugScreen debugScreen(gameBoy.cpu);
    GGB::ComponentsScreen componentsScreen(gameBoy.cartridge, gameBoy.mmu); 
    GGB::GameBoyScreen gameBoyScreen(gameBoy);   

    window.addScreen(&debugScreen);
    window.addScreen(&componentsScreen);
    window.addScreen(&gameBoyScreen);
    window.startLoop();
}
