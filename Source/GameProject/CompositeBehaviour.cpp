#include "stdafx.h"
#include "CompositeBehaviour.h"

CompositeBehaviour::CompositeBehaviour() : m_running(false)
{
	m_ongoingBehaviour = m_children.end();
}

CompositeBehaviour::CompositeBehaviour(const std::vector<BehaviourPtr>& children) : m_children(children), m_running(false)
{
	m_ongoingBehaviour = m_children.end();
}

CompositeBehaviour::~CompositeBehaviour()
{
}

void CompositeBehaviour::addChild(BehaviourPtr child)
{
	m_children.push_back(child);
	m_ongoingBehaviour = m_children.end();
}

void CompositeBehaviour::setChildren(const std::vector<BehaviourPtr>& children)
{
	m_children = children;
	m_ongoingBehaviour = m_children.end();
}
