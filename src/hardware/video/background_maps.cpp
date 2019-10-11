#include "background_maps.hpp"

namespace GGB::Hardware::Video
{
    BackgroundMaps::BackgroundMaps(Mmu& mmu) : mmu(mmu) { }

    BackgroundMap BackgroundMaps::getBackgroundMap() const
    {
        return getMap(Const::FlagLcdControlBgMap);
    }

    BackgroundMap BackgroundMaps::getWindowMap() const
    {
        return getMap(Const::FlagLcdControlWindowMap);
    }

    BackgroundMap BackgroundMaps::getMap(const uint8_t controlFlag) const
    {
        uint16_t startAddress = mmu.readIORegisterBit(Const::AddrRegLcdControl, controlFlag, true)
            ? Const::AddrBgMap1
            : Const::AddrBgMap0;
        
        BackgroundMap backgroundMap;
        for(int i = 0; i < 32 * 32; i++)
        {
            backgroundMap.data[i/32][i%32] = mmu.read(startAddress + i, true);
        }
        return backgroundMap;
    }
}