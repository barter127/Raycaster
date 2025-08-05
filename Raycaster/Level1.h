#pragma once

#ifndef _LEVEL1_SCREEN_H
#define _LEVEL1_SCREEN_H

#include "SDL.h"
#include "Screen.h"

class Surface2D;

class Level1 : Screen
{
public:
	Level1(SDL_Renderer* renderer);
	~Level1();

	void Update(float deltaTime, SDL_Event event);
	void Render();

private:

	// RENDERING VARS!!!

	SDL_Surface* screenBuffer = nullptr;
	SDL_Texture* screenTexture = nullptr;

	Surface2D* wallTexture = nullptr; // Could expand to an array of surfaces.
	Surface2D* floorTexture = nullptr; // Could expand to an array of surfaces.
	Surface2D* ceilingTexture = nullptr; // Could expand to an array of surfaces.

	float posX = 22, posY = 12;  // X and y start position.
	float dirX = -1, dirY = 0; // Initial direction vector.
	float planeX = 0, planeY = 0.66; // The 2d raycaster version of camera plane.
	float moveSpeed = 2.0f;
	float rotSpeed = 1.0f;
};

#endif