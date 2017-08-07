#pragma once
#include "stdafx.h"
#include "CollisionShape.h"

class OBox : public CollisionShape {
public:
	OBox();
	OBox(glm::vec2 xExtent, glm::vec2 yExtent, glm::vec2 centre);
	virtual ~OBox();

	// test collision with Collider of unknown concrete type
	virtual std::pair<bool, glm::vec2> doesCollide(CollisionShape* other);

	// test collision with point
	virtual std::pair<bool, glm::vec2> doesCollide(glm::vec2 point);

	// test collision with AABox
	virtual std::pair<bool, glm::vec2> doesCollideWithAABox(AABox* box);

	// test collision with OBox
	virtual std::pair<bool, glm::vec2> doesCollideWithOBox(OBox* box);

	// test collision with CircleCollider
	virtual std::pair<bool, glm::vec2> doesCollideWithCircle(CircleCollider* circle);

	// Accessor and mutator functions
	glm::vec2 getXExtent() {
		return m_xExtent;
	}
	glm::vec2 getYExtent() {
		return m_yExtent;
	}
	glm::vec2 getCentre() {
		return m_centre;
	}

	void setHalfExtents(glm::vec2 xExtent, glm::vec2 yExtent) {
		m_xExtent = xExtent;
		m_yExtent = yExtent;
	}

	void setCentre(glm::vec2 centre) {
		m_centre = centre;
	}

	// Returns all four corners of the OBox
	std::tuple<glm::vec2, glm::vec2, glm::vec2, glm::vec2> getCorners();

	virtual void transform(glm::mat3 transformation);

protected:
	glm::vec2 m_xExtent;
	glm::vec2 m_yExtent;
	glm::vec2 m_centre;
};