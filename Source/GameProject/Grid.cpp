#include "stdafx.h"
#include "Grid.h"
#include "GameProjectApp.h"

Grid::Grid()
{
	size_t squaresWide = (GameProjectApp::max_corner - GameProjectApp::min_corner).x / square_size;
	size_t squaresHigh = (GameProjectApp::max_corner - GameProjectApp::min_corner).y / square_size;

	//TODO make grid of all open squares, with each adjacent (diagonal or orthogonal) connected to each other
	for (size_t i = 0; i < squaresWide; ++i) {
		std::vector<GridSquarePtr> column;
		for (size_t j = 0; j < squaresHigh; ++j) {
			glm::vec2 position((0.5f + i)*square_size, (0.5f + j) * square_size);
			column.push_back(std::make_shared<GridSquare>(position, open));
		}
		m_squares.push_back(std::vector<GridSquarePtr>());
	}
	//TODO calculate connections for all squares
}

GridSquarePtr Grid::getSquare(glm::vec2 position)
{
	//TODO based on position, return 
	return GridSquarePtr();
}

void Grid::calculateEdges()
{
	//TODO for all, connect to right, for all but last, connect above and up-right
	//for last column, connect above for all but last
	//Rule: if neither impassable, cost is square_size * average of square move cost (* 1.4 if diagonal)
	for (size_t i = 0; i < m_squares.size(); ++i) {
		bool lastColumn = i + 1 == m_squares.size();
		for (size_t j = 0; j < m_squares[i].size(); ++j) {
			bool lastSquare = j + 1 == m_squares[i].size();
			if (!lastSquare) {
				connectSquares(m_squares[i][j], m_squares[i][j+1]);
			}
			if (!lastColumn) {
				connectSquares(m_squares[i][j], m_squares[i + 1][j]);
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
	}
}
