#include "Map.h"
#include "Game.h"
#include <fstream>


Map::Map() {
	
}

Map::~Map() {
	
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			srcY = atoi(&tile) * 32;
            //std::cout << tile;
			mapFile.get(tile);
			srcX = atoi(&tile) * 32;
            //std::cout << tile << ",";
			Game::AddTile(srcX, srcY, x * 64, y * 64);
            while (!(std::isalnum(mapFile.peek())) && !mapFile.eof()) {
                mapFile.ignore();
            }
		}
	}
	mapFile.close();
}
