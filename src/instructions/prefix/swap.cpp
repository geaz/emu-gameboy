#include "swap.h"
#include "../../helper/string_helper.h"

Swap::Swap()
{
    Swap* self = this;
    group[0x30] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP B"; },
        // Cycles: 8
    };
    group[0x31] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP C"; },
        // Cycles: 8
    };
    group[0x32] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP D"; },
        // Cycles: 8
    };
    group[0x33] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP E"; },
        // Cycles: 8
    };
    group[0x34] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP H"; },
        // Cycles: 8
    };
    group[0x35] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP L"; },
        // Cycles: 8
    };
    group[0x36] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP (HL)"; },
        // Cycles: 16
    };
    group[0x37] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP A"; },
        // Cycles: 8
    };

}