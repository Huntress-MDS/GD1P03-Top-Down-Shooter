#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapLoader.h"
#include "RenderManager.h"
using namespace sf;


// Variables

// Arrays
std::string mapArray[1]
{
	"Maps/Map1.txt"
};
// Objects
RenderManager renderer;
MapLoader mapLoader;
Map* map = mapLoader.LoadLevel(mapArray[0]);
// Functions
void UpdateCamera(View* _camera);


int main()
{
	// Create the main window
	RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");
	View camera(sf::FloatRect({ 0.f, 0.f }, { 1000.f, 600.f }));

	camera.zoom(1.2f);
	window.setView(camera);

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
		UpdateCamera(&camera);
		window.setView(camera);

		// Render all level related stuff
		renderer.Draw(&window, map);

		// Display the rendered stuff to the window
		window.display();
	}

	return 0;
}


void UpdateCamera(View* _camera)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		_camera->move({ 1.0f, 0.0f });
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		_camera->move({ -1.0f, 0.0f });
	}
}