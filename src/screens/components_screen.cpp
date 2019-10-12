#include <string>
#include <sstream>

#include <imgui.h>

#include "components_screen.hpp"
#include "string_helper.hpp"

namespace GGB 
{
    bool ShowComponentsScreen = false;

    ComponentsScreen::ComponentsScreen(Hardware::Cartridge& cartridge, Hardware::Mmu& mmu)
        : cartridge(cartridge), mmu(mmu) { }

    void ComponentsScreen::update()
    { 
        if(!GGB::ShowComponentsScreen) return;
        ImGui::Begin("Components", &GGB::ShowComponentsScreen, ImGuiWindowFlags_NoResize); 
        ImGui::SetWindowSize(ImVec2(470, 440), ImGuiCond_Always);
        
        ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None);
        
        if(ImGui::BeginTabItem("Memory"))
        {
            drawMemoryMap("Memory", memoryToolTips, Const::MemorySize, 
                [this] (uint32_t address) -> uint8_t { return mmu.read(address, true); });
            ImGui::EndTabItem();
        }      
        if(ImGui::BeginTabItem("Cartridge"))
        {
            std::string supported = cartridge.supported ? "True" : "False";
            ImGui::InputText("Supported", &supported[0], 6, ImGuiInputTextFlags_ReadOnly);
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
                    std::string label = val + " (" + Helper::IntToHexString(key) + ")";
                    if(ImGui::MenuItem(label.c_str())) scroll_to_value = key;
                }
                ImGui::EndPopup();
            }
        }    

        if(ImGui::BeginChild((title + "memory_child").c_str()))
        {
            int remaining = memorySize % 16;
            ImGuiListClipper clipper(memorySize / 16 + (remaining > 0 ? 1 : 0));
            while (clipper.Step())
            {
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                {             
                    ImGui::Text((Helper::IntToHexString((i * 16), 4, false) + " |").c_str()); 
                    
                    int bound = remaining > 0 && i == clipper.ItemsCount ? remaining : 16;                
                    for(int j = 0; j < bound; j++)
                    {
                        ImGui::SameLine(); 
                        ImGui::Text(Helper::IntToHexString(memoryReadFunc((i * 16) + j), 2, false).c_str());
                        if(ImGui::IsItemHovered())
                        {                        
                            ImVec2 pos = ImGui::GetItemRectMin();
                            pos.x -= 4; pos.y -= 4;
                            ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + 24, pos.y + 24), IM_COL32(150, 150, 150, 100));

                            std::string tooltip = Helper::IntToHexString((i * 16) + j);
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
                    int scroll_px = 20 * (scroll_to_value / 16 + (scroll_to_value % 16 > 0 ? 1 : 0));
                    ImGui::SetScrollFromPosY(ImGui::GetCursorStartPos().y + scroll_px);
                    scroll_to_value = -1;
                }
            }
            ImGui::EndChild();        
        }   
    }
}