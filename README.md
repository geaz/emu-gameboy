# A Gameboy emulator written in C++ (WIP)

I started this project to create an emulator which is capable to do emulation in **interpreter mode** and in **jit mode**.
This is not a highly optimized emulator. The aim was to create a code base which is easy to follow for beginners.
This is why each instruction group is implemented in an own class to provide a better implementation overview.

Each instruction group contains a group of the *struct Instruction*. The *struct* contains everything necessary to process the given instruction. This way it should be easy to tell how the **dissasembly**, **interpreter mode** and **jit mode** for each single instruction works.

```
struct Instruction
{
    short length;
    unsigned char opcode;
    std::function<std::string (int)> getMnemonic;
    //TODO Interpreter executeInterpreter(CPU);
    //TODO JIT with DynASM getAsm();
};
```

Further more the emulator contains a simple dissasembler and aims to be cycle accurate.
If you are just interested on how the implementation of the instructions were done, just look into the *src/instructions* subfolders.
You will find the hardware implementation of the emulator in the *src/hardware* folder. 

## Ressources

- http://gbdev.gg8.se/wiki/articles/Pan_Docs
- http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
- https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf