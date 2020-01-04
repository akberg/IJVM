#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "ijvm.h"

void initRegShape(sf::RectangleShape &reg, sf::Vector2f pos, sf::Color color);
int virtualMachine();