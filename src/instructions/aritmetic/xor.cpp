#include "xor.h"
#include "../../helper/string_helper.h"

Xor::Xor()
{
    Xor* self = this;
    group[0xa8] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  B"; }
    };
    group[0xa9] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  C"; }
    };
    group[0xaa] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  D"; }
    };
    group[0xab] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  E"; }
    };
    group[0xac] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  H"; }
    };
    group[0xad] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  L"; }
    };
    group[0xae] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  (HL)"; }
    };
    group[0xaf] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  A"; }
    };
    group[0xee] =
    {
        2,
        [self](int opcode) -> std::string { return "XOR  " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };

}