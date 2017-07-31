#pragma once
#include "stdafx.h"

struct MapEdge {
	MapNode* target;
	float cost;
};

struct MapNode {
	glm::vec2 position;

	float gScore;
	MapNode* parent;

	std::vector<MapEdge> connections;
};


class MapGraph {
public:

	std::stack<glm::vec2> dijkstraSearch(MapNode* startNode, MapNode* endNode);

	std::vector<MapNode> m_graph;
};