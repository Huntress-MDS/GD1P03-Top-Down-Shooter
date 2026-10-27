#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Button.h"
using namespace sf;


class RenderManager
{
public:
	void Draw(RenderWindow* _window, Map* _currentMap, Player* _player, std::vector<Enemy*>* _enemies, std::vector<Entity*>* _bullets, bool _inDebugMode);
	void Draw(RenderWindow* _window, std::vector<Button*>* _buttons);
};

