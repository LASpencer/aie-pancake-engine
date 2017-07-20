#pragma once
#include "stdafx_test.h"
#include "Application.h"
#include "Renderer2D.h"

class TestApp :
	public aie::Application
{
public:
	TestApp();
	~TestApp();

	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();

protected:
	aie::Renderer2D* m_2dRenderer;
	int m_frames;
};

