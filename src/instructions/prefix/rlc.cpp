#include "rlc.h"
#include "../../helper/string_helper.h"

Rlc::Rlc()
{
    Rlc* self = this;
    group[0x00] =
    {
        2,
        [self](int opcode) -> std::string { return "RLC  B"; },
        // Cycles: 8
    };
    group[0x01] =
    {
        2,
        [self](int opcode) -> std::string { return "RLC  C"; },
        // Cycles: 8
    };
    group[0x02] =
    {
        2,
        [self](int opcode) -> std::string { return "RLC  D"; },
        // Cycles: 8
    };
    group[0x03] =
    {
        2,
        [self](int opcode) -> std::string { return "RLC  E"; },
        // Cycles: 8
    };
    group[0x04] =
    {
        2,
        [self](int opcode) -> std::string { return "RLC  H"; },
        // Cycles: 8
    };
    group[0x05] =
    {
        2,
        [self](int opcode) -> std::string { return "RLC  L"; },
        // Cycles: 8
    };
    group[0x06] =
    {
        2,
        [self](int opcode) -> std::string { return "RLC  (HL)"; },
        // Cycles: 16
    };
    group[0x07] =
    {
        2,
        [self](int opcode) -> std::string { return "RLC  A"; },
        // Cycles: 8
    };

}