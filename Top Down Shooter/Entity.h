#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
using namespace sf;


class Entity : public RectangleShape
{
public:
	enum MOVE_DIRECTION
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	virtual void Update() = 0;
	virtual void Move() = 0;
	bool Collide(std::vector<Tile*>* _collisionVector, MOVE_DIRECTION _direction);
	bool Collide(Entity* _entity);
	void RotateTowardsPosition(Vector2f _position, bool _worldSpace = false);
	bool CheckIfPointInAreaX(float _point);
	bool CheckIfPointInAreaY(float _point);
	bool CheckIfQueuedForDeletion() { return m_queuedForDeletion; }
protected:
	Map* m_mapPointer;
	RenderWindow* m_windowPointer;
	Angle m_lookDirection;
	Vector2f m_position;
	Vector2f m_size;
	Vector2f m_hitbox;
	Vector2f m_hurtbox;
	float m_speed;
	int m_hitboxResizer = 1;
	bool m_queuedForDeletion = false;
};