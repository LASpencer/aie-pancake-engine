#include "stdafx.h"
#include "PathfindingBehaviour.h"
#include "Input.h"

PathfindingBehaviour::PathfindingBehaviour(MapGraph * map, MapNode * startingNode) : m_map(map), m_currentNode(startingNode)
{
	m_target = std::make_shared<PointTarget>(startingNode->position);
	m_arrive.setTarget(m_target);
}

PathfindingBehaviour::~PathfindingBehaviour()
{
}

void PathfindingBehaviour::update(Agent * agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		glm::vec2 mousePos(input->getMouseX(), input->getMouseY());
		for (MapNode* node : m_map->m_graph) {
			if (glm::length(mousePos - node->position) < 15) {
				m_path = m_map->dijkstraSearch(m_currentNode, node);
				m_currentNode = node;
				break;
			}
		}
	}
	if (!m_path.empty() && glm::length(agent->getPosition() - m_target->getPosition()) < 10) {
		m_target->setTarget(m_path.top());
		m_path.pop();
	}
	agent->addForce(m_arrive.getForce(agent));
}
