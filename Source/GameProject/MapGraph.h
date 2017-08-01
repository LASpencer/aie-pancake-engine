#pragma once
#include "stdafx.h"

struct MapNode;

struct MapEdge {
	MapNode* target;
	float cost;
};

struct MapNode {
	glm::vec2 position;

	float gScore;
	float fScore;
	MapNode* parent;

	std::vector<MapEdge> connections;
};


class MapGraph {
public:
	MapGraph();
	~MapGraph();

	std::stack<glm::vec2> dijkstraSearch(MapNode* startNode, MapNode* endNode);

	std::stack<glm::vec2> dijkstraSearch(size_t startNode, size_t endNode);

	std::stack<glm::vec2> aStarSearch(MapNode* startNode, MapNode* endNode, float(*heuristic)(MapNode*, MapNode*));

	void addNode(glm::vec2 position);

	void addEdge(size_t start, size_t end, float cost); //HACK better to use iterators/pointers? Or some other handle?

	void addEdge(MapNode* start, MapNode* end, float cost);

	std::vector<MapNode*> m_graph;
};