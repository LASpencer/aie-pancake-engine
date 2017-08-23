#include "stdafx.h"
#include "LogBehaviour.h"
#include "imgui.h"


LogBehaviour::LogBehaviour(GameProjectApp* app, BehaviourPtr behaviour, std::string message) : m_app(app), m_behaviour(behaviour), m_message(message)
{
}

LogBehaviour::~LogBehaviour()
{
}

Behaviour * LogBehaviour::clone()
{
	BehaviourPtr clonedBehaviour(m_behaviour->clone());

	return new LogBehaviour(m_app, clonedBehaviour, m_message);
}

BehaviourResult LogBehaviour::update(Agent * agent, float deltaTime)
{
	BehaviourResult result = m_behaviour->update(agent, deltaTime);
	if (m_app->shouldShowBehaviourTree()) {
		ImVec4 colour;
		switch (result) {
		case(success):
			colour = { 0.1f,0.5f,1,1 };	//Blue
			break;
		case(failure):
			colour = { 1,0,0,1 };	//Red
			break;
		case(running):
			colour = { 0,1,0,1 };	//Green
			break;
		default:
			colour = { 1,1,0,1 };	// Yellow
			break;
		}
		ImGui::TextColored(colour, m_message.c_str());
	}
	return result;
}

void LogBehaviour::setBehaviour(BehaviourPtr behaviour)
{
	m_behaviour = behaviour;
}

BehaviourPtr LogBehaviour::getBehaviour()
{
	return m_behaviour;
}

void LogBehaviour::setMessage(std::string message)
{
	m_message = message;
}
