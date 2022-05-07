#include "InterfaceUI.h"

using namespace sf;

InterfaceUI::InterfaceUI() {

	font.loadFromFile("bahnschrift.ttf");
	playerHealth.setFont(font);
	playerScore.setFont(font);

	playerHealth.setFillColor(Color::Green);
	playerScore.setFillColor(Color::Red);

	playerHealth.setCharacterSize(15);
	playerScore.setCharacterSize(15);

	playerHealth.setPosition(25, 25);
	playerScore.setPosition(25, 50);
}


void InterfaceUI::ShowUI(Player& player, RenderWindow& window, Camera & cam) {

	playerHealth.setPosition(cam.camera.getCenter().x - 315, cam.camera.getCenter().y - 240);
	playerScore.setPosition(cam.camera.getCenter().x - 315, cam.camera.getCenter().y - 220);

	std::ostringstream playerscore;
	std::ostringstream playerhp;

	playerscore << player.score;
	playerhp << player.health;

	if (player.health < 0 || player.score < 0) {
		playerHealth.setString("Player Health : 0");
		playerScore.setString("Player Score : 0");
	}
	else {
		playerHealth.setString("Player Health: " + playerhp.str());
		playerScore.setString("Player Score: " + playerscore.str());
	}
	
	window.draw(playerHealth);
	window.draw(playerScore);
}

void InterfaceUI::PlayerDeath(Player&player) {

	RenderWindow window(sf::VideoMode(800, 600), "Results");
	sf::Text text;
	std::ostringstream playerScore;

	playerScore << player.score;

	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(Color::Black);
	text.setPosition(window.getSize().x / 2 - 110, window.getSize().y / 2 - 25);
	text.setString("Your score is :" + playerScore.str());

	while (window.isOpen()) {
	
		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)

				window.close();
		}

		window.clear(Color::White);
		window.draw(text);
		window.display();
		
	}
}