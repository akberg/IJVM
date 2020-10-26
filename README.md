# IJVM
Simple software implementation in C++ of the IJVM ISA (Mic-1), as described in Structured Computer Organization (Tanenbaum, 2013). Just for fun.  

---

The IJVM architecture is a push/pop architecture, implementing a simplification of the instruction set of the Java virtual machine. Its memory consists of a constand pool (CP) and a stack for data, and a separate program memory. Mic-1 is the first iteration presented in the textbook, stripped of optimization designs such as pipelining.  
![IJVM ISA](https://github.com/akberg/IJVM/blob/master/IJVM/ijvm_mic1.PNG)

## Project overview

**ijvm.h**  
Defines the processor as a class, with all registers and pointers to stack and CP as fields. Member methods:
* constructor: Initialize processor with pointers to program and data memory.
* display(): Display information, by default implemented to use the command line.
* cycle(): Run one cycle.

**Memory.h**  
Holds memory arrays. The program as an `unsigned char` array, and the stack as an `unsigned int` array of fixed size. the constant pool goes at the bottom of the stack. Next up will be allocating memory according some settings, and reading the program and constant pool from a binary file. Finally an assembler produce a binary from at IJVM-assembly source file.

**ControlStore.h**  
Defines the Microinstruction as a class, with all flags as fields. Also defines the control store as an array sized 512 of microinstructions. The 24-bit microinstruction could have fitted in a 32-bit `integer` type, however space is not a concern so a class was chosen for readability and ease of implementation. 
