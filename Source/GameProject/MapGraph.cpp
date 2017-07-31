#include "stdafx.h"
#include "MapGraph.h"

std::stack<glm::vec2> MapGraph::dijkstraSearch(MapNode* startNode, MapNode* endNode)
{
	MapNode* currentNode;
	auto gComp = [](MapNode* lhs, MapNode* rhs) {return lhs->gScore > rhs->gScore; };
	std::priority_queue<MapNode*, std::vector<MapNode*>, decltype(gComp)> openNodes(gComp);
	std::set<MapNode*> closedNodes;
	std::stack<glm::vec2> path;

	for (MapNode node : m_graph) {
		node.gScore = INFINITY;
		node.parent = nullptr;
	}
	openNodes.push(startNode);
	startNode->gScore = 0;

	while (!openNodes.empty()) {
		currentNode = openNodes.top();
		openNodes.pop();
		closedNodes.insert(currentNode);
		if (currentNode == endNode) {
			break;
		}
		for (MapEdge edge : currentNode->connections) {
			MapNode* targetNode = edge.target;
			if (closedNodes.count(targetNode) == 0) {
				bool isNotInQueue = targetNode->parent == nullptr;
				float cost = currentNode->gScore + edge.cost;
				if (cost < targetNode->gScore) {
					targetNode->gScore = cost;
					targetNode->parent = currentNode;
				}
				if (isNotInQueue) {
					openNodes.push(targetNode);
				}
			}
		}
	}
	while (currentNode != nullptr) {
		path.push(currentNode->position);
		currentNode = currentNode->parent;
	}
	return path;
}
