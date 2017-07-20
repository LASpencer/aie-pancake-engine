#include "stdafx.h"
#include "GameProjectApp.h"

int main() {
	
	auto app = new GameProjectApp();

	app->run("Code Design and Data Structures Project - Leonard Andrew Spencer", 1280, 720, false);
	
	delete app;

	return 0;
}