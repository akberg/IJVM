#include "ControlStore.h"
#include "ijvm.h"
#include <iostream>

IJVM::IJVM(uint8_t *pgmem, uint32_t *memory, uint32_t sp, uint32_t cp, bool debug)
: SP(sp), prgm(pgmem), memory(memory), debug(debug) {
	MBR = prgm[0];
	LV = sp;
	MPC = 0x100;
}

short alu(uint32_t A, uint32_t B, uint8_t func) {
	// Return ALU result of given func
	switch (func & 0b00111111) {
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
	case 0b110101:
		return B + 1;
	case 0b111111:
		return B - A;
	case 0b110110:
		return B - 1;
	case 0b111011:
		return ~A + 1; // -A
	case 0b001100:
		return A & B;
	case 0b011100:
		return A | B;
	case 0b110001:
		return 1;
	case 0b010010:
		return -1;
	case 0b010000:
	default:
		return 0;
	}
}

void IJVM::setPC(uint32_t pc) { this->PC = pc; }
void IJVM::setSP(uint32_t sp) { this->SP = sp; }


void IJVM::cycle(bool debug) {

	if (debug) getchar();

	// Fetch microinstruksjon
	MIR = controlStore[MPC];
		
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
		B = (MBR >= 0x8000) ? MBR ^ 0xff00 : MBR;
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
	
	// ALU operation
	C = alu(H, B, MIR.alu);

	// Shift operation
	if (MIR.alu & 128) 
	{
		C = C << 16;
	}
	else if (MIR.alu & 64)
	{
		C = C >> 8;
	}

	// Next microinstruction
	MPC = MIR.jmpc ? MBR : MIR.next_addr;

	// branch conditions
	if (MIR.jamn || MIR.jamz)
	{
		// Add 9th bit
		MPC |= 0b100000000;
	}
	if (MIR.jmpc)
	{
		MPC |= MBR;
	}

	// Store C in appropriate registers
	{
		if ((MIR.c >> 0) & 1) MAR = C;
		if ((MIR.c >> 1) & 1) MDR = C;
		if ((MIR.c >> 2) & 1) PC = C;
		if ((MIR.c >> 3) & 1) SP = C;
		if ((MIR.c >> 4) & 1) LV = C;
		if ((MIR.c >> 5) & 1) CPP = C;
		if ((MIR.c >> 6) & 1) TOS = C;
		if ((MIR.c >> 7) & 1) OPC = C;
		if ((MIR.c >> 8) & 1) H = C;
	}

	// Instruction fetch
	if (fetching)
	{
		MBR = fetched;
		fetching = false;
	}
	if (MIR.mem & 1)
	{
		fetched = prgm[PC];
		fetching = true;
	}

	// Memory read or write
	if (MIR.mem & 2)
	{
		// Write
		memory[MAR] = MDR;
	}
	else if (MIR.mem & 4)
	{
		// Read
		MDR = memory[MAR];
	}
}

