#include "Camera.h"

void Camera::MoveCamera(float x, float y) {

	float mapx = x; 
	float mapy = y;

	//Conditions de changement de coordonnées de la cam

	if (x < 320)
		mapx = 320;
	if (x > 962)
		mapx = 962;
	if (y < 240)
		mapy = 240;
	if (y > 554)  
		mapy = 554;

	camera.setCenter(mapx, mapy);
}