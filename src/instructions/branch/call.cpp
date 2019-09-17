#include "call.h"
#include "../../helper/string_helper.h"

Call::Call()
{
    Call* self = this;
    group[0xc4] =
    {
        3,
        [self](int opcode) -> std::string { return "CALL NZ, a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };
    group[0xcc] =
    {
        3,
        [self](int opcode) -> std::string { return "CALL Z, a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };
    group[0xcd] =
    {
        3,
        [self](int opcode) -> std::string { return "CALL a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };
    group[0xd4] =
    {
        3,
        [self](int opcode) -> std::string { return "CALL NC, a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };
    group[0xdc] =
    {
        3,
        [self](int opcode) -> std::string { return "CALL C, a'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode)); }
    };

}