#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapLoader.h"
#include "RenderManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
using namespace sf;


// Variables
float cameraSpeed = 4.5f;
float cameraMoveBoxSize = 50.0f;
// Arrays and vectors
std::string mapArray[1]
{
	"Maps/Map1.txt"
};
std::vector<Enemy*> enemies;
std::vector<Entity*> enemyBullets;
// Objects
Player* player = nullptr;
RenderManager renderer;
MapLoader mapLoader;
Map* map = mapLoader.LoadLevel(mapArray[0]);
// Functions
void UpdateCamera(View* _camera);
void RunUpdates(RenderWindow* _window, View* _camera);


int main()
{
	// Create the main window
	RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");
	View camera(sf::FloatRect({ 0.f, 0.f }, { 800.0f, 600.0f }));

	player = new Player(&window, map);
	enemies.push_back(new Enemy(&window, map, player, { 100.0f, 100.0f }, &enemyBullets));
	enemies.push_back(new Enemy(&window, map, player, { -100.0f, -100.0f }, &enemyBullets));

	camera.zoom(1.2f);
	window.setView(camera);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		// Checks for events related to the main window
		while (const std::optional event = window.pollEvent())
		{
			// Close window when the 'close window' button pressed
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		// Clear the window
		window.clear();

		// Do Update Loops
		RunUpdates(&window, &camera);

		// Render all level related stuff
		renderer.Draw(&window, map, player, &enemies, &enemyBullets);

		// Display the rendered stuff to the window
		window.display();
	}

	return 0;
}


void RunUpdates(RenderWindow* _window, View* _camera)
{
	player->Update();

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update();

		for (int j = 0; j < player->m_bullets.size(); j++)
		{
			enemies[i]->Collide(player->m_bullets[j]);
		}

		if (enemies[i]->CheckIfQueuedForDeletion())
		{
			Entity* _tempPointer = enemies[i];
			enemies.erase(enemies.begin() + i);
			delete _tempPointer;
		}
	}

	for (int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i]->Update();
		enemyBullets[i]->Collide(player);

		if (enemyBullets[i]->CheckIfQueuedForDeletion())
		{
			enemyBullets.erase(enemyBullets.begin() + i);
		}
	}

	for (int i = 0; i < player->m_bullets.size(); i++)
	{
		player->m_bullets[i]->Update();
	}

	UpdateCamera(_camera);
	_window->setView(*_camera);
}


void UpdateCamera(View* _camera)
{
	if (player->getPosition().x > (_camera->getCenter().x + cameraMoveBoxSize))
	{
		_camera->move({ cameraSpeed, 0 });
	}
	else if (player->getPosition().x < (_camera->getCenter().x - cameraMoveBoxSize))
	{
		_camera->move({ -cameraSpeed, 0 });
	}

	if (player->getPosition().y > (_camera->getCenter().y + cameraMoveBoxSize))
	{
		_camera->move({ 0, cameraSpeed });
	}
	else if (player->getPosition().y < (_camera->getCenter().y - cameraMoveBoxSize))
	{
		_camera->move({ 0, -cameraSpeed });
	}
}