#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "EnemyController.h"
#include "InterfaceUI.h"


using namespace sf;

int main() {

	RenderWindow window(VideoMode(1400, 1080), "TheBattleAgainstFerociousCubes");
	
	Player player("Player");
	
	InterfaceUI ui;

	PlayerController pControl;

	Clock clock;
	
	Map map;
	
	Camera cam;

	EnemyController eControl;

	

	cam.camera.reset(FloatRect(0, 0, 640, 480));

	float CurrentFrame = 0;

	while (window.isOpen()) {

		if (eControl.eNumber == 0) {
			eControl.Spawning();
		}

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed)
				window.close();
		}

		if (player.health > 0) {
			pControl.Update(time, player, CurrentFrame, cam, map);
		}
		else {
			window.close();
			ui.PlayerDeath(player);
		}

		eControl.EControl(player, time, map, CurrentFrame);

		window.setView(cam.camera);
		window.clear(Color::White);
		map.DrawMap(window);

		for (int i = 0; i < eControl.eNumber; i++) {
			window.draw(eControl.eGroup[i]->sprite);
		}

		for (int i = 0; i < player.projNum; i++) {
			window.draw(player.projectiles[i]->sprite);
		}


		window.draw(player.sprite);
		ui.ShowUI(player, window, cam);
		window.display();
	}
	
	

	
		return 0;
}

