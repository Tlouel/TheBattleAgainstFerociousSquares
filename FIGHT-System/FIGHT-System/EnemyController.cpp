#include "EnemyController.h"

//Si le mob croise le joueur, le mob meurt MAIS le joueur subit des dégâts et après on supprime le mobs de la liste 
//pareil avec la balle sauf que là le joueur gagne en point
void EnemyController::EControl(Player& player, float time, Map& map, float CurrentFrame) {
	
		if (!eGroup.empty()) {
		for (int i = 0; i < eNumber; i++) {
			eGroup[i]->Update(player, time, *eGroup[i], map, CurrentFrame);
			if (eGroup[i]->rect.intersects(player.rect)) {
				player.health -= eGroup[i]->damage;
				delete eGroup[i];
				eGroup.erase(eGroup.begin() + i);
				eNumber--;
			}
			for (int j = 0; j < player.projNum; j++) {
				if (eGroup[i]->rect.intersects(player.projectiles[j]->rectProj)) {
					eGroup[i]->health -= player.projectiles[j]->damage;
					if (eGroup[i]->health <= 0) {
						player.score += eGroup[i]->scorePerDeath;
						delete eGroup[i];
						eGroup.erase(eGroup.begin() + i);
						eNumber--;
					}
					delete player.projectiles[j];
					player.projectiles.erase(player.projectiles.cbegin() + j);
					player.projNum--;
				}
			}
		}
	}
}


void EnemyController::Spawning() {
	wave++;

	//Random
	srand(time(0));

	//Faire apparaître certains monstres en fonction de la vague

	if (wave > 10 && eNumber == 0) {

		eNumber = 4 + rand() % 12;

		for (int i = 0; i < eNumber; i++) {
			eGroup.push_back(new Enemy(Names[rand() % 2]));
			eGroup[i]->rect.left = spawnCoord[rand() % 5].first * 32, eGroup[i]->rect.top = spawnCoord[rand() % 5].second * 32;
			eGroup[i]->sprite.setPosition(eGroup[i]->rect.left, eGroup[i]->rect.top);
		}

	}
	else if (eNumber == 0 && wave % 10 == 0) {

		eNumber = 1;

		eGroup.push_back(new Enemy("ChunkyCube"));
		eGroup[0]->rect.left = 400, eGroup[0]->rect.top = 400;
		eGroup[0]->sprite.setPosition(eGroup[0]->rect.left, eGroup[0]->rect.top);
	}
	else if (eNumber == 0 && wave%3!=0) {

		eNumber = 1 + rand() % 5;

		for (int i = 0; i < eNumber; i++) {
			eGroup.push_back(new Enemy(Names[rand() % 2]));
			eGroup[i]->rect.left = spawnCoord[rand()%5].first * 32, eGroup[i]->rect.top = spawnCoord[rand()%5].second * 32;
			eGroup[i]->sprite.setPosition(eGroup[i]->rect.left, eGroup[i]->rect.top);
		}
	}
	else if(eNumber==0 && wave%3==0) {

		eNumber = 1;

		eGroup.push_back(new Enemy("BigCube"));
		eGroup[0]->rect.left = 300, eGroup[0]->rect.top = 300;
		eGroup[0]->sprite.setPosition(eGroup[0]->rect.left, eGroup[0]->rect.top);
	}
}

