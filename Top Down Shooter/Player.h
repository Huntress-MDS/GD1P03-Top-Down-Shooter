#pragma once
#include "Entity.h"


class Player : public Entity
{
public:
	std::vector<Entity*> m_bullets;
	Player(RenderWindow* _windowPointer, Map* _mapPointer);
	void Update() override;
	void CheckForActions();
	void CheckForBulletsToDestroy();
	void Move() override;
protected:
	bool m_canShoot = true;
};

