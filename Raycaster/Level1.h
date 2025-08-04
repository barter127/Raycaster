#pragma once

#ifndef _LEVEL1_SCREEN_H
#define _LEVEL1_SCREEN_H

#include "SDL.h"
#include "Screen.h"

class Level1 : Screen
{
public:
	Level1(SDL_Renderer* renderer);
	~Level1();

	void Update(float deltaTime, SDL_Event event);
	void Render();
};

#endif