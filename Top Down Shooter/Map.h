#pragma once
#include "Tile.h"
#include <vector>
using namespace sf;


class Map
{
public:
	const static int m_mapWidth = 50;
	const static int m_mapHeight = 50;
	std::vector<Tile*> tiles;
	Map();
	void DisplayMap();
protected:
	friend class MapLoader;
	char m_mapArray[m_mapWidth][m_mapHeight];
};

