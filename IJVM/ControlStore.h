#pragma once

class MicroInstruction {
public:
	unsigned short next_addr;
	bool jamn;
	bool jamz;
	bool jmpc;
	unsigned short alu;
	unsigned short c;
	unsigned short b;
	unsigned short mem;

	MicroInstruction() {}
	MicroInstruction(
		unsigned short next_addr,
		bool jamn,
		bool jamz,
		bool jmpc,
		unsigned short alu,
		unsigned short c,
		unsigned short mem,
		unsigned short b
	) {}
};

/*
	Decode a microinstruction from a single 36 (64) bit word
*/
MicroInstruction decode(int word);

enum opcodes { BIPUSH = 0x10, DUP = 0x59, GOTO = 0xA7, IADD = 0x60, IAND = 0x7E};

/*
	Control store to hold microinstruction set
*/
// const MicroInstruction controlStore[512] = {
//	// next_addr       jmpc   shift   alu  c  mem b
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x000 NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x010 BIPUSH
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x013 LDC_W
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x015 ILOAD
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x020
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x030
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x036 ISTORE
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x040
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x050
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x057 POP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x059 DUP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x057 POP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x05f SWAP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x060 IADD
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x064 ISUB
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x070
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x07e IAND
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x080 IOR
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x084 IINC
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x090
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x099 IFEQ
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x09b IFLT
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x09f IF_ICMPEQ
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x0a0
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x0ac IRETURN
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x0b0
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x0b6 INVOKEVIRTUAL
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x0c0
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x0c4 WIDE
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x0d0
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x0e0
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x0f0
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x100
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// 0x110
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0),		// NOP
//	const MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0)		// NOP
//};
