#include "sla.h"
#include "../../helper/string_helper.h"

Sla::Sla()
{
    Sla* self = this;
    group[0x20] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  B"; }
    };
    group[0x21] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  C"; }
    };
    group[0x22] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  D"; }
    };
    group[0x23] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  E"; }
    };
    group[0x24] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  H"; }
    };
    group[0x25] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  L"; }
    };
    group[0x26] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  (HL)"; }
    };
    group[0x27] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  A"; }
    };

}