#include "background_maps.hpp"

namespace GGB::Hardware::Video
{
    BackgroundMaps::BackgroundMaps(Mmu& mmu) : mmu(mmu) 
    { 
        mmu.registerOnAddrWrite([this](MemoryWriteEvent writeEvent) { onMmuWrite(writeEvent); });
    }

    BackgroundMap BackgroundMaps::getBackgroundMap()
    {
        return getMap(Const::FlagLcdControlBgMap);
    }

    BackgroundMap BackgroundMaps::getWindowMap()
    {
        return getMap(Const::FlagLcdControlWindowMap);
    }

    void BackgroundMaps::onMmuWrite(MemoryWriteEvent writeEvent)
    {
        if(writeEvent.address >= Const::AddrBgMap0Start && writeEvent.address <= Const::AddrBgMap0End)
            mapData0MemUpdated = true;
        else if(writeEvent.address >= Const::AddrBgMap1Start && writeEvent.address <= Const::AddrBgMap1End)
            mapData1MemUpdated = true;
    }

    BackgroundMap BackgroundMaps::getMap(const uint8_t controlFlag)
    {
        uint16_t startAddress = mmu.readIORegisterBit(Const::AddrRegLcdControl, controlFlag, true)
            ? Const::AddrBgMap1Start
            : Const::AddrBgMap0Start;
        
        BackgroundMap returnValue;
        if(startAddress == Const::AddrBgMap0Start)
        {
            if(mapData0MemUpdated)
            {
                map0 = loadMap(startAddress);
                mapData0MemUpdated = false;
            }
            returnValue = map0;
        }
        if(startAddress == Const::AddrBgMap1Start)
        {
            if(mapData1MemUpdated)
            {
                map1 = loadMap(startAddress);
                mapData1MemUpdated = false;
            }
            returnValue = map1;
        }
        return returnValue;
    }

    BackgroundMap BackgroundMaps::loadMap(const uint16_t startAddress) const
    {
        BackgroundMap backgroundMap;
        for(int i = 0; i < 32 * 32; i++)
        {
            backgroundMap.data[i/32][i%32] = mmu.read(startAddress + i, true);
        }
        return backgroundMap;
    }
}