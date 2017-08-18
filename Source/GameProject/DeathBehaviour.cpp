#include "stdafx.h"
#include "DeathBehaviour.h"
#include "imgui.h"

DeathBehaviour::DeathBehaviour()
{
}

DeathBehaviour::~DeathBehaviour()
{
}

Behaviour * DeathBehaviour::clone()
{
	return new DeathBehaviour(*this);
}

BehaviourResult DeathBehaviour::update(Agent * agent, float deltaTime)
{
	ImGui::Text("Death behaviour");
	//TODO running until countdown to respawn finishes? Or just be dead
	return success;
}
