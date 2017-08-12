#include "stdafx.h"
#include "AvoidTerrainForce.h"
#include "Entity.h"
#include "GameProjectApp.h"
#include "Collider.h"
#include "CollisionShape.h"

AvoidForce::AvoidForce()
{
	//HACK figure out best way to do these
	m_rays.push_back(Ray({ 0,0 }, { 0.2,1 }, 100.f));
	m_rays.push_back(Ray({ 0,0 }, { -0.2,1 }, 100.f));
}

AvoidForce::~AvoidForce()
{
}

glm::vec2 AvoidForce::getForce(Agent * agent)
{
	//TODO this destroys framerate, solve that
	//TODO get colliders, find closest collision for rays, apply force based on these
	EntityPtr entity(agent->getEntity());
	GameProjectApp* app = entity->getApp();
	glm::vec2 force(0);
	//TODO get all body colliders not belonging to this entity
	std::vector<EntityPtr> entitiesWithCollider = Entity::getEntitiesWithComponent(Component::collider, app->getEntityList());
	//TODO maybe have m_app build container of body colliders/owner, passed to this
	for (Ray ray : m_rays) {
		float distance = -1.f;
		Ray globalRay = ray;
		globalRay.transform(entity->getPosition()->getGlobalTransform());
		for (EntityPtr otherEntity : entitiesWithCollider) {
			if (otherEntity.get() != entity.get()) {
				std::vector<CollisionShapePtr> hitboxes = std::dynamic_pointer_cast<Collider>(otherEntity->getComponent(Component::collider))->getGlobalBoxes();
				for (CollisionShapePtr box : hitboxes) {
					if (box->getType() == BoxType::body) {
						distance = std::max(distance, box->testRayCollision(&globalRay));
					}
				}
			}
		}
		//TODO apply force based on minimum distance found
		if (distance > 0.f) {
			force -= globalRay.getDirection();
		}
	}
	if (force != glm::vec2(0)) {
		//HACK write better way to figure out force
		return agent->getMaxForce() * glm::normalize(force);
	}
	else {
		return glm::vec2(0);
	}
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
