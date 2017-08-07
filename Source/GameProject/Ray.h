#pragma once
#include "stdafx.h"
#include "Renderer2D.h"

//TODO RayTester(or whatever) class that holds ray and a rule(lambda returning bool), as well as distance to and identity of last collider hit which follows rule

class Ray {
public:
	Ray();
	Ray(glm::vec2 origin, glm::vec2 direction, float length = INFINITY);
	~Ray();

	glm::vec2 getOrigin() {
		return m_origin;
	}
	glm::vec2 getDirection() {
		return m_direction;
	}
	float getLength() {
		return m_length;
	}

	void setOrigin(glm::vec2 origin);

	void setDirection(glm::vec2 direction);

	void setLength(float length);

	// Returns closest point on ray to given point
	glm::vec2 findClosestPoint(glm::vec2 point);

	void draw(aie::Renderer2D* renderer);

	

protected:
	glm::vec2 m_origin;
	glm::vec2 m_direction;
	float m_length;
};