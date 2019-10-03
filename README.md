# GGB - A Game Boy emulator written in C++ (WIP)

## Compatibility / Aims

*It is not intended to provide a full compatibility for all available cartridges.*
*Or to implement every single quirk of the Game Boy Hardware.*

This is a *programming experience project* and it does not aim to be a daily use emulator to play with. 
Use other great emulators for this purpose. For example:
- [Gambatte](https://github.com/sinamas/gambatte)
- [Sameboy](https://sameboy.github.io/)
- [BGB](http://bgb.bircd.org/)
- [Visualboy Advance](https://github.com/visualboyadvance-m/visualboyadvance-m)

Primary aims were:
- get a common understanding of emulation and the interaction of the components
- create a **interpreter mode** CPU and a **JIT mode** CPU, to learn about JIT

Further more I wanted to get the CPU do its work correctly. But I did not want to get it as accuarate as possible.
Thats why this emulator uses a rather simple cycle count method to keep the components in sync (Components syned after each instruction).
Which should be enough for most cases. There are more accurate methods like described [here](https://gekkio.fi/blog/2015/mooneye-gb-a-gameboy-emulator-written-in-rust/).

| Blargg CPU Test   |      Tetris      |  Tennis |
|-------------------|------------------|---------|
| ![cpu_instrs](pics/blargg-cpu_instrs.png) |  ![cpu_instrs](pics/Tetris.gif) | ![cpu_instrs](pics/Tennis.gif) |



## Opcode Generator

After I started this project I used this [table](http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html) to create my opcode classes.
Pretty fast I was frustrated by this tedious task. Therefore I created a python script to automate it.
The script *genOpcodes.py*, in the *gen* folder, scrapes the table and creates C++ classes by using the templates in the *gen/templates* folder.
By using this script I got great frame classes to work in.

The top *instruction_set* class contains two maps including all the different opcodes.  

**WARNING:** The Pastraiser OpCode Table has a few bugs. 0xE2 and 0xF2 are only one byte long! The Carry Flag indicator for the Right Shifting operations seem to be wrong, too.

![instruction_set](pics/gen-instruction-set.png)

Furthermore the script creates frame classes for all opcode groups.  

![gen-group](pics/gen-group.png)

## Instruction struct

The top *instruction_set* class contains two arrays. Including all opcodes.

```cpp
typedef uint8_t (*OpcodeFunc)(Cpu*);
struct Instruction
{
    uint8_t length;                 // Byte Length of the Instruction
    char* mnemonic;                 // Mnemonic of the Instruction
    OpcodeFunc executeInterpreter;  // Function Pointer to execute interpreter mode for given opcode
    //TODO OpcodeFunc? eecuteJit;   // Function Pointer to execute jit mode for given opcode
};
```

## TODOs
- Implement Graphics    (WIP)
- Implement JIT

## Ressources

- 8080 Manual (see *docs folder* - really great to understand how a cpu works)
- [The Cycle-Accurate Game Boy Docs]https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf) (Back up in the *docs* folder)
- [Pandocs](http://bgb.bircd.org/pandocs.htm) (Backup of the Site in the *docs folder*)
- [Opcodes](http://www.devrs.com/gb/files/opcodes.html)
- [Opcodes Table](http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html)
- [Memory Map](http://gameboy.mongenel.com/dmg/asmmemmap.html)
- [Game Boy - CPU Manual](https://realboyemulator.files.wordpress.com/2013/01/gbcpuman.pdf) (Backup of the Site in the *docs folder*)
- [Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI)