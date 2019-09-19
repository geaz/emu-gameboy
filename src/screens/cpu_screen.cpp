#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "cpu_screen.h"
#include "../helper/string_helper.h"

CpuScreen::CpuScreen(Cpu& cpu) : cpu(cpu)
{ }

void CpuScreen::handleKeys(const int key, const int scancode, const int action, const int mods) 
{
    if(key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        cpu.state = STEP;
    }
}

void CpuScreen::update()
{ 
    ImGui::Begin("Cpu", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(320, -1), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(161, 490), ImGuiCond_Always);

    ImGui::Text("General");
    ImGui::Separator();

    ImGui::Text("State:");
    ImGui::SameLine(); 
    if(cpu.state == RUNNING) ImGui::TextColored(ImVec4(0.00f, 0.42f, 1.00f, 1.00f), "RUNNING");
    else if(cpu.state == PAUSED) ImGui::TextColored(ImVec4(1.00f, 0.48f, 0.00f, 1.00f), "PAUSED");
    else if(cpu.state == INTERRUPT) ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.97f, 1.00f), "INTERRUPT");
    else if(cpu.state == ERROR) ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.00f, 1.00f), "ERROR");
    ImGui::Dummy(ImVec2(0.0f, 5.0f));

    if(cpu.state == PAUSED)
    {
        if(ImGui::Button("Play")) cpu.state = RUNNING;
        ImGui::SameLine(); 
        if(ImGui::Button("Next")) cpu.state = STEP;
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

    ImGui::PushItemWidth(-15);
    int fz = (int)cpu.getFlag(Z_ZERO);
    int fn = (int)cpu.getFlag(N_SUBSTRACT);
    int fh = (int)cpu.getFlag(H_HALFCARRY);
    int fc = (int)cpu.getFlag(C_CARRY);
    ImGui::InputInt("Z", &fz, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("N", &fn, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("H", &fh, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputInt("C", &fc, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::PopItemWidth();

    ImGui::Text("Registers");
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 5.0f));  
    
    ImGui::PushItemWidth(-25);
    std::string sp = StringHelper::IntToHexString(cpu.sp.read());
    std::string pc = StringHelper::IntToHexString(cpu.pc.read());
    ImGui::InputText("SP", &sp[0], 6, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputText("PC", &pc[0], 6, ImGuiInputTextFlags_ReadOnly);
    ImGui::PopItemWidth();
    
    ImGui::PushItemWidth(-15);
    ImGui::Columns(2, "registers0", false);
    std::string a = StringHelper::IntToHexString(cpu.a.read(), 2);
    std::string f = StringHelper::IntToHexString(cpu.f.read(), 2);
    ImGui::InputText("A", &a[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::InputText("F", &f[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();

    std::string b = StringHelper::IntToHexString(cpu.b.read(), 2);
    std::string c = StringHelper::IntToHexString(cpu.c.read(), 2);
    ImGui::InputText("B", &b[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::InputText("C", &c[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();

    std::string d = StringHelper::IntToHexString(cpu.d.read(), 2);
    std::string e = StringHelper::IntToHexString(cpu.e.read(), 2);
    ImGui::InputText("D", &d[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::InputText("E", &e[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();

    std::string h = StringHelper::IntToHexString(cpu.h.read(), 2);
    std::string l = StringHelper::IntToHexString(cpu.l.read(), 2);
    ImGui::InputText("H", &h[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::InputText("L", &l[0], 4, ImGuiInputTextFlags_ReadOnly); ImGui::NextColumn();
    ImGui::Columns(1);    
    ImGui::PopItemWidth();

    ImGui::End();
}