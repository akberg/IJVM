#pragma once
#include <stdint.h>

/*
	Class dividing microinstruction
*/
class MicroInstruction {
public:
	uint16_t next_addr;
	bool jamn;
	bool jamz;
	bool jmpc;
	uint8_t alu;		// Contains shift[7:6] + alu[5:0]
	uint32_t c;
	uint32_t b;
	uint8_t mem;

	MicroInstruction(
		uint16_t next_addr,
		uint8_t jmpc,
		uint8_t alu,
		uint32_t c,
		uint8_t mem,
		uint32_t b
	) {
		this->next_addr = next_addr;
		this->jmpc = jmpc>>2 & 1;
		this->jamn = jmpc>>1 & 1;
		this->jamz = jmpc & 1;
		this->alu = alu;
		this->c = c;
		this->mem = mem;
		this->b = b;
	}

	MicroInstruction() : MicroInstruction(0, 0, 0, 0, 0, 0) {}
};

/*
	Decode a microinstruction from a single 36 (64) bit word
*/
MicroInstruction decode(int word);

enum isa { 
	BIPUSH = 0x10,			// Push byte onto stack
	DUP = 0x59,				// Copy top word on stack and push onto stack
	GOTO = 0xA7,			// Unconditional branch
	IADD = 0x60,			// Pop to words from stack; Push their sum
	IAND = 0x7E,			// Pop to words from stack; Push boolean AND
	IFEQ = 0x99,			// Pop word from stack and branch if zero
	IFLT = 0x9B,			// Pop word from stack and branch if less than zero
	IF_ICMPEQ = 0x9F,		// Pop to words from stack; Branch if equal
	IINC = 0x84,			// Add a constant to a local variable 
	ILOAD = 0x15,			// Push local variable onto stack
	INVOKEVIRTUAL = 0xB6,	// Invoke a method
	IOR = 0x80,				// Pop to words from stack; Push boolean OR
	IRETURN = 0xAC,			// Return from method with integer value
	ISTORE = 0x36,			// Pop word from stack and store in a local variable
	ISUB = 0x64,			// Pop to words from stack; Push their difference
	LDC_W = 0x13,			// Push constant from constant pool onto stack
	NOP = 0x0,				// Do nothing
	POP = 0x57,				// Delete word on top of stack
	SWAP = 0x5F,			// Swap the two top words on the stack
	WIDE = 0xC4				// Prefix intruction; next instruction has a 16-bit index
};
#define _MAR 1
#define _MDR 2
#define _PC	 4
#define _SP  8
#define _LV  16
#define _CPP 32
#define _TOS 64
#define _OPC 128
#define _H   256

/*
	B bus:
	0=MDR		5=LV
	1=PC		6=CPP
	2=MBR		7=TOS
	3=MBRU		8=OPC
	4=SP
*/

/*
	Control store to hold microinstruction set
*/
const MicroInstruction controlStore[512] = {
	// next_addr, jmpc,   shift/alu  c  mem b
	MicroInstruction(0x100, 0, 0, 0, 0, 0),						// 0x000 NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0x11, 0, 0b110101, _SP + _MAR, 0, 4),		// 0x010 BIPUSH SP = MAR = SP + 1
	MicroInstruction(0x12, 0, 0b110101, _PC, 1, 1),				// 0x011 bipush2 PC = PC + 1; fetch
	MicroInstruction(0x100, 0, 0b010100, _MDR + _TOS, 2, 2),	// 0x012 bipush3 MDR = TOS = MBR; wr
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x013 LDC_W
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0x16, 0, 0b010100, _H, 0, 5),				// 0x015 ILOAD H = LV
	MicroInstruction(0x17, 0, 0b111100, _MAR, 4, 3),			// 0x016 iload2 MAR = H + MBRU; rd
	MicroInstruction(0x18, 0, 0b110101, _MAR + _SP, 0, 4),		// 0x017 iload3 MAR = SP = SP + 1
	MicroInstruction(0x19, 0, 0b110101, _PC, 1, 1),				// 0x018 iload4 PC = PC + 1; fetch
	MicroInstruction(0x100, 0, 0b010100, _TOS, 0, 0),			// 0x019 iload5 TOS = MDR
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x020
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x030
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0x37, 0, 0b010100, _H, 0, 5),			// 0x036 ISTORE1 H = LV
	MicroInstruction(0x38, 0, 0b111100, _MAR, 0, 3),		// 0x037 istore2 MAR = H + MBRU
	MicroInstruction(0x39, 0, 0b010100, _MDR, 2, 7),		// 0x038 istore3 MDR = TOS; wr
	MicroInstruction(0x3a, 0, 0b110110, _SP + _MAR, 4, 4),	// 0x039 istore4 SP = MAR = SP - 1; rd
	MicroInstruction(0x3b, 0, 0b110101, _PC, 1, 1),			// 0x03a istore5 PC = PC + 1; fetch
	MicroInstruction(0x100, 0, 0b010100, _TOS, 0, 0),		// 0x03b istore6 TOS = MDR
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x040
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP	
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x050
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x057 POP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x059 DUP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x05f SWAP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x060 IADD
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x064 ISUB
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x070
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x07e IAND
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x080 IOR
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x084 IINC
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x090
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x099 IFEQ
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x09b IFLT
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x09f IF_ICMPEQ
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x0a0
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x0ac IRETURN
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x0b0
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x0b6 INVOKEVIRTUAL
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x0c0
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x0c4 WIDE
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x0d0
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x0e0
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x0f0
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 4, 0b110101, _PC, 1, 1),				// 0x001 Main PC = PC + 1; fetch; goto(MBR)
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// 0x110
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0),		// NOP
	MicroInstruction(0, 0, 0, 0, 0, 0)		// NOP
};
