#include "stdafx.h"
#include "KeyboardControlForce.h"
#include "Input.h"
#include "Agent.h"

KeyboardControlForce::KeyboardControlForce()
{
}

KeyboardControlForce::~KeyboardControlForce()
{
}

glm::vec2 KeyboardControlForce::getForce(Agent * agent)
{
	aie::Input* input = aie::Input::getInstance();
	glm::vec2 force(0);

	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		force += glm::vec2(0, 1);
	}
	else if (input->isKeyDown(aie::INPUT_KEY_S)) {
		force += glm::vec2(0, -1);
	}

	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		force += glm::vec2(1, 0);
	}
	else if (input->isKeyDown(aie::INPUT_KEY_A)) {
		force += glm::vec2(-1, 0);
	}
	if (force != glm::vec2(0)) {
		force = glm::normalize(force);
		force *= agent->getMaxForce();
	}
	return force;
}
