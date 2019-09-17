#include "add.h"
#include "../../helper/string_helper.h"

Add::Add()
{
    Add* self = this;
    group[0x09] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  HL, BC"; },
        // Cycles: 8
    };
    group[0x19] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  HL, DE"; },
        // Cycles: 8
    };
    group[0x29] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  HL, HL"; },
        // Cycles: 8
    };
    group[0x39] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  HL, SP"; },
        // Cycles: 8
    };
    group[0x80] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  A, B"; },
        // Cycles: 4
    };
    group[0x81] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  A, C"; },
        // Cycles: 4
    };
    group[0x82] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  A, D"; },
        // Cycles: 4
    };
    group[0x83] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  A, E"; },
        // Cycles: 4
    };
    group[0x84] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  A, H"; },
        // Cycles: 4
    };
    group[0x85] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  A, L"; },
        // Cycles: 4
    };
    group[0x86] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  A, (HL)"; },
        // Cycles: 8
    };
    group[0x87] =
    {
        1,
        [self](int opcode) -> std::string { return "ADD  A, A"; },
        // Cycles: 4
    };
    group[0xc6] =
    {
        2,
        [self](int opcode) -> std::string { return "ADD  A, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };
    group[0xe8] =
    {
        2,
        [self](int opcode) -> std::string { return "ADD  SP, a'" + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 16
    };

}