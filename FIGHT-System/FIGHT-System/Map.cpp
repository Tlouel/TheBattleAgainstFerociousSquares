#include "Map.h"

using namespace sf;

void Map::DrawMap(RenderWindow& window) {

	Image mapImage;
	mapImage.loadFromFile("Tilemap\\Tiles.png");
	Texture mapTexture;
	mapTexture.loadFromImage(mapImage);
	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);

	for (int i = 0; i < MapH; i++) {
		for (int j = 0; j < MapW; j++)
		{
			if (map[i][j] == 0) {
				mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
			}
			else if (map[i][j] == 2) {
				mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
			}
			else if ((map[i][j] == 1)) {
				mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
			}

			mapSprite.setPosition(j * 32, i * 32);

			window.draw(mapSprite);
		}
	}
}


