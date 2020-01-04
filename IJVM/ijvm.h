#pragma once
#include <stdint.h>
#include "ControlStore.h"
/*
	\brief IJVM Mic-1 architecture
*/
class IJVM {
private:
	// Need a way to emulate a memory: 256 32-bit words
	uint32_t *memory;
	uint8_t *prgm;

	// Registers kept as 32 bit integers
	uint32_t PC = 0;		// Program Counter
	uint32_t OPC = 0;		// Old Program Counter
	uint32_t MBR = 0;		// Memory Buffer Read; MPC if jmpc is set
	uint32_t MAR = 0;		// Memory Address Read
	uint32_t MDR = 0;		// Memory Data Read
	uint32_t TOS = 0;		// Top of stack
	uint32_t CPP = 0;		// Constant Pool Pointer
	uint32_t SP = 0;		// Stack pointer
	uint32_t LV = 0;		// Local Variable
	uint32_t H = 0;			// H register

	// Busses
	uint32_t B;			// B bus, for alu B input
	uint32_t C;			// C bus, for alu output

	uint32_t MPC = 0x0;	// Microprogram address, be set to Main1 address
	MicroInstruction MIR;

	uint8_t fetched = 0;	// Simulation of hardware latency 
	bool fetching = false;	// when fetching instructions

	bool debug;

public:
	IJVM() : debug(false) {};
	IJVM(bool debug) : debug(debug) {};
	/*
		@brief Full constructor. Implementing method area,
		constant pool and stack/local variable as separate
		arrays, as they have different properties in 
		terms of permissions and word size
		@param sp		Stack Pointer
		@param pgmem	Pointer to Instruction memory (8 bit)
		@param memory	Pointer to memory (32 bit)
	*/
	IJVM(uint8_t *pgmem, uint32_t *memory, uint32_t sp, uint32_t cp, bool debug = false);
	/*
		@brief Run one cycle
	*/
	void cycle(bool debug);

	void setSP(uint32_t sp);
	void setPC(uint32_t pc);

	uint32_t getPC() { return PC; }			// Program Counter
	uint32_t getOPC() { return OPC; }		// Old Program Counter
	uint32_t getMBR() { return MBR; }		// Memory Buffer Read; MPC if jmpc is set
	uint32_t getMAR() { return MAR; }		// Memory Address Read
	uint32_t getMDR() { return MDR; }		// Memory Data Read
	uint32_t getTOS() { return TOS; }		// Top of stack
	uint32_t getCPP() { return CPP; }		// Constant Pool Pointer
	uint32_t getSP() { return SP; }			// Stack pointer
	uint32_t getLV() { return LV; }			// Local Variable
	uint32_t getH() { return H; }			// H register
	uint32_t getMPC() { return MPC; }	// Microprogram address, be set to Main1 address

	uint32_t getBusB() { return B; }			// B bus, for alu B input
	uint32_t getBusC() { return C; }			// C bus, for alu output

	MicroInstruction getMIR() { return MIR; }

	void display();
};

short alu(uint32_t A, uint32_t B, uint8_t func);