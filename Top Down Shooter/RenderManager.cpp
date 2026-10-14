#include "RenderManager.h"


// Draw things inputted
void RenderManager::Draw(RenderWindow* _window, Map* _currentMap)
{
	for (int i = 0; i < _currentMap->tiles.size(); i++)
	{
		_window->draw(*_currentMap->tiles[i]);
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

