#include "stdafx.h"
#include "AvoidForce.h"
#include "Entity.h"

AvoidForce::AvoidForce()
{
	//HACK figure out best way to do these
	m_rays.push_back(Ray({ 0,0 }, { 0,1 }, 200.f));
	m_rays.push_back(Ray({ 0,0 }, { 0.2,1 }, 200.f));
	m_rays.push_back(Ray({ 0,0 }, { -0.2,1 }, 200.f));
}

AvoidForce::~AvoidForce()
{
}

glm::vec2 AvoidForce::getForce(Agent * agent)
{
	//TODO get colliders, find closest collision for rays, apply force based on these
	EntityPtr entity(agent->getEntity());
	glm::vec2 force(0);
	//TODO get all body colliders not belonging to this entity
	//TODO maybe have m_app build container of body colliders/owner, passed to this
	for (Ray ray : m_rays) {
		Ray globalRay = ray;
		globalRay.transform(entity->getPosition()->getGlobalTransform());
		
	}
	return glm::vec2();
}

void AvoidForce::draw(Agent * agent, aie::Renderer2D * renderer)
{
	//TODO draw rays
	EntityPtr entity(agent->getEntity());
	for (Ray ray : m_rays) {
		Ray globalRay = ray;
		globalRay.transform(entity->getPosition()->getGlobalTransform());
		globalRay.draw(renderer);
	}

}
