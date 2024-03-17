#include "GameObjects/GameObject.h"
#include "Debug.h"

void GameObject::Start() {
	if (IsPendingDestroy()) {
		return;
	}

	OnStart();

	NF_LOG("GameObject", "GameObject has spawned into the game.");
}

void GameObject::ProcessInput(Input* GameInput)
{
	if (IsPendingDestroy()) {
		return;
	}

	OnProcessInput(GameInput);
}

void GameObject::Update(float DeltaTime)
{
	if (IsPendingDestroy()) {
		return;
	}
	
	OnUpdate(DeltaTime);
}

void GameObject::PostUpdate(float DeltaTime)
{
	if (IsPendingDestroy()) {
		return;
	}

	OnPostUpdate(DeltaTime);
}

void GameObject::DestroyObject()
{
	// Ensure the OnDestroy only runs once
	if (!m_ShouldDestroy) {
		OnDestroy();
	}

	m_ShouldDestroy = true;
}

void GameObject::SetTransform(NFTransform Transform)
{
	m_Transform = Transform;
}

void GameObject::SetPosition(Vector2 Position)
{
	NFTransform NewTransform(
		Position,
		m_Transform.Rotation,
		m_Transform.Scale
	);

	SetTransform(NewTransform);
}

void GameObject::SetRotation(float Rotation)
{
	NFTransform NewTransform(
		m_Transform.Position,
		Rotation,
		m_Transform.Scale
	);

	SetTransform(NewTransform);
}

void GameObject::SetScale(Vector2 Scale)
{
	NFTransform NewTransform(
		m_Transform.Position,
		m_Transform.Rotation,
		Scale
	);

	SetTransform(NewTransform);
}

void GameObject::OnDestroy() {
	NF_LOG("GameObject", "GameObject has been destroyed.");
}