#include "stdafx.h"
#include "AvoidTerrainForce.h"
#include "Entity.h"
#include "GameProjectApp.h"
#include "Collider.h"
#include "CollisionShape.h"
#include "Agent.h"
#include "Grid.h"

AvoidTerrainForce::AvoidTerrainForce()
{
}

AvoidTerrainForce::~AvoidTerrainForce()
{
}

glm::vec2 AvoidTerrainForce::getForce(Agent * agent)
{
	EntityPtr entity(agent->getEntity());
	GameProjectApp* app = entity->getApp();
	Grid* grid = app->getGrid();
	glm::vec2 force(0);
	GridSquarePtr square = agent->getSquare();
	if (square->getType() == impassable) {
		std::pair<bool, glm::vec2> collision = square->getCollider()->doesCollide(agent->getPosition());
		if (collision.first) {
			return glm::normalize(-collision.second) * agent->getMaxForce();
		}
		else {
			return agent->getPosition() - square->getPosition();
		}
	}
	else if (agent->getVelocity() != glm::vec2(0.f)) {
		// Check future collision, and 
		std::vector<GridSquarePtr> neighbours = grid->getAdjacentSquares(square);
		Ray futurePath(agent->getPosition(), agent->getVelocity(), glm::length(agent->getVelocity()) * 0.5f);
		for (GridSquarePtr neighbour : neighbours) {
			if (neighbour->getType() == impassable) {
				std::shared_ptr<AABox> collider = neighbour->getCollider();
				float collisionDistance = collider->testRayCollision(&futurePath);
				if (collisionDistance >= 0.f) {
					glm::vec2 collisionPoint = futurePath.getOrigin() + futurePath.getDirection() * collisionDistance;
					glm::vec2 displacement = collisionPoint - neighbour->getPosition();
					if (abs(displacement.x) > abs(displacement.y)) {
						if (displacement.x > 0.f) {
							force = glm::vec2(1, 0);
						}
						else {
							force = glm::vec2(-1, 0);
						}
					}
					else {
						if (displacement.y > 0.f) {
							force = glm::vec2(0, 1);
						}
						else {
							force = glm::vec2(0, -1);
						}
					}
					return force * agent->getMaxForce();
				}
			}
		}
	}
	return glm::vec2(0);
}

void AvoidTerrainForce::draw(Agent * agent, aie::Renderer2D * renderer)
{
	//TODO draw rays
	////EntityPtr entity(agent->getEntity());
	////for (Ray ray : m_rays) {
	////	Ray globalRay = ray;
	////	globalRay.transform(entity->getPosition()->getGlobalTransform());
	////	globalRay.draw(renderer);
	////}

}