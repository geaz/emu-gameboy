#include "tile_list.hpp"

namespace GGB::Hardware::Video
{
    TileList::TileList(Mmu& mmu) : mmu(mmu) 
    {
         mmu.registerOnAddrWrite([this](MemoryWriteEvent writeEvent) { onMmuWrite(writeEvent); });
    }

    Tile TileList::getBackgroundTile(const uint8_t tileNr)
    {
        return mmu.readIORegisterBit(Const::AddrRegLcdControl, Const::FlagLcdControlBgData, true)
            ? getTile(Const::AddrTileData1Start, tileNr)
            : getTile(Const::AddrTileData0Start, static_cast<int8_t>(tileNr) + 128); 
    }

    Tile TileList::getWindowTile(const uint8_t tileNr)
    {
        return getTile(Const::AddrTileData0Start, static_cast<int8_t>(tileNr) + 128); 
    }

    Tile TileList::getSpriteTile(const uint8_t tileNr)
    {
        return getTile(Const::AddrTileData1Start, tileNr); 
    }

    void TileList::onMmuWrite(MemoryWriteEvent writeEvent)
    {
        if(writeEvent.address >= Const::AddrTileData0Start && writeEvent.address <= Const::AddrTileData0End)
            tile0MemUpdated = true;
        else if(writeEvent.address >= Const::AddrTileData1Start && writeEvent.address <= Const::AddrTileData1End)
            tile1MemUpdated = true;
    }

    Tile TileList::getTile(const uint16_t startAddr, const uint8_t tileNr)
    {
        Tile returnValue;
        if(startAddr == Const::AddrTileData0Start)
        {
            if(tile0MemUpdated)
            {                
                updateTiles(tile0Data, startAddr);
                tile0MemUpdated = false;
            }
            returnValue = tile0Data[tileNr];
        }
        else if(startAddr == Const::AddrTileData1Start)
        {
            if(tile1MemUpdated)
            {                
                updateTiles(tile1Data, startAddr);
                tile1MemUpdated = false;
            }
            returnValue = tile1Data[tileNr];
        }
        return returnValue;
    }

    void TileList::updateTiles(Tile* tileData, const uint16_t startAddr)
    {
        for(int i = 0; i < 256; i++)
        {
            Tile tile;
            tile.nr = i;

            // Each tile is 16 bytes long
            uint16_t tileMemoryStart = (uint16_t)startAddr + (i * 16);
            for(int i = 0; i < 8; i++)
            {
                uint8_t lineData1 = mmu.read(tileMemoryStart + (i * 2), true);
                uint8_t lineData2 = mmu.read(tileMemoryStart + (i * 2) + 1, true);
                for(int j = 7; j >= 0; j--)
                {
                    uint8_t lowBit = (lineData1 >> j) & 0x1; 
                    uint8_t highBit =  (lineData2 >> j) & 0x1; 
                    tile.data[i][std::abs(j - 7)] = (highBit << 1) | lowBit;
                }
            }
            tileData[i] = tile;
        }        
    }
}