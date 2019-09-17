#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include <imgui.h>

#include "disassembler_screen.h"
#include "../helper/string_helper.h"

DisassemblerScreen::DisassemblerScreen(Rom rom) : rom(rom)
{     
    disassembler.parseRom(rom);
}

void DisassemblerScreen::update()
{ 
    ImGui::Begin("Disassembly (Instructions only)", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(320, -1), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(381, 590), ImGuiCond_Always);

    ImGuiListClipper clipper(disassembler.parsedInstructions.size());
    while (clipper.Step())
    {
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        {
            ParsedInstruction parsedInstruction = disassembler.parsedInstructions[i];

            std::stringstream rowLabel;
            rowLabel << "(" << StringHelper::Pad(std::to_string(parsedInstruction.number), 4, '0') << ") ";
            rowLabel << StringHelper::Pad(std::to_string(parsedInstruction.bytePosition), 4, '0');
            
            if(parsedInstruction.definition.length == 1)
            {
                rowLabel << " | " << StringHelper::IntToHexString(parsedInstruction.bytes, 2, false) << "      ";
            }
            else if(parsedInstruction.definition.length == 2)
            {
                rowLabel << " | " << StringHelper::IntToHexString((parsedInstruction.bytes & 0xFF00) >> 8, 2, false);
                rowLabel << " " << StringHelper::IntToHexString(parsedInstruction.bytes & 0x00FF, 2, false) << "   ";
            }
            else if(parsedInstruction.definition.length == 3)
            {
                rowLabel << " | " << StringHelper::IntToHexString((parsedInstruction.bytes & 0xFF0000) >> 16, 2, false);
                rowLabel << " " << StringHelper::IntToHexString((parsedInstruction.bytes & 0x00FF00) >> 8, 2, false);
                rowLabel << " " << StringHelper::IntToHexString(parsedInstruction.bytes & 0x0000FF, 2, false);
            }

            rowLabel << " | " << parsedInstruction.definition.getMnemonic(parsedInstruction.bytes);

            ImGui::Selectable(rowLabel.str().c_str(), false);
        }
    }

    ImGui::End();
}