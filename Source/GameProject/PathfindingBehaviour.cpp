#include "stdafx.h"
#include "PathfindingBehaviour.h"
#include "Input.h"
#include "imgui.h"

PathfindingBehaviour::PathfindingBehaviour()
{
}

PathfindingBehaviour::PathfindingBehaviour(const PathfindingBehaviour & other)
{
}

PathfindingBehaviour::~PathfindingBehaviour()
{
}

Behaviour * PathfindingBehaviour::clone()
{
	return new PathfindingBehaviour(*this);
}

BehaviourResult PathfindingBehaviour::update(Agent * agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		glm::vec2 mousePos(input->getMouseX(), input->getMouseY());
		bool pathFound = agent->setGoal(mousePos);
		if (!pathFound) {
			return failure;
		}
	}
	agent->followPath();
	return success; //TODO return false if pathfinding fails?
}
