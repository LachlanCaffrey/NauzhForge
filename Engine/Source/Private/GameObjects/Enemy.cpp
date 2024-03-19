#include "GameObjects/Enemy.h"

#define Super Character

#define SCALE 3.0f
#define SIZE ((64.0f - 36.0f)* SCALE)
#define HALF_SIZE (SIZE / 2.0f)

Enemy::Enemy()
{
	m_MaxSpeed = 100.0f;

	AnimationParams AnimParams;
	AnimParams.fps = 24.0f;
	AnimParams.FrameHeight = 64.0f;
	AnimParams.FrameWidth = 64.0f;
	AnimParams.EndFrame = 9;
	AnimParams.MaxFrames = 10;

	AddSprite(
		"Content/Sprites/Kla'ed/Engine/PNGs/Kla'ed - Fighter - Engine.png",
		&AnimParams
	);

	m_EnemySprite1 = AddSprite(
		"Content/Sprites/Kla'ed/Base/PNGs/Kla'ed - Fighter - Base.png"
	);

	m_EnemySprite2 = AddSprite(
		"Content/Sprites/Kla'ed/Base/PNGs/Kla'ed - Fighter - Base.png"
	);

	Bounds* EnemyBounds = AddBounds(0.0f, SIZE);
	EnemyBounds->m_OriginOffset = -HALF_SIZE;
	EnemyBounds->m_Tag = "ENEMY";
}

void Enemy::OnStart()
{
	Super::OnStart();

	// Start the enemy above the screen
	SetPosition({ 640.f, -HALF_SIZE });
	// Flip it 180 to look downward
	SetRotation(180.0f);
	// Change the scale
	SetScale(SCALE);
}

void Enemy::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	AddMovementInput(Vector2(0.0f, 1.0f));

	if (GetTransform().Position.y - HALF_SIZE > 720.0f) {
		SetPosition({ 640.0f, -HALF_SIZE });
	}
}
