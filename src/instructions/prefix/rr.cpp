#include "rr.h"
#include "../../helper/string_helper.h"

Rr::Rr()
{
    Rr* self = this;
    group[0x18] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   B"; }
    };
    group[0x19] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   C"; }
    };
    group[0x1a] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   D"; }
    };
    group[0x1b] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   E"; }
    };
    group[0x1c] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   H"; }
    };
    group[0x1d] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   L"; }
    };
    group[0x1e] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   (HL)"; }
    };
    group[0x1f] =
    {
        2,
        [self](int opcode) -> std::string { return "RR   A"; }
    };

}