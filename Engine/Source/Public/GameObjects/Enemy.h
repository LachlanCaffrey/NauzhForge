#pragma once
#include "GameObjects/Character.h"

class Enemy : public Character {
public:
	Enemy();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override;

protected:
	// Enemy sprites that represents the enemies
	Sprite* m_EnemySprite1;
	Sprite* m_EnemySprite2;
};