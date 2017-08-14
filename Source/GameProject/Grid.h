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
	//TODO ctor taking tilemap

	GridSquare(glm::vec2 position, TileType type = TileType::open);

	glm::vec2 getPosition();

	TileType getType();

	float getMoveCost();

	float getSpeedFactor();

	float getGScore();

	float getFScore();

	float getHScore();

	std::shared_ptr<AABox> getCollider();

	void draw(aie::Renderer2D* renderer);

	void drawNodes(aie::Renderer2D* renderer);

	std::vector<EntityWeakPtr>& getContents();


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

	//TODO rewrite so it returns stack of gridsquareptrs
	std::stack<GridSquarePtr> findPath(GridSquarePtr start, GridSquarePtr end, 
		float(*heuristic)(GridSquarePtr, GridSquarePtr) = [](GridSquarePtr a, GridSquarePtr b) {return glm::length(a->getPosition() - b->getPosition()); });

	GridSquarePtr getNearestOpenSquare(glm::vec2 position);

	// Places entities as contents of appropriate grid square
	void placeEntities(std::vector<EntityPtr> entities);

	std::vector<GridSquarePtr> getImpassableSquares();

	void draw(aie::Renderer2D* renderer);

private:
	std::vector<std::vector<GridSquarePtr>> m_squares;

	void calculateEdges();

	void connectSquares(GridSquarePtr a, GridSquarePtr b, bool reachable = true);
};