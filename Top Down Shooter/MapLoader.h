#pragma once
#include <string>
#include "Enemy.h"
#include "Map.h"


class MapLoader
{
public:
	Map* LoadLevel(std::string _filePath, std::vector<Enemy*>* _enemies, RenderWindow* _window, Entity* _player, std::vector<Entity*>* _bullets);
private:
	const float m_tileSize = 32;
};

