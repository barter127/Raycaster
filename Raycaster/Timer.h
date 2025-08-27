#pragma once

#ifndef _TIMER_H
#define _TIMER_H
#include "SDL.h"
#include <string>
#include "Vector2D.h"
#include "GameText.h"

class Timer
{
private:
	// the total number of seconds the timer has been running for.
	float m_time = 0.0f;

	// Should the timer tick up?
	bool m_isPaused = true;

	// Timer text displayed to the screen.
	GameText* m_timerUI = nullptr;

	// Read the second value from m_time and read it as hours, mins, and secs. Then convert to string.
	// Example Output: 23:11.21
	std::string TimerToString();

public:
	Timer(SDL_Renderer* renderer, std::string path, unsigned int fontSize);
	~Timer();

	void Update(float deltaTime);
	void Render(Vector2D position);

	// Resume timer countdown. Does nothing if timer is already counting.
	void Play();

	// Stops timer countdown. Does nothing if time has already stop.
	void Pause();

	// Set m_time to 0 or 00:00:00.
	void Reset();

	// Change the colour of the text.
	inline void ChangeColour(SDL_Color colour) { m_timerUI->SetColour(colour); }
};
#endif // !_TIMER_H
