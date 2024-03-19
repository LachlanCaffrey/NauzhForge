#include "GameObjects/Player.h"
#include "Input.h"

#define Super Character

#define ENGINE_IDLE 0
#define ENGINE_POWERED 1
#define SCALE 3.0f
#define SIZE ((48.0f - 16.0f) * SCALE)
#define HALF_SIZE (SIZE / 2.0f)

Player::Player()
{
	m_MaxSpeed = 600.0f;
	m_Deceleration = 10.0f;
	m_AccelerationSpeed = 5000.0f;

	// Add engine sprite
	AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engines/PNGs/Main Ship - Engines - Supercharged Engine.png"
	);

	// Add ship base sprite
	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Full Health.png"
	);

	AnimationParams AnimParams;
	AnimParams.fps = 24.0f;
	AnimParams.FrameHeight = 48.0f;
	AnimParams.FrameWidth = 48.0f;
	AnimParams.EndFrame = 3;
	AnimParams.MaxFrames = 4;

	// Add the idle engine effect
	m_MainEngineEffects.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Idle.png",
		&AnimParams 
	));

	// Add the powered engine effect
	m_MainEngineEffects.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParams
	));

	// Hide the powered sprite by default
	SetPoweredEngine(false);

	Bounds* PlayerBounds = AddBounds({ 640.0f, 360.0f }, SIZE);
	PlayerBounds->m_OriginOffset = -HALF_SIZE;
}

void Player::OnStart()
{
	Super::OnStart();

	SetPosition({ 640.0f, 360.0f });
	SetScale(SCALE);
}

void Player::OnProcessInput(Input* GameInput)
{
	Super::OnProcessInput(GameInput); 

	if (GameInput->IsKeyDown(NF_KEY_W)) {
		AddMovementInput(Vector2(0.0f, -1.0f));
		SetRotation(0.0f);
	}
	if (GameInput->IsKeyDown(NF_KEY_S)) {
		AddMovementInput(Vector2(0.0f, 1.0f));
		SetRotation(180.0f);
	}
	if (GameInput->IsKeyDown(NF_KEY_A)) {
		AddMovementInput(Vector2(-1.0f, 0.0f));
		SetRotation(270.0f);
	}
	if (GameInput->IsKeyDown(NF_KEY_D)) {
		AddMovementInput(Vector2(1.0f, 0.0f));
		SetRotation(90.0f);
	}
}

void Player::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	if (m_MoveDirection.Length() > 0.0f) {
		SetPoweredEngine(true);
	}
	else {
		SetPoweredEngine(false);
	}
}

void Player::SetPoweredEngine(bool Powered)
{
	if (m_MainEngineEffects.size() > 1) {
		if (m_MainEngineEffects[ENGINE_IDLE] != nullptr || m_MainEngineEffects[ENGINE_POWERED] != nullptr) {
			m_MainEngineEffects[ENGINE_IDLE]->SetActive(!Powered);
			m_MainEngineEffects[ENGINE_POWERED]->SetActive(Powered);
		}
	}
}

void Player::OnOverlapEnter(Bounds* OverlapBounds, Bounds* HitBounds)
{
	if (OverlapBounds->m_Tag == "ENEMY") {
		OverlapBounds->GetOwner()->DestroyObject();
	}
}
