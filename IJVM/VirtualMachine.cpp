#include "virtualMachine.h"
#include <iostream>

void initRegShape(sf::RectangleShape &reg, sf::Vector2f pos, sf::Color color) {
	reg.setPosition(pos);
	reg.setFillColor(color);
}

int virtualMachine() {
	const int windowHeigh = 760, windowWidth = 760;
	const int regHeigh = 20, regWidth = 160;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeigh), "Virtual Machine");
	
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("ijvm_mic1.png", sf::IntRect(0, 0, 760, 760))) {
		std::cout << "Image file not found" << std::endl;
		return -1;
	}
	sf::Sprite background;
	background.setColor(sf::Color(0, 255, 0));
	background.setTexture(backgroundTexture);


	sf::RectangleShape PC(sf::Vector2f(regWidth, regHeigh));		// Program Counter
	sf::RectangleShape OPC(sf::Vector2f(regWidth, regHeigh));		// Old Program Counter
	sf::RectangleShape MBR(sf::Vector2f(regWidth, regHeigh));		// Memory Buffer Read; MPC if jmpc is set
	sf::RectangleShape MAR(sf::Vector2f(regWidth, regHeigh));		// Memory Address Read
	sf::RectangleShape MDR(sf::Vector2f(regWidth, regHeigh));		// Memory Data Read
	sf::RectangleShape TOS(sf::Vector2f(regWidth, regHeigh));		// Top of stack
	sf::RectangleShape CPP(sf::Vector2f(regWidth, regHeigh));		// Constant Pool Pointer
	sf::RectangleShape SP(sf::Vector2f(regWidth, regHeigh));		// Stack pointer
	sf::RectangleShape LV(sf::Vector2f(regWidth, regHeigh));		// Local Variable
	sf::RectangleShape H(sf::Vector2f(regWidth, regHeigh));			// H register
	
	sf::RectangleShape registers[] = { PC, OPC, MBR, MAR, MDR, TOS, CPP, SP, LV, H };
	for (int i = 0; i < 10; i++) {
		initRegShape(registers[i], sf::Vector2f(70, i * 70 + 50), sf::Color(148, 148, 148));
	}


	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {			// Takle eventuelle hendelser
			if (event.type == sf::Event::Closed) {	// Avslutt hvis vinduet lukkes
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				std::cout << sf::Mouse().getPosition().x <<", "<< sf::Mouse().getPosition().y << std::endl;
			}
		}

		window.clear();
		window.draw(background);

		/*for (sf::RectangleShape reg : registers) {
			window.draw(reg);
		}*/

		window.display();
	}
	return 0;
}