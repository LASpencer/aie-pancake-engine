#include "stdafx.h"
#include "CircleCollider.h"
#include "AABox.h"
#include "OBox.h"
#include "Ray.h"

CircleCollider::CircleCollider() : CollisionShape(), m_radius(1.f)
{
}

CircleCollider::CircleCollider(glm::vec2 centre, float radius, BoxType type) : CollisionShape(type), m_centre(centre), m_radius(radius)
{
}

CircleCollider::~CircleCollider()
{
}

CollisionShape * CircleCollider::clone()
{
	return new CircleCollider(*this);
}

std::pair<bool, glm::vec2> CircleCollider::doesCollide(CollisionShape * other)
{
	std::pair<bool, glm::vec2> otherResult = other->doesCollide(this);
	return std::make_pair(otherResult.first, -1.f * otherResult.second);
}

std::pair<bool, glm::vec2> CircleCollider::doesCollide(glm::vec2 point)
{
	glm::vec2 displacement = point - m_centre;

	if (glm::length(displacement) >= m_radius) {
		return std::make_pair(false, glm::vec2());
	}
	else {
		glm::vec2 nearestEdge;
		if (glm::vec2(0) == displacement) {
			nearestEdge = m_centre + glm::vec2(m_radius, 0);	// Arbitrarily picked vector if point is centre
		} else {
			nearestEdge = m_centre + glm::normalize(displacement) * m_radius;
		}
		return std::make_pair(true, point - nearestEdge);
	}

}

std::pair<bool, glm::vec2> CircleCollider::doesCollide(AABox * box)
{
	// Check if circle's centre is inside box
	std::pair<bool, glm::vec2> collision = box->doesCollide(m_centre);
	if (collision.first) {
		// If so, get penetration of centre into box
		glm::vec2 penetration = collision.second;
		// Add radius to penetration's magnitude
		glm::vec2 penNormal = glm::normalize(penetration);
		penetration += m_radius*penNormal;
		return std::make_pair(true, -1.0f * penetration);
	}
	else {
		// Find closest point on box to circle
		float clampedX, clampedY;
		// x value clamped between max and min corners
		clampedX = std::min(std::max(m_centre.x, box->getMinCorner().x), box->getMaxCorner().x);
		// y value clamped between max and min corners
		clampedY = std::min(std::max(m_centre.y, box->getMinCorner().y), box->getMaxCorner().y);
		glm::vec2 closestPoint = glm::vec2(clampedX, clampedY);
		// Test collision with closest point
		return doesCollide(closestPoint);
	}
}

std::pair<bool, glm::vec2> CircleCollider::doesCollide(OBox * box)
{
	std::pair<bool, glm::vec2> otherResult = box->doesCollide(this);
	return std::make_pair(otherResult.first, otherResult.second * -1.0f);
}

std::pair<bool, glm::vec2> CircleCollider::doesCollide(CircleCollider * circle)
{
	glm::vec2 displacement = circle->m_centre - m_centre;
	// Check if distance between centres is less than sum of circle radii
	if (glm::length(displacement) < m_radius + circle->m_radius) {
		// Get nearest point at edge of circle to centre of other circle
		glm::vec2 nearestEdge, otherNearestEdge;
		glm::vec2 direction;
		if (displacement == glm::vec2(0)) {
			direction = glm::vec2(1, 0);
		} else {
			direction = glm::normalize(displacement);
		}
		// Nearest point is at m_radius distance along direction
		nearestEdge = m_centre + m_radius * direction;
		otherNearestEdge = circle->m_centre - circle->m_radius * direction;
		// Penetration vector is difference between these edges
		return std::make_pair(true, otherNearestEdge - nearestEdge);
	}
	else {
		// If distance between centres is greater, no collision
		return std::make_pair(false, glm::vec2());
	}
}

float CircleCollider::testRayCollision(Ray * ray)
{
	// TODO test this!
	// Distance to intersection D is found by D^2 + bD + c = 0
	// If real roots exist, lowest is entry distance. IF that's negative origin inside circle
	glm::vec2 rayDirection = ray->getDirection();
	glm::vec2 rayOrigin = ray->getOrigin();
	glm::vec2 displacement = rayOrigin - m_centre;
	float rayLength = ray->getLength();
	float b = 2.f * glm::dot(rayDirection, displacement);
	float c = glm::dot(displacement, displacement) * m_radius * m_radius;
	float determinant = (b * b) - 4.f * c;
	if (determinant < 0.f) {
		// Imaginary determinant means no intersection
		return -1.f;
	} else {
		float distance = 2.f * c / (std::sqrtf(determinant) - b);
		return std::min(0.f, distance);
	}
}

void CircleCollider::transform(glm::mat3 transformation)
{
	// Translate centre
	m_centre = (glm::vec2)(transformation * glm::vec3(m_centre.x, m_centre.y, 1.f));
	// Radius scaled by longest axis
	m_radius *= std::max(glm::length(transformation[0]), glm::length(transformation[1]));
}
