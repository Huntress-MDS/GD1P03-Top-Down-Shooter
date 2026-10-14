#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class Tile : public RectangleShape
{
public:
	// Functions
	Tile(std::string _type, float _tileSize, Vector2f _position);
	bool CheckIfPointInAreaX(float _point);
	bool CheckIfPointInAreaY(float _point);
	std::string GetTileType() { return m_tileType; }
protected:
	// String to hold the type of the tile
	std::string m_tileType = "";
	// float for the tile size
	float m_tileSize = 0;
};
