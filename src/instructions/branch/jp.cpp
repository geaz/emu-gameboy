#include "jp.h"
#include "../../helper/string_helper.h"

Jp::Jp()
{
    Jp* self = this;
    group[0xc2] =
    {
        3,
        [self](int opcode) -> std::string { return "JP   NZ, a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };
    group[0xc3] =
    {
        3,
        [self](int opcode) -> std::string { return "JP   a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };
    group[0xca] =
    {
        3,
        [self](int opcode) -> std::string { return "JP   Z, a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };
    group[0xd2] =
    {
        3,
        [self](int opcode) -> std::string { return "JP   NC, a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };
    group[0xda] =
    {
        3,
        [self](int opcode) -> std::string { return "JP   C, a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };
    group[0xe9] =
    {
        1,
        [self](int opcode) -> std::string { return "JP   (HL)"; }
    };

}