#pragma once
#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace GGB::Helper
{
    // https://tweex.net/post/c-anything-tofrom-a-hex-string/
    static std::string IntToHexString(const int data, int stringWidth = 4, bool withPrefix = true)
    {
        std::stringstream hexStringStream; 
        hexStringStream.str(std::string());    
        hexStringStream << std::hex << std::setfill('0');
        hexStringStream << std::setw(stringWidth) << data;

        std::string hexString = hexStringStream.str();
        std::transform(hexString.begin(), hexString.end(), hexString.begin(), ::toupper);

        std::string returnValue = withPrefix
            ? "0x" + hexString
            : hexString;
        return returnValue;
    }

    static std::string Pad(const std::string text, int width, const char fillChar)
    {
        std::stringstream stringStream; 
        stringStream.str(std::string());    
        stringStream << std::setfill(fillChar);
        stringStream << std::setw(width) << text;

        return stringStream.str();
    }
}

#endif // STRINGHELPER_H
