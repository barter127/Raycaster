#pragma once

#ifndef _SCREEN_H
#define _SCREEN_H

#include "SDL.h"

class Screen
{
protected:
	SDL_Renderer* m_renderer;

public:
	Screen(SDL_Renderer* renderer);
	~Screen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};
#endif // _GAMESCREEN_H

