// Testing.cpp : Defines the entry point for the console application.
//
#include "stdafx_test.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "TestApp.h"

int main(int argc, char* const argv[]) {
	TestApp* app = new TestApp();
	app->run("app", 200, 200, false);
	delete app;
	int result = Catch::Session().run(argc, argv);
	system("pause");
	return result;
}


