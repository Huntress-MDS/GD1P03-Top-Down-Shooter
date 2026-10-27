#include "Enemy.h"
#include "Bullet.h"
#include <iostream>


Enemy::Enemy(RenderWindow* _windowPointer, Map* _mapPointer, Entity* _playerPointer, Vector2f _pos, std::vector<Entity*>* _bullets)
{
	// Set defaults
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

	// Debug stuff
	m_debugDectionArea.setSize({ m_detectionRadius * 2, m_detectionRadius * 2 });
	m_debugDectionArea.setFillColor(Color(255, 0, 0, 100));
	m_debugDectionArea.setOrigin({ m_detectionRadius, m_detectionRadius });

	// Functions
	setSize(m_size);
	setOrigin({ m_size.x / 2, m_size.y / 2 });
	setFillColor(Color::Magenta);
}


void Enemy::Update()
{
	Move();

	DoActions();
	CheckForBulletsToDestroy();

	m_debugDectionArea.setPosition(m_position);
	setPosition(m_position);
}


void Enemy::DoActions()
{
	if (m_shootTimer.getElapsedTime().asSeconds() > m_cooldown && m_inDetectionRadius)
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

	// Area Checks
	if ((m_position.x - m_playerPointer->getPosition().x < m_stopRadius && m_position.x - m_playerPointer->getPosition().x > -m_stopRadius) && (m_position.y - m_playerPointer->getPosition().y < m_stopRadius && m_position.y - m_playerPointer->getPosition().y > -m_stopRadius))
	{
		// X Pos checks
		if (m_position.x > m_playerPointer->getPosition().x)
		{
			if (!Collide(&m_mapPointer->tiles, RIGHT))
			{
				directionVector.x += 1;
			}
		}
		else if (m_position.x < m_playerPointer->getPosition().x)
		{
			if (!Collide(&m_mapPointer->tiles, LEFT))
			{
				directionVector.x -= 1;
			}
		}
		// Y pos checks
		if (m_position.y > m_playerPointer->getPosition().y)
		{
			if (!Collide(&m_mapPointer->tiles, DOWN))
			{
				directionVector.y += 1;
			}
		}
		else if (m_position.y < m_playerPointer->getPosition().y)
		{
			if (!Collide(&m_mapPointer->tiles, UP))
			{
				directionVector.y -= 1;
			}
		}
	}
	else if (m_position.x - m_playerPointer->getPosition().x < m_detectionRadius && m_position.x - m_playerPointer->getPosition().x > -m_detectionRadius)
	{
		if (m_position.y - m_playerPointer->getPosition().y < m_detectionRadius && m_position.y - m_playerPointer->getPosition().y > -m_detectionRadius)
		{
			m_inDetectionRadius = true;

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
		}
		else
		{
			m_inDetectionRadius = false;
		}
	}
	else
	{
		m_inDetectionRadius = false;
	}

	// stop the enemy when at the border and make shoot faster
	if (((int)(m_position.y - m_playerPointer->getPosition().y) == m_stopRadius || (int)(m_position.y - m_playerPointer->getPosition().y) == -m_stopRadius) || ((int)(m_position.x - m_playerPointer->getPosition().x) == m_stopRadius || (int)(m_position.x - m_playerPointer->getPosition().x) == -m_stopRadius))
	{
		directionVector.x = 0;
		directionVector.y = 0;
		m_cooldown = 1.5f;
	}
	else
	{
		m_cooldown = 3.0f;
	}

	// Normalize the vector
	if (directionVector.x != 0 || directionVector.y != 0)
	{
		m_position.x += directionVector.normalized().x * m_speed;
		m_position.y += directionVector.normalized().y * m_speed;
	}

	RotateTowardsPosition(m_playerPointer->getPosition(), true);
}


void Enemy::CheckRaycast()
{
	m_raycast.point1.position = m_position;
	m_raycast.point2.position = m_playerPointer->getPosition();
}
