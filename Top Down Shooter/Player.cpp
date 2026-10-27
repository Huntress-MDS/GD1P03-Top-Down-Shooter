#include "Player.h"
#include "Bullet.h"


Player::Player(RenderWindow* _windowPointer)
{
	m_speed = 5.0f;
	m_size = { 32, 32 };
	m_hitbox = { 16, 16 };
	m_hitboxResizer = 5;
	m_hurtbox = { 16, 16 };
	m_windowPointer = _windowPointer;

	setSize(m_size);
	setOrigin({ m_size.x / 2, m_size.y / 2 });
	setFillColor(Color::Yellow);
}


void Player::Update()
{
	Move();

	CheckForActions();
	CheckForBulletsToDestroy();

	setPosition(m_position);
}


void Player::CheckForActions()
{
	if (Mouse::isButtonPressed(Mouse::Button::Left) && m_canShoot)
	{
		m_bullets.push_back(new Bullet(m_mapPointer, m_lookDirection, m_position, {16, 16}, true));
		m_canShoot = false;
	}
	else if (!Mouse::isButtonPressed(Mouse::Button::Left))
	{
		m_canShoot = true;
	}
}


void Player::CheckForBulletsToDestroy()
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->CheckIfQueuedForDeletion())
		{
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}


void Player::Move()
{
	Vector2f directionVector;

	// Input checks
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		if (!Collide(&m_mapPointer->tiles, LEFT))
		{
			directionVector.x -= 1;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		if (!Collide(&m_mapPointer->tiles, RIGHT))
		{
			directionVector.x += 1;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W))
	{
		if (!Collide(&m_mapPointer->tiles, UP))
		{
			directionVector.y -= 1;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S))
	{
		if (!Collide(&m_mapPointer->tiles, DOWN))
		{
			directionVector.y += 1;
		}
	}

	if (directionVector.x != 0 || directionVector.y != 0)
	{
		m_position.x += directionVector.normalized().x * m_speed;
		m_position.y += directionVector.normalized().y * m_speed;
	}

	RotateTowardsPosition((Vector2f)Mouse::getPosition(*m_windowPointer));
}
