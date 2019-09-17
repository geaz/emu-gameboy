#include "set.h"
#include "../../helper/string_helper.h"

Set::Set()
{
    Set* self = this;
    group[0xc0] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, B"; },
        // Cycles: 8
    };
    group[0xc1] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, C"; },
        // Cycles: 8
    };
    group[0xc2] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, D"; },
        // Cycles: 8
    };
    group[0xc3] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, E"; },
        // Cycles: 8
    };
    group[0xc4] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, H"; },
        // Cycles: 8
    };
    group[0xc5] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, L"; },
        // Cycles: 8
    };
    group[0xc6] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, (HL)"; },
        // Cycles: 16
    };
    group[0xc7] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, A"; },
        // Cycles: 8
    };
    group[0xc8] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, B"; },
        // Cycles: 8
    };
    group[0xc9] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, C"; },
        // Cycles: 8
    };
    group[0xca] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, D"; },
        // Cycles: 8
    };
    group[0xcb] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, E"; },
        // Cycles: 8
    };
    group[0xcc] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, H"; },
        // Cycles: 8
    };
    group[0xcd] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, L"; },
        // Cycles: 8
    };
    group[0xce] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, (HL)"; },
        // Cycles: 16
    };
    group[0xcf] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, A"; },
        // Cycles: 8
    };
    group[0xd0] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, B"; },
        // Cycles: 8
    };
    group[0xd1] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, C"; },
        // Cycles: 8
    };
    group[0xd2] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, D"; },
        // Cycles: 8
    };
    group[0xd3] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, E"; },
        // Cycles: 8
    };
    group[0xd4] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, H"; },
        // Cycles: 8
    };
    group[0xd5] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, L"; },
        // Cycles: 8
    };
    group[0xd6] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, (HL)"; },
        // Cycles: 16
    };
    group[0xd7] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, A"; },
        // Cycles: 8
    };
    group[0xd8] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, B"; },
        // Cycles: 8
    };
    group[0xd9] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, C"; },
        // Cycles: 8
    };
    group[0xda] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, D"; },
        // Cycles: 8
    };
    group[0xdb] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, E"; },
        // Cycles: 8
    };
    group[0xdc] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, H"; },
        // Cycles: 8
    };
    group[0xdd] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, L"; },
        // Cycles: 8
    };
    group[0xde] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, (HL)"; },
        // Cycles: 16
    };
    group[0xdf] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, A"; },
        // Cycles: 8
    };
    group[0xe0] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, B"; },
        // Cycles: 8
    };
    group[0xe1] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, C"; },
        // Cycles: 8
    };
    group[0xe2] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, D"; },
        // Cycles: 8
    };
    group[0xe3] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, E"; },
        // Cycles: 8
    };
    group[0xe4] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, H"; },
        // Cycles: 8
    };
    group[0xe5] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, L"; },
        // Cycles: 8
    };
    group[0xe6] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, (HL)"; },
        // Cycles: 16
    };
    group[0xe7] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, A"; },
        // Cycles: 8
    };
    group[0xe8] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, B"; },
        // Cycles: 8
    };
    group[0xe9] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, C"; },
        // Cycles: 8
    };
    group[0xea] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, D"; },
        // Cycles: 8
    };
    group[0xeb] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, E"; },
        // Cycles: 8
    };
    group[0xec] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, H"; },
        // Cycles: 8
    };
    group[0xed] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, L"; },
        // Cycles: 8
    };
    group[0xee] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, (HL)"; },
        // Cycles: 16
    };
    group[0xef] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, A"; },
        // Cycles: 8
    };
    group[0xf0] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, B"; },
        // Cycles: 8
    };
    group[0xf1] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, C"; },
        // Cycles: 8
    };
    group[0xf2] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, D"; },
        // Cycles: 8
    };
    group[0xf3] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, E"; },
        // Cycles: 8
    };
    group[0xf4] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, H"; },
        // Cycles: 8
    };
    group[0xf5] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, L"; },
        // Cycles: 8
    };
    group[0xf6] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, (HL)"; },
        // Cycles: 16
    };
    group[0xf7] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, A"; },
        // Cycles: 8
    };
    group[0xf8] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, B"; },
        // Cycles: 8
    };
    group[0xf9] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, C"; },
        // Cycles: 8
    };
    group[0xfa] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, D"; },
        // Cycles: 8
    };
    group[0xfb] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, E"; },
        // Cycles: 8
    };
    group[0xfc] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, H"; },
        // Cycles: 8
    };
    group[0xfd] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, L"; },
        // Cycles: 8
    };
    group[0xfe] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, (HL)"; },
        // Cycles: 16
    };
    group[0xff] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, A"; },
        // Cycles: 8
    };

}