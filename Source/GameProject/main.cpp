#include "stdafx.h"
#include "GameProjectApp.h"
//TODO update to new bootstrap version
int main() {
	
	std::srand(time(0));

	auto app = new GameProjectApp();

	app->run("Artificial Intelligence Project - Leonard Andrew Spencer", GameProjectApp::max_corner.x, GameProjectApp::max_corner.y, false);
	
	delete app;

	return 0;
}