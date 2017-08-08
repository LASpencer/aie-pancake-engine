#include "stdafx.h"
#include "Ray.h"

Ray::Ray() : m_origin(0), m_direction(1,0), m_length(INFINITY)
{
}

Ray::Ray(glm::vec2 origin, glm::vec2 direction, float length) : m_origin(origin), m_direction(glm::normalize(direction)), m_length(length)
{
}

Ray::~Ray()
{
}

void Ray::setOrigin(glm::vec2 origin)
{
	m_origin = origin;
}

void Ray::setDirection(glm::vec2 direction)
{
	m_direction = glm::normalize(direction);
}

void Ray::setLength(float length)
{
	m_length = abs(length);
}

glm::vec2 Ray::findClosestPoint(glm::vec2 point)
{
	float distance = std::min(m_length, std::max(0.f, glm::dot(point, m_direction)));
	return m_origin + distance * m_direction;
}

void Ray::transform(glm::mat3 transformation)
{
	m_origin = (glm::vec2)(transformation * glm::vec3(m_origin.x, m_origin.y, 1.f));
	glm::vec2 transformedDirection = (glm::vec2)(transformation * glm::vec3(m_direction.x, m_direction.y, 0.f));
	m_direction = glm::normalize(transformedDirection);
	m_length *= glm::length(transformedDirection);
}

void Ray::draw(aie::Renderer2D * renderer)
{
	glm::vec2 endpoint;
	if (m_length == INFINITY) {
		endpoint = m_origin + m_direction * 1000.f;
	} else {
		endpoint = m_origin + m_direction * m_length;
	}
	renderer->drawLine(m_origin.x, m_origin.y, endpoint.x, endpoint.y);
}
