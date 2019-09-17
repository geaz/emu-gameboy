#include "set.h"
#include "../../helper/string_helper.h"

Set::Set()
{
    Set* self = this;
    group[0xc0] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, B"; }
    };
    group[0xc1] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, C"; }
    };
    group[0xc2] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, D"; }
    };
    group[0xc3] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, E"; }
    };
    group[0xc4] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, H"; }
    };
    group[0xc5] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, L"; }
    };
    group[0xc6] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, (HL)"; }
    };
    group[0xc7] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  0, A"; }
    };
    group[0xc8] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, B"; }
    };
    group[0xc9] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, C"; }
    };
    group[0xca] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, D"; }
    };
    group[0xcb] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, E"; }
    };
    group[0xcc] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, H"; }
    };
    group[0xcd] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, L"; }
    };
    group[0xce] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, (HL)"; }
    };
    group[0xcf] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  1, A"; }
    };
    group[0xd0] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, B"; }
    };
    group[0xd1] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, C"; }
    };
    group[0xd2] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, D"; }
    };
    group[0xd3] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, E"; }
    };
    group[0xd4] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, H"; }
    };
    group[0xd5] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, L"; }
    };
    group[0xd6] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, (HL)"; }
    };
    group[0xd7] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  2, A"; }
    };
    group[0xd8] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, B"; }
    };
    group[0xd9] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, C"; }
    };
    group[0xda] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, D"; }
    };
    group[0xdb] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, E"; }
    };
    group[0xdc] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, H"; }
    };
    group[0xdd] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, L"; }
    };
    group[0xde] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, (HL)"; }
    };
    group[0xdf] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  3, A"; }
    };
    group[0xe0] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, B"; }
    };
    group[0xe1] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, C"; }
    };
    group[0xe2] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, D"; }
    };
    group[0xe3] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, E"; }
    };
    group[0xe4] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, H"; }
    };
    group[0xe5] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, L"; }
    };
    group[0xe6] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, (HL)"; }
    };
    group[0xe7] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  4, A"; }
    };
    group[0xe8] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, B"; }
    };
    group[0xe9] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, C"; }
    };
    group[0xea] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, D"; }
    };
    group[0xeb] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, E"; }
    };
    group[0xec] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, H"; }
    };
    group[0xed] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, L"; }
    };
    group[0xee] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, (HL)"; }
    };
    group[0xef] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  5, A"; }
    };
    group[0xf0] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, B"; }
    };
    group[0xf1] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, C"; }
    };
    group[0xf2] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, D"; }
    };
    group[0xf3] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, E"; }
    };
    group[0xf4] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, H"; }
    };
    group[0xf5] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, L"; }
    };
    group[0xf6] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, (HL)"; }
    };
    group[0xf7] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  6, A"; }
    };
    group[0xf8] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, B"; }
    };
    group[0xf9] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, C"; }
    };
    group[0xfa] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, D"; }
    };
    group[0xfb] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, E"; }
    };
    group[0xfc] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, H"; }
    };
    group[0xfd] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, L"; }
    };
    group[0xfe] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, (HL)"; }
    };
    group[0xff] =
    {
        2,
        [self](int opcode) -> std::string { return "SET  7, A"; }
    };

}