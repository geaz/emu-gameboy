#include "rst.h"
#include "../../helper/string_helper.h"

Rst::Rst()
{
    Rst* self = this;
    group[0xc7] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  00H"; },
        // Cycles: 16
    };
    group[0xcf] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  08H"; },
        // Cycles: 16
    };
    group[0xd7] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  10H"; },
        // Cycles: 16
    };
    group[0xdf] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  18H"; },
        // Cycles: 16
    };
    group[0xe7] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  20H"; },
        // Cycles: 16
    };
    group[0xef] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  28H"; },
        // Cycles: 16
    };
    group[0xf7] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  30H"; },
        // Cycles: 16
    };
    group[0xff] =
    {
        1,
        [self](int opcode) -> std::string { return "RST  38H"; },
        // Cycles: 16
    };

}