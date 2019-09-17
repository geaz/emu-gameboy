#include "adc.h"
#include "../../helper/string_helper.h"

Adc::Adc()
{
    Adc* self = this;
    group[0x88] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, B"; },
        // Cycles: 4
    };
    group[0x89] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, C"; },
        // Cycles: 4
    };
    group[0x8a] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, D"; },
        // Cycles: 4
    };
    group[0x8b] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, E"; },
        // Cycles: 4
    };
    group[0x8c] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, H"; },
        // Cycles: 4
    };
    group[0x8d] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, L"; },
        // Cycles: 4
    };
    group[0x8e] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, (HL)"; },
        // Cycles: 8
    };
    group[0x8f] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, A"; },
        // Cycles: 4
    };
    group[0xce] =
    {
        2,
        [self](int opcode) -> std::string { return "ADC  A, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };

}