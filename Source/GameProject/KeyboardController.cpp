#include "stdafx.h"
#include "KeyboardController.h"
#include "Entity.h"
#include "Body.h"

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

	float magnitude = 200.f;
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

	std::dynamic_pointer_cast<Body>(entity->getComponent(Component::body))->addForce(force);
}
