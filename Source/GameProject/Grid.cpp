#include "stdafx.h"
#include "Grid.h"
#include "GameProjectApp.h"

const float Grid::square_size = 80.f;

const float Grid::difficult_move_cost = 2.f;
const float Grid::difficult_speed_factor = 1.f/Grid::difficult_move_cost;

Grid::Grid()
{
	size_t squaresWide = (GameProjectApp::max_corner - GameProjectApp::min_corner).x / square_size;
	size_t squaresHigh = (GameProjectApp::max_corner - GameProjectApp::min_corner).y / square_size;

	//TODO make grid of all open squares, with each adjacent (diagonal or orthogonal) connected to each other
	for (size_t i = 0; i < squaresWide; ++i) {
		std::vector<GridSquarePtr> column;
		for (size_t j = 0; j < squaresHigh; ++j) {
			glm::vec2 position(GameProjectApp::min_corner.x + (0.5f + i)*square_size,
								GameProjectApp::min_corner.y + (0.5f + j) * square_size);
			column.push_back(std::make_shared<GridSquare>(position, open));
		}
		m_squares.push_back(column);
	}
	// calculate connections for all squares
	calculateEdges();
}

Grid::Grid(std::vector<std::vector<TileType>> tiles)
{
	for (size_t i = 0; i < tiles.size(); ++i) {
		std::vector<GridSquarePtr> column;
		for (size_t j = 0; j < tiles[i].size(); ++j) {
			glm::vec2 position(GameProjectApp::min_corner.x + (0.5f + i)*square_size,
				GameProjectApp::min_corner.y + (0.5f + j) * square_size);
			column.push_back(std::make_shared<GridSquare>(position, tiles[i][j]));
		}
		m_squares.push_back(column);
	}
	// calculate connections for all squares
	calculateEdges();
}


GridSquarePtr Grid::getSquare(glm::vec2 position)
{
	size_t x = std::min((size_t)(std::max(0.f, position.x - GameProjectApp::min_corner.x) * (1.f / square_size)), m_squares.size()-1);
	size_t y = std::min((size_t)(std::max(0.f, position.y - GameProjectApp::min_corner.y) * (1.f / square_size)), m_squares[x].size()-1);
	return m_squares[x][y];
}

std::vector<GridSquarePtr> Grid::getAdjacentSquares(glm::vec2 position)
{
	return getAdjacentSquares(getSquare(position));
}

std::vector<GridSquarePtr> Grid::getAdjacentSquares(GridSquarePtr square)
{
	std::vector<GridSquarePtr> adjacentSquares;
	for (GridSquareWeakPtr neigbour : square->m_unreachableNeighbour) {
		adjacentSquares.push_back(GridSquarePtr(neigbour));
	}
	for (GridEdge edge : square->m_connections) {
		adjacentSquares.push_back(GridSquarePtr(edge.target));
	}
	return adjacentSquares;
}

std::stack<glm::vec2> Grid::findPath(GridSquarePtr start, GridSquarePtr end, float(*heuristic)(GridSquare *, GridSquare *))
{
	GridSquare* currentSquare;
	auto fComp = [](GridSquare* lhs, GridSquare* rhs) {return lhs->getFScore() > rhs->getFScore(); };
	std::priority_queue<GridSquare*, std::vector<GridSquare*>, decltype(fComp)> openNodes(fComp);
	std::set<GridSquare*> closedNodes;
	std::stack<glm::vec2> path;

	for (auto col : m_squares) {
		for (GridSquarePtr square : col) {
			square->gScore = INFINITY;
			square->fScore = INFINITY;
			square->hScore = INFINITY;
			square->m_parent = nullptr;
		}
	}
	openNodes.push(start.get());
	start->gScore = 0;
	start->fScore = heuristic(start.get(), end.get());

	while (!openNodes.empty()) {
		currentSquare = openNodes.top();
		openNodes.pop();
		closedNodes.insert(currentSquare);
		if (currentSquare = end.get()) {
			break;
		}
		for (GridEdge edge : currentSquare->m_connections) {
			GridSquare* targetSquare = edge.target.lock().get();
			if (closedNodes.count(targetSquare) == 0)
			{
				bool isNotInQueue = targetSquare->m_parent == nullptr;
				if (targetSquare->hScore == INFINITY) {
					targetSquare->hScore = heuristic(targetSquare, end.get());
				}
				float cost = currentSquare->gScore + edge.cost;
				if (cost < targetSquare->gScore) {
					targetSquare->gScore = cost;
					targetSquare->fScore = targetSquare->gScore + targetSquare->hScore;
				}
				if (isNotInQueue) {
					openNodes.push(targetSquare);
				}
			}
		}
	}
	if (currentSquare == end.get()) {
		while (currentSquare != nullptr) {
			path.push(currentSquare->m_position);
			currentSquare = currentSquare->m_parent;
		}
	}
	return path;
}

GridSquarePtr Grid::getNearestOpenSquare(glm::vec2 position)
{
	typedef std::pair<GridSquarePtr, float> SquarePriority;
	GridSquarePtr square = getSquare(position);
	if (square->getType() != impassable) {
		return square;
	}
	else {
		auto fComp = [](GridSquarePtr lhs, GridSquarePtr rhs) {return lhs->getFScore() > rhs->getFScore(); };
		std::priority_queue<GridSquarePtr, std::vector<GridSquarePtr>, decltype(fComp)> searchQueue(fComp);
		std::set<GridSquarePtr> exploredSquares;
		glm::vec2 displacement = square->getPosition() - position;
		for (auto col : m_squares) {
			for (GridSquarePtr square : col) {
				square->gScore = INFINITY;
				square->fScore = INFINITY;
				square->hScore = INFINITY;
				square->m_parent = nullptr;
			}
		}
		square->fScore = glm::dot(displacement, displacement);
		exploredSquares.insert(square);
		
		while (!searchQueue.empty()) {
			GridSquarePtr current = searchQueue.top();
			searchQueue.pop();
			if (current->getType() != impassable) {
				return current;
			}
			else {
				for (GridSquarePtr neighbour : getAdjacentSquares(current)) {
					if (exploredSquares.count(neighbour) == 0) {
						exploredSquares.insert(neighbour);
						displacement = neighbour->getPosition() - position;
						neighbour->fScore = glm::dot(displacement, displacement);
						searchQueue.push(neighbour);
					}
				}
			}
		}
		return square;	// Return current position if no path found
	}
}

void Grid::draw(aie::Renderer2D * renderer)
{
	for (auto col : m_squares) {
		for (GridSquarePtr square : col) {
			square->draw(renderer);
		}
	}
	//Draw nodes
	//HACK should be conditional on some bool/"debug mode"
	for (auto col : m_squares) {
		for (GridSquarePtr square : col) {
			square->drawNodes(renderer);
		}
	}
}

void Grid::calculateEdges()
{

	for (size_t i = 0; i < m_squares.size(); ++i) {
		bool lastColumn = i + 1 == m_squares.size();
		for (size_t j = 0; j < m_squares[i].size(); ++j) {
			bool lastSquare = j + 1 == m_squares[i].size();
			bool firstSquare = j == 0;
			if (!lastSquare) {
				// Connect to next square
				connectSquares(m_squares[i][j], m_squares[i][j+1]);
			}
			if (!lastColumn) {
				// Connect to next column
				connectSquares(m_squares[i][j], m_squares[i + 1][j]);
				// Connect diagonally
				if (!firstSquare) {
					connectSquares(m_squares[i][j], m_squares[i + 1][j - 1]);
				}
				if (!lastSquare) {
					connectSquares(m_squares[i][j], m_squares[i + 1][j+1]);
				}
			}
		}
	}
}

void Grid::connectSquares(GridSquarePtr a, GridSquarePtr b)
{
	if (a->m_type != impassable && b->m_type != impassable) {
		float moveCost = 0.5f * (a->getMoveCost() + b->getMoveCost());
		float totalCost = moveCost * glm::length(a->m_position - b->m_position);
		a->m_connections.push_back({ GridSquareWeakPtr(b), totalCost });
		b->m_connections.push_back({ GridSquareWeakPtr(a), totalCost });
	}
	else {
		a->m_unreachableNeighbour.push_back(GridSquareWeakPtr(b));
		b->m_unreachableNeighbour.push_back(GridSquareWeakPtr(a));
	}
}

GridSquare::GridSquare() : m_position(glm::vec2(0)), m_type(open), gScore(0), fScore(0), hScore(0), m_parent(nullptr)
{
	glm::vec2 cornerExtent(Grid::square_size * 0.5f, Grid::square_size * 0.5f);
	m_collider = std::make_shared<AABox>(m_position - cornerExtent, m_position + cornerExtent, BoxType::terrain);
}

GridSquare::GridSquare(glm::vec2 position, TileType type) : m_position(position), m_type(type), gScore(0), fScore(0), hScore(0), m_parent(nullptr)
{
	glm::vec2 cornerExtent(Grid::square_size * 0.5f, Grid::square_size * 0.5f);
	m_collider = std::make_shared<AABox>(m_position - cornerExtent, m_position + cornerExtent, BoxType::terrain);
}

glm::vec2 GridSquare::getPosition()
{
	return m_position;
}

TileType GridSquare::getType()
{
	return m_type;
}

float GridSquare::getMoveCost()
{
	switch (m_type) {
	case(open):
		return 1.f;
		break;
	case(difficult):
		return Grid::difficult_move_cost;
		break;
	case(impassable):
		return INFINITY;
		break;
	default:
		return INFINITY;
		break;
	}
}

float GridSquare::getSpeedFactor()
{
	switch (m_type) {
	case(open):
		return 1.f;
		break;
	case(difficult):
		return Grid::difficult_speed_factor;
		break;
	case(impassable):
		return 1.f;
		break;
	default:
		return 1.f;
		break;
	}
}

float GridSquare::getGScore()
{
	return gScore;
}

float GridSquare::getFScore()
{
	return fScore;
}

float GridSquare::getHScore()
{
	return hScore;
}

std::shared_ptr<AABox> GridSquare::getCollider()
{
	return m_collider;
}

void GridSquare::draw(aie::Renderer2D * renderer)
{
	//TODO based on type, draw sprite
	switch (m_type) {
	case(open):
		renderer->setRenderColour(0x00ff00ff);
		break;
	case(difficult):
		renderer->setRenderColour(0xffff00ff);
		break;
	case(impassable):
		renderer->setRenderColour(0xff0000ff);
		break;
	default:
		break;
	}
	renderer->drawBox(m_position.x, m_position.y, Grid::square_size, Grid::square_size);
}

void GridSquare::drawNodes(aie::Renderer2D * renderer)
{
	renderer->setRenderColour(0xffffffff);
	renderer->drawCircle(m_position.x, m_position.y, Grid::square_size * 0.2f);
	for (GridEdge edge : m_connections) {
		GridSquarePtr target(edge.target);
		renderer->drawLine(m_position.x, m_position.y, target->m_position.x, target->m_position.y, 2.f);
	}
}

void GridSquare::setPosition(glm::vec2 position)
{
	m_position = position;
	//TODO update position of collider
}
