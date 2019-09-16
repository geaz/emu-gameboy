#include "jp.h"
#include "../../helper/string_helper.h"

Jp::Jp()
{
    Jp* jp = this;
    group[0xC2] =
    {
        3, 0xC2,
        [jp](int opcode) -> std::string { return "JP NZ, " + StringHelper::IntToHexString(jp->getAddrFrom16Bit(opcode)); }
    };
    group[0xD2] =
    {
        3, 0xD2,
        [jp](int opcode) -> std::string { return "JP NZ, " + StringHelper::IntToHexString(jp->getAddrFrom16Bit(opcode)); }
    };
    group[0xC3] =
    {
        3, 0xC3,
        [jp](int opcode) -> std::string { return "JP " + StringHelper::IntToHexString(jp->getAddrFrom16Bit(opcode)); }
    };
    group[0xE9] =
    {
        1, 0xE9,
        [](int opcode) -> std::string { return "JP (HL)"; }
    };
    group[0xCA] =
    {
        3, 0xCA,
        [jp](int opcode) -> std::string { return "JP Z, " + StringHelper::IntToHexString(jp->getAddrFrom16Bit(opcode)); }
    };
    group[0xDA] =
    {
        3, 0xDA,
        [jp](int opcode) -> std::string { return "JP C, " + StringHelper::IntToHexString(jp->getAddrFrom16Bit(opcode)); }
    };
}