#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"
#include "Player.h"
using namespace sf;


class RenderManager
{
public:
	void Draw(RenderWindow* _window, Map* _currentMap, Player* _player);
	//void Draw(RenderWindow* _window, std::vector<Button*>* _buttons);
};

