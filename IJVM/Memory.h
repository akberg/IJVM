#pragma once
#include "ControlStore.h"

// Make prgm 8-bit, let PC access it
// directly and let MAR access it with 
// 4 times multiplier
uint8_t prgm[] = {
	BIPUSH, 0xdeadbeef,
	BIPUSH, 0xf00dface,
	ISTORE, 0,
	ILOAD, 0,
	NOP,
	NOP
};

// 32 bit stack, constant pool be added
// here
uint32_t stack[256] = { 0 };