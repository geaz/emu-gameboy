#include "ld.h"
#include "../../helper/string_helper.h"

Ld::Ld()
{
    Ld* self = this;
    group[0x01] =
    {
        3,
        [self](int opcode) -> std::string { return "LD   BC, " + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); },
        // Cycles: 12
    };
    group[0x02] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (BC), A"; },
        // Cycles: 8
    };
    group[0x06] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   B, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };
    group[0x08] =
    {
        3,
        [self](int opcode) -> std::string { return "LD   (a16), SP"; },
        // Cycles: 20
    };
    group[0x0a] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, (BC)"; },
        // Cycles: 8
    };
    group[0x0e] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   C, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };
    group[0x11] =
    {
        3,
        [self](int opcode) -> std::string { return "LD   DE, " + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); },
        // Cycles: 12
    };
    group[0x12] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (DE), A"; },
        // Cycles: 8
    };
    group[0x16] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   D, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };
    group[0x1a] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, (DE)"; },
        // Cycles: 8
    };
    group[0x1e] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   E, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };
    group[0x21] =
    {
        3,
        [self](int opcode) -> std::string { return "LD   HL, " + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); },
        // Cycles: 12
    };
    group[0x22] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (HL+), A"; },
        // Cycles: 8
    };
    group[0x26] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   H, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };
    group[0x2a] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, (HL+)"; },
        // Cycles: 8
    };
    group[0x2e] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   L, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };
    group[0x31] =
    {
        3,
        [self](int opcode) -> std::string { return "LD   SP, " + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); },
        // Cycles: 12
    };
    group[0x32] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (HL-), A"; },
        // Cycles: 8
    };
    group[0x36] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   (HL), " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 12
    };
    group[0x3a] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, (HL-)"; },
        // Cycles: 8
    };
    group[0x3e] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   A, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };
    group[0x40] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   B, B"; },
        // Cycles: 4
    };
    group[0x41] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   B, C"; },
        // Cycles: 4
    };
    group[0x42] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   B, D"; },
        // Cycles: 4
    };
    group[0x43] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   B, E"; },
        // Cycles: 4
    };
    group[0x44] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   B, H"; },
        // Cycles: 4
    };
    group[0x45] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   B, L"; },
        // Cycles: 4
    };
    group[0x46] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   B, (HL)"; },
        // Cycles: 8
    };
    group[0x47] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   B, A"; },
        // Cycles: 4
    };
    group[0x48] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   C, B"; },
        // Cycles: 4
    };
    group[0x49] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   C, C"; },
        // Cycles: 4
    };
    group[0x4a] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   C, D"; },
        // Cycles: 4
    };
    group[0x4b] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   C, E"; },
        // Cycles: 4
    };
    group[0x4c] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   C, H"; },
        // Cycles: 4
    };
    group[0x4d] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   C, L"; },
        // Cycles: 4
    };
    group[0x4e] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   C, (HL)"; },
        // Cycles: 8
    };
    group[0x4f] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   C, A"; },
        // Cycles: 4
    };
    group[0x50] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   D, B"; },
        // Cycles: 4
    };
    group[0x51] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   D, C"; },
        // Cycles: 4
    };
    group[0x52] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   D, D"; },
        // Cycles: 4
    };
    group[0x53] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   D, E"; },
        // Cycles: 4
    };
    group[0x54] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   D, H"; },
        // Cycles: 4
    };
    group[0x55] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   D, L"; },
        // Cycles: 4
    };
    group[0x56] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   D, (HL)"; },
        // Cycles: 8
    };
    group[0x57] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   D, A"; },
        // Cycles: 4
    };
    group[0x58] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   E, B"; },
        // Cycles: 4
    };
    group[0x59] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   E, C"; },
        // Cycles: 4
    };
    group[0x5a] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   E, D"; },
        // Cycles: 4
    };
    group[0x5b] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   E, E"; },
        // Cycles: 4
    };
    group[0x5c] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   E, H"; },
        // Cycles: 4
    };
    group[0x5d] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   E, L"; },
        // Cycles: 4
    };
    group[0x5e] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   E, (HL)"; },
        // Cycles: 8
    };
    group[0x5f] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   E, A"; },
        // Cycles: 4
    };
    group[0x60] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   H, B"; },
        // Cycles: 4
    };
    group[0x61] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   H, C"; },
        // Cycles: 4
    };
    group[0x62] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   H, D"; },
        // Cycles: 4
    };
    group[0x63] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   H, E"; },
        // Cycles: 4
    };
    group[0x64] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   H, H"; },
        // Cycles: 4
    };
    group[0x65] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   H, L"; },
        // Cycles: 4
    };
    group[0x66] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   H, (HL)"; },
        // Cycles: 8
    };
    group[0x67] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   H, A"; },
        // Cycles: 4
    };
    group[0x68] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   L, B"; },
        // Cycles: 4
    };
    group[0x69] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   L, C"; },
        // Cycles: 4
    };
    group[0x6a] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   L, D"; },
        // Cycles: 4
    };
    group[0x6b] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   L, E"; },
        // Cycles: 4
    };
    group[0x6c] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   L, H"; },
        // Cycles: 4
    };
    group[0x6d] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   L, L"; },
        // Cycles: 4
    };
    group[0x6e] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   L, (HL)"; },
        // Cycles: 8
    };
    group[0x6f] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   L, A"; },
        // Cycles: 4
    };
    group[0x70] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (HL), B"; },
        // Cycles: 8
    };
    group[0x71] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (HL), C"; },
        // Cycles: 8
    };
    group[0x72] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (HL), D"; },
        // Cycles: 8
    };
    group[0x73] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (HL), E"; },
        // Cycles: 8
    };
    group[0x74] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (HL), H"; },
        // Cycles: 8
    };
    group[0x75] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (HL), L"; },
        // Cycles: 8
    };
    group[0x77] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   (HL), A"; },
        // Cycles: 8
    };
    group[0x78] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, B"; },
        // Cycles: 4
    };
    group[0x79] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, C"; },
        // Cycles: 4
    };
    group[0x7a] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, D"; },
        // Cycles: 4
    };
    group[0x7b] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, E"; },
        // Cycles: 4
    };
    group[0x7c] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, H"; },
        // Cycles: 4
    };
    group[0x7d] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, L"; },
        // Cycles: 4
    };
    group[0x7e] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, (HL)"; },
        // Cycles: 8
    };
    group[0x7f] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   A, A"; },
        // Cycles: 4
    };
    group[0xe2] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   (C), A"; },
        // Cycles: 8
    };
    group[0xea] =
    {
        3,
        [self](int opcode) -> std::string { return "LD   (a16), A"; },
        // Cycles: 16
    };
    group[0xf2] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   A, (C)"; },
        // Cycles: 8
    };
    group[0xf8] =
    {
        2,
        [self](int opcode) -> std::string { return "LD   HL, SP+r8"; },
        // Cycles: 12
    };
    group[0xf9] =
    {
        1,
        [self](int opcode) -> std::string { return "LD   SP, HL"; },
        // Cycles: 8
    };
    group[0xfa] =
    {
        3,
        [self](int opcode) -> std::string { return "LD   A, (a16)"; },
        // Cycles: 16
    };

}