#pragma once
#ifndef MEMORYFLAGS_H
#define MEMORYFLAGS_H

enum IORegister
{    
    REG_PAD = 0xFF00,
    REG_SERIAL_TRANSFER = 0xFF01,
    REG_SERIAL_CONTROL = 0xFF02,
    REG_DIVIDER = 0xFF04,
    REG_TIMA = 0xFF05,
    REG_TMA = 0xFF06,
    REG_TAC = 0xFF07,
    REG_INTERRUPT_FLAG = 0xFF0F,
    REG_LCD_CONTROL = 0xFF40,
    REG_LCD_STATUS = 0xFF41,    
    REG_SCROLL_Y = 0xFF42,
    REG_SCROLL_X = 0xFF43,
    REG_LCD_Y = 0xFF44,
    REG_LCD_Y_COMPARE = 0xFF45,
    REG_DMA = 0xFF46,
    REG_BG_PALETTE = 0xFF47,    // Bit 7-6 - Data for Dot Data 11 (Normally darkest color
                                // Bit 5-4 - Data for Dot Data 10
                                // Bit 3-2 - Data for Dot Data 01
                                // Bit 1-0 - Data for Dot Data 00 (Normally lightest color)
    REG_OB_PALETTE_0 = 0xFF48,
    REG_OB_PALETTE_1 = 0xFF49,
    REG_WINDOW_Y = 0xFF4A,
    REG_WINDOW_X = 0xFF4B,
    REG_INTERRUPT_ENABLE = 0xFFFF
};

enum PadRegisterBit
{
                // Bit 7 - Not used           
                // Bit 6 - Not used
    P15 = 5,    // Bit 5 - P15 out port
    P14 = 4,    // Bit 4 - P14 out port
    P13 = 3,    // Bit 3 - P13 in port
    P12 = 2,    // Bit 2 - P12 in port
    P11 = 1,    // Bit 1 - P11 in port
    P10 = 0     // Bit 0 - P10 in port
};

enum SerialTransferBit
{
    START_FLAG = 7,     //  7 - Transfer Start Flag     0: Non transfer                 1: Start transfer
    SHIFT_CLOCK = 0     //  0 - Shift Clock             0: External Clock (500KHz Max.) 1: Internal Clock (8192Hz)
};

enum TimerBit
{
    TIMER_STOP = 2,         // Bit 2 - Timer Stop
                            //      0: Stop Timer
                            //      1: Start Timer
    CLOCK_SELECT_HIGH = 1,  // Bits 1+0 - Input Clock Select 
    CLOCK_SELECT_LOW = 0,   //      00: 4.096 KHz    (~4.194 KHz SGB)                      
                            //      01: 262.144 Khz  (~268.4 KHz SGB)
                            //      10: 65.536 KHz   (~67.11 KHz SGB)
                            //      11: 16.384 KHz   (~16.78 KHz SGB)
};

enum InterruptBit
{
    INTERRUPT_INPUT = 4,    // (Prio 5) Bit 4: Transition from High to Low of Pin number P10-P13
    INTERRUPT_SERIAL = 3,   // (Prio 4) Bit 3: Serial I/O transfer complete
    INTERRUPT_TIMER = 2,    // (Prio 3) Bit 2: Timer Overflow              
    INTERRUPT_LCD = 1,      // (Prio 2) Bit 1: LCDC 
    INTERRUPT_V_BLANK = 0   // (Prio 1) Bit 0: V-Blank
};

enum LCDRegisterBit
{
    LCD_ENABLE = 7,                 // Bit 7 - LCD Display Enable             (0=Off, 1=On)
    WINDOW_TILE_MAP_SELECT = 6,     // Bit 6 - Window Tile Map Display Select (0=9800-9BFF, 1=9C00-9FFF)
    WINDOW_ENABLE = 5,              // Bit 5 - Window Display Enable          (0=Off, 1=On)
    BG_TILE_DATA_SELECT = 4,        // Bit 4 - BG & Window Tile Data Select   (0=8800-97FF, 1=8000-8FFF)
    BG_TILE_MAP_SELECT = 3,         // Bit 3 - BG Tile Map Display Select     (0=9800-9BFF, 1=9C00-9FFF)
    OBJ_SIZE = 2,                   // Bit 2 - OBJ (Sprite) Size              (0=8x8, 1=8x16)
    OBJ_ENABLE = 1,                 // Bit 1 - OBJ (Sprite) Display Enable    (0=Off, 1=On)
    BG_DISPLAY = 0                  // Bit 0 - BG Display                     (0=Off, 1=On)
};

enum LCDStatusBit
{
    LCD_C_INTERRUPT_ENABLED = 6,        // Bit 6 - LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
    LCD_OAM_INTERRUPT_ENABLED = 5,      // Bit 5 - Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
    LCD_V_BLANK_INTERRUPT_ENABLED = 4,  // Bit 4 - Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
    LCD_H_BLANK_INTERRUPT_ENABLE = 3,   // Bit 3 - Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
    LCD_COINCIDENCE_MODE = 2,           // Bit 2 - Coincidence Flag  (0:LYC<>LY, 1:LYC=LY) (Read Only)
    LCD_MODE_HIGH = 1,                  //Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Read Only)
    LCD_MODE_LOW = 0                    //        00: During H-Blank
                                        //        01: During V-Blank
                                        //        10: During Searching OAM-RAM
                                        //        11: During Transfering Data to LCD Driver
};

enum LCDMode 
{
    MODE_HBLANK = 0,
    MODE_VBLANK = 1,
    MODE_OAM = 2,
    MODE_TRANSFER = 3
};

enum InterruptVector
{
    VECTOR_V_BLANK = 0x40,
    VECTOR_LCD = 0x48,
    VECTOR_TIMER = 0x50,
    VECTOR_SERIAL = 0x58,
    VECTOR_INPUT = 0x60
};

#endif // MEMORYFLAGS_H