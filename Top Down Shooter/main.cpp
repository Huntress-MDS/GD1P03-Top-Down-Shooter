#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapLoader.h"
#include "RenderManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Button.h"
using namespace sf;


// Constants
const int mapAmout = 2;

// Variables
int currentMap = -1;
float cameraSpeed = 4.5f;
float cameraMoveBoxSize = 50.0f;
bool inDebugMode = false;
bool isDebugWindowOpen = false;

// Arrays and vectors
std::string mapArray[mapAmout]
{
	"Maps/Map1.txt",
	"Maps/Map2.txt"
};
std::vector<Button*> debugWindowButtons;
std::vector<Enemy*> enemies;
std::vector<Entity*> enemyBullets;

// Objects
Player* player = nullptr;
RenderWindow* mainWindow;
RenderWindow* debugWindow;
RenderManager renderer;
MapLoader mapLoader;
Map* map = nullptr;
Clock uiCoolDownTimer;
Font font("Assets/Fonts/Rodondo.otf");

// Functions
void UpdateCamera(View* _camera);
void CheckAdditionalInputs();
void RunUpdates(RenderWindow* _window, View* _camera);
void LoadNextLevel();
void ReloadLevel();
void SetupDebugWindow(RenderWindow* _window);
// Debug Functions
void DebugToggleDebugView() { inDebugMode = !inDebugMode; }
void DebugToggleInvincible() { player->ToggleInvincible(); }


int main()
{
	// Create debug window
	debugWindow = new RenderWindow(VideoMode({ 640, 640 }), "Debug Window", sf::Style::Titlebar);
	SetupDebugWindow(debugWindow);
	// Create the main window
	mainWindow = new RenderWindow(VideoMode({ 800, 600 }), "SFML window");
	View camera(sf::FloatRect({ 0.f, 0.f }, { 800.0f, 600.0f }));

	player = new Player(mainWindow);
	LoadNextLevel();

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

		// Debug Window Drawing Code
		if (debugWindow->isOpen())
		{
			// Checks to see whether it should be visible or not
			debugWindow->setVisible(isDebugWindowOpen);

			// Renders
			debugWindow->clear(Color::Transparent);

			renderer.Draw(debugWindow, &debugWindowButtons);
			debugWindow->display();
		}
	}

	return 0;
}


void RunUpdates(RenderWindow* _window, View* _camera)
{
	player->Update();

	if (player->m_levelComplete)
	{
		LoadNextLevel();
	}

	// enemy updates
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update();

		// Checking bullet collisions
		for (int j = 0; j < player->m_bullets.size(); j++)
		{
			enemies[i]->Collide(player->m_bullets[j]);
		}

		// Checking if they are dead
		if (enemies[i]->CheckIfQueuedForDeletion())
		{
			Entity* _tempPointer = enemies[i];
			enemies.erase(enemies.begin() + i);
			delete _tempPointer;
		}
	}

	// Enemy bullet updates
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		// Update and check for collision with player
		enemyBullets[i]->Update();
		if (enemyBullets[i]->Collide(player))
		{
			ReloadLevel();
		}

		// Delete when needed
		if (enemyBullets[i]->CheckIfQueuedForDeletion())
		{
			enemyBullets.erase(enemyBullets.begin() + i);
		}
	}

	// Player bullets update
	for (int i = 0; i < player->m_bullets.size(); i++)
	{
		player->m_bullets[i]->Update();
	}

	if (isDebugWindowOpen)
	{
		// Player bullets update
		for (int i = 0; i < debugWindowButtons.size(); i++)
		{
			debugWindowButtons.at(i)->ButtonUpdate();
		}
	}

	UpdateCamera(_camera);
	_window->setView(*_camera);
	CheckAdditionalInputs();
}


void LoadNextLevel()
{
	player->m_levelComplete = false;
	enemies.clear();

	currentMap++;
	if (currentMap < mapAmout)
	{
		map = mapLoader.LoadLevel(mapArray[currentMap], &enemies, mainWindow, player, &enemyBullets);
		player->SetMapPointer(map);
	}
}


void ReloadLevel()
{
	enemies.clear();

	if (currentMap < mapAmout)
	{
		map = mapLoader.LoadLevel(mapArray[currentMap], &enemies, mainWindow, player, &enemyBullets);
		player->SetMapPointer(map);
	}
}


// Sets up the debug window
void SetupDebugWindow(RenderWindow* _window)
{
	// Creates all the buttons and assigns their functions
	debugWindowButtons.push_back(new Button(_window, { 256, 64 }, { 128, 48 }, &font, "Next Level", LoadNextLevel));
	debugWindowButtons.push_back(new Button(_window, { 256, 192 }, { 128, 48 }, &font, "Toggle debug view", DebugToggleDebugView));
	debugWindowButtons.push_back(new Button(_window, { 256, 320 }, { 128, 48 }, &font, "Toggle invunerability", DebugToggleInvincible));
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


void CheckAdditionalInputs()
{
	// Toggles the debug menu when PgUp is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageUp))
	{
		if (uiCoolDownTimer.isRunning())
		{
			if (uiCoolDownTimer.getElapsedTime().asSeconds() > 0.5f)
			{
				isDebugWindowOpen = !isDebugWindowOpen;
				uiCoolDownTimer.restart();
			}
		}
	}

	// Closes the game when ESC is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		debugWindow->close();
		mainWindow->close();
	}
}