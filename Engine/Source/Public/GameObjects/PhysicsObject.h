#pragma once
#include "GameObjects/SpriteObject.h"

class PhysicsObject : public SpriteObject {
public:
	PhysicsObject();

	// Add force to the object
	// @param 1 - Direction of the force to be apply
	// @param 2 - Power/strength of the force to be apply
	void AddForce(Vector2 Direction, float Force);

protected:
	virtual void OnPostUpdate(float DeltaTime) override;

protected:
	// After stopped moving then slow down
	float m_Deceleration;

	// Constant wind force against the physics
	float m_Drag;

	// How heavy the object is
	float m_Mass;

	// Maximum velocity speed that we can travel
	float m_MaxSpeed;

	// Direction and speed of the physics object
	Vector2 m_Velocity;

private:
	// The hidden force changing velocity
	Vector2 m_Acceleration;

	// Custom force that pushes our objects in physics
	Vector2 m_AccelerationForce;

	// Previous velocity on the last tick
	Vector2 m_LastTickVelocity;
};