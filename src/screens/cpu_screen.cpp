#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include <imgui.h>

#include "cpu_screen.h"
#include "../helper/string_helper.h"

CpuScreen::CpuScreen(Cpu& cpu) : cpu(cpu)
{ }

void CpuScreen::update()
{ 
    ImGui::Begin("Cpu", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(460, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(221, 551), ImGuiCond_Always);

    ImGui::Text("General");
    ImGui::Separator();

    ImGui::Text("State:");
    ImGui::SameLine(); 
    if(cpu.state == RUNNING) ImGui::TextColored(ImVec4(0.00f, 0.42f, 1.00f, 1.00f), "RUNNING");
    else if(cpu.state == PAUSED) ImGui::TextColored(ImVec4(1.00f, 0.48f, 0.00f, 1.00f), "PAUSED");
    else if(cpu.state == INTERRUPT) ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.97f, 1.00f), "INTERRUPT");
    else if(cpu.state == ERROR) ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.00f, 1.00f), "ERROR");

    ImGui::Text("Next:");
    ImGui::SameLine(); ImGui::Text(cpu.nextInstruction.definition.mnemonic.c_str());
    ImGui::Text("Processed:");
    ImGui::SameLine(); ImGui::Text(cpu.currentInstruction.definition.mnemonic.c_str());
    ImGui::Dummy(ImVec2(0.0f, 5.0f));

    if(cpu.state == PAUSED)
    {
        if(ImGui::Button("Play")) cpu.state = RUNNING;
        ImGui::SameLine(); 
        ImGui::Button("Next");
    }
    else if(cpu.state == RUNNING || cpu.state == INTERRUPT)
    {
        if(ImGui::Button("Pause")) cpu.state = PAUSED;
    }
    else if(cpu.state == ERROR)
    {
        ImGui::Button("Reset");
    }
    ImGui::Dummy(ImVec2(0.0f, 20.0f));

    ImGui::Text("Flags");
    ImGui::Separator();    
    ImGui::Dummy(ImVec2(0.0f, 5.0f));

    static int fz = (int)cpu.f.getBit(7);
    static int fn = (int)cpu.f.getBit(6);
    static int fh = (int)cpu.f.getBit(5);
    static int fc = (int)cpu.f.getBit(4);
    ImGui::InputInt("Z", &fz, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("N", &fn, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("H", &fh, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("C", &fc, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
    ImGui::Dummy(ImVec2(0.0f, 20.0f));

    ImGui::Text("Registers");
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 5.0f));  

    static std::string sp = StringHelper::IntToHexString(cpu.sp.get());
    static std::string pc = StringHelper::IntToHexString(cpu.pc.get());
    ImGui::InputText("SP", &sp[0], 6, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputText("PC", &pc[0], 6, ImGuiInputTextFlags_ReadOnly);
    
    ImGui::Columns(2, "registers0", false);
    static std::string a = StringHelper::IntToHexString(cpu.a.get());
    static std::string f = StringHelper::IntToHexString(cpu.f.get());
    ImGui::InputText("A", &a[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::InputText("F", &f[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();

    static std::string b = StringHelper::IntToHexString(cpu.b.get());
    static std::string c = StringHelper::IntToHexString(cpu.c.get());
    ImGui::InputText("B", &b[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::InputText("C", &c[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();

    static std::string d = StringHelper::IntToHexString(cpu.d.get());
    static std::string e = StringHelper::IntToHexString(cpu.e.get());
    ImGui::InputText("D", &d[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::InputText("E", &e[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();

    static std::string h = StringHelper::IntToHexString(cpu.h.get());
    static std::string l = StringHelper::IntToHexString(cpu.l.get());
    ImGui::InputText("H", &h[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::InputText("L", &l[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::Columns(1);

    ImGui::End();
}