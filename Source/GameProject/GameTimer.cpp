#include "stdafx.h"
#include "GameTimer.h"


GameTimer::GameTimer(bool running) : m_running(running), m_time(0.f)
{
}

GameTimer::~GameTimer()
{
}

void GameTimer::start()
{
	m_running = true;
}

void GameTimer::pause()
{
	m_running = false;
}

void GameTimer::reset()
{
	m_time = 0.f;
}

void GameTimer::update(float deltaTime)
{
	if (m_running) {
		m_time += deltaTime;
	}
}

float GameTimer::getTime()
{
	return m_time;
}
