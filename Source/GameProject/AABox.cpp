#include "stdafx.h"
#include "AABox.h"

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

std::pair<bool, glm::vec2> AABox::doesCollideWithAABox(AABox * box)
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
