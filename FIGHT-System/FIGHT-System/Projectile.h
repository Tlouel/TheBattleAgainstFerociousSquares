#pragma once

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics/Image.hpp>
#include "Map.h"


class Projectile {
public:
	bool life;
	int damage;
	int direction;
	float speed;

	sf::Image projImage;
	sf::FloatRect rectProj;
	sf::Sprite sprite;
	sf::Texture texture;
	
	~Projectile(){}
	Projectile(int direction, sf::FloatRect rectProj, int damage);
	void Update(float time, Projectile& projectile, Map& map);
};

#endif 

