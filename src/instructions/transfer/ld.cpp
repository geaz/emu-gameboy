#include "ld.h"
#include "../../helper/string_helper.h"

Ld::Ld()
{
    Ld* ld = this;
    group[0x40] =
    {
        1, 0x40,
        [](int opcode) -> std::string { return "LD B, B"; }
    };
    group[0x50] =
    {
        1, 0x50,
        [](int opcode) -> std::string { return "LD D, B"; }
    };
    group[0x60] =
    {
        1, 0x60,
        [](int opcode) -> std::string { return "LD H, B"; }
    };
    group[0x70] =
    {
        1, 0x70,
        [](int opcode) -> std::string { return "LD (HL), B"; }
    };
    group[0xE0] =
    {
        2, 0xE0,
        [](int opcode) -> std::string { return "LDH (" + StringHelper::IntToHexString(opcode & 0x00FF, 2) + "), A"; }
    };
    group[0xF0] =
    {
        2, 0xF0,
        [](int opcode) -> std::string { return "LDH A, (" + StringHelper::IntToHexString(opcode & 0x00FF, 2) + ")"; }
    };
    group[0x01] =
    {
        3, 0x01,
        [ld](int opcode) -> std::string { return "LD BC, " + StringHelper::IntToHexString(ld->getAddrFrom16Bit(opcode)); }
    };
    group[0x11] =
    {
        3, 0x11,
        [ld](int opcode) -> std::string { return "LD DE, " + StringHelper::IntToHexString(ld->getAddrFrom16Bit(opcode)); }
    };
    group[0x21] =
    {
        3, 0x21,
        [ld](int opcode) -> std::string { return "LD HL, " + StringHelper::IntToHexString(ld->getAddrFrom16Bit(opcode)); }
    };
    group[0x31] =
    {
        3, 0x31,
        [ld](int opcode) -> std::string { return "LD SP, " + StringHelper::IntToHexString(ld->getAddrFrom16Bit(opcode)); }
    };
    group[0x41] =
    {
        1, 0x41,
        [](int opcode) -> std::string { return "LD B, C"; }
    };
    group[0x51] =
    {
        1, 0x51,
        [](int opcode) -> std::string { return "LD D, C"; }
    };
    group[0x61] =
    {
        1, 0x61,
        [](int opcode) -> std::string { return "LD H, C"; }
    };
    group[0x71] =
    {
        1, 0x71,
        [](int opcode) -> std::string { return "LD (HL), C"; }
    };
    group[0x02] =
    {
        1, 0x02,
        [](int opcode) -> std::string { return "LD (BC), A"; }
    };
    group[0x12] =
    {
        1, 0x12,
        [](int opcode) -> std::string { return "LD (DE), A"; }
    };
    group[0x22] =
    {
        1, 0x22,
        [](int opcode) -> std::string { return "LD (HL+), A"; }
    };
    group[0x32] =
    {
        1, 0x32,
        [](int opcode) -> std::string { return "LD (HL-), A"; }
    };
    group[0x42] =
    {
        1, 0x42,
        [](int opcode) -> std::string { return "LD B, D"; }
    };
    group[0x52] =
    {
        1, 0x52,
        [](int opcode) -> std::string { return "LD D, D"; }
    };
    group[0x62] =
    {
        1, 0x62,
        [](int opcode) -> std::string { return "LD H, D"; }
    };
    group[0x72] =
    {
        1, 0x72,
        [](int opcode) -> std::string { return "LD (HL), D"; }
    };
    group[0xE2] =
    {
        1, 0xE2,
        [](int opcode) -> std::string { return "LD (C), A"; }
    };
    group[0xF2] =
    {
        1, 0xF2,
        [](int opcode) -> std::string { return "LD A, (C)"; }
    };
    group[0x43] =
    {
        1, 0x43,
        [](int opcode) -> std::string { return "LD B, E"; }
    };
    group[053] =
    {
        1, 0x53,
        [](int opcode) -> std::string { return "LD D, E"; }
    };
    group[0x63] =
    {
        1, 0x63,
        [](int opcode) -> std::string { return "LD H, E"; }
    };
    group[0x73] =
    {
        1, 0x73,
        [](int opcode) -> std::string { return "LD (HL), E"; }
    };
    group[0x44] =
    {
        1, 0x44,
        [](int opcode) -> std::string { return "LD B, H"; }
    };
    group[0x54] =
    {
        1, 0x54,
        [](int opcode) -> std::string { return "LD D, H"; }
    };
    group[0x64] =
    {
        1, 0x64,
        [](int opcode) -> std::string { return "LD H, H"; }
    };
    group[0x74] =
    {
        1, 0x74,
        [](int opcode) -> std::string { return "LD (HL), H"; }
    };
    group[0x45] =
    {
        1, 0x45,
        [](int opcode) -> std::string { return "LD B, L"; }
    };
    group[0x55] =
    {
        1, 0x55,
        [](int opcode) -> std::string { return "LD D, L"; }
    };
    group[0x65] =
    {
        1, 0x65,
        [](int opcode) -> std::string { return "LD H, L"; }
    };
    group[0x75] =
    {
        1, 0x75,
        [](int opcode) -> std::string { return "LD (HL), L"; }
    };
    group[0x06] =
    {
        2, 0x06,
        [](int opcode) -> std::string { return "LD B, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };
    group[0x16] =
    {
        2, 0x16,
        [](int opcode) -> std::string { return "LD D, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };
    group[0x26] =
    {
        2, 0x26,
        [](int opcode) -> std::string { return "LD H, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };
    group[0x36] =
    {
        2, 0x36,
        [](int opcode) -> std::string { return "LD (HL), " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };
    group[0x46] =
    {
        1, 0x46,
        [](int opcode) -> std::string { return "LD B, (HL)"; }
    };
    group[0x56] =
    {
        1, 0x56,
        [](int opcode) -> std::string { return "LD D, (HL)"; }
    };
    group[0x66] =
    {
        1, 0x66,
        [](int opcode) -> std::string { return "LD H, (HL)"; }
    };
}