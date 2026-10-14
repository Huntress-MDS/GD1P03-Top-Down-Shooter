#pragma once
#include <string>
#include "Map.h"


class MapLoader
{
public:
	Map* LoadLevel(std::string _filePath);
private:
	const float m_tileSize = 32;
};

