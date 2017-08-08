#include "stdafx.h"
#include "OBox.h"
#include "AABox.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "Ray.h"

OBox::OBox() : CollisionShape(), m_xExtent(1,0), m_yExtent(0,1), m_centre(0)
{
}

OBox::OBox(glm::vec2 xExtent, glm::vec2 yExtent, glm::vec2 centre, BoxType type) : CollisionShape(type), m_xExtent(xExtent), m_yExtent(yExtent), m_centre(centre)
{
}

OBox::~OBox()
{
}

CollisionShape * OBox::clone()
{
	return new OBox(*this);
}

std::pair<bool, glm::vec2> OBox::doesCollide(CollisionShape * other)
{
	std::pair<bool, glm::vec2> otherResult = other->doesCollide(this);
	return std::make_pair(otherResult.first, -1.f * otherResult.second);
}

std::pair<bool, glm::vec2> OBox::doesCollide(glm::vec2 point)
{
	glm::vec2 displacement = point - m_centre;
	float xProjection = glm::dot(m_xExtent, displacement);
	float yProjection = glm::dot(m_yExtent, displacement);
	// Check projections less than extents
	if (glm::length(m_xExtent) > abs(xProjection) && glm::length(m_yExtent) > abs(yProjection)) {
		glm::vec2 xDisplacement = xProjection * glm::normalize(m_xExtent);
		glm::vec2 yDisplacement = yProjection * glm::normalize(m_yExtent);
		glm::vec2 xPenetration, yPenetration, minPenetration;

		if (xProjection >= 0) {
			xPenetration = xDisplacement - m_xExtent;
		}
		else {
			xPenetration = xDisplacement + m_xExtent;
		}
		if (yProjection >= 0) {
			yPenetration = yDisplacement - m_yExtent;
		}
		else {
			yPenetration = yDisplacement + m_yExtent;
		}

		if (glm::length(xPenetration) < glm::length(yPenetration)) {
			minPenetration = xPenetration;
		}
		else {
			minPenetration = yPenetration;
		}

		bool penetrationNotZero = minPenetration != glm::vec2(0);
		return std::make_pair(penetrationNotZero, minPenetration);
	}
	else {
		return std::make_pair(false, glm::vec2(0));
	}

}

std::pair<bool, glm::vec2> OBox::doesCollide(AABox * box)
{
	// get each corner of both boxes
	std::tuple<glm::vec2, glm::vec2, glm::vec2, glm::vec2> corners = getCorners();
	glm::vec2 thisCorners[4] = { std::get<0>(corners), std::get<1>(corners), std::get<2>(corners), std::get<3>(corners) };
	corners = box->getCorners();
	glm::vec2 otherCorners[4] = { std::get<0>(corners), std::get<1>(corners), std::get<2>(corners), std::get<3>(corners) };

	// get each axis to test
	glm::vec2 axis[8];
	glm::vec2 minAxis;
	float minOverlap = INFINITY;
	for (size_t i = 0; i < 4; i++) {
		glm::vec2 thisSide, otherSide;
		if (i == 3) {
			// Side from last corner to first
			thisSide = thisCorners[0] - thisCorners[3];
			otherSide = otherCorners[0] - otherCorners[3];
		}
		else {
			// Side from current corner to next
			thisSide = thisCorners[i + 1] - thisCorners[i];
			otherSide = otherCorners[i + 1] - otherCorners[i];
		}
		// Normalise sides
		thisSide = glm::normalize(thisSide);
		otherSide = glm::normalize(otherSide);
		// Axis is normal of side
		axis[i][0] = -(thisSide[1]);
		axis[i][1] = thisSide[0];
		axis[i + 4][0] = -(otherSide[1]);
		axis[i + 4][1] = otherSide[0];
	}
	// Project boxes onto each axis and check for overlap
	for (size_t i = 0; i < 8; i++) {
		float thisMin = INFINITY;
		float otherMin = INFINITY;
		float thisMax = -INFINITY;
		float otherMax = -INFINITY;
		// Project each point onto axis and record minimum and maximum values for each box
		for (size_t corner = 0; corner < 4; corner++) {
			float thisProjection = glm::dot(axis[i],thisCorners[corner]);
			float otherProjection = glm::dot(axis[i], otherCorners[corner]);
			thisMin = std::min(thisMin, thisProjection);
			thisMax = std::max(thisMax, thisProjection);
			otherMin = std::min(otherMin, otherProjection);
			otherMax = std::max(otherMax, otherProjection);
		}
		float overlap = std::min(thisMax - otherMin, otherMax - thisMin);
		// Check if overlap exists on this axis
		if (overlap <= 0) {
			// If no overlap, boxes do not collide
			return std::make_pair(false, glm::vec2(0));
		}
		else {
			// Check if this is axis with lowest overlap so far
			if (overlap < minOverlap) {
				minOverlap = overlap;
				minAxis = axis[i];
			}
		}
	}
	// If no axis without overlap was found, collision must have occured
	// Penetration vector is axis with minimum overlap, multiplied by that overlap
	glm::vec2 minPenetration = minOverlap * minAxis;
	// Calculate centre of AABox
	glm::vec2 otherCentre = 0.5f * (box->getMinCorner() + box->getMaxCorner());
	// Make sure penetration vector is pointing away from other box's centre
	glm::vec2 translationDirection = m_centre - otherCentre;
	if (glm::dot(minPenetration, translationDirection) < 0) {
		minPenetration = -minPenetration;
	}
	return std::make_pair(true, minPenetration);
}

std::pair<bool, glm::vec2> OBox::doesCollide(OBox * box)
{
	// get each corner of both boxes
	std::tuple<glm::vec2, glm::vec2, glm::vec2, glm::vec2> corners = getCorners();
	glm::vec2 thisCorners[4] = { std::get<0>(corners), std::get<1>(corners), std::get<2>(corners), std::get<3>(corners) };
	corners = box->getCorners();
	glm::vec2 otherCorners[4] = { std::get<0>(corners), std::get<1>(corners), std::get<2>(corners), std::get<3>(corners) };

	// get each axis to test
	glm::vec2 axis[8];
	glm::vec2 minAxis;
	float minOverlap = INFINITY;
	for (size_t i = 0; i < 4; i++) {
		glm::vec2 thisSide, otherSide;
		if (i == 3) {
			// Side from last corner to first
			thisSide = thisCorners[0] - thisCorners[3];
			otherSide = otherCorners[0] - otherCorners[3];
		}
		else {
			// Side from current corner to next
			thisSide = thisCorners[i + 1] - thisCorners[i];
			otherSide = otherCorners[i + 1] - otherCorners[i];
		}
		// Normalise sides
		thisSide = glm::normalize(thisSide);
		otherSide = glm::normalize(otherSide);
		// Axis is normal of side
		axis[i][0] = -(thisSide[1]);
		axis[i][1] = thisSide[0];
		axis[i + 4][0] = -(otherSide[1]);
		axis[i + 4][1] = otherSide[0];
	}
	// Project boxes onto each axis and check for overlap
	for (size_t i = 0; i < 8; i++) {
		float thisMin = INFINITY;
		float otherMin = INFINITY;
		float thisMax = -INFINITY;
		float otherMax = -INFINITY;
		// Project each point onto axis and record minimum and maximum values for each box
		for (size_t corner = 0; corner < 4; corner++) {
			float thisProjection = glm::dot(axis[i], thisCorners[corner]);
			float otherProjection = glm::dot(axis[i], otherCorners[corner]);
			thisMin = std::min(thisMin, thisProjection);
			thisMax = std::max(thisMax, thisProjection);
			otherMin = std::min(otherMin, otherProjection);
			otherMax = std::max(otherMax, otherProjection);
		}
		float overlap = std::min(thisMax - otherMin, otherMax - thisMin);
		// Check if overlap exists on this axis
		if (overlap <= 0) {
			// If no overlap, boxes do not collide
			return std::make_pair(false, glm::vec2(0));
		}
		else {
			// Check if this is axis with lowest overlap so far
			if (overlap < minOverlap) {
				minOverlap = overlap;
				minAxis = axis[i];
			}
		}
	}
	// If no axis without overlap was found, collision must have occured
	// Penetration vector is axis with minimum overlap, multiplied by that overlap
	glm::vec2 minPenetration = minOverlap * minAxis;
	// Calculate centre of AABox
	// Make sure penetration vector is pointing away from other box's centre
	glm::vec2 translationDirection = m_centre - box->m_centre;
	if (glm::dot(minPenetration, translationDirection) < 0) {
		minPenetration = -minPenetration;
	}
	return std::make_pair(true, minPenetration);
}

std::pair<bool, glm::vec2> OBox::doesCollide(CircleCollider * circle)
{
	// Get corners of this box
	std::tuple<glm::vec2, glm::vec2, glm::vec2, glm::vec2> corners = getCorners();
	glm::vec2 thisCorners[4] = { std::get<0>(corners), std::get<1>(corners), std::get<2>(corners), std::get<3>(corners) };

	// get each axis to test
	glm::vec2 axis[4];
	glm::vec2 minAxis;
	float minOverlap = INFINITY;
	for (size_t i = 0; i < 4; i++) {
		glm::vec2 thisSide;
		if (i == 3) {
			// Side from last corner to first
			thisSide = thisCorners[0] - thisCorners[3];
		}
		else {
			// Side from current corner to next
			thisSide = thisCorners[i + 1] - thisCorners[i];
		}
		// Normalise sides
		thisSide = glm::normalize(thisSide);
		// Axis is normal of side
		axis[i][0] = -(thisSide[1]);
		axis[i][1] = thisSide[0];
	}
	// Project box and circle onto each axis and check for overlap
	for (size_t i = 0; i < 4; i++) {
		float thisMin = INFINITY;
		float thisMax = -INFINITY;
		// Circle projection will always be projection of centre +/- radius
		float circleCentre = glm::dot(axis[i], circle->getCentre());
		float circleMin = circleCentre - circle->getRadius();
		float circleMax = circleCentre + circle->getRadius();
		// Project each point onto axis and record minimum and maximum values for each box
		for (size_t corner = 0; corner < 4; corner++) {
			float thisProjection = glm::dot(axis[i], thisCorners[corner]);
			thisMin = std::min(thisMin, thisProjection);
			thisMax = std::max(thisMax, thisProjection);
		}
		float overlap = std::min(thisMax - circleMin, circleMax - thisMin);
		// Check if overlap exists on this axis
		if (overlap <= 0) {
			// If no overlap, box and circle do not collide
			return std::make_pair(false, glm::vec2());
		}
		else {
			// Check if this is axis with lowest overlap so far
			if (overlap < minOverlap) {
				minOverlap = overlap;
				minAxis = axis[i];
			}
		}
	}
	// If no axis without overlap was found, collision must have occured
	// Penetration vector is axis with minimum overlap, multiplied by that overlap
	glm::vec2 minPenetration = minOverlap * minAxis;
	// Make sure penetration vector is pointing away from circle's centre
	glm::vec2 translationDirection = m_centre - circle->getCentre();
	if (glm::dot(minPenetration, translationDirection) < 0) {
		minPenetration = -minPenetration;
	}
	return std::make_pair(true, minPenetration);
}

float OBox::testRayCollision(Ray * ray)
{
	//TODO write test
	std::tuple<Plane, Plane, Plane, Plane> planes = getPlanes();
	Plane sides[4] = { std::get<0>(planes), std::get<1>(planes), std::get<2>(planes), std::get<3>(planes) };
	float dEntry = 0.0f;
	float dExit = ray->getLength();
	float dHit1, dHit2, rate;
	glm::vec2 rayDirection = ray->getDirection();
	glm::vec2 rayOrigin = ray->getOrigin();
	if (glm::dot(rayDirection, sides[0].normal) != 0.f) {
		rate = 1.f / (glm::dot(rayDirection, sides[0].normal));
		dHit1 = -(glm::dot(rayOrigin, sides[0].normal) + sides[0].offset) * rate;
		dHit2 = (glm::dot(rayOrigin, sides[1].normal) + sides[1].offset) * rate;
		dEntry = std::max(dEntry, std::min(dHit1, dHit2));
		dExit = std::min(dExit, std::max(dHit1, dHit2));
	}
	if (glm::dot(rayDirection, sides[2].normal) != 0.f) {
		rate = 1.f / (glm::dot(rayDirection, sides[2].normal));
		dHit1 = -(glm::dot(rayOrigin, sides[2].normal) + sides[2].offset)* rate;
		dHit2 = (glm::dot(rayOrigin, sides[3].normal) + sides[3].offset) * rate;
		dEntry = std::max(dEntry, std::min(dHit1, dHit2));
		dExit = std::min(dExit, std::max(dHit1, dHit2));
	}
	if (dEntry <= dExit) {
		return dEntry;
	}
	else {
		return -1;
	}
}

void OBox::draw(aie::Renderer2D * renderer)
{
	//todo
}

std::tuple<glm::vec2, glm::vec2, glm::vec2, glm::vec2> OBox::getCorners()
{

	glm::vec2 thisCorners[4];
	thisCorners[0] = m_centre + m_xExtent + m_yExtent;
	thisCorners[1] = m_centre + m_xExtent - m_yExtent;
	thisCorners[2] = m_centre - m_xExtent - m_yExtent;
	thisCorners[3] = m_centre - m_xExtent + m_yExtent;
	return std::make_tuple(thisCorners[0], thisCorners[1], thisCorners[2], thisCorners[3]);
}

std::tuple<Plane, Plane, Plane, Plane> OBox::getPlanes()
{
	Plane planes[4];
	planes[0].normal = glm::normalize(m_xExtent);
	planes[1].normal = -planes[0].normal;
	planes[2].normal = glm::normalize(m_yExtent);
	planes[3].normal = -planes[2].normal;
	for (int i = 0; i < 4; ++i) {
		planes[i].offset = -(glm::dot(planes[i].normal, planes[i].normal + m_centre));
	}
	return std::make_tuple(planes[0], planes[1], planes[2], planes[3]);
}

void OBox::transform(glm::mat3 transformation)
{
	glm::mat3 boxComponents(m_xExtent.x, m_xExtent.y, 0.f,
							m_yExtent.x, m_yExtent.y, 0.f,
							m_centre.x, m_centre.y, 1.f);
	boxComponents = transformation * boxComponents;
	m_xExtent = (glm::vec2)boxComponents[0];
	m_yExtent = (glm::vec2)boxComponents[1];
	m_centre = (glm::vec2)boxComponents[2];
}
