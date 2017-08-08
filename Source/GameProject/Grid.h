#pragma once
#include "stdafx.h"

class Grid;
class GridSquare;

typedef std::shared_ptr<GridSquare> GridSquarePtr;
typedef std::weak_ptr<GridSquare> GridSquareWeakPtr;

struct GridEdge {
	GridSquareWeakPtr target;
	float cost;
};

enum TileType {
	open,
	difficult,
	impassable
};

class GridSquare {
public:
	friend class Grid;

	GridSquare();

	GridSquare(glm::vec2 position, TileType type = TileType::open);

	glm::vec2 getPosition();

	TileType getType();


private:
	glm::vec2 m_position;
	TileType type;

	float m_gScore;
	float m_fScore;
	GridSquarePtr m_parent;

	std::vector<GridEdge> m_connections;
};

class Grid {
public:
	static const float square_size;
	
	Grid();
	
	GridSquarePtr getSquare(glm::vec2 position);

	std::stack<glm::vec2> findPath(GridSquarePtr start, GridSquarePtr end, float(*heuristic)(GridSquare*, GridSquare*) = [](GridSquare*, GridSquare*) {return 0.f; });

private:
	std::vector<std::vector<GridSquarePtr>> m_squares;
};