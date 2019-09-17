#include "sla.h"
#include "../../helper/string_helper.h"

Sla::Sla()
{
    Sla* self = this;
    group[0x20] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  B"; },
        // Cycles: 8
    };
    group[0x21] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  C"; },
        // Cycles: 8
    };
    group[0x22] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  D"; },
        // Cycles: 8
    };
    group[0x23] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  E"; },
        // Cycles: 8
    };
    group[0x24] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  H"; },
        // Cycles: 8
    };
    group[0x25] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  L"; },
        // Cycles: 8
    };
    group[0x26] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  (HL)"; },
        // Cycles: 16
    };
    group[0x27] =
    {
        2,
        [self](int opcode) -> std::string { return "SLA  A"; },
        // Cycles: 8
    };

}