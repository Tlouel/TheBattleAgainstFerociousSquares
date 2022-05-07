#include "Entity.h"

using namespace sf;

Entity::Entity(std::string name) {

	this->name = name;

	if (name == "Player") {
		health = 100;
		rect = FloatRect(150, 150, 26, 32);
	}
	else if (name == "Small") {
		health = 10;
		rect = FloatRect(100, 50, 29, 32);
	}
	else if (name == "Medium") {
		health = 20;
		rect = FloatRect(48, 48, 25, 32);
	}
	else if (name == "BigCube") {
		health = 100;
		rect = FloatRect(48, 48, 65, 80);
	}
	else if (name == "ChunkyCube"){
		health = 200;
		rect = FloatRect(48, 48, 97, 98);
	}

	image.loadFromFile("Sprite\\"+ name + ".png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}


