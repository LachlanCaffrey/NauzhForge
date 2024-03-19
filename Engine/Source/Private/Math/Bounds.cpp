#include "Math/Bounds.h"

Bounds::Bounds(GameObject* Owner, Vector2 Origin, Vector2 Extent)
{
	m_Rect.Origin = Origin;
	m_Rect.Extent = Extent;
	m_Owner = Owner;
	m_CollisionType = CT_OVERLAP;
	m_Tag = "ALL";
}

bool Bounds::BoundsIntersect(const Bounds& BoundsA, const Bounds& BoundsB)
{
	Vector2 BoundsAMin = BoundsA.m_Rect.Min() - BoundsA.m_OriginOffset;
	Vector2 BoundsAMax = BoundsA.m_Rect.Max() + BoundsA.m_OriginOffset;
	Vector2 BoundsBMin = BoundsB.m_Rect.Min() - BoundsB.m_OriginOffset;
	Vector2 BoundsBMax = BoundsB.m_Rect.Max() + BoundsB.m_OriginOffset;

	// Is the min x of BoundsB less than the max x of BoundsA
	bool MinX = BoundsBMin.x <= BoundsAMax.x;
	// Is the max x of BoundsB greater than the min x BoundsA
	bool MaxX = BoundsBMax.x >= BoundsAMin.x;
	// Is the min y of BoundsB less than the max y of BoundsA
	bool MinY = BoundsBMin.y <= BoundsAMax.y;
	// Is the max y of BoundsB greater than the min y BoundsA
	bool MaxY = BoundsBMax.y >= BoundsAMin.y;

	return MinX && MaxX && MinY && MaxY;
}
