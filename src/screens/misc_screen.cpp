#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include <imgui.h>

#include "misc_screen.h"
#include "../helper/string_helper.h"


MiscScreen::MiscScreen(const Disassembler disassembler) : disassembler(disassembler)
{ }

void MiscScreen::update()
{ 
    ImGui::Begin("Miscellaneous ", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(-1, 288), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(322, 301), ImGuiCond_Always);

    ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None);

    if(ImGui::BeginTabItem("Registers"))
    {
        ImGui::EndTabItem();
    }

    if(ImGui::BeginTabItem("Controls"))
    {
        ImGui::EndTabItem();
    }
    
    if(ImGui::BeginTabItem("Info"))
    {
        ImGui::Text(("Loaded rom: " + disassembler.currentRom.romPath).c_str());
        ImGui::Text(("Parsed Instructions: " + std::to_string(disassembler.getInstructionCount())).c_str());

        static bool showAppMetrics = false;
        if(ImGui::Button("UI Metrics", ImVec2(100, 20))) { showAppMetrics = true; }
        if (showAppMetrics) { ImGui::ShowMetricsWindow(&showAppMetrics); }

        ImGui::EndTabItem();
    }
    
    ImGui::EndTabBar();
    ImGui::End();
}