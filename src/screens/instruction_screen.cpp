#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include <imgui.h>

#include "instruction_screen.h"
#include "../helper/string_helper.h"

bool InstructionScreen::showInstruction = false;

InstructionScreen::InstructionScreen(Cpu& cpu) : cpu(cpu)
{ }

void InstructionScreen::update()
{   
    if(!InstructionScreen::showInstruction) return;  
    ImGui::Begin("Instructions (Last 500)", &InstructionScreen::showInstruction, ImGuiWindowFlags_NoResize); 
    ImGui::SetWindowSize(ImVec2(322, 201), ImGuiCond_Always);

    ImGui::InputText("Breakpoint", cpu.breakPoint, 5);

    ImGuiListClipper clipper(cpu.parsedInstructions.size());
    while (clipper.Step())
    {
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        {             
            ParsedInstruction parsedInstruction = cpu.parsedInstructions[i];
            ImGui::Text((StringHelper::IntToHexString(parsedInstruction.bytePosition) + ": ").c_str());
            
            std::stringstream rowLabel;
            if(parsedInstruction.definition.length == 1)
            {
                rowLabel << StringHelper::IntToHexString(parsedInstruction.parsedBytes.opcode, 2, false) << "      ";
            }
            else if(parsedInstruction.definition.length == 2)
            {
                rowLabel << StringHelper::IntToHexString((parsedInstruction.parsedBytes.opcode), 2, false);
                rowLabel << " " << StringHelper::IntToHexString(parsedInstruction.parsedBytes.low, 2, false) << "   ";
            }
            else if(parsedInstruction.definition.length == 3)
            {
                rowLabel << StringHelper::IntToHexString((parsedInstruction.parsedBytes.opcode), 2, false);
                rowLabel << " " << StringHelper::IntToHexString(parsedInstruction.parsedBytes.low, 2, false);
                rowLabel << " " << StringHelper::IntToHexString(parsedInstruction.parsedBytes.high, 2, false);
            }
            rowLabel << " | " << parsedInstruction.definition.mnemonic;

            ImGui::SameLine();
            ImGui::Selectable(rowLabel.str().c_str(), i == 0);
        }
    }

    ImGui::End();
}