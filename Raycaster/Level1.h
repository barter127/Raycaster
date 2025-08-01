#pragma once

#ifndef _Level1_Screen_H
#define _Level1_Screen_H

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