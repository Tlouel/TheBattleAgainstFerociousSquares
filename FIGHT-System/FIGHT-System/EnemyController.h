#pragma once

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Enemy.h"
#include "PlayerController.h"
#include "Map.h"

#include <ctime>
#include <math.h>
#include <vector>
#include <string>

using namespace std;


class EnemyController {
public:
	int wave = 0;
	int eNumber = 0;
	string Names[2] = { "Small", "Medium" };
	
	EnemyController(){}

	void Spawning(); //Méthode de Spawn
	void EControl(Player& player,float time, Map& map, float CurrentFrame);//Méthode de contrôle/d'état de Spawn
	
	vector<Enemy*> eGroup; //spawn de groupes de mobs composés de différents ennemis
	vector<pair<int, int>> spawnCoord = {make_pair(7,15), make_pair(8,5), make_pair(2,8), make_pair(5,3), make_pair(10,8)}; //Paires de valeurs pour les coordoonées de spawn
	
};
#endif 
