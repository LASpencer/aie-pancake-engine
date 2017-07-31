#include "stdafx.h"
#include "MapGraph.h"

MapGraph::MapGraph()
{
}

MapGraph::~MapGraph()
{
	for (MapNode* node : m_graph) {
		delete node;
	}
}

std::stack<glm::vec2> MapGraph::dijkstraSearch(MapNode* startNode, MapNode* endNode)
{
	MapNode* currentNode;
	auto gComp = [](MapNode* lhs, MapNode* rhs) {return lhs->gScore > rhs->gScore; };
	std::priority_queue<MapNode*, std::vector<MapNode*>, decltype(gComp)> openNodes(gComp);
	std::set<MapNode*> closedNodes;
	std::stack<glm::vec2> path;

	for (MapNode* node : m_graph) {
		node->gScore = INFINITY;
		node->parent = nullptr;
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

std::stack<glm::vec2> MapGraph::dijkstraSearch(size_t startNode, size_t endNode)
{
	return dijkstraSearch(m_graph[startNode], m_graph[endNode]);
}

void MapGraph::addNode(glm::vec2 position)
{
	MapNode* newNode = new MapNode({position, 0, nullptr, {}});
	m_graph.push_back(newNode);
}

void MapGraph::addEdge(size_t start, size_t end, float cost)
{
	addEdge(m_graph[start], m_graph[end], cost);
}

void MapGraph::addEdge(MapNode * start, MapNode * end, float cost)
{
	start->connections.push_back({ end, cost });
}