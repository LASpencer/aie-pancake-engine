#include "stdafx.h"
#include "KeyboardController.h"
#include "Entity.h"
#include "Agent.h"
#include "KeyboardControlForce.h"

KeyboardController::KeyboardController() : m_keyboardControl(std::make_shared<KeyboardControlForce>())
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
	agent->addForce(std::dynamic_pointer_cast<SteeringForce>(m_keyboardControl), 1.f);
	return success;
}
