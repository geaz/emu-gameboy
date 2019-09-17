#include "rrc.h"
#include "../../helper/string_helper.h"

Rrc::Rrc()
{
    Rrc* self = this;
    group[0x08] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  B"; },
        // Cycles: 8
    };
    group[0x09] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  C"; },
        // Cycles: 8
    };
    group[0x0a] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  D"; },
        // Cycles: 8
    };
    group[0x0b] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  E"; },
        // Cycles: 8
    };
    group[0x0c] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  H"; },
        // Cycles: 8
    };
    group[0x0d] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  L"; },
        // Cycles: 8
    };
    group[0x0e] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  (HL)"; },
        // Cycles: 16
    };
    group[0x0f] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  A"; },
        // Cycles: 8
    };

}