#pragma once
#include "stdafx.h"
#include "Renderer2D.h"
#include "AABox.h"

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

	// Gets cost for pathfinding through square
	float getMoveCost();

	// Gets movement speed modifier in square
	float getSpeedFactor();

	float getGScore();

	float getFScore();

	float getHScore();

	std::shared_ptr<AABox> getCollider();

	// Draws rectangle of appropriate colour
	void draw(aie::Renderer2D* renderer);

	void drawNodes(aie::Renderer2D* renderer);

	std::vector<EntityWeakPtr>& getContents();

	// Checks if point is within square
	bool isInSquare(glm::vec2 position);
	
	// Checks if point is withing square or reachable neighbours
	bool isInSelfOrNeighbour(glm::vec2 position);

private:
	glm::vec2 m_position;
	TileType m_type;
	std::shared_ptr<AABox> m_collider;

	float gScore;
	float hScore;
	float fScore;
	GridSquareWeakPtr m_parent;

	std::vector<GridEdge> m_connections;
	std::vector<GridSquareWeakPtr> m_unreachableNeighbour;

	std::vector<EntityWeakPtr> m_contents;

	void setPosition(glm::vec2 position);
};

class Grid {
public:
	static const float square_size;

	static const float difficult_move_cost;

	static const float difficult_speed_factor;
	
	Grid();

	Grid(std::vector<std::vector<TileType>> tiles);
	
	GridSquarePtr getSquare(glm::vec2 position);

	std::vector<GridSquarePtr> getAdjacentSquares(glm::vec2 position);

	std::vector<GridSquarePtr> getAdjacentSquares(GridSquarePtr square);

	// Finds path to end square, or empty stack if no paths found
	std::stack<GridSquarePtr> findPath(GridSquarePtr start, GridSquarePtr end, 
		float(*heuristic)(GridSquarePtr, GridSquarePtr) = [](GridSquarePtr a, GridSquarePtr b) {return glm::length(a->getPosition() - b->getPosition()); });

	// Finds nearest square that's not impassabl
	GridSquarePtr getNearestOpenSquare(glm::vec2 position);

	// Places entities as contents of appropriate grid square
	void placeEntities(std::vector<EntityPtr> entities);

	// Returns all impassable squares in grid
	std::vector<GridSquarePtr> getImpassableSquares();

	void draw(aie::Renderer2D* renderer);

	void toggleShowNodes();

private:
	std::vector<std::vector<GridSquarePtr>> m_squares;

	bool m_showNodes;

	void calculateEdges();

	void connectSquares(GridSquarePtr a, GridSquarePtr b, bool reachable = true);
};