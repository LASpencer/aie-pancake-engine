#include "stdafx.h"
#include "AABox.h"
#include "OBox.h"
#include "CircleCollider.h"
#include "Ray.h"

AABox::AABox() : CollisionShape(), m_min(0), m_max(1,1)
{
}

AABox::AABox(glm::vec2 cornerA, glm::vec2 cornerB, BoxType type) : CollisionShape(type)
{
	setCorners(cornerA, cornerB);
}

AABox::~AABox()
{
}

CollisionShape * AABox::clone()
{
	return new AABox(*this);
}

std::pair<bool, glm::vec2> AABox::doesCollide(CollisionShape * other)
{
	std::pair<bool, glm::vec2> otherResult = other->doesCollide(this);
	return std::make_pair(otherResult.first, -1.f * otherResult.second);
}

std::pair<bool, glm::vec2> AABox::doesCollide(glm::vec2 point)
{
	if (point.x <= m_min.x
		|| point.x >= m_max.x
		|| point.y <= m_min.y
		|| point.y >= m_max.y) {
		return std::make_pair(false, glm::vec2());
	}
	else {
		glm::vec2 penetration;
		float minX, minY;
		// Get smallest distance from left and right sides
		if (abs(point.x - m_min.x) < abs(point.x - m_max.x)) {
			minX = point.x - m_min.x;
		}
		else {
			minX = point.x - m_max.x;
		}
		// Get smallest distance from top and bottom
		if (abs(point.y - m_min.y) < abs(point.y - m_max.y)) {
			minY = point.y - m_min.y;
		}
		else {
			minY = point.y - m_max.y;
		}
		// If left/right side nearer, return vector pointing from that side
		if (abs(minX) < abs(minY)) {
			penetration.x = minX;
			penetration.y = 0;
		}	// Else return vector pointng from top/bottom
		else {
			penetration.x = 0;
			penetration.y = minY;
		}

		return	std::make_pair(true, penetration);
	}
}

std::pair<bool, glm::vec2> AABox::doesCollide(AABox * box)
{
	// Check if boxes overlap
	if (box->m_min.x >= m_max.x ||
		box->m_min.y >= m_max.y ||
		box->m_max.x <= m_min.x ||
		box->m_max.y <= m_min.y) {
		// If box corners don't overlap, no collision
		return std::make_pair(false, glm::vec2());
	}
	else {
		// Calculate penetration vector
		glm::vec2 penetration;
		float minX, minY;
		// get smallest distance in x axis between max and min corners
		if (abs(box->m_min.x - m_max.x) < abs(box->m_max.x - m_min.x)) {
			minX = box->m_min.x - m_max.x;
		}
		else {
			minX = box->m_max.x - m_min.x;
		}
		// get smallest distance in y axis between max and min corners
		if (abs(box->m_min.y - m_max.y) < abs(box->m_max.y - m_min.y)) {
			minY = box->m_min.y - m_max.y;
		}
		else {
			minY = box->m_max.y - m_min.y;
		}
		// if distance in x axis is smaller, return vector pointing from that side
		if (abs(minX) < abs(minY)) {
			penetration.x = minX;
			penetration.y = 0;
		}
		else {
			// if distance in y axis is smaller, return vector pointing from that side
			penetration.x = 0;
			penetration.y = minY;
		}

		return	std::make_pair(true, penetration);
	}
}

std::pair<bool, glm::vec2> AABox::doesCollide(OBox * box)
{
	std::pair<bool, glm::vec2> otherResult = box->doesCollide(this);
	return std::make_pair(otherResult.first, otherResult.second * -1.0f);
}

std::pair<bool, glm::vec2> AABox::doesCollide(CircleCollider * circle)
{
	std::pair<bool, glm::vec2> otherResult = circle->doesCollide(this);
	return std::make_pair(otherResult.first, otherResult.second * -1.0f);
}

float AABox::testRayCollision(Ray * ray)
{
	float dEntry = 0.0f;	// Distance from ray where point would enter if interesecting.
	float dExit = ray->getLength();	// Distance from ray where point would exit if intersecting
	glm::vec2 rayDirection = ray->getDirection();
	glm::vec2 rayOrigin = ray->getOrigin();
	if (rayDirection.x != 0.0f) {
		float xRate = 1.f / rayDirection.x;
		// Get distance from ray where x component is equal to corners
		float dx1 = xRate * (m_min.x - rayOrigin.x);
		float dx2 = xRate * (m_max.x - rayOrigin.x);

		dEntry = std::max(dEntry, std::min(dx1, dx2));
		dExit = std::min(dExit, std::max(dx1, dx2));
	} else if (rayOrigin.x < m_min.x || rayOrigin.x > m_max.x) {
		// If vertical, check if collision even possible
		return -1;
	}
	if (rayDirection.y != 0.0f) {
		float yRate = 1.f / rayDirection.y;
		// Get distance from ray where y component equal to corners
		float dy1 = yRate * (m_min.y - rayOrigin.y);
		float dy2 = yRate * (m_max.y - rayOrigin.y);
		dEntry = std::max(dEntry, std::min(dy1, dy2));
		dExit = std::min(dExit, std::max(dy1, dy2));
	} else if (rayOrigin.y < m_min.y || rayOrigin.y > m_max.y){
		return -1;
	}
	if (dEntry <= dExit) {
		return dEntry;
	} else {
		return -1;
	}
}

void AABox::draw(aie::Renderer2D * renderer)
{
	glm::vec2 center = 0.5f * (m_min + m_max);
	renderer->drawBox(center.x, center.y, m_max.x - m_min.x, m_max.y - m_min.y);
}

void AABox::transform(glm::mat3 transformation)
{
	//TODO AABox transformation
	//TODO write bounding method, get each corner and transform, bound to transformed corners
}

void AABox::setCorners(glm::vec2 a, glm::vec2 b)
{
	m_min.x = std::min(a.x, b.x);
	m_min.y = std::min(a.y, b.y);

	m_max.x = std::max(a.x, b.x);
	m_max.y = std::max(a.y, b.y);
}

std::tuple<glm::vec2, glm::vec2, glm::vec2, glm::vec2> AABox::getCorners()
{
	glm::vec2 topLeft(m_min.x, m_max.y);
	glm::vec2 bottomRight(m_max.x, m_min.y);
	return std::make_tuple(m_min, topLeft, m_max, bottomRight);
}
