#include "stdafx.h"
#include "CompositeBehaviour.h"

CompositeBehaviour::CompositeBehaviour() : m_running(false)
{
}

CompositeBehaviour::CompositeBehaviour(const std::vector<BehaviourPtr>& children) : m_children(children), m_running(false)
{
}

CompositeBehaviour::~CompositeBehaviour()
{
}

void CompositeBehaviour::addChild(BehaviourPtr child)
{
	m_children.push_back(child);
}

void CompositeBehaviour::setChildren(const std::vector<BehaviourPtr>& children)
{
	m_children = children;
}
