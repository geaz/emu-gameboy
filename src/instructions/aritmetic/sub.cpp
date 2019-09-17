#include "sub.h"
#include "../../helper/string_helper.h"

Sub::Sub()
{
    Sub* self = this;
    group[0x90] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  B"; }
    };
    group[0x91] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  C"; }
    };
    group[0x92] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  D"; }
    };
    group[0x93] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  E"; }
    };
    group[0x94] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  H"; }
    };
    group[0x95] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  L"; }
    };
    group[0x96] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  (HL)"; }
    };
    group[0x97] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  A"; }
    };
    group[0xd6] =
    {
        2,
        [self](int opcode) -> std::string { return "SUB  " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };

}