#include <string>
#include <sstream>

#include <imgui.h>

#include "rom_screen.h"
#include "../helper/string_helper.h"

RomScreen::RomScreen(const Rom rom) : rom(rom)
{ }

void RomScreen::update()
{ 
    ImGui::Begin("Rom", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(320, -1), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(140, 590), ImGuiCond_Always);

    ImGuiListClipper clipper(rom.romSize);
    while (clipper.Step())
    {
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        {
            std::stringstream rowLabel;
            rowLabel << StringHelper::Pad(std::to_string(i), 6, '0');
            rowLabel << " | " << StringHelper::IntToHexString((unsigned char) rom.romData[i], 2);

            ImGui::Selectable(rowLabel.str().c_str(), false);
        }
    }

    ImGui::End();
}