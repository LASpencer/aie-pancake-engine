#pragma once
#include "stdafx.h"

enum BoxType;

class AABox;
class OBox;
class CircleCollider;

class CollisionShape {
public:
	CollisionShape();

	virtual ~CollisionShape();

	virtual CollisionShape* clone();

	virtual void transform(glm::mat3 transformation) = 0;

	virtual std::pair<bool, glm::vec2> doesCollide(CollisionShape* other) = 0;

	virtual std::pair<bool, glm::vec2> doesCollide(AABox* other) = 0;

	virtual std::pair<bool, glm::vec2> doesCollide(OBox* other) = 0;

	virtual std::pair<bool, glm::vec2> doesCollide(CircleCollider* other) = 0;

protected:
	BoxType m_type;
};