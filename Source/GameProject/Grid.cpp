#include "stdafx.h"
#include "Grid.h"
#include "GameProjectApp.h"

const float Grid::square_size = 40.f;

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

GridSquarePtr Grid::getSquare(glm::vec2 position)
{
	size_t x = std::min((size_t)(std::max(0.f, position.x - GameProjectApp::min_corner.x) * (1.f / square_size)), m_squares.size());
	size_t y = std::min((size_t)(std::max(0.f, position.y - GameProjectApp::min_corner.y) * (1.f / square_size)), m_squares[x].size());
	return m_squares[x][y];
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
}

GridSquare::GridSquare() : m_position(glm::vec2(0)), m_type(open), gScore(0), fScore(0), hScore(0), m_parent(nullptr)
{
}

GridSquare::GridSquare(glm::vec2 position, TileType type) : m_position(position), m_type(type), gScore(0), fScore(0), hScore(0), m_parent(nullptr)
{
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

void GridSquare::draw(aie::Renderer2D * renderer)
{
	//TODO based on type, draw sprite
}

void GridSquare::drawNodes(aie::Renderer2D * renderer)
{
	renderer->drawCircle(m_position.x, m_position.y, Grid::square_size * 0.2f);
	for (GridEdge edge : m_connections) {
		GridSquarePtr target(edge.target);
		renderer->drawLine(m_position.x, m_position.y, target->m_position.x, target->m_position.y, 2.f);
	}
}
