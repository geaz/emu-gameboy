#pragma once
#ifndef GGBCONSTANTS_H
#define GGBCONSTANTS_H

#include <cstdint>

namespace GGB::Const
{
    // General
    inline const uint32_t MemorySize = 0x10000;    
    inline const uint8_t LcdWidth = 160;
    inline const uint8_t LcdHeight = 144;
    inline const uint8_t TotalSprites = 40;
    inline const uint8_t MaxSpritesY = 10;

    // APU Constants    
    inline const uint8_t AudioOutputQuantity = 2;
    inline const uint32_t AudioSampleRate = 44100;
    inline const uint16_t AudioBufferFrames = 1024;
    inline const uint8_t AudioDefaultLength = 64; // Value for All Channels except Wave (see https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware)
    inline const uint16_t AudioWaveLength = 256; // Value for Wave Channel (see https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware)

    inline const uint8_t AudioWavePatternArray[4][8] = {
        { 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 1, 1, 1 },
        { 0, 1, 1, 1, 1, 1, 1, 0 }
    };
    inline const uint8_t AudioDivisorArray[8] = { 8, 16, 32, 48, 64, 80, 96, 112 };

    // Timing Consts
    inline const uint32_t CyclesCpu = 4194304;
    inline const uint32_t CyclesFrame = 70368;   
    inline const uint16_t CyclesHBlank = 204;     // Mode 0 (H-Blank) 204 cycles per Scanline
    inline const uint16_t CyclesVBlank = 456;     // Mode 1 (V-Blank) 4560 cycles per Frame 4560/10 times per Frame
    inline const uint16_t CyclesOam = 80;         // Mode 2 (OAM Search) 80 cycles per Scanline
    inline const uint16_t CyclesTransfer = 173;   // Mode 3 (Transfer LCD) 173 cycles per Scanline
    inline const uint16_t Cycles256Hz = CyclesCpu / 256;
    inline const uint16_t Cycles128Hz = CyclesCpu / 128;
    inline const uint32_t Cycles64Hz = CyclesCpu / 64;
    // We want to produce the samples a bit faster then consuming them
    // For the sample production we set the sample rate a bit higher to reduce lags during playback
    inline const uint16_t CyclesAudioSample = CyclesCpu / (AudioSampleRate + 250); 
    
    // We take the VBlank to syncronize the clock
    // The gameboy refreshes the screen ~60 times per seconds (CPU_CYCLES/FRAME_CYCLES)
    // One Frame takes ~16.775.709‬ nano seconds
    inline const int64_t OneFrameDurationNSec = 1000000000 / (CyclesCpu / CyclesFrame);

    // Cartridge Addresses
    inline const uint16_t AddrCartType = 0x0147;
    inline const uint16_t AddrCartSwitchTriggerStart = 0x2000;
    inline const uint16_t AddrCartSwitchTriggerEnd = 0x3FFF;
    inline const uint16_t AddrSwitchBankStart = 0x4000;
    inline const uint16_t AddrSwitchBankEnd = 0x7FFF;

    // Cartridge Types
    inline const uint8_t CartTypeRom = 0x0;
    inline const uint8_t CartTypeMBC1 = 0x1;

    // PPU Addresses
    inline const uint16_t AddrTileData0 = 0x8800;
    inline const uint16_t AddrTileData1 = 0x8000;
    inline const uint16_t AddrBgMap0 = 0x9800;
    inline const uint16_t AddrBgMap1 = 0x9C00; 

    // APU Addresses
    inline const uint16_t AddrWaveRamStart = 0xFF30;
    inline const uint16_t AddrWaveRamStop = 0xFF3F;
    inline const uint16_t AddrRegChannel1Sweep = 0xFF10;
    inline const uint16_t AddrRegChannel1LengthDuty = 0xFF11;
    inline const uint16_t AddrRegChannel1Envelope = 0xFF12;
    inline const uint16_t AddrRegChannel1FreqLow8Bit = 0xFF13;
    inline const uint16_t AddrRegChannel1Data = 0xFF14;    
    inline const uint16_t AddrRegChannel2LengthDuty = 0xFF16;
    inline const uint16_t AddrRegChannel2Envelope = 0xFF17;
    inline const uint16_t AddrRegChannel2FreqLow8Bit = 0xFF18;
    inline const uint16_t AddrRegChannel2Data = 0xFF19;
    inline const uint16_t AddrRegChannel3On = 0xFF1A;
    inline const uint16_t AddrRegChannel3Length = 0xFF1B;
    inline const uint16_t AddrRegChannel3Level = 0xFF1C;
    inline const uint16_t AddrRegChannel3FreqLow8Bit = 0xFF1D;
    inline const uint16_t AddrRegChannel3Data = 0xFF1E;
    inline const uint16_t AddrRegChannel4Length = 0xFF20;
    inline const uint16_t AddrRegChannel4Envelope = 0xFF21;
    inline const uint16_t AddrRegChannel4Counter = 0xFF22;
    inline const uint16_t AddrRegChannel4Data = 0xFF23;
    // Volume Left/Right
    inline const uint16_t AddrRegOutputControl = 0xFF24;
    //  Selection of Sound output terminal
    inline const uint16_t AddrRegChannelControl = 0xFF25;
    //  Sound on/off
    inline const uint16_t AddrRegSoundControl = 0xFF26;

    // Register Addresses
    inline const uint16_t AddrRegInput = 0xFF00;
    inline const uint16_t AddrRegInternalClockLow = 0xFF03;
    inline const uint16_t AddrRegDivider = 0xFF04;
    inline const uint16_t AddrRegTIMA = 0xFF05;
    inline const uint16_t AddrRegTMA = 0xFF06;
    inline const uint16_t AddrRegTAC = 0xFF07;        

    inline const uint16_t AddrRegLcdControl = 0xFF40;
    inline const uint16_t AddrRegLcdStatus = 0xFF41;
    inline const uint16_t AddrRegScrollY = 0xFF42;
    inline const uint16_t AddrRegScrollX = 0xFF43;
    inline const uint16_t AddrRegLcdY = 0xFF44;
    inline const uint16_t AddrRegLcdYCompare = 0xFF45;    
    inline const uint16_t AddrRegDma = 0xFF46;
    inline const uint16_t AddrRegBgPalette = 0xFF47; // Bit 7-6 - Data for Dot Data 11 (Normally darkest color
                                                     // Bit 5-4 - Data for Dot Data 10
                                                     // Bit 3-2 - Data for Dot Data 01
                                                     // Bit 1-0 - Data for Dot Data 00 (Normally lightest color)
    inline const uint16_t AddrRegOBPalette0 = 0xFF48;
    inline const uint16_t AddrRegOBPalette1 = 0xFF49;
    inline const uint16_t AddrRegWindowY = 0xFF4A;
    inline const uint16_t AddrRegWindowX = 0xFF4B;
    inline const uint16_t AddrRegInterruptFlag = 0xFF0F;
    inline const uint16_t AddrRegInterruptEnabled = 0xFFFF;

    // Interrupt Vectors
    inline const uint16_t AddrVectorVBlank = 0x40;
    inline const uint16_t AddrVectorLcd = 0x48;
    inline const uint16_t AddrVectorTimer = 0x50;
    inline const uint16_t AddrVectorSerial = 0x58;
    inline const uint16_t AddrVectorInput = 0x60;

    // Bit Flags
    inline const uint8_t FlagPadButtonsSet = 32;
    inline const uint8_t FlagPadDirectionSet = 16;    

    inline const uint8_t FlagTimerStart = 4;
    inline const uint8_t FlagTimerClockMode = 3;

    inline const uint8_t FlagInterruptInput = 16;    
    inline const uint8_t FlagInterruptSerial = 8;
    inline const uint8_t FlagInterruptTimer = 4;
    inline const uint8_t FlagInterruptLcd = 2;
    inline const uint8_t FlagInterruptVBlank = 1;

    inline const uint8_t FlagLcdControlLcdOn = 128;     // Bit 7 - LCD Display Enable             (0=Off, 1=On)
    inline const uint8_t FlagLcdControlWindowMap = 64;  // Bit 6 - Window Tile Map Display Select (0=9800-9BFF, 1=9C00-9FFF)
    inline const uint8_t FlagLcdControlWindowOn = 32;   // Bit 5 - Window Display Enable          (0=Off, 1=On)
    inline const uint8_t FlagLcdControlBgData = 16;     // Bit 4 - BG & Window Tile Data Select   (0=8800-97FF, 1=8000-8FFF)
    inline const uint8_t FlagLcdControlBgMap = 8;       // Bit 3 - BG Tile Map Display Select     (0=9800-9BFF, 1=9C00-9FFF)
    inline const uint8_t FlagLcdControlObjSize = 4;      // Bit 2 - OBJ (Sprite) Size              (0=8x8, 1=8x16)
    inline const uint8_t FlagLcdControlObjOn = 2;       // Bit 1 - OBJ (Sprite) Display Enable    (0=Off, 1=On)
    inline const uint8_t FlagLcdControlBgOn = 1;        // Bit 0 - BG Display                     (0=Off, 1=On)

    inline const uint8_t FlagLcdStatusLcdYCInterruptOn = 64;    // Bit 6 - LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
    inline const uint8_t FlagLcdStatusOamInterruptOn = 32;      // Bit 5 - Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
    inline const uint8_t FlagLcdStatusVBlankInterruptOn = 16;   // Bit 4 - Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
    inline const uint8_t FlagLcdStatusHBlankInterruptOn = 8;    // Bit 3 - Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
    inline const uint8_t FlagLcdStatusCoincidence = 4;          // Bit 2 - Coincidence Flag  (0:LYC<>LY, 1:LYC=LY) (Read Only)
    inline const uint8_t FlagLcdStatusModeHigh = 2;             //Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Read Only)
    inline const uint8_t FlagLcdStatusModeLow = 1;              //        00: During H-Blank
                                                                //        01: During V-Blank
                                                                //        10: During Searching OAM-RAM
                                                                //        11: During Transfering Data to LCD Driver

    inline const uint8_t FlagSpriteAttrObjBgPrio = 128; // Bit7   OBJ-to-BG Priority (0=OBJ Above BG, 1=OBJ Behind BG color 1-3)
                                                        // (Used for both BG and Window. BG color 0 is always behind OBJ)
    inline const uint8_t FlagSpriteAttrFlipY = 64;      // Bit6   Y flip          (0=Normal, 1=Vertically mirrored)
    inline const uint8_t FlagSpriteAttrFlipX = 32;      // Bit5   X flip          (0=Normal, 1=Horizontally mirrored)                                                       
    inline const uint8_t FlagSpriteAttrPaletteNr = 16;  // Bit4   Palette number  **Non CGB Mode Only** (0=OBP0, 1=OBP1)    

    inline const uint8_t FlagChannelSweepTime = 112;    
    inline const uint8_t FlagChannelSweepIncrease = 8;  
    inline const uint8_t FlagChannelSweepShift = 7;   
    inline const uint8_t FlagChannelDuty = 192;
    inline const uint8_t FlagChannelLengthData = 63;           
    inline const uint8_t FlagChannelEnvelopeVolumeInt = 240;
    inline const uint8_t FlagChannelEnvelopeIncrease = 8;
    inline const uint8_t FlagChannelEnvelopeSweep = 7;      
    inline const uint8_t FlagChannelRestart = 128;    // Bit 7   - Initial (1=Restart Sound)     (Write Only)
    inline const uint8_t FlagChannelLengthStop = 64;  // Bit 6   - Counter/consecutive selection (Read/Write)
                                                      // (1=Stop output when length in NR31 expires)
    inline const uint8_t FlagChannelFreq = 7;         // Bit 2-0 - Frequency's higher 3 bits (x) (Write Only)
    inline const uint8_t FlagOutputVolume = 7;  
    inline const uint8_t FlagChannel3On = 128;          // Bit 7 - Sound Channel 3 Off  (0=Stop, 1=Playback)  (Read/Write)
    inline const uint8_t FlagChannel3Output = 96;       // Bit 6-5 - Select output level (Read/Write)
    inline const uint8_t FlagChannel4ShiftFreq = 240;
    inline const uint8_t FlagChannel4CounterWidthMode = 8;
    inline const uint8_t FlagChannel4DividingRatio = 7;      

    inline const uint8_t FlagChannel4ToOutput2 = 128; // Bit 7 - Output sound 4 to SO2 terminal
    inline const uint8_t FlagChannel3ToOutput2 = 64;  // Bit 6 - Output sound 3 to SO2 terminal
    inline const uint8_t FlagChannel2ToOutput2 = 32;  // Bit 5 - Output sound 2 to SO2 terminal
    inline const uint8_t FlagChannel1ToOutput2 = 16;  // Bit 4 - Output sound 1 to SO2 terminal
    inline const uint8_t FlagChannel4ToOutput1 = 8;   // Bit 3 - Output sound 4 to SO1 terminal
    inline const uint8_t FlagChannel3ToOutput1 = 4;   // Bit 2 - Output sound 3 to SO1 terminal
    inline const uint8_t FlagChannel2ToOutput1 = 2;   // Bit 1 - Output sound 2 to SO1 terminal
    inline const uint8_t FlagChannel1ToOutput1 = 1;   // Bit 0 - Output sound 1 to SO1 terminal

    inline const uint8_t FlagSoundAllOn = 128;  // Bit 7 - All sound on/off  (0: stop all sound circuits) (Read/Write)
    inline const uint8_t FlagSound4On = 8;      // Bit 3 - Sound 4 ON flag (Read Only)
    inline const uint8_t FlagSound3On = 4;      // Bit 2 - Sound 3 ON flag (Read Only)
    inline const uint8_t FlagSound2On = 2;      // Bit 1 - Sound 2 ON flag (Read Only)
    inline const uint8_t FlagSound1On = 1;      // Bit 0 - Sound 1 ON flag (Read Only)

    // Byte Positions
    inline const uint8_t ByteSpriteAttributes = 3;
    inline const uint8_t ByteSpriteTileNr = 2;
    inline const uint8_t ByteSpritePosX = 1;
    inline const uint8_t ByteSpritePosY = 0;
}

#endif // GGBCONSTANTS_H