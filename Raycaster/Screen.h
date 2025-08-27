#pragma once

#ifndef _SCREEN_H
#define _SCREEN_H

// Sandbox Pattern
#include "SDL.h"

#include <iostream>

#include "Texture2D.h"
#include "AudioPlayer.h"
#include "GameText.h"
#include "Collisions.h"
#include "Physics.h"
#include "Timer.h"
#include "LevelRenderer.h"
#include "GameObject.h"
#include "LMap.h"
#include "WindowData.h"
#include "BenchMarkTimer.h"

#include "Vector2D.h"
#include "Vector3D.h"

class Screen
{
protected:
	SDL_Renderer* m_renderer;

public:
	Screen(SDL_Renderer* renderer);
	~Screen();

	virtual void Render() = 0;
	virtual void Update(float deltaTime, SDL_Event e) = 0;
};
#endif // _GAMESCREEN_H

