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
bool inDebugMode = true;
// Arrays and vectors
std::string mapArray[1]
{
	"Maps/Map1.txt"
};
std::vector<Enemy*> enemies;
std::vector<Entity*> enemyBullets;
// Objects
Player* player = nullptr;
RenderWindow* mainWindow;
RenderManager renderer;
MapLoader mapLoader;
Map* map = nullptr;
// Functions
void UpdateCamera(View* _camera);
void RunUpdates(RenderWindow* _window, View* _camera);


int main()
{
	// Create the main window
	mainWindow = new RenderWindow(sf::VideoMode({ 800, 600 }), "SFML window");
	View camera(sf::FloatRect({ 0.f, 0.f }, { 800.0f, 600.0f }));

	player = new Player(mainWindow);
	map = mapLoader.LoadLevel(mapArray[0], &enemies, mainWindow, player, &enemyBullets);
	player->SetMapPointer(map);

	camera.zoom(1.2f);
	mainWindow->setView(camera);
	mainWindow->setFramerateLimit(60);

	while (mainWindow->isOpen())
	{
		// Checks for events related to the main window
		while (const std::optional event = mainWindow->pollEvent())
		{
			// Close window when the 'close window' button pressed
			if (event->is<sf::Event::Closed>())
			{
				mainWindow->close();
			}
		}

		// Clear the window
		mainWindow->clear();

		// Do Update Loops
		RunUpdates(mainWindow, &camera);

		// Render all level related stuff
		renderer.Draw(mainWindow, map, player, &enemies, &enemyBullets, inDebugMode);

		// Display the rendered stuff to the window
		mainWindow->display();
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