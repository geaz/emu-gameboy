#include "rr.h"
#include "../../helper/string_helper.h"

Rr::Rr()
{
    Rr* self = this;
    group[0x18] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   B"; },
        // Cycles: 8
    };
    group[0x19] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   C"; },
        // Cycles: 8
    };
    group[0x1a] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   D"; },
        // Cycles: 8
    };
    group[0x1b] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   E"; },
        // Cycles: 8
    };
    group[0x1c] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   H"; },
        // Cycles: 8
    };
    group[0x1d] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   L"; },
        // Cycles: 8
    };
    group[0x1e] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   (HL)"; },
        // Cycles: 16
    };
    group[0x1f] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   A"; },
        // Cycles: 8
    };

}