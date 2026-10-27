#include "Tile.h"


// The constructor
Tile::Tile(std::string _type, float _tileSize, Vector2f _position) : m_tileType(_type), m_tileSize(_tileSize)
{
	// Sets its colour based on its type
	if (m_tileType == "Wall")
	{
		setFillColor(sf::Color::Blue);
	}
	else if (m_tileType == "Goal")
	{
		setFillColor(sf::Color::Green);
	}
	else if (m_tileType == "Pit")
	{
		setFillColor(sf::Color::Black);
	}

	// Sets defaults
	setSize({ m_tileSize, m_tileSize });
	setPosition(sf::Vector2f({ float(_position.x * m_tileSize), float(_position.y * m_tileSize) }));
}


// Do math to check if a point is within the tile's x position and size
bool Tile::CheckIfPointInAreaX(float _point)
{
	if (_point > getPosition().x && _point < getPosition().x + getSize().x)
	{
		return true;
	}

	return false;
}


// Do math to check if a point is within the tile's y position and size
bool Tile::CheckIfPointInAreaY(float _point)
{
	if (_point > getPosition().y && _point < getPosition().y + getSize().y)
	{
		return true;
	}

	return false;
}
