#include "stdafx.h"
#include "CollisionShape.h"

CollisionShape::CollisionShape()
{
}

CollisionShape::CollisionShape(BoxType type) : m_type(type)
{
}

CollisionShape::~CollisionShape()
{
}
