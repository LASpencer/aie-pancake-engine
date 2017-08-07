#include "stdafx.h"
#include "KeyboardController.h"
#include "Entity.h"
#include "Agent.h"

KeyboardController::KeyboardController()
{
}


KeyboardController::~KeyboardController()
{
}

Behaviour * KeyboardController::clone()
{
	return new KeyboardController(*this);
}

BehaviourResult KeyboardController::update(Agent* agent, float deltaTime)
{
	// HACK
	aie::Input* input = aie::Input::getInstance();

	float magnitude = agent->getMaxForce();
	glm::vec2 force(0);

	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		force += glm::vec2(0, magnitude);
	} else if (input->isKeyDown(aie::INPUT_KEY_S)) {
		force += glm::vec2(0, -magnitude);
	}
	
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		force += glm::vec2(magnitude,0 );
	} else if (input->isKeyDown(aie::INPUT_KEY_A)) {
		force += glm::vec2(-magnitude, 0);
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL)) {
		force = -agent->getVelocity();
	}

	agent->addForce(force);

	return success;
}
