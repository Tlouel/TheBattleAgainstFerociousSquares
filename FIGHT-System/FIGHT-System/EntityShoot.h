#pragma once

#ifndef  ENTITYSHOOT_H
#define  ENTITYSHOOT_H

#include "EntityWalk.h"

class EntityShoot : public EntityWalk {
protected:
	void AnimationShoot(EntityShoot& es, float time, float CurrentFrame);
	void Update(float time, EntityWalk& walk, Map& map, float CurrentFrame);
	void Collision(EntityWalk& walk, Map& map);

public:
	float shootRange; //Champs de tir
	float shootTime; //Temps de tir

	int damage;

	EntityShoot(){}
	EntityShoot(std::string name);
};

#endif 

