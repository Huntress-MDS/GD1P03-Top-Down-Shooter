#include "RenderManager.h"


// Draw things inputted
void RenderManager::Draw(RenderWindow* _window, Map* _currentMap, Player* _player, std::vector<Enemy*>* _enemies, std::vector<Entity*>* _bullets)
{
	for (int i = 0; i < _currentMap->tiles.size(); i++)
	{
		_window->draw(*_currentMap->tiles[i]);
	}

	_window->draw(*_player);

	for (int i = 0; i < _enemies->size(); i++)
	{
		_window->draw(*_enemies->at(i));
	}

	for (int i = 0; i < _bullets->size(); i++)
	{
		_window->draw(*_bullets->at(i));
	}

	for (int i = 0; i < _player->m_bullets.size(); i++)
	{
		_window->draw(*_player->m_bullets[i]);
	}
}


// Draw inputted buttons
//void RenderManager::Draw(RenderWindow* _window, std::vector<Button*>* _buttons)
//{
//	for (int i = 0; i < _buttons->size(); i++)
//	{
//		_window->draw(*_buttons->at(i));
//		_window->draw(*_buttons->at(i)->m_text);
//	}
//}

