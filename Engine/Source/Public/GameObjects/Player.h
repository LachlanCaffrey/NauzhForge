#pragma once
#include "GameObjects/Character.h"

class Player : public Character {
public: 
	Player();

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

	// Change the engine effect animations
	void SetPoweredEngine(bool Powered);

	virtual void OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds) override;

protected:
	// Store the different effects for the engine effects
	TArray<Sprite*> m_MainEngineEffects;
};