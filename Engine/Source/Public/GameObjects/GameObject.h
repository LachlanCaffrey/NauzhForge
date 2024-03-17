#pragma once
#include "Math/Vector2.h"
#include "EngineTypes.h"

class Input;

struct NFTransform {
	// Default constructor
	NFTransform() : Position(0.0f), Rotation(0.0f), Scale(1.0) {}

	// Assignment constructor
	NFTransform(Vector2 Position, float Rotation, Vector2 Scale) :
		Position(Position), Rotation(Rotation), Scale(Scale) {}

	// Transform constructor
	NFTransform(const NFTransform& Other) : 
		Position(Other.Position), Rotation(Other.Rotation), Scale(Other.Scale) {}

	Vector2 Position;
	float Rotation;
	Vector2 Scale;

};

class GameObject {
public:
	GameObject() : m_ShouldDestroy(false) {}
	virtual ~GameObject() = default;

	// Runs when this obbject spawns into game
	void Start();

	// Listen for input commands
	void ProcessInput(Input* GameInput);

	// Run every frame
	void Update(float DeltaTime);

	// Runs every frame after the update
	virtual void PostUpdate(float DeltaTime);

	// Destroy the game object
	void DestroyObject();

	// Is the object pending destroy at the end
	bool IsPendingDestroy() const { return m_ShouldDestroy; }

	// Remove any memory references
	virtual void Cleanup() {}

	// Get the transform of the object
	// Position, Rotation, Scale
	NFTransform GetTransform() const { return m_Transform; }

	// Set the transform of the object
	virtual void SetTransform(NFTransform Transform);

	// Set the position of the object
	void SetPosition(Vector2 Position);

	// Set the roation of the object
	void SetRotation(float Rotation);

	// Set the scale of the object
	void SetScale(Vector2 Scale);

protected:
	// Run when the game object has been marked for destroy
	virtual void OnDestroy();

	// Run when the game object spawns into game
	virtual void OnStart() {}

	// Runs on the game objects process input (before each frame)
	virtual void OnProcessInput(Input* GameInput) {}

	// Runs on the game objects update (each frame)
	virtual void OnUpdate(float DeltaTime) {}

	// Runs on the game objects update (after each frame)
	virtual void OnPostUpdate(float DeltaTime) {}
private:
	// Determine if the object should be destroyed at the end of the loop
	bool m_ShouldDestroy;

	// Store the transform location for the object
	NFTransform m_Transform;
};