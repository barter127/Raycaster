#include "Timer.h"
#include "GameText.h"
#include "Commons.h"

Timer::Timer(SDL_Renderer* renderer, std::string path, unsigned int fontSize)
{
	// Reset timer value.
	Reset();

	// Initalise m_timerUI with default colour black
	m_timerUI = new GameText(renderer, path, fontSize);
	m_timerUI->SetColour({ 0, 0, 0 });
}

Timer::~Timer()
{
	DELETE_PTR(m_timerUI);
}

void Timer::Update(float deltaTime)
{
	// Only tick timer if it isn't paused.
	if (!m_isPaused)
	{
		m_time += deltaTime;

		// Clamp timer at 99:59:999 to prevent overflow.
		if (m_time >= 5999.999f)
		{
			m_isPaused = true;
			m_time = 5999.999f;
		}
	}
}

void Timer::Render(Vector2D position)
{
	// Convert the current time value to string.
	std::string timerDisplay = TimerToString();

	// Render timer value to screen.
	m_timerUI->RenderAt(timerDisplay, position.x, position.y);
}

void Timer::Play()
{
	if (m_isPaused)
		m_isPaused = false;
}

void Timer::Pause()
{
	if (!m_isPaused)
		m_isPaused = true;
}

void Timer::Reset()
{
	m_time = 0.0f;
}

std::string Timer::TimerToString()
{
	// Convert m_time (stored as seconds) to minutes and seconds.
	unsigned short mins = m_time / 60.0f;
	unsigned short secs = fmod(m_time, 60);

	// Convert minutes and seconds values to strings so they can be rendered.
	std::string minsStr = std::to_string(mins);
	std::string secsStr = std::to_string(secs);

	// Create temporary str so the number of digits (str length) can be read.
	std::string tempTimeStr = std::to_string(m_time);

	// Read m_time to 3 DP. Floats have precision of 6 DP.
	std::string msStr = tempTimeStr.substr(tempTimeStr.length()-6, 3); 

	// If value stored is less than two digits add a "0" to the start.
	// Not nessecary but improves game feel as timers length doesn't change.
	if (mins < 10)
	{
		minsStr.insert(0, "0");
	}
	if (secs < 10)
	{
		secsStr.insert(0, "0");
	}

	// Concatenate and return timer with mins:secs.millisecs format.
	return minsStr + ":" + secsStr + "." + msStr;
}