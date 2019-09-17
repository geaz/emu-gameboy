#include "rrc.h"
#include "../../helper/string_helper.h"

Rrc::Rrc()
{
    Rrc* self = this;
    group[0x08] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  B"; }
    };
    group[0x09] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  C"; }
    };
    group[0x0a] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  D"; }
    };
    group[0x0b] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  E"; }
    };
    group[0x0c] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  H"; }
    };
    group[0x0d] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  L"; }
    };
    group[0x0e] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  (HL)"; }
    };
    group[0x0f] =
    {
        2,
        [self](int opcode) -> std::string { return "RRC  A"; }
    };

}