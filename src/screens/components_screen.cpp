#include <string>
#include <sstream>

#include <imgui.h>

#include "components_screen.h"
#include "../helper/string_helper.h"

ComponentsScreen::ComponentsScreen(Memory& memory) : memory(memory)
{ }

void ComponentsScreen::update()
{ 
    ImGui::Begin("Components", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(480, -1), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(301, 490), ImGuiCond_Always);
    
    ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None);
    if(ImGui::BeginTabItem("Memory"))
    {
        ImGui::Button("Jump To");
        if (ImGui::BeginPopupContextItem("jump_context_menu", 0))
        {
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::Selectable("Set to zero");
            ImGui::EndPopup();
        }

        ImGui::BeginChild("memory_child");
        ImGuiListClipper clipper(memory.getSize() / 10);
        while (clipper.Step())
        {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            {             
                ImGui::Text((StringHelper::IntToHexString((i * 10), 4, false) + " |").c_str());                 
                for(int j = 0; j < 10; j++)
                {
                    ImGui::SameLine(); 
                    ImGui::Text(StringHelper::IntToHexString(memory.read((i * 10) + j), 2, false).c_str());
                    if(ImGui::IsItemHovered())
                    {                        
                        auto pos = ImGui::GetItemRectMin();
                        pos.x -= 4; pos.y -= 4;
                        ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + 24, pos.y + 24), IM_COL32(150, 150, 150, 100));
                    }
                }
            }
        }
        ImGui::EndChild();
        ImGui::EndTabItem();
    }
    if(ImGui::BeginTabItem("Cartridge"))
    {
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
    

    /*ImGui::BeginMenuBar();
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
    ImGui::EndMenuBar();*/

    

    ImGui::End();
}