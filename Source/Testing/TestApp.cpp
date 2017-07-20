#include "stdafx_test.h"
#include "TestApp.h"


TestApp::TestApp()
{
}


TestApp::~TestApp()
{
}

bool TestApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	m_frames = 0;
	return true;
}

void TestApp::shutdown()
{
	delete m_2dRenderer;
}

void TestApp::update(float deltaTime)
{
	quit();
}

void TestApp::draw()
{
	clearScreen();
}
