#include "SFML\Graphics.hpp"
#ifndef CAMERA_H
#define CAMERA_H
#pragma once

class Camera
{
public:
	sf::View camera;
	Camera() {}
	void MoveCamera(float x, float y);
};

#endif 
