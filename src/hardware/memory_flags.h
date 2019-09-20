enum IORegister
{    
    PAD_REGISTER = 0xFF00,
    SERIAL_TRANSFER = 0xFF01,
    SERIAL_CONTROL = 0xFF02,
    DIVIDER = 0xFF04,
    TIMA = 0xFF05,
    TMA = 0xFF06,
    TAC = 0xFF07,
    INTERRUPT_FLAG = 0xFF0F,
    LCD_CONTROL = 0xFF40,
    LCD_STATUS = 0xFF41,    
    SCROLL_Y = 0xFF42,
    SCROLL_X = 0xFF42,
    LCD_Y = 0xFF44,
    LCD_COMPARE = 0xFF45,
    DMA = 0xFF46,
    BG_PALETTE = 0xFF47,    // Bit 7-6 - Data for Dot Data 11 (Normally darkest color
                            // Bit 5-4 - Data for Dot Data 10
                            // Bit 3-2 - Data for Dot Data 01
                            // Bit 1-0 - Data for Dot Data 00 (Normally lightest color)
    OB_PALETTE_0 = 0xFF48,
    OB_PALETTE_1 = 0xFF49,
    WINDOW_Y = 0xFF4A,
    WINDOW_X = 0xFF4B,
    INTERRUPT_ENABLED = 0xFFFF
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
    INPUT_INTERRUPT = 4,    // (Prio 5) Bit 4: Transition from High to Low of Pin number P10-P13
    SERIAL_INTERRUPT = 3,   // (Prio 4) Bit 3: Serial I/O transfer complete
    TIMER_INTERRUPT = 2,    // (Prio 3) Bit 2: Timer Overflow              
    LCDC_INTERRUPT = 1,     // (Prio 2) Bit 1: LCDC 
    V_BLANK_INTERRUPT = 0   // (Prio 1) Bit 0: V-Blank
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
    BG_DISPLAY = 0                  // Bit 0 - BG Display (for CGB see below) (0=Off, 1=On)
};

enum LCDStatusBit
{
    LCD_COINCIDENCE_INTERRUPT = 6,  // Bit 6 - LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
    LCD_OAM_INTERRUPT = 5,          // Bit 5 - Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
    LCD_V_BLANK_INTERRUPT = 4,      // Bit 4 - Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
    LCD_H_BLANK_INTERRUPT = 3,      // Bit 3 - Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
    LCD_COINCIDENCE = 2,            // Bit 2 - Coincidence Flag  (0:LYC<>LY, 1:LYC=LY) (Read Only)
    LCD_MODE_HIGH = 1,              //Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Read Only)
    LCD_MODE_LOW = 0,               //        00: During H-Blank
                                    //        01: During V-Blank
                                    //        10: During Searching OAM-RAM
                                    //        11: During Transfering Data to LCD Driver
};
