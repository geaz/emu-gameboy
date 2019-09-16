#include <string>
#include <iomanip>
#include <algorithm>

#include <imgui.h>

#include "disassembler_screen.h"
#include "../helper/string_helper.h"

DisassemblerScreen::DisassemblerScreen(int row, int column, Rom rom) : Screen(row, column), rom(rom)
{     
    disassembler.parseRom(rom);
}

void DisassemblerScreen::update()
{ 
    ImGui::Begin("Disassembly", 0, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse); 
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(500, 800), ImGuiCond_Always);
    ImGui::Text(("Loaded rom: " + rom.romPath).c_str());
    ImGui::Spacing();

    ImGui::Columns(4, "disassembly", false);
    ImGui::Text("ID"); ImGui::NextColumn();
    ImGui::Text("Position"); ImGui::NextColumn();
    ImGui::Text("Opcode"); ImGui::NextColumn();
    ImGui::Text("Mnemonic"); ImGui::NextColumn();
    ImGui::Separator();

    ImGuiListClipper clipper(disassembler.parsedInstructions.size());
    while (clipper.Step())
    {
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        {
            ParsedInstruction parsedInstruction = disassembler.parsedInstructions[i];
            ImGui::Selectable(std::to_string(parsedInstruction.number).c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
            ImGui::NextColumn();
            ImGui::Text(std::to_string(parsedInstruction.bytePosition).c_str()); ImGui::NextColumn();
            ImGui::Text(StringHelper::IntToHexString(parsedInstruction.bytes, 6, false).c_str()); ImGui::NextColumn();
            ImGui::Text(parsedInstruction.definition.getMnemonic(parsedInstruction.bytes).c_str()); ImGui::NextColumn();
        }
    }

    ImGui::End();
}