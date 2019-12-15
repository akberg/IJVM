#include "ControlStore.h"

short alu(short A, short B, short func) {
	switch (func) {
	case 0b011000:
		return A;
	case 0b010100:
		return B;
	case 0b011010:
		return ~A;
	case 0b101100:
		return ~B;
	case 0b111100:
		return A + B;
	case 0b111101:
		return A + B + 1;
	case 0b111001:
		return A + 1;
	default:
		return 0;
	}
}

void ijvm() {
	// Need a way to emulate a memory
	unsigned short memory[256];

	// Registers kept as 32 bit integers
	unsigned short PC = 0;
	unsigned short OPC = 0;
	unsigned short MBR = 0;
	unsigned short MAR = 0;
	unsigned short MDR = 0;
	unsigned short TOS = 0;
	unsigned short CPP = 0;
	unsigned short SP = 0;
	unsigned short LV = 0;
	unsigned short H = 0;

	// Busses
	unsigned short B;
	unsigned short C;


	
	unsigned short MPC = 0x0;

	MicroInstruction MIR;

	while (1)
	{
		// Fetch 
		MIR = MicroInstruction(0, 0, 0, 0, 0, 0, 0, 0);//controlStore[MPC];
		MPC = MIR.next_addr;
		
		// Drive B bus
		switch (MIR.b)
		{
		case 0:
			B = MDR;
			break;
		case 1:
			B = PC;
			break;
		case 2:
			B = (MBR ^ 0xff7f == 0xffff) ? MBR & 0xff00 : MBR;
			break;
		case 3:
			B = MBR;
			break;
		case 4:
			B = SP;
			break;
		case 5:
			B = LV;
			break;
		case 6:
			B = CPP;
			break;
		case 7:
			B = TOS;
			break;
		case 8:
			B = OPC;
			break;
		default:
			B = 0;

		}
		
		C = alu(H, B, MIR.alu);

		// branch conditions
		if (C > 0xefff && MIR.jamn || C == 0 && MIR.jamz || MIR.jmpc) 
		{
			MPC &= 0b100000000;
		}

		// Store C

	}
}