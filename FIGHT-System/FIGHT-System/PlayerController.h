#pragma once

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Player.h"
#include "Camera.h"

class PlayerController {
public:
	PlayerController() {}
	void Update(float time, Player& player, float CurrentFrame, Camera& cam, Map& map);

};
#endif

