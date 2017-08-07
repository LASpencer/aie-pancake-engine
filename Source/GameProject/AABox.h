#pragma once
#include "stdafx.h"
#include"CollisionShape.h"

class AABox : CollisionShape {
public:
	AABox();
	AABox(glm::vec2 cornerA, glm::vec2 cornerB, BoxType type);
	~AABox();

	virtual CollisionShape* clone();

	// test collision with Collider of unknown concrete type
	virtual std::pair<bool, glm::vec2> doesCollide(CollisionShape* other);

	// test collision with point
	virtual std::pair<bool, glm::vec2> doesCollide(glm::vec2 point);

	// test collision with AABox
	virtual std::pair<bool, glm::vec2> doesCollide(AABox* box);

	// test collision with OBox
	virtual std::pair<bool, glm::vec2> doesCollide(OBox* box);

	// test collision with CircleCollider
	virtual std::pair<bool, glm::vec2> doesCollide(CircleCollider* circle);

	// Accessor and mutator methods
	glm::vec2 getMinCorner() {
		return m_min;
	}

	glm::vec2 getMaxCorner() {
		return m_max;
	}

	virtual void transform(glm::mat3 transformation);

	// Set corners of the bounding box
	void setCorners(glm::vec2 a, glm::vec2 b);

	// Returns all four corners of the AABox, clockwise from minimum corner
	std::tuple<glm::vec2, glm::vec2, glm::vec2, glm::vec2> getCorners();

	// Fit AABox around collision shapes given
	void boundShapes(std::vector<CollisionShape> points);

protected:
	glm::vec2 m_min;		// Minimum corner of box
	glm::vec2 m_max;		// Maximum corner of box
};