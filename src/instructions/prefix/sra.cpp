#include "sra.h"
#include "../../helper/string_helper.h"

Sra::Sra()
{
    Sra* self = this;
    group[0x28] =
    {
        2,
        [self](int opcode) -> std::string { return "SRA  B"; },
        // Cycles: 8
    };
    group[0x29] =
    {
        2,
        [self](int opcode) -> std::string { return "SRA  C"; },
        // Cycles: 8
    };
    group[0x2a] =
    {
        2,
        [self](int opcode) -> std::string { return "SRA  D"; },
        // Cycles: 8
    };
    group[0x2b] =
    {
        2,
        [self](int opcode) -> std::string { return "SRA  E"; },
        // Cycles: 8
    };
    group[0x2c] =
    {
        2,
        [self](int opcode) -> std::string { return "SRA  H"; },
        // Cycles: 8
    };
    group[0x2d] =
    {
        2,
        [self](int opcode) -> std::string { return "SRA  L"; },
        // Cycles: 8
    };
    group[0x2e] =
    {
        2,
        [self](int opcode) -> std::string { return "SRA  (HL)"; },
        // Cycles: 16
    };
    group[0x2f] =
    {
        2,
        [self](int opcode) -> std::string { return "SRA  A"; },
        // Cycles: 8
    };

}