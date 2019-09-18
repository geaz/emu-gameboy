#include <string>
#include <sstream>

#include <imgui.h>

#include "memory_screen.h"
#include "../helper/string_helper.h"

MemoryScreen::MemoryScreen(Memory& memory) : memory(memory)
{ }

void MemoryScreen::update()
{ 
    ImGui::Begin("Memory", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar); 
    ImGui::SetWindowPos(ImVec2(320, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(141, 551), ImGuiCond_Always);
    
    ImGui::BeginMenuBar();
    if(ImGui::BeginMenu("Jump"))
    {
        ImGui::MenuItem("Restart and Interrupt Vectors");
        ImGui::MenuItem("Cartridge Header Area");
        ImGui::MenuItem("Cartridge ROM - Bank 0");
        ImGui::MenuItem("Cartridge ROM - Switchable Bank");
        ImGui::MenuItem("Character RAM");
        ImGui::MenuItem("BG Map Data 1");
        ImGui::MenuItem("BG Map Data 2");
        ImGui::MenuItem("Cartridge RAM");
        ImGui::MenuItem("Internal RAM");
        ImGui::MenuItem("Echo RAM");
        ImGui::MenuItem("Object Attribute Memory");
        ImGui::MenuItem("Unusable Memory");
        ImGui::MenuItem("Hardware I/O Registers");
        ImGui::MenuItem("Zero Page - 127 bytes");
        ImGui::MenuItem("Interrupt Enable Flag");
        ImGui::EndMenu();
    }
    ImGui::EndMenuBar();

    ImGuiListClipper clipper(memory.getSize());
    while (clipper.Step())
    {
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        {
            std::stringstream rowLabel;
            rowLabel << StringHelper::IntToHexString(i, 4);
            rowLabel << " | " << StringHelper::IntToHexString(memory.read(i), 2);

            ImGui::Selectable(rowLabel.str().c_str(), false);
        }
    }

    ImGui::End();
}