#pragma once
#include "stdafx.h"
#include"CollisionShape.h"

class CircleCollider : public CollisionShape {
public:
	CircleCollider();
	CircleCollider(glm::vec2 centre, float radius);
	virtual ~CircleCollider();

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


	virtual void transform(glm::mat3 transformation);

	glm::vec2 getCentre() {
		return m_centre;
	};

	float getRadius() {
		return m_radius;
	};

	void setCentre(glm::vec2 centre) {
		m_centre = centre;
	};

	void setRadius(float radius) {
		m_radius = radius;
	};

protected:
	glm::vec2 m_centre;
	float m_radius;
};