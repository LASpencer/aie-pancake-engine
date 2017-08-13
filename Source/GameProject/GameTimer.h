#pragma once
class GameTimer
{
public:
	GameTimer(bool running = false);
	~GameTimer();

	float getTime();

	// Timer starts running
	void start();

	// Timer stops running
	void pause();

	// Resets time to 0
	void reset();

	// Increases time if running
	void update(float deltaTime);

protected:
	bool m_running;
	float m_time;
};

