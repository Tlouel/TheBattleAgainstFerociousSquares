#include "EntityWalk.h"

EntityWalk::EntityWalk(std::string name) : Entity(name){
	this->name = name;

	if (name == "Player"){
		dx = 0.05;
		dy = 0.05;
	}
	else if (name == "Small") {
		dx = 0.025;
		dy = 0.025;
	}
	else if (name == "Medium") {
		dx = 0.05;
		dy = 0.05;
	}
	else if (name == "BigCube") {
		dx = 0.05;
		dy = 0.05;
	}
	else if (name == "ChunkyCube") {
		dx = 0.05;
		dy = 0.05;
	}
}
#pragma region Animation
void EntityWalk::AnimationWalk(EntityWalk& walk, float time, float CurrentFrame) {
	

	if (walk.dy<0) {
		if (CurrentFrame > 0.008 && walk.name!= "PlayerUp") {
			walk.image.loadFromFile("Sprite\\" + walk.name + "-TopAnim.png");
			CurrentFrame -= 0.08;
		}
		else {
			walk.image.loadFromFile("Sprite\\" + walk.name + "-Top.png");
		}
	}
	else if (walk.dx>0) {
		if (CurrentFrame > 0.008 && walk.name != "PlayerUp") {
			walk.image.loadFromFile("Sprite\\" + walk.name + "-RightAnim.png");
			CurrentFrame -= 0.08;
		}
		else {
			walk.image.loadFromFile("Sprite\\" + walk.name + "-Right.png");
		}
	}
	else if (walk.dy>0) {
		if (CurrentFrame > 0.008 && walk.name != "PlayerUp") {
			walk.image.loadFromFile("Sprite\\" + walk.name + "-DownAnim.png");
			CurrentFrame -= 0.08;
		}
		else {
			walk.image.loadFromFile("Sprite\\" + walk.name + "-Down.png");
		}
		
	}
	else if (walk.dx < 0) {
		walk.image.loadFromFile("Sprite\\" + walk.name + "-Left.png");
		if (CurrentFrame > 0.008 && walk.name != "PlayerUp") {
			walk.image.loadFromFile("Sprite\\" + walk.name + "-LeftAnim.png");
			CurrentFrame -= 0.08;
		}
	}
	else {
		walk.image.loadFromFile("Sprite\\" + walk.name + ".png");
	}
	walk.texture.loadFromImage(image);
	walk.sprite.setTexture(texture);
}
#pragma endregion

void EntityWalk::Collision(EntityWalk& walk, Map & map) {


	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {

			if (map.map[i][j] == 1 || map.map[i][j] == 2) {
				if (dx > 0)
					rect.left = j * 32 - rect.width;
				else if (dx < 0) 
					rect.left = j * 32 + 32;
				else if (dy > 0)
					rect.top = i * 32 - rect.height;
				else if (dy < 0)
					rect.top = i * 32 + 32;
			}

		}
	}
}


void EntityWalk::Update(float time, EntityWalk& walk, Map & map, float CurrentFrame) {

	//Coordonées mobs

	walk.x = round((int)walk.sprite.getPosition().x / 32);
	walk.y = round((int)walk.sprite.getPosition().y / 32);

	//Temps, vitesse pour définir la valeur rect
	rect.left += dx * time;
	rect.top += dy * time;

	Collision(walk, map);

	walk.sprite.setPosition(rect.left, rect.top);

	AnimationWalk(walk, time, CurrentFrame);
	dx = 0;
	dy = 0;
}

