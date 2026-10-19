#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapLoader.h"
#include "RenderManager.h"
#include "Player.h"
using namespace sf;


// Variables
float cameraSpeed = 4.5f;
float cameraMoveBoxSize = 50.0f;
// Arrays
std::string mapArray[1]
{
	"Maps/Map1.txt"
};
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
		renderer.Draw(&window, map, player);

		// Display the rendered stuff to the window
		window.display();
	}

	return 0;
}


void RunUpdates(RenderWindow* _window, View* _camera)
{
	player->Update();

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