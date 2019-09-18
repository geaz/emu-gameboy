#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include <imgui.h>

#include "misc_screen.h"
#include "../helper/string_helper.h"


MiscScreen::MiscScreen()
{ }

void MiscScreen::update()
{ 
    ImGui::Begin("Miscellaneous ", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(0, 288), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(321, 261), ImGuiCond_Always);

    //ImGui::Text(("Loaded rom: " + disassembler.currentRom.romPath).c_str());
    //ImGui::Text(("Parsed Instructions: " + std::to_string(disassembler.getInstructionCount())).c_str());

    static bool showAppMetrics = false;
    if(ImGui::Button("UI Metrics", ImVec2(100, 20))) { showAppMetrics = true; }
    if (showAppMetrics) { ImGui::ShowMetricsWindow(&showAppMetrics); }
    
    ImGui::End();
}