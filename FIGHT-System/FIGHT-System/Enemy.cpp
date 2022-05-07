#include "Enemy.h"

Enemy::Enemy(string name) : EntityWalk(name){
	this->name = name;

	if (name == "Small") {
		damage = 10;
        scorePerDeath = 15;
	}
    else if (name == "Medium") {
        damage = 20;
        scorePerDeath = 30;
    }
    else if (name == "BigCube") {
        damage = 50;
        scorePerDeath = 100;
    }
    else if (name == "ChunkyCube") {
        damage = 100;
        scorePerDeath = 500;
    }
}

void Enemy::Update(Player&player, float time, Enemy& walk, Map& map, float CurrentFrame) {

    //Positions joueur et positions mob pour que ces derniers se dirigent vers le joueur
    player.x = round((int)player.sprite.getGlobalBounds().left / 32);
    player.y = round((int)player.sprite.getGlobalBounds().top / 32);

    walk.x = round((int)walk.sprite.getGlobalBounds().left/ 32);
    walk.y = round((int)walk.sprite.getGlobalBounds().top/ 32);

    //Créer une instance finder, paires de valeurs pour les enemis et paires de valeurs du joueur
    EnemyPathFinding finder;
    EnemyPathFinding::Pair ePos = make_pair(walk.y, walk.x);
    EnemyPathFinding::Pair pPos = make_pair(player.y , player.x);

    if (ePos != pPos) {
        if (walk.mapPos.empty()) {
            //A* : passe la map, la position du mob et celle du joueur
            finder.searchPhase(walk, map, ePos, pPos);
        }
        else {
            if (walk.mapPos[0].first == walk.y && walk.mapPos[0].second == walk.x) {
                auto it = walk.mapPos.begin();
                walk.mapPos.erase(it);

                //Mouvement strict sur 4 côtés
                if (walk.mapPos[0].first > walk.y)
                    walk.rect.top += walk.dy * time;
                else if (walk.mapPos[0].first < walk.y)
                    walk.rect.top -= walk.dy * time;
                else if (walk.mapPos[0].second > walk.x)
                    walk.rect.left += walk.dx * time;
                else if (walk.mapPos[0].second < walk.x)
                    walk.rect.left -= walk.dx * time;

                //Position du sprite et effacer le vecteur
                walk.sprite.setPosition(walk.rect.left, walk.rect.top);
                walk.mapPos.clear();
            }
            else {
                
                if (walk.mapPos[0].first > walk.y)
                    walk.rect.top += dy * time;
                else if (walk.mapPos[0].first < walk.y)
                    walk.rect.top -= dy * time;
                else if (walk.mapPos[0].second > walk.x)
                    walk.rect.left += dx * time;
                else if (walk.mapPos[0].second < walk.x)
                    walk.rect.left -= dx * time;

                walk.sprite.setPosition(walk.rect.left, walk.rect.top);
                walk.mapPos.clear();
            }
            
        }
    }
}

#pragma region Pathfinding A*

struct EnemyPathFinding::cell {
    //Cellules parentes
    int parent_i, parent_j;
    double f, g, h;
};

bool EnemyPathFinding::isValid(int row ,int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool EnemyPathFinding::isBlocked(Map& map, int row, int col) {
    if (map.map[row][col] == 1 || map.map[row][col] == 2) {
        return false;
    }
    else {
        return true;
    }
}

bool EnemyPathFinding::isDestination(int row, int col, Pair dest) {
    if (row == dest.first && col == dest.second) {
        return true;
    }
    else {
        return false;
    }
}

double EnemyPathFinding::calculateValue(int row, int col, Pair dest) {
    return ((double)sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}

void EnemyPathFinding::pathTracing(Enemy& mob, cell cellDetails[][COL], Pair dest) {
    int row = dest.first; 
    int col = dest.second;


    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));

        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;

        row = temp_row;
        col = temp_col;
    }

    Path.push(make_pair(row, col));

    while (!Path.empty()) {
        
        pair<int, int> p = Path.top();
        Path.pop();
        
        mob.mapPos.push_back(p);
    }

    return;
}

void EnemyPathFinding::searchPhase(Enemy& mob, Map& map, Pair src, Pair dest) {
    bool closedList[ROW][COL];

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            closedList[i][j] = false;
        }
    }

    //Tableau de structures
    cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = 1000;
            cellDetails[i][j].g = 1000;
            cellDetails[i][j].h = 1000;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }
   
    //Valeurs première cellule
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    set<pPair> openList;

    //Ajouter la première cellule
    openList.insert(make_pair(0.0, make_pair(i, j)));
    
    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();
        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        if (isValid(i - 1, j) == true) {
           
            if (isDestination(i - 1, j, dest) == true) {
                
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                
                pathTracing(mob, cellDetails, dest);
                foundDest = true;
                return;
            }
            
            else if (closedList[i - 1][j] == false && isBlocked(map, i - 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateValue(i - 1, j, dest);
                fNew = gNew + hNew;

                
                if (cellDetails[i - 1][j].f == 1000 || cellDetails[i - 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j)));

                    
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        if (isValid(i + 1, j) == true) {
           
            if (isDestination(i + 1, j, dest) == true) {
               
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                
                pathTracing(mob, cellDetails, dest);
                foundDest = true;

                return;
            }
           
            else if (closedList[i + 1][j] == false && isBlocked(map, i + 1, j) == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateValue(i + 1, j, dest);
                fNew = gNew + hNew;
               
                if (cellDetails[i + 1][j].f == 1000 || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                 
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        if (isValid(i, j + 1) == true) {
            
            if (isDestination(i, j + 1, dest) == true) {
               
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                
                pathTracing(mob, cellDetails, dest);
                foundDest = true;

                return;
            }

            else if (closedList[i][j + 1] == false && isBlocked(map, i, j + 1) == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateValue(i, j + 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j + 1].f == 1000 || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i, j + 1)));

                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        if (isValid(i, j - 1) == true) {
           
            if (isDestination(i, j - 1, dest) == true) {
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
               
                pathTracing(mob, cellDetails, dest);
                foundDest = true;

                return;
            }

          
            else if (closedList[i][j - 1] == false && isBlocked(map, i, j - 1) == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateValue(i, j - 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j - 1].f == 1000 || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(fNew,make_pair(i, j - 1)));

                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }
    }
}
#pragma endregion