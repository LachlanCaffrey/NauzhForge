#include "GameObjects/PhysicsObject.h"
#include "Debug.h"

#define Super SpriteObject

PhysicsObject::PhysicsObject() : 
	m_Deceleration(0.0f), 
	m_Drag(1.0f), 
	m_Mass(1.0f), 
	m_MaxSpeed(600.0f) {}

void PhysicsObject::AddForce(Vector2 Direction, float Force)
{
	m_AccelerationForce = Direction * Force;
}

void PhysicsObject::OnPostUpdate(float DeltaTime)
{
	// Constant wind force against the object
	Vector2 DragForce(m_Velocity * -m_Drag);

	// Combined force for the velocity
	// Acceleration force being a custom additive force
	Vector2 FullForce(DragForce + m_AccelerationForce);

	// Physics force algorithm F = ma (a = F / m)
	m_Acceleration = FullForce / std::max(m_Mass, 0.00001f);

	// Applying acceleration and multiply it by time
	m_Velocity += m_Acceleration * DeltaTime;

	// Cap the velocity at the maximum value
	if (m_Velocity.Length() > m_MaxSpeed) {
		m_Velocity = Vector2::Normalised(m_Velocity) * m_MaxSpeed;
	}

	// The force that should stop the object faster
	Vector2 DecelForce;

	// Set deceleration force only if we need to decelerate 
	if (m_Velocity.Length() < m_LastTickVelocity.Length()) {
		DecelForce = m_Velocity * -m_Deceleration;
	}

	// Apply deceleration
	m_Velocity += DecelForce * DeltaTime;

	// The amount to move from the position based on time
	Vector2 TimeVelocity(m_Velocity * DeltaTime);

	// Move the object based on velocity
	SetPosition(GetTransform().Position + TimeVelocity);

	// Reset the push force
	m_AccelerationForce = Vector2();

	// Update the last tick velocity
	m_LastTickVelocity = m_Velocity;

	// Runs the sprite conditions after physics has applied
	Super::OnPostUpdate(DeltaTime);
}
