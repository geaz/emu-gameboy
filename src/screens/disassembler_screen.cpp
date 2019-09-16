#include <string>
#include <iomanip>
#include <algorithm>

#include "disassembler_screen.h"
#include "../helper/string_helper.h"
#include "../opengl/widgets/rect.h"
DisassemblerScreen::DisassemblerScreen(int row, int column, Rom rom) : Screen(row, column)
{     
    disassembler.parseRom(rom);

    textWidget = new TextWidget("Minecraft", "Minecraft.ttf", 5, 20);    
    addWidget(textWidget);
}

void DisassemblerScreen::update()
{ 
    ParsedInstruction currentInstruction = disassembler.currentInstruction;

    textWidget->setText("(" + std::to_string(currentInstruction.number) + ")     " + std::to_string(currentInstruction.bytePosition) + "    " + StringHelper::IntToHexString(currentInstruction.bytes, 2, false) + "    " + currentInstruction.definition.getMnemonic(currentInstruction.bytes));
}