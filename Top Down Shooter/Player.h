#pragma once
#include "Entity.h"


class Player : public Entity
{
public:
	std::vector<Entity*> m_bullets;
	Player(RenderWindow* _windowPointer);
	void Update() override;
	void CheckForActions();
	void CheckForBulletsToDestroy();
	void Move() override;
	// Inline functions
	void SetMapPointer(Map* _mapPointer) { m_mapPointer = _mapPointer; }
protected:
	bool m_canShoot = true;
};

