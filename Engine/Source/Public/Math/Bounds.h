#pragma once
#include "Math/Vector2.h"
#include "cstdint"
#include "EngineTypes.h"

class GameObject;

struct NFRect {
	// Simple constructor
	NFRect() : Origin(0.0f), Extent(1.0f) {}

	// Complex contructor
	NFRect(Vector2 Origin, Vector2 Extent) : Origin(Origin), Extent(Extent) {}

	// Min value position of the rect relative to the screen
	Vector2 Min() const { return Origin - Extent; }

	// Max value position of the rect relative to the screen
	Vector2 Max() const { return Origin + Extent; }

	// Center of the rectangle
	Vector2 Origin;

	// Half size of the box
	Vector2 Extent;
};

enum NFCollisionType : unsigned int {
	CT_NONE = 0,
	CT_OVERLAP
};

struct STBoundsColour {
	// Default constructor
	STBoundsColour() : r(255), g(0), b(0) {}

	// Colour set constructor
	STBoundsColour(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

	uint8_t r;
	uint8_t g;
	uint8_t b;
};

class Bounds {
public: 
	Bounds(GameObject* Owner, Vector2 Origin = 0.0f, Vector2 Extent = 1.0f);

	// The center equals the origin + the offset
	Vector2 GetCenter() { return m_Rect.Origin + m_OriginOffset; }

	// Detect if two bounds are intersecting
	static bool BoundsIntersect(const Bounds& BoundsA, const Bounds& BoundsB);

	GameObject* GetOwner() const { return m_Owner; }

public:
	// This is the rectangle that defines the bounds
	NFRect m_Rect;

	// This is the offset from the original position
	Vector2 m_OriginOffset;

	// Collision type
	NFCollisionType m_CollisionType;

	// Name of the collision
	const char* m_Tag;

	// Colour of the bounds if debug is active
	STBoundsColour m_RenderColour;

	// All currently overlapping bounds
	TArray<Bounds*> m_Overlapped;

private:
	//This is the owner object the bounds is attached to
	GameObject* m_Owner;
};