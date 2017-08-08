#include "stdafx.h"
#include "GameProjectApp.h"
//TODO update to new bootstrap version
int main() {
	
	auto app = new GameProjectApp();

	app->run("Code Design and Data Structures Project - Leonard Andrew Spencer", GameProjectApp::max_corner.x, GameProjectApp::max_corner.y, false);
	
	delete app;

	return 0;
}