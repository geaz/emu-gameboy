#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "string_helper.h"
#include "debug_screen.h"
#include "components_screen.h"

namespace GGB
{
    bool ShowDebugScreen = false;
    bool ShowAppMetrics = false;
    
    DebugScreen::DebugScreen(Debugger& debugger) : debugger(debugger) { }

    void DebugScreen::handleKeys(const int key, const int scancode, const int action, const int mods) 
    {
        using Enum::CpuState;
        if(key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT)) debugger.cpu.state = CpuState::STEP;
        if(key == GLFW_KEY_P && action == GLFW_PRESS) debugger.cpu.state = debugger.cpu.state == CpuState::PAUSED ? CpuState::RUNNING : CpuState::PAUSED;
    }

    void DebugScreen::update()
    { 
        using Enum::CpuState;
        using Enum::CpuFlag;

        if(!GGB::ShowDebugScreen) return;
        ImGui::Begin("Debugger", &GGB::ShowDebugScreen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar); 
        ImGui::SetWindowSize(ImVec2(275, 440), ImGuiCond_Always);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Show"))
            {
                if (ImGui::MenuItem("Components")) GGB::ShowComponentsScreen = !GGB::ShowComponentsScreen;
                if (ImGui::MenuItem("App Metrics")) ShowAppMetrics = !ShowAppMetrics ;
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        if (ShowAppMetrics) ImGui::ShowMetricsWindow(&ShowAppMetrics);

        ImGui::Text("CPU:");
        ImGui::SameLine(); 
        if(debugger.cpu.state == CpuState::RUNNING) ImGui::TextColored(ImVec4(0.00f, 0.42f, 1.00f, 1.00f), "RUNNING");
        else if(debugger.cpu.state == CpuState::PAUSED) ImGui::TextColored(ImVec4(1.00f, 0.48f, 0.00f, 1.00f), "PAUSED");
        else if(debugger.cpu.state == CpuState::INTERRUPT) ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.97f, 1.00f), "INTERRUPT");
        else if(debugger.cpu.state == CpuState::ERROR) ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.00f, 1.00f), "ERROR");
        ImGui::Dummy(ImVec2(0.0f, 5.0f));

        ImGui::Text("Next Instruction:");
        Hardware::Instructions::ParsedInstruction parsedInstruction = debugger.cpu.nextInstruction;
        ImGui::Text((Helper::IntToHexString(parsedInstruction.bytePosition) + ": ").c_str());
        
        std::stringstream rowLabel;
        if(parsedInstruction.definition.length == 1)
        {
            rowLabel << Helper::IntToHexString(parsedInstruction.parsedBytes.opcode, 2, false) << "      ";
        }
        else if(parsedInstruction.definition.length == 2)
        {
            rowLabel << Helper::IntToHexString((parsedInstruction.parsedBytes.opcode), 2, false);
            rowLabel << " " << Helper::IntToHexString(parsedInstruction.parsedBytes.low, 2, false) << "   ";
        }
        else if(parsedInstruction.definition.length == 3)
        {
            rowLabel << Helper::IntToHexString((parsedInstruction.parsedBytes.opcode), 2, false);
            rowLabel << " " << Helper::IntToHexString(parsedInstruction.parsedBytes.low, 2, false);
            rowLabel << " " << Helper::IntToHexString(parsedInstruction.parsedBytes.high, 2, false);
        }
        rowLabel << " | " << parsedInstruction.definition.mnemonic;

        ImGui::SameLine();
        ImGui::Text(rowLabel.str().c_str());
        ImGui::Dummy(ImVec2(0.0f, 5.0f));

        if(debugger.cpu.state == CpuState::PAUSED)
        {
            if(ImGui::Button("Play")) debugger.cpu.state = CpuState::RUNNING;
            ImGui::SameLine(); 
            if(ImGui::Button("Next")) debugger.cpu.state = CpuState::STEP;
        }
        else if(debugger.cpu.state == CpuState::RUNNING || debugger.cpu.state == CpuState::INTERRUPT)
        {
            if(ImGui::Button("Pause")) debugger.cpu.state = CpuState::PAUSED;
        }
        else if(debugger.cpu.state == CpuState::ERROR)
        {
            ImGui::Button("Reset");
        }
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        ImGui::Text("Flags");
        ImGui::Separator();    
        ImGui::Dummy(ImVec2(0.0f, 5.0f));

        ImGui::PushItemWidth(-15);
        int fz = (int)debugger.cpu.f.readBit((uint8_t)CpuFlag::Z_ZERO);
        int fn = (int)debugger.cpu.f.readBit((uint8_t)CpuFlag::N_SUBSTRACT);
        int fh = (int)debugger.cpu.f.readBit((uint8_t)CpuFlag::H_HALFCARRY);
        int fc = (int)debugger.cpu.f.readBit((uint8_t)CpuFlag::C_CARRY);

        ImGui::Columns(4, "flags0", false);
        ImGui::InputInt("Z", &fz, NULL, NULL, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::InputInt("N", &fn, NULL, NULL, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::InputInt("H", &fh, NULL, NULL, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::InputInt("C", &fc, NULL, NULL, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::Columns(1);    
        ImGui::PopItemWidth();
        ImGui::Dummy(ImVec2(0.0f, 5.0f));

        ImGui::Text("Registers");
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 5.0f));  
        
        ImGui::PushItemWidth(-25);
        ImGui::Columns(2, "registers0", false);
        std::string sp = Helper::IntToHexString(debugger.cpu.sp.read());
        std::string pc = Helper::IntToHexString(debugger.cpu.pc.read());
        ImGui::InputText("SP", &sp[0], 6, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::InputText("PC", &pc[0], 6, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::Columns(1); 
        ImGui::PopItemWidth();
        
        ImGui::PushItemWidth(-15);
        ImGui::Columns(2, "registers1", false);
        std::string a = Helper::IntToHexString(debugger.cpu.a.read(), 2);
        std::string f = Helper::IntToHexString(debugger.cpu.f.read(), 2);
        ImGui::InputText("A", &a[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::InputText("F", &f[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();

        std::string b = Helper::IntToHexString(debugger.cpu.b.read(), 2);
        std::string c = Helper::IntToHexString(debugger.cpu.c.read(), 2);
        ImGui::InputText("B", &b[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::InputText("C", &c[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();

        std::string d = Helper::IntToHexString(debugger.cpu.d.read(), 2);
        std::string e = Helper::IntToHexString(debugger.cpu.e.read(), 2);
        ImGui::InputText("D", &d[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::InputText("E", &e[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();

        std::string h = Helper::IntToHexString(debugger.cpu.h.read(), 2);
        std::string l = Helper::IntToHexString(debugger.cpu.l.read(), 2);
        ImGui::InputText("H", &h[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::InputText("L", &l[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
        ImGui::Columns(1);    
        ImGui::PopItemWidth();

        ImGui::End();
    }
}