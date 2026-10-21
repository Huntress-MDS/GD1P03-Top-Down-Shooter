#include "Bullet.h"


Bullet::Bullet(Map* _mapPointer, Angle _direction, Vector2f _startPosition, Vector2f _size, bool _friendly) : m_isFriendly(_friendly)
{
	m_mapPointer = _mapPointer;
	m_direction = _direction;
	m_position = _startPosition;
	m_size = _size;
	m_speed = 10.0f;
	m_hitbox = { m_size.x / 2, m_size.y / 2 };

	setSize(m_size);
	setOrigin({ m_size.x / 2, m_size.y / 2 });
	setFillColor(Color::Red);
}


void Bullet::Update()
{
	Move();

	if (Collide(&m_mapPointer->tiles, RIGHT))
	{
		m_queuedForDeletion = true;
	}

	setPosition(m_position);
}


void Bullet::Move()
{
	m_position.x += cos(m_direction.asRadians()) * m_speed;
	m_position.y += sin(m_direction.asRadians()) * m_speed;
}
