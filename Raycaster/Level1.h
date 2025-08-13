#pragma once

#ifndef _LEVEL1_SCREEN_H
#define _LEVEL1_SCREEN_H

#include "SDL.h"
#include "Screen.h"

class Player;
class LevelRenderer;

class Level1 : Screen
{
public:
	Level1(SDL_Renderer* renderer);
	~Level1();

	void Update(float deltaTime, SDL_Event event);
	void Render();

private:
	LevelRenderer* m_levelRender;
	Player* m_player;
};

#endif