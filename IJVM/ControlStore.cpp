#include "ControlStore.h"

MicroInstruction decode(int word)
{
	unsigned int b = (~(word & 0xfffffff0)) ^ 0xf;
	unsigned int mem = (~((word >> 4) & 0xfffffff8)) ^ 0x7;
	unsigned int c = (~((word >> 7) & 0xffffff00)) ^ 0x9;
	unsigned int alu = (~((word >> 16) & 0xffffff00)) ^ 0xff;
	unsigned int jmpc = (~((word >> 24) & 0xfffffff8)) ^ 0x7;
	unsigned int next = (~((word >> 28) & 0xffffff00)) ^ 0xff;

	bool jamz = ~(jmpc & 5) >> 1;
	bool jamn = ~(jmpc & 3) >> 2;

	return MicroInstruction((short)next, jamn, (short)alu, (short)c, (short)mem, (short)b);
}