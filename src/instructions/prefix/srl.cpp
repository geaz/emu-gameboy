#include "srl.h"
#include "../../helper/string_helper.h"

Srl::Srl()
{
    Srl* self = this;
    group[0x38] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  B"; }
    };
    group[0x39] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  C"; }
    };
    group[0x3a] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  D"; }
    };
    group[0x3b] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  E"; }
    };
    group[0x3c] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  H"; }
    };
    group[0x3d] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  L"; }
    };
    group[0x3e] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  (HL)"; }
    };
    group[0x3f] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  A"; }
    };

}