#include "string_helper.h"

#include <sstream>
#include <iomanip>
#include <algorithm>

// https://tweex.net/post/c-anything-tofrom-a-hex-string/
std::string StringHelper::IntToHexString(const int data, int stringWidth, bool withPrefix)
{
    std::stringstream hexStringStream; 
    hexStringStream.str(std::string());    
    hexStringStream << std::hex << std::setfill('0');
    hexStringStream << std::setw(stringWidth) << data;

    std::string hexString = hexStringStream.str();
    std::transform(hexString.begin(), hexString.end(), hexString.begin(), std::toupper);

    std::string returnValue = withPrefix
        ? "0x" + hexString
        : hexString;
    return returnValue;
}