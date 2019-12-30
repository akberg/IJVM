#include "ijvm.h"
#include "Memory.h"
#include <iostream>

int main() {
	IJVM computer(prgm, stack, 0, 0);

	// TODO: Load a program into a memory.
	//		 Define a stack and other memory locations

	while (1) {
		// Run one cycle
		computer.cycle(false);
		// Update
		//computer.display();
		//std::getchar();
	}
}

void IJVM::display() {
	system("cls");
	std::cout << 
		"MAR: " << MAR << "\t\tMPC: " << MPC << "\tStack: " << memory[0] << std::endl <<
		"MDR: " << MDR << "\t\t     " << "\t     : " << memory[1] << std::endl <<
		"PC:  " << PC << "\t\t      " << "\t      : " << memory[2] << std::endl <<
		"MBR: " << MBR << "\t\t      " << "\t      : " << memory[3] << std::endl <<
		"SP:  " << SP << "\t\t      " << "\t      : " << memory[4] << std::endl <<
		"LV:  " << LV << "\t\t      " << "\t      : " << memory[5] << std::endl <<
		"CPP: " << CPP << "\t\t      " << "\t      : " << memory[6] << std::endl <<
		"TOS: " << TOS << "\t\t      " << "\t      : " << memory[7] << std::endl <<
		"OPC: " << OPC << std::endl <<
		"H:   " << H << std::endl;
}