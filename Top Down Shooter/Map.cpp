#include "Map.h"
#include <iostream>


Map::Map()
{
	
}


void Map::DisplayMap()
{
	for (int y = 0; y < m_mapWidth; y++)
	{

		for (int x = 0; x < m_mapHeight; x++)
		{
			std::cout << m_mapArray[x][y];
		}

		std::cout << std::endl;
	}
}
