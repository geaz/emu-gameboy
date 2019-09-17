#include "res.h"
#include "../../helper/string_helper.h"

Res::Res()
{
    Res* self = this;
    group[0x80] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, B"; },
        // Cycles: 8
    };
    group[0x81] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, C"; },
        // Cycles: 8
    };
    group[0x82] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, D"; },
        // Cycles: 8
    };
    group[0x83] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, E"; },
        // Cycles: 8
    };
    group[0x84] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, H"; },
        // Cycles: 8
    };
    group[0x85] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, L"; },
        // Cycles: 8
    };
    group[0x86] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, (HL)"; },
        // Cycles: 16
    };
    group[0x87] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, A"; },
        // Cycles: 8
    };
    group[0x88] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, B"; },
        // Cycles: 8
    };
    group[0x89] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, C"; },
        // Cycles: 8
    };
    group[0x8a] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, D"; },
        // Cycles: 8
    };
    group[0x8b] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, E"; },
        // Cycles: 8
    };
    group[0x8c] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, H"; },
        // Cycles: 8
    };
    group[0x8d] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, L"; },
        // Cycles: 8
    };
    group[0x8e] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, (HL)"; },
        // Cycles: 16
    };
    group[0x8f] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, A"; },
        // Cycles: 8
    };
    group[0x90] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, B"; },
        // Cycles: 8
    };
    group[0x91] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, C"; },
        // Cycles: 8
    };
    group[0x92] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, D"; },
        // Cycles: 8
    };
    group[0x93] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, E"; },
        // Cycles: 8
    };
    group[0x94] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, H"; },
        // Cycles: 8
    };
    group[0x95] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, L"; },
        // Cycles: 8
    };
    group[0x96] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, (HL)"; },
        // Cycles: 16
    };
    group[0x97] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, A"; },
        // Cycles: 8
    };
    group[0x98] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, B"; },
        // Cycles: 8
    };
    group[0x99] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, C"; },
        // Cycles: 8
    };
    group[0x9a] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, D"; },
        // Cycles: 8
    };
    group[0x9b] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, E"; },
        // Cycles: 8
    };
    group[0x9c] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, H"; },
        // Cycles: 8
    };
    group[0x9d] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, L"; },
        // Cycles: 8
    };
    group[0x9e] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, (HL)"; },
        // Cycles: 16
    };
    group[0x9f] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, A"; },
        // Cycles: 8
    };
    group[0xa0] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, B"; },
        // Cycles: 8
    };
    group[0xa1] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, C"; },
        // Cycles: 8
    };
    group[0xa2] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, D"; },
        // Cycles: 8
    };
    group[0xa3] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, E"; },
        // Cycles: 8
    };
    group[0xa4] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, H"; },
        // Cycles: 8
    };
    group[0xa5] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, L"; },
        // Cycles: 8
    };
    group[0xa6] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, (HL)"; },
        // Cycles: 16
    };
    group[0xa7] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, A"; },
        // Cycles: 8
    };
    group[0xa8] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, B"; },
        // Cycles: 8
    };
    group[0xa9] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, C"; },
        // Cycles: 8
    };
    group[0xaa] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, D"; },
        // Cycles: 8
    };
    group[0xab] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, E"; },
        // Cycles: 8
    };
    group[0xac] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, H"; },
        // Cycles: 8
    };
    group[0xad] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, L"; },
        // Cycles: 8
    };
    group[0xae] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, (HL)"; },
        // Cycles: 16
    };
    group[0xaf] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, A"; },
        // Cycles: 8
    };
    group[0xb0] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, B"; },
        // Cycles: 8
    };
    group[0xb1] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, C"; },
        // Cycles: 8
    };
    group[0xb2] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, D"; },
        // Cycles: 8
    };
    group[0xb3] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, E"; },
        // Cycles: 8
    };
    group[0xb4] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, H"; },
        // Cycles: 8
    };
    group[0xb5] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, L"; },
        // Cycles: 8
    };
    group[0xb6] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, (HL)"; },
        // Cycles: 16
    };
    group[0xb7] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, A"; },
        // Cycles: 8
    };
    group[0xb8] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, B"; },
        // Cycles: 8
    };
    group[0xb9] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, C"; },
        // Cycles: 8
    };
    group[0xba] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, D"; },
        // Cycles: 8
    };
    group[0xbb] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, E"; },
        // Cycles: 8
    };
    group[0xbc] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, H"; },
        // Cycles: 8
    };
    group[0xbd] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, L"; },
        // Cycles: 8
    };
    group[0xbe] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, (HL)"; },
        // Cycles: 16
    };
    group[0xbf] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, A"; },
        // Cycles: 8
    };

}