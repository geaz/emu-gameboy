#include "bit.h"
#include "../../helper/string_helper.h"

Bit::Bit()
{
    Bit* self = this;
    group[0x40] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  0, B"; },
        // Cycles: 8
    };
    group[0x41] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  0, C"; },
        // Cycles: 8
    };
    group[0x42] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  0, D"; },
        // Cycles: 8
    };
    group[0x43] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  0, E"; },
        // Cycles: 8
    };
    group[0x44] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  0, H"; },
        // Cycles: 8
    };
    group[0x45] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  0, L"; },
        // Cycles: 8
    };
    group[0x46] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  0, (HL)"; },
        // Cycles: 16
    };
    group[0x47] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  0, A"; },
        // Cycles: 8
    };
    group[0x48] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  1, B"; },
        // Cycles: 8
    };
    group[0x49] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  1, C"; },
        // Cycles: 8
    };
    group[0x4a] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  1, D"; },
        // Cycles: 8
    };
    group[0x4b] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  1, E"; },
        // Cycles: 8
    };
    group[0x4c] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  1, H"; },
        // Cycles: 8
    };
    group[0x4d] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  1, L"; },
        // Cycles: 8
    };
    group[0x4e] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  1, (HL)"; },
        // Cycles: 16
    };
    group[0x4f] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  1, A"; },
        // Cycles: 8
    };
    group[0x50] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  2, B"; },
        // Cycles: 8
    };
    group[0x51] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  2, C"; },
        // Cycles: 8
    };
    group[0x52] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  2, D"; },
        // Cycles: 8
    };
    group[0x53] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  2, E"; },
        // Cycles: 8
    };
    group[0x54] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  2, H"; },
        // Cycles: 8
    };
    group[0x55] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  2, L"; },
        // Cycles: 8
    };
    group[0x56] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  2, (HL)"; },
        // Cycles: 16
    };
    group[0x57] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  2, A"; },
        // Cycles: 8
    };
    group[0x58] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  3, B"; },
        // Cycles: 8
    };
    group[0x59] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  3, C"; },
        // Cycles: 8
    };
    group[0x5a] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  3, D"; },
        // Cycles: 8
    };
    group[0x5b] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  3, E"; },
        // Cycles: 8
    };
    group[0x5c] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  3, H"; },
        // Cycles: 8
    };
    group[0x5d] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  3, L"; },
        // Cycles: 8
    };
    group[0x5e] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  3, (HL)"; },
        // Cycles: 16
    };
    group[0x5f] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  3, A"; },
        // Cycles: 8
    };
    group[0x60] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  4, B"; },
        // Cycles: 8
    };
    group[0x61] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  4, C"; },
        // Cycles: 8
    };
    group[0x62] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  4, D"; },
        // Cycles: 8
    };
    group[0x63] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  4, E"; },
        // Cycles: 8
    };
    group[0x64] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  4, H"; },
        // Cycles: 8
    };
    group[0x65] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  4, L"; },
        // Cycles: 8
    };
    group[0x66] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  4, (HL)"; },
        // Cycles: 16
    };
    group[0x67] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  4, A"; },
        // Cycles: 8
    };
    group[0x68] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  5, B"; },
        // Cycles: 8
    };
    group[0x69] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  5, C"; },
        // Cycles: 8
    };
    group[0x6a] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  5, D"; },
        // Cycles: 8
    };
    group[0x6b] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  5, E"; },
        // Cycles: 8
    };
    group[0x6c] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  5, H"; },
        // Cycles: 8
    };
    group[0x6d] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  5, L"; },
        // Cycles: 8
    };
    group[0x6e] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  5, (HL)"; },
        // Cycles: 16
    };
    group[0x6f] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  5, A"; },
        // Cycles: 8
    };
    group[0x70] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  6, B"; },
        // Cycles: 8
    };
    group[0x71] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  6, C"; },
        // Cycles: 8
    };
    group[0x72] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  6, D"; },
        // Cycles: 8
    };
    group[0x73] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  6, E"; },
        // Cycles: 8
    };
    group[0x74] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  6, H"; },
        // Cycles: 8
    };
    group[0x75] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  6, L"; },
        // Cycles: 8
    };
    group[0x76] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  6, (HL)"; },
        // Cycles: 16
    };
    group[0x77] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  6, A"; },
        // Cycles: 8
    };
    group[0x78] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  7, B"; },
        // Cycles: 8
    };
    group[0x79] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  7, C"; },
        // Cycles: 8
    };
    group[0x7a] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  7, D"; },
        // Cycles: 8
    };
    group[0x7b] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  7, E"; },
        // Cycles: 8
    };
    group[0x7c] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  7, H"; },
        // Cycles: 8
    };
    group[0x7d] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  7, L"; },
        // Cycles: 8
    };
    group[0x7e] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  7, (HL)"; },
        // Cycles: 16
    };
    group[0x7f] =
    {
        2,
        [self](int opcode) -> std::string { return "BIT  7, A"; },
        // Cycles: 8
    };

}