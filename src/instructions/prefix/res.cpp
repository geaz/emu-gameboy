#include "res.h"
#include "../../helper/string_helper.h"

Res::Res()
{
    Res* self = this;
    group[0x80] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, B"; }
    };
    group[0x81] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, C"; }
    };
    group[0x82] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, D"; }
    };
    group[0x83] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, E"; }
    };
    group[0x84] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, H"; }
    };
    group[0x85] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, L"; }
    };
    group[0x86] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, (HL)"; }
    };
    group[0x87] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  0, A"; }
    };
    group[0x88] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, B"; }
    };
    group[0x89] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, C"; }
    };
    group[0x8a] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, D"; }
    };
    group[0x8b] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, E"; }
    };
    group[0x8c] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, H"; }
    };
    group[0x8d] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, L"; }
    };
    group[0x8e] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, (HL)"; }
    };
    group[0x8f] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  1, A"; }
    };
    group[0x90] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, B"; }
    };
    group[0x91] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, C"; }
    };
    group[0x92] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, D"; }
    };
    group[0x93] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, E"; }
    };
    group[0x94] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, H"; }
    };
    group[0x95] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, L"; }
    };
    group[0x96] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, (HL)"; }
    };
    group[0x97] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  2, A"; }
    };
    group[0x98] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, B"; }
    };
    group[0x99] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, C"; }
    };
    group[0x9a] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, D"; }
    };
    group[0x9b] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, E"; }
    };
    group[0x9c] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, H"; }
    };
    group[0x9d] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, L"; }
    };
    group[0x9e] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, (HL)"; }
    };
    group[0x9f] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  3, A"; }
    };
    group[0xa0] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, B"; }
    };
    group[0xa1] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, C"; }
    };
    group[0xa2] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, D"; }
    };
    group[0xa3] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, E"; }
    };
    group[0xa4] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, H"; }
    };
    group[0xa5] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, L"; }
    };
    group[0xa6] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, (HL)"; }
    };
    group[0xa7] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  4, A"; }
    };
    group[0xa8] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, B"; }
    };
    group[0xa9] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, C"; }
    };
    group[0xaa] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, D"; }
    };
    group[0xab] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, E"; }
    };
    group[0xac] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, H"; }
    };
    group[0xad] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, L"; }
    };
    group[0xae] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, (HL)"; }
    };
    group[0xaf] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  5, A"; }
    };
    group[0xb0] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, B"; }
    };
    group[0xb1] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, C"; }
    };
    group[0xb2] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, D"; }
    };
    group[0xb3] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, E"; }
    };
    group[0xb4] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, H"; }
    };
    group[0xb5] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, L"; }
    };
    group[0xb6] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, (HL)"; }
    };
    group[0xb7] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  6, A"; }
    };
    group[0xb8] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, B"; }
    };
    group[0xb9] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, C"; }
    };
    group[0xba] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, D"; }
    };
    group[0xbb] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, E"; }
    };
    group[0xbc] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, H"; }
    };
    group[0xbd] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, L"; }
    };
    group[0xbe] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, (HL)"; }
    };
    group[0xbf] =
    {
        2,
        [self](int opcode) -> std::string { return "RES  7, A"; }
    };

}