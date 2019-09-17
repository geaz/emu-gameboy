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
    Disassembler disassembler;
    disassembler.parseRom(rom);

    Window window("Gameboy", 740, 588);
    window.setClearColor(224, 248, 208, 255);
    
    MiscScreen miscScreen(disassembler);
    DisassemblerScreen disassemblerScreen(disassembler);

    window.addScreen(&miscScreen);
    window.addScreen(&disassemblerScreen);
    window.startLoop();
}
