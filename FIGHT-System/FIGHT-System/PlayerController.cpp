#include "PlayerController.h"

using namespace sf;

void PlayerController::Update(float time, Player& player, float CurrentFrame, Camera & cam, Map & map) {
	
	CurrentFrame += 0.05 * time;

	if (player.shootTime <= 5) {
		player.shootTime += player.shootRange;
	}



	else if (Keyboard::isKeyPressed(Keyboard::U)) {
		player.Upgrade(player);
	}
	//Ajouter balle, réinitialiser le temps de tir et augmenter le nombres de projectiles

	else if (Keyboard::isKeyPressed(Keyboard::Right) && player.shootTime >= 5){
		player.projectiles.push_back(new Projectile(1, FloatRect(player.rect.left, player.rect.top, 16, 16), player.damage));
		player.shootTime = 0;
		player.projNum++;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up) && player.shootTime >= 5) {
		player.projectiles.push_back(new Projectile(2, FloatRect(player.rect.left, player.rect.top, 16, 16), player.damage));
		player.shootTime = 0;
		player.projNum++;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && player.shootTime >= 5) {
		player.projectiles.push_back(new Projectile(3, FloatRect(player.rect.left, player.rect.top, 16, 16), player.damage));
		player.shootTime = 0;
		player.projNum++;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && player.shootTime >= 5) {
		player.projectiles.push_back(new Projectile(4, FloatRect(player.rect.left, player.rect.top, 16, 16), player.damage));
		player.shootTime = 0;
		player.projNum++;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		player.dy = -0.05;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		player.dx = -0.05;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player.dy = 0.05;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.dx = 0.05;

	}
	cam.MoveCamera(player.sprite.getPosition().x, player.sprite.getPosition().y);

	for (int i = 0; i < player.projNum; i++) {
		if (player.projectiles[i]->life) {
			player.projectiles[i]->Update(time, *player.projectiles[i], map);
		}
		else {
			delete player.projectiles[i];
			player.projectiles.erase(player.projectiles.cbegin() + i);
			player.projNum--;
		}
	}

	player.Update(time, player, map, CurrentFrame);
}


