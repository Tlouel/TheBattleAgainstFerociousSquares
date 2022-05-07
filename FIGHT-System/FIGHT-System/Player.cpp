#include "Player.h"
#include "PlayerController.h"


Player::Player(string name) : EntityShoot(name) {
	this->name = name;
	projNum = 0;
}

void Player::AnimationPlayer(Player & player) {}
 
void Player::Update(float time, EntityWalk& walk, Map& map, float CurrentFrame) {
	EntityShoot::Update(time, walk , map, CurrentFrame);

}

void Player::Collision(EntityWalk& walk, Map& map) {
	EntityShoot::Collision(walk, map);
}

void Player::Upgrade(Player& player) {

	//Player ++ level selon le score et les bonus

	if (player.score >= 300 && player.name != "PlayerUp") {
		player.name = "PlayerUp";
		player.health = 200;
		player.score -= 50;
		player.damage = 20;
	}
	else if (player.score >= 500 && player.name == "PlayerUp") {
		player.health = 400;
		player.damage = 40;
		player.score -= 500;
	}
	else if (player.score >= 100 && player.name == "PlayerUp") {
		player.health = 200;
		player.score -= 100;
	}

}