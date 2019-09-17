#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rom.h"
#include "opengl/window.h"
#include "screens/disassembler_screen.h"
#include "screens/misc_screen.h"

int main(int argc, char** args) {
    if(argc < 2)
    {
        std::cout << "Please enter a rom path as argument!";
        return 0;
    }

    Rom rom(args[1]);

    Window window("Gameboy", 700, 588);
    window.setClearColor(255, 255, 255, 255);
    
    MiscScreen miscScreen(rom);
    DisassemblerScreen disassemblerScreen(rom);

    window.addScreen(&miscScreen);
    window.addScreen(&disassemblerScreen);
    window.startLoop();
}
