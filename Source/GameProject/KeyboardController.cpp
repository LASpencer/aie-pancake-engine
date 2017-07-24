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

void KeyboardController::update(EntityPtr entity, float deltaTime)
{
	// HACK
	aie::Input* input = aie::Input::getInstance();

	std::shared_ptr<Agent> agent = std::dynamic_pointer_cast<Agent>(entity->getComponent(Component::agent));

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

	agent->addForce(force);
}
