#include "dec.h"
#include "../../helper/string_helper.h"

Dec::Dec()
{
    Dec* self = this;
    group[0x05] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  B"; }
    };
    group[0x0b] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  BC"; }
    };
    group[0x0d] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  C"; }
    };
    group[0x15] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  D"; }
    };
    group[0x1b] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  DE"; }
    };
    group[0x1d] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  E"; }
    };
    group[0x25] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  H"; }
    };
    group[0x2b] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  HL"; }
    };
    group[0x2d] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  L"; }
    };
    group[0x35] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  (HL)"; }
    };
    group[0x3b] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  SP"; }
    };
    group[0x3d] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  A"; }
    };

}