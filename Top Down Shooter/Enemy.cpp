#include "Enemy.h"
#include "Bullet.h"


Enemy::Enemy(RenderWindow* _windowPointer, Map* _mapPointer, Entity* _playerPointer, Vector2f _pos, std::vector<Entity*>* _bullets)
{
	m_speed = 2.0f;
	m_size = { 32, 32 };
	m_hitbox = { 16, 16 };
	m_hitboxResizer = 5;
	m_hurtbox = { 16, 16 };
	m_windowPointer = _windowPointer;
	m_mapPointer = _mapPointer;
	m_playerPointer = _playerPointer;
	m_position = _pos;
	_bulletArrayPointer = _bullets;

	setSize(m_size);
	setOrigin({ m_size.x / 2, m_size.y / 2 });
	setFillColor(Color::Magenta);
}


void Enemy::Update()
{
	Move();

	DoActions();
	CheckForBulletsToDestroy();

	setPosition(m_position);
}


void Enemy::DoActions()
{
	if (m_shootTimer.getElapsedTime().asSeconds() > 5.0f)
	{
		_bulletArrayPointer->push_back(new Bullet(m_mapPointer, m_lookDirection, m_position, { 16, 16 }, false));
		m_shootTimer.restart();
	}
}


void Enemy::CheckForBulletsToDestroy()
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->CheckIfQueuedForDeletion())
		{
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}


void Enemy::Move()
{
	Vector2f directionVector;

	// X Pos checks
	if (m_position.x > m_playerPointer->getPosition().x)
	{
		if (!Collide(&m_mapPointer->tiles, LEFT))
		{
			directionVector.x -= 1;
		}
	}
	else if (m_position.x < m_playerPointer->getPosition().x)
	{
		if (!Collide(&m_mapPointer->tiles, RIGHT))
		{
			directionVector.x += 1;
		}
	}
	// Y pos checks
	if (m_position.y > m_playerPointer->getPosition().y)
	{
		if (!Collide(&m_mapPointer->tiles, UP))
		{
			directionVector.y -= 1;
		}
	}
	else if (m_position.y < m_playerPointer->getPosition().y)
	{
		if (!Collide(&m_mapPointer->tiles, DOWN))
		{
			directionVector.y += 1;
		}
	}

	// Normalize the vector
	if (directionVector.x != 0 || directionVector.y != 0)
	{
		m_position.x += directionVector.normalized().x * m_speed;
		m_position.y += directionVector.normalized().y * m_speed;
	}

	RotateTowardsPosition(m_playerPointer->getPosition(), true);
}
