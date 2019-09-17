#include "srl.h"
#include "../../helper/string_helper.h"

Srl::Srl()
{
    Srl* self = this;
    group[0x38] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  B"; },
        // Cycles: 8
    };
    group[0x39] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  C"; },
        // Cycles: 8
    };
    group[0x3a] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  D"; },
        // Cycles: 8
    };
    group[0x3b] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  E"; },
        // Cycles: 8
    };
    group[0x3c] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  H"; },
        // Cycles: 8
    };
    group[0x3d] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  L"; },
        // Cycles: 8
    };
    group[0x3e] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  (HL)"; },
        // Cycles: 16
    };
    group[0x3f] =
    {
        2,
        [self](int opcode) -> std::string { return "SRL  A"; },
        // Cycles: 8
    };

}