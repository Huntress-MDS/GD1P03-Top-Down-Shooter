#pragma once
#include "Entity.h"


class Enemy : public Entity
{
public:
	std::vector<Entity*> m_bullets;
	Enemy(RenderWindow* _windowPointer, Map* _mapPointer, Entity* _playerPointer, Vector2f _pos, std::vector<Entity*>* _bullets);
	void Update() override;
	void DoActions();
	void CheckForBulletsToDestroy();
	void Move() override;
protected:
	std::vector<Entity*>* _bulletArrayPointer;
	Entity* m_playerPointer;
	bool m_canShoot = true;
	Clock m_shootTimer;
};
