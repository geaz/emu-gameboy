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

    GGB::Hardware::Cartridge cartridge(args[1]);
    GGB::GameBoy gameBoy(cartridge);

    OpenGL::Window window("GGB", 
        GGB::Constants::GAMEBOY_LCD_WIDTH * 2, 
        GGB::Constants::GAMEBOY_LCD_HEIGHT * 2);
        
    GGB::DebugScreen debugScreen(gameBoy.debugger);
    GGB::ComponentsScreen componentsScreen(gameBoy.debugger); 
    GGB::GameBoyScreen gameBoyScreen(gameBoy);   

    window.addScreen(&debugScreen);
    window.addScreen(&componentsScreen);
    window.addScreen(&gameBoyScreen);
    window.startLoop();
}
