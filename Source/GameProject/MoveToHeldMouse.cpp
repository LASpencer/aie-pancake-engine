#include "stdafx.h"
#include "MoveToHeldMouse.h"
#include "Input.h"
#include "Agent.h"

MoveToHeldMouse::MoveToHeldMouse()
{
}

MoveToHeldMouse::~MoveToHeldMouse()
{
}

Behaviour * MoveToHeldMouse::clone()
{
	return new MoveToHeldMouse();
}

BehaviourResult MoveToHeldMouse::update(Agent * agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	BehaviourResult result = failure;
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		glm::vec2 mousePosition(input->getMouseX(), input->getMouseY());
		bool pathFound = agent->setGoal(mousePosition);
		if (pathFound) {
			agent->followPath();
			result = success;
		}
	}
	return result;
}
