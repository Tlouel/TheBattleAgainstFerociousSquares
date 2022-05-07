#include "EntityShoot.h"

EntityShoot::EntityShoot(std::string name) : EntityWalk(name){
	this->name = name;
	
	if (name == "Player"){
		shootRange = 0.02;
		shootTime = 5;
		damage = 10;
	}
}

void EntityShoot::AnimationShoot(EntityShoot& es, float time, float CurrentFrame) {}

void EntityShoot::Update(float time, EntityWalk& walk, Map& map, float CurrentFrame) {
	EntityWalk::Update(time, walk, map,  CurrentFrame);
}

void EntityShoot::Collision(EntityWalk& walk, Map& map) {
	EntityWalk::Collision(walk,  map);
}