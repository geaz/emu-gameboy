#include <string>
#include <sstream>

#include <imgui.h>

#include "cartridge_screen.h"
#include "../helper/string_helper.h"

CartridgeScreen::CartridgeScreen(Cartridge& cartridge) : cartridge(cartridge)
{ }

void CartridgeScreen::update()
{ 
    ImGui::Begin("Cartridge", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(320, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(141, 551), ImGuiCond_Always);

    ImGuiListClipper clipper(cartridge.cartridgeSize);
    while (clipper.Step())
    {
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        {
            std::stringstream rowLabel;
            rowLabel << StringHelper::IntToHexString(i, 4);
            rowLabel << " | " << StringHelper::IntToHexString((unsigned char) cartridge.cartridgeData[i], 2);

            ImGui::Selectable(rowLabel.str().c_str(), false);
        }
    }

    ImGui::End();
}