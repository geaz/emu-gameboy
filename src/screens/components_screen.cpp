#include <string>
#include <sstream>

#include <imgui.h>

#include "components_screen.h"
#include "string_helper.h"

namespace GGB 
{
    bool ShowComponentsScreen = false;

    ComponentsScreen::ComponentsScreen(Debugger& debugger) : debugger(debugger) { }

    void ComponentsScreen::update()
    { 
        if(!GGB::ShowComponentsScreen) return;
        ImGui::Begin("Components", &GGB::ShowComponentsScreen, ImGuiWindowFlags_NoResize); 
        ImGui::SetWindowSize(ImVec2(470, 440), ImGuiCond_Always);
        
        ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None);
        if(ImGui::BeginTabItem("Memory"))
        {
            drawMemoryMap("Memory", memoryToolTips, Const::MemorySize, 
                [this] (uint32_t address) -> uint8_t { return debugger.mmu.read(address, true); });
            ImGui::EndTabItem();
        }
        if(ImGui::BeginTabItem("Cartridge"))
        {
            std::string supported = debugger.cartridge.supported ? "True" : "False";
            ImGui::InputText("Supported", &supported[0], 6, ImGuiInputTextFlags_ReadOnly);
            drawMemoryMap("Cartridge", cartridgeToolTips, debugger.cartridge.cartridgeSize, 
                [this] (uint32_t address) -> uint8_t { return debugger.cartridge.read(address); });
            ImGui::EndTabItem();
        }
        if(ImGui::BeginTabItem("Audio"))
        {      
            ImGui::Checkbox("Channel 1 (Square - Env/Sweep)", &debugger.apu.debugSquare1Enabled);
            ImGui::PushItemWidth(-50);
            ImGui::PlotLines("Left", debugger.square1Left, IM_ARRAYSIZE(debugger.square1Left), NULL, NULL, -1.0f, 1.0f, ImVec2(0,30));
            ImGui::PlotLines("Right", debugger.square1Right, IM_ARRAYSIZE(debugger.square1Right), NULL, NULL, -1.0f, 1.0f, ImVec2(0,30));
            ImGui::PopItemWidth();   

            ImGui::Checkbox("Channel 2 (Square - Env)", &debugger.apu.debugSquare2Enabled);
            ImGui::PushItemWidth(-50);
            ImGui::PlotLines("Left", debugger.square2Left, IM_ARRAYSIZE(debugger.square2Left), NULL, NULL, -1.0f, 1.0f, ImVec2(0,30));
            ImGui::PlotLines("Right", debugger.square2Right, IM_ARRAYSIZE(debugger.square2Right), NULL, NULL, -1.0f, 1.0f, ImVec2(0,30));
            ImGui::PopItemWidth();

            ImGui::Checkbox("Channel 3 (Wave)", &debugger.apu.debugWaveEnabled);
            ImGui::PushItemWidth(-50);
            ImGui::PlotLines("Left", debugger.waveLeft, IM_ARRAYSIZE(debugger.waveLeft), NULL, NULL, -1.0f, 1.0f, ImVec2(0,30));
            ImGui::PlotLines("Right", debugger.waveRight, IM_ARRAYSIZE(debugger.waveRight), NULL, NULL, -1.0f, 1.0f, ImVec2(0,30));
            ImGui::PopItemWidth();

            ImGui::Checkbox("Channel 4 (Noise)", &debugger.apu.debugNoiseEnabled);
            ImGui::PushItemWidth(-50);
            ImGui::PlotLines("Left", debugger.noiseLeft, IM_ARRAYSIZE(debugger.noiseLeft), NULL, NULL, -1.0f, 1.0f, ImVec2(0,30));
            ImGui::PlotLines("Right", debugger.noiseRight, IM_ARRAYSIZE(debugger.noiseRight), NULL, NULL, -1.0f, 1.0f, ImVec2(0,30));
            ImGui::PopItemWidth();

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