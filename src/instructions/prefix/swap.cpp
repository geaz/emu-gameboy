#include "swap.h"
#include "../../helper/string_helper.h"

Swap::Swap()
{
    Swap* self = this;
    group[0x30] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP B"; }
    };
    group[0x31] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP C"; }
    };
    group[0x32] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP D"; }
    };
    group[0x33] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP E"; }
    };
    group[0x34] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP H"; }
    };
    group[0x35] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP L"; }
    };
    group[0x36] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP (HL)"; }
    };
    group[0x37] =
    {
        2,
        [self](int opcode) -> std::string { return "SWAP A"; }
    };

}