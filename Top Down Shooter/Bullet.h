#pragma once
#include "Entity.h"


class Bullet : public Entity
{
public:
	Bullet(Map* _mapPointer, Angle _direction, Vector2f _startPosition, Vector2f _size);
	void Update() override;
	void Move() override;
protected:
	Angle m_direction;
	bool m_isFriendly = false;
};

