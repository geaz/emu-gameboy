# GGB - A Game Boy emulator written in C++ (WIP)

The aim of this project was to create a cycle accurate emulator which is capable to do emulation in **interpreter mode** and in **jit mode**.

## Compatibility

It is not intended to provide a full compatibility for all available cartridges.
This is a programming experience project and it does not aim to be a daily use emulator to play with. 
Use other great emulators for this purpose. For example:
- [Gambatte](https://github.com/sinamas/gambatte)
- [Visualboy Advance](https://github.com/visualboyadvance-m/visualboyadvance-m)

This said, I tried to implement this emulator as accurate as possible.

![cpu_instrs](pics/blargg-cpu_instrs.png)

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