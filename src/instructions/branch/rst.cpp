#include "rst.h"

Rst::Rst()
{
    group[0xC7] =
    {
        1, 0xC7,
        [](int opcode) -> std::string { return "RST  00H"; }
    };
    group[0xD7] =
    {
        1, 0xD7,
        [](int opcode) -> std::string { return "RST  10H"; }
    };
    group[0xE7] =
    {
        1, 0xE7,
        [](int opcode) -> std::string { return "RST  20H"; }
    };
    group[0xF7] =
    {
        1, 0xF7,
        [](int opcode) -> std::string { return "RST  30H"; }
    };
    group[0xCF] =
    {
        1, 0xCF,
        [](int opcode) -> std::string { return "RST  08H"; }
    };
    group[0xDF] =
    {
        1, 0xDF,
        [](int opcode) -> std::string { return "RST  18H"; }
    };
    group[0xEF] =
    {
        1, 0xEF,
        [](int opcode) -> std::string { return "RST  28H"; }
    };
    group[0xFF] =
    {
        1, 0xFF,
        [](int opcode) -> std::string { return "RST  38H"; }
    };
}