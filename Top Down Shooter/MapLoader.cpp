#include "MapLoader.h"
#include <fstream>
#include <iostream>


// function for loading the level from a string
Map* MapLoader::LoadLevel(std::string _filePath, std::vector<Enemy*>* _enemies, RenderWindow* _window, Entity* _player, std::vector<Entity*>* _bullets)
{
	std::fstream loadFileStream;
	Map* map = new Map();
	// open the file
	loadFileStream.open(_filePath, std::ios::in);

	std::string loadFileString;
	int lineCount = 0;

	// Updates the level array to use the characters from the file
	while (loadFileStream.is_open())
	{
		while (std::getline(loadFileStream, loadFileString))
		{
			for (int i = 0; i < loadFileString.size(); i++)
			{
				map->m_mapArray[i][lineCount] = loadFileString[i];
			}

			lineCount++;
		}

		loadFileStream.close();
	}

	// A nested for loop to create tiles and add them to a vector
	// each tile is different based on the character in the array
	for (int y = 0; y < map->m_mapHeight; y++)
	{
		for (int x = 0; x < map->m_mapWidth; x++)
		{
			// std::cout << "x: " << x << " y: " << y << " Level: " << levelArray[x][y] << std::endl;

			if (map->m_mapArray[x][y] == 'x')
			{
				// Spawn bocks
				Tile* newBox = new Tile("Wall", m_tileSize, Vector2f(float(x), float(y)));
				map->tiles.push_back(newBox);
			}
			else if (map->m_mapArray[x][y] == 'g')
			{
				// Spawn goal
				Tile* newBox = new Tile("Goal", m_tileSize, Vector2f(float(x), float(y)));
				map->tiles.push_back(newBox);
			}
			else if (map->m_mapArray[x][y] == 's')
			{
				// Move player to starting pos
				_player->OveridePosition(Vector2f(float(x * m_tileSize), float(y * m_tileSize)));
			}
			else if (map->m_mapArray[x][y] == 'p')
			{
				// Spawn goal
				Tile* newBox = new Tile("Pit", m_tileSize, Vector2f(float(x), float(y)));
				map->tiles.push_back(newBox);
			}
			else if (map->m_mapArray[x][y] == 'e')
			{
				// Spawn Enemies
				Enemy* newEnemy = new Enemy(_window, map, _player, { float(x * m_tileSize), float(y * m_tileSize) }, _bullets);
				_enemies->push_back(newEnemy);
			}
		}
	}

	return map;
}