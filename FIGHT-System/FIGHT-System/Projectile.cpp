#include "Projectile.h"

#include <iostream>

using namespace sf;

Projectile::Projectile(int direction, FloatRect rectProj, int damage) {

	this->direction = direction;
	this->rectProj = rectProj;
	this->damage = damage;

	life = true;
	speed = 0.2f;
	
	projImage.loadFromFile("Sprite\\bullet.png");
	projImage.createMaskFromColor(Color(0, 0, 0));
	texture.loadFromImage(projImage);
	sprite.setTexture(texture);
}

void Projectile::Update(float time, Projectile& bullet, Map & map) {

	for (int i = bullet.rectProj.top / 32; i < (bullet.rectProj.top + bullet.rectProj.height) / 32; i++) {
		for (int j = bullet.rectProj.left / 32; j < (bullet.rectProj.left + bullet.rectProj.width) / 32; j++) {
		
			if (map.map[i][j] == 1 || map.map[i][j] == 2) {
				bullet.life = false;
			}

		}
	}

	if (bullet.direction == 1) 
		bullet.rectProj.left += bullet.speed * time;
	else if (bullet.direction == 2) 
		bullet.rectProj.top -= bullet.speed * time;
	else if (bullet.direction == 3)
		bullet.rectProj.left -= bullet.speed * time;
	else if (bullet.direction == 4)
		bullet.rectProj.top += bullet.speed * time;

	bullet.sprite.setPosition(bullet.rectProj.left, bullet.rectProj.top);
}