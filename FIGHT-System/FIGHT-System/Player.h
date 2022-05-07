#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include"EntityShoot.h"
#include "Projectile.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Player : public EntityShoot {
public:
	int projNum;
	int score = 0;

	Player() {}
	Player(string name);

	void AnimationPlayer(Player& player);
	void Update(float time, EntityWalk& walk, Map& map, float CurrentFrame);
	void Collision(EntityWalk& walk, Map& map);
	void Upgrade(Player& player);//Changement de phase, level up + bonus
	
	vector <Projectile*> projectiles;
};
#endif 