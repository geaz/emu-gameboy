#include "adc.h"
#include "../../helper/string_helper.h"

Adc::Adc()
{
    Adc* self = this;
    group[0x88] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, B"; }
    };
    group[0x89] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, C"; }
    };
    group[0x8a] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, D"; }
    };
    group[0x8b] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, E"; }
    };
    group[0x8c] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, H"; }
    };
    group[0x8d] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, L"; }
    };
    group[0x8e] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, (HL)"; }
    };
    group[0x8f] =
    {
        1,
        [self](int opcode) -> std::string { return "ADC  A, A"; }
    };
    group[0xce] =
    {
        2,
        [self](int opcode) -> std::string { return "ADC  A, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };

}