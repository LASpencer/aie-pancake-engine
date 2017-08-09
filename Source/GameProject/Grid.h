#pragma once
#include "stdafx.h"
#include "Renderer2D.h"

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
	//TODO ctor taking tilemap

	GridSquare(glm::vec2 position, TileType type = TileType::open);

	glm::vec2 getPosition();

	TileType getType();

	float getMoveCost();

	float getGScore();

	float getFScore();

	float getHScore();

	void draw(aie::Renderer2D* renderer);

	void drawNodes(aie::Renderer2D* renderer);

private:
	glm::vec2 m_position;
	TileType m_type;

	float gScore;
	float hScore;
	float fScore;
	GridSquare* m_parent;

	std::vector<GridEdge> m_connections;
};

class Grid {
public:
	static const float square_size;

	static const float difficult_move_cost;

	static const float difficult_speed_factor;
	
	Grid();
	
	GridSquarePtr getSquare(glm::vec2 position);

	std::stack<glm::vec2> findPath(GridSquarePtr start, GridSquarePtr end, 
		float(*heuristic)(GridSquare*, GridSquare*) = [](GridSquare* a, GridSquare* b) {return glm::length(a->getPosition() - b->getPosition()); });

	void draw(aie::Renderer2D* renderer);

private:
	std::vector<std::vector<GridSquarePtr>> m_squares;

	void calculateEdges();

	void connectSquares(GridSquarePtr a, GridSquarePtr b);
};