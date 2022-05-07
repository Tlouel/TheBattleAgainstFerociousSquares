#pragma once

#ifndef INTERFACEUI_H
#define INTERFACEUI_H

#include "Player.h"
#include "Camera.h"

#include <sstream>

class InterfaceUI
{
public:
	sf::Font font;
	sf::Text playerHealth, playerScore;

	InterfaceUI();

	void ShowUI(Player& player, sf::RenderWindow& window, Camera &cam);
	void PlayerDeath(Player& player);
};

#endif 
