#include "stdafx.h"
#include "CollisionShape.h"
#include "Collider.h"

CollisionShape::CollisionShape() : m_type(none)
{
}

CollisionShape::CollisionShape(BoxType type) : m_type(type)
{
}

CollisionShape::~CollisionShape()
{
}
