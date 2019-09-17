#include "cp.h"
#include "../../helper/string_helper.h"

Cp::Cp()
{
    Cp* self = this;
    group[0xb8] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   B"; }
    };
    group[0xb9] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   C"; }
    };
    group[0xba] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   D"; }
    };
    group[0xbb] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   E"; }
    };
    group[0xbc] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   H"; }
    };
    group[0xbd] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   L"; }
    };
    group[0xbe] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   (HL)"; }
    };
    group[0xbf] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   A"; }
    };
    group[0xfe] =
    {
        2,
        [self](int opcode) -> std::string { return "CP   " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };

}