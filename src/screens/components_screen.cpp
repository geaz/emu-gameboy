#include <string>
#include <sstream>

#include <imgui.h>

#include "components_screen.h"
#include "../helper/string_helper.h"

ComponentsScreen::ComponentsScreen(Mmu& mmu, Cartridge& cartridge) 
    : mmu(mmu), cartridge(cartridge) { }

void ComponentsScreen::update()
{ 
    ImGui::Begin("Components", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(480, -1), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(331, 490), ImGuiCond_Always);
    
    ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None);
    if(ImGui::BeginTabItem("Memory"))
    {
        drawMemoryMap("Memory", memoryToolTips, mmu.getSize(), 
            [this] (uint32_t address) -> uint8_t { return mmu.read(address, true); });
        ImGui::EndTabItem();
    }
    if(ImGui::BeginTabItem("Cartridge"))
    {
        drawMemoryMap("Cartridge", cartridgeToolTips, cartridge.cartridgeSize, 
            [this] (uint32_t address) -> uint8_t { return cartridge.read(address); });
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
    ImGui::End();
}

void ComponentsScreen::drawMemoryMap(
            const std::string title, 
            const std::map<uint16_t, std::string> toolTipMap,
            uint32_t memorySize,
            std::function<uint8_t (uint32_t)> memoryReadFunc)
{
    int scroll_to_value = -1;

    if(toolTipMap.size() > 0)
    {
        ImGui::Button((title + " Map").c_str());
        if (ImGui::BeginPopupContextItem((title + "jump_context_menu").c_str(), 0))
        {
            for(auto const& [key, val] : toolTipMap)
            {
                std::string label = val + " (" + StringHelper::IntToHexString(key) + ")";
                if(ImGui::MenuItem(label.c_str())) scroll_to_value = key;
            }
            ImGui::EndPopup();
        }
    }    

    if(ImGui::BeginChild((title + "memory_child").c_str()))
    {
        int remaining = memorySize % 10;
        ImGuiListClipper clipper(memorySize / 10 + (remaining > 0 ? 1 : 0));
        while (clipper.Step())
        {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            {             
                ImGui::Text((StringHelper::IntToHexString((i * 10), 4, false) + " |").c_str()); 
                
                int bound = remaining > 0 && i == clipper.ItemsCount ? remaining : 10;                
                for(int j = 0; j < bound; j++)
                {
                    ImGui::SameLine(); 
                    ImGui::Text(StringHelper::IntToHexString(memoryReadFunc((i * 10) + j), 2, false).c_str());
                    if(ImGui::IsItemHovered())
                    {                        
                        ImVec2 pos = ImGui::GetItemRectMin();
                        pos.x -= 4; pos.y -= 4;
                        ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + 24, pos.y + 24), IM_COL32(150, 150, 150, 100));

                        std::string tooltip = StringHelper::IntToHexString((i * 10) + j);
                        if(toolTipMap.find((i * 10) + j) != toolTipMap.end())
                        {
                            tooltip += '\n' + toolTipMap.at((i * 10) + j);
                        }
                        ImGui::SetTooltip(tooltip.c_str());                                                       
                    }
                }
            }
            if(scroll_to_value != -1)
            {
                // Line Height = 20 px
                int scroll_px = 20 * (scroll_to_value / 10 + (scroll_to_value % 10 > 0 ? 1 : 0));
                ImGui::SetScrollFromPosY(ImGui::GetCursorStartPos().y + scroll_px);
                scroll_to_value = -1;
            }
        }
        ImGui::EndChild();        
    }   
}