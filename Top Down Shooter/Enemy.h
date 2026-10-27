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
protected:
	std::vector<Entity*>* _bulletArrayPointer;
	Entity* m_playerPointer;
	Clock m_shootTimer;
	bool m_canShoot = true;
	bool m_inDetectionRadius = false;
	float m_detectionRadius = 450.0f;
	float m_stopRadius = 200.0f;
};
