#include "stdafx.h"
#include "Grid.h"
#include "GameProjectApp.h"

Grid::Grid()
{
	size_t squaresWide = (GameProjectApp::max_corner - GameProjectApp::min_corner).x / square_size;
	size_t squaresHigh = (GameProjectApp::max_corner - GameProjectApp::min_corner).y / square_size;

	//TODO make grid of all open squares, with each adjacent (diagonal or orthogonal) connected to each other
}

GridSquarePtr Grid::getSquare(glm::vec2 position)
{
	//TODO based on position, return 
	return GridSquarePtr();
}