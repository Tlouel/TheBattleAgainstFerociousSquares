#pragma once

#ifndef ENTITYWALK_H
#define ENTITYWALK_H

#include "Entity.h"
#include "Map.h"

class EntityWalk : public Entity {
protected:
	void AnimationWalk(EntityWalk& walk, float time, float CurrentFrame);
	void Update(float time, EntityWalk& walk, Map& map, float CurrentFrame);
	void Collision(EntityWalk& walk, Map& map); //Collision avec la map (tiles)

public:
	int x, y; //Coord sup gauche
	float dx, dy; //Vitesse

	EntityWalk(){}
	EntityWalk(std::string name);
};


#endif


