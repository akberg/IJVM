# IJVM
Simple software implementation in C++ of the IJVM ISA (Mic-1), as described in Structured Computer Organization (Tanenbaum, 2013). Just for fun. Implementation is done with a focus on the described architecture, rather than performance, writing out the ControlStore, buses and ALU instead of factoring the ISA into functions.  

---

The IJVM architecture is a push/pop architecture, implementing a simplification of the instruction set of the Java virtual machine. Its memory consists of a constand pool (CP) and a stack for data, and a separate program memory. Mic-1 is the first iteration presented in the textbook, stripped of optimization designs such as pipelining.  
![IJVM ISA](https://github.com/akberg/IJVM/blob/master/IJVM/ijvm_mic1.PNG)

## The IJVM instruction set
The table below gives the IJVM ISA as presented in the textbook and implemented here. Each instruction consists of an opcode and sometimes an operand, such as a memory offset or a constant. The first column gives the hexadecimal encoding of the instruction. The second gives its assembly language mnemonic. The third gives a brief description of its effect (Tanenbaum, 2013). 

| **Hex** | **Opcode**           | **Description**                                         |
|---------|----------------------|---------------------------------------------------------|
| 0x10    | BIPUSH *byte*        | Push byte onto stack                                    |  
| 0x59    | DUP                  | Copy top word on stack and push onto stack              |  
| 0xA7    | GOTO *offset*        | Unconditional branch                                    |  
| 0x60    | IADD                 | Pop two words from stack; push their sum                |
| 0x7E    | IAND                 | Pop two words from stack; push Boolean AND              |
| 0x99    | IFEQ *offset*        | Pop word from stack and branch if it is zero            |
| 0x9B    | IFLT *offset*        | Pop word from stack and branch if it is less than zero  |
| 0x9F    | IF_ICMPEQ *offset*   | Pop two words from stack; branch if equal               |
| 0x84    | IINC *varnum const*  | Add a constant to a local variable                      |
| 0x15    | ILOAD *varnum*       | Push local variable onto stack                          |
| 0xB6    | INVOKEVIRTUAL *disp* | Invoke a method                                         |
| 0x80    | IOR                  | Pop two words from stack; push Boolean OR               |
| 0xAC    | IRETURN              | Return from method with integer value                   |
| 0x36    | ISTORE *varnum*      | Pop word from stack and store in local variable         |
| 0x64    | ISUB                 | Pop two words from stack; push their difference         |
| 0x13    | LDC_W *index*        | Push constant from constant pool onto stack             |
| 0x00    | NOP                  | Do nothing                                              |
| 0x57    | POP                  | Delete word on top of stack                             |
| 0x5F    | SWAP                 | Swap the two top words on the stack                     |
| 0xC4    | WIDE                 | Prefix instruction; next instruction has a 16-bit index |

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

### TODO
* Implement the rest of the ISA.
* Get rid of the VS project overhead in favor of a Makefile or something.
* Implement an assembler and read binary file.
