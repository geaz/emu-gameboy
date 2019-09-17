#include "dec.h"
#include "../../helper/string_helper.h"

Dec::Dec()
{
    Dec* self = this;
    group[0x05] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  B"; },
        // Cycles: 4
    };
    group[0x0b] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  BC"; },
        // Cycles: 8
    };
    group[0x0d] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  C"; },
        // Cycles: 4
    };
    group[0x15] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  D"; },
        // Cycles: 4
    };
    group[0x1b] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  DE"; },
        // Cycles: 8
    };
    group[0x1d] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  E"; },
        // Cycles: 4
    };
    group[0x25] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  H"; },
        // Cycles: 4
    };
    group[0x2b] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  HL"; },
        // Cycles: 8
    };
    group[0x2d] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  L"; },
        // Cycles: 4
    };
    group[0x35] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  (HL)"; },
        // Cycles: 12
    };
    group[0x3b] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  SP"; },
        // Cycles: 8
    };
    group[0x3d] =
    {
        1,
        [self](int opcode) -> std::string { return "DEC  A"; },
        // Cycles: 4
    };

}