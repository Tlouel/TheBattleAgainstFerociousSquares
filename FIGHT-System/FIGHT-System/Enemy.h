#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

#include <vector>
#include <iostream>
#include <stack>
#include <set>
#include <math.h>
#include <string>

using namespace std;

class Enemy : public EntityWalk {
public:
	vector<pair<int,int>> mapPos; //Paires de données de positions du joueur

	int damage;
	int scorePerDeath; // +score quand ennemi mort

	~Enemy(){}
	Enemy(){}
	Enemy(string name);
	void Update(Player&player, float time, Enemy& walk, Map& map, float CurrentFrame);
};

#pragma region PathFindingA*

class EnemyPathFinding {

public:

	
	static int const  ROW = 20;//Lignes
	static int const  COL = 20;//Colonnes

	//Paires de valeurs pour les coordonées
	typedef pair<int, int> Pair; 
	typedef pair<double, pair<int, int>> pPair;

	//structure cellulaire : array qui peut récupérer et stocker les données de vecteur ou matrice de tailles variées
	struct cell;

	//Vérifier la validité de la cellule
	bool isValid(int row, int col);

	bool isBlocked(Map& map, int row , int col);
	
	bool isDestination(int row, int col,  Pair dest);
	
	double calculateValue(int row, int col, Pair dest);

	void pathTracing(Enemy& enemy, cell cellDetails[][COL], Pair dest); // Marque le chemin

	void searchPhase(Enemy& enemy, Map& map, Pair src, Pair dest); //Trouver la target

};
#pragma endregion
#endif 