#pragma once
#include "Entity.h"


class Enemy : public Entity
{
public:
	std::vector<Entity*> m_bullets;
	RectangleShape m_debugDectionArea;
	Enemy(RenderWindow* _windowPointer, Map* _mapPointer, Entity* _playerPointer, Vector2f _pos, std::vector<Entity*>* _bullets);
	void Update() override;
	void DoActions();
	void CheckForBulletsToDestroy();
	void Move() override;
	void CheckRaycast();
protected:
	std::vector<Entity*>* _bulletArrayPointer;
	Entity* m_playerPointer;
	Clock m_shootTimer;
	struct Raycast2f
	{
		sf::Vertex point1{ sf::Vector2f(0.f, 0.f) };
		sf::Vertex point2{ sf::Vector2f(150.f, 150.f) };
	};
	Raycast2f m_raycast;
	bool m_canShoot = true;
	bool m_inDetectionRadius = false;
	float m_detectionRadius = 200.0f;
	float m_stopRadius = 125.0f;
};
