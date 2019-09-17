#include "rst.h"
#include "../../helper/string_helper.h"

Rst::Rst()
{
    Rst* self = this;
    group[0xc7] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  00H"; }
    };
    group[0xcf] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  08H"; }
    };
    group[0xd7] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  10H"; }
    };
    group[0xdf] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  18H"; }
    };
    group[0xe7] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  20H"; }
    };
    group[0xef] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  28H"; }
    };
    group[0xf7] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  30H"; }
    };
    group[0xff] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  38H"; }
    };

}