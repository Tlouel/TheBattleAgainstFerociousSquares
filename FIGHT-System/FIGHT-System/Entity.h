#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using std::string;

class Entity {
public:
	string name;
	int health;

	sf::FloatRect rect;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	Entity(){}
	Entity(std::string name);
};
#endif 
