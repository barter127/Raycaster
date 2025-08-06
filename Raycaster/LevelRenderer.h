#pragma once

#ifndef _LEVEL_RENDERER_H
#define _LEVEL_RENDERER_H

#include "SDL.h"

class LevelTexture;

class LevelRenderer
{
public:
	LevelRenderer(SDL_Renderer* renderer);
	~LevelRenderer();

	void Render();

private:
	/**
	 * \brief Render walls to backbuffer as described by the map layout.
	 * 
	 * Uses the indexes in the map data to determine the texture that will be rendererd. If texture is an invalid index wall is drawn as bright purple.
	 *
	 * Sets width and height member vars.
	 */
	void RenderWalls();

	/**
	 * \brief Render ceiling and roof using the set ceiling and floor textures.
	 *
	 * 
	 *
	 * Sets width and height member vars.
	 */
	void RenderCeilRoof();

	SDL_Renderer* m_renderer;

	// Screen buffers.
	SDL_Surface* m_backBuffer = nullptr;
	SDL_Texture* m_frontBuffer = nullptr;

	// Level Variables
	float m_posX = 22, m_posY = 12;  // X and y start position.
	float m_dirX = -1, m_dirY = 0; // Initial direction vector.
	float m_planeX = 0, m_planeY = 0.66; // The 2d raycaster version of camera plane.
	float m_moveSpeed = 2.0f;
	float m_rotSpeed = 1.0f;

	// Level Textures.
	LevelTexture* wallTexture = nullptr; // Could expand to an array of surfaces.
	LevelTexture* floorTexture = nullptr; // Could expand to an array of surfaces.
	LevelTexture* ceilingTexture = nullptr; // Could expand to an array of surfaces.

	int* m_wallPixelData = nullptr;
	int* m_floor1PixelData = nullptr;
	int* m_floor2PixelData = nullptr;
	int* m_ceilPixelData = nullptr;


	int floorTex1Multiplier = 2;
	int floorTex2Multiplier = 1;
};

#endif // !_LEVEL_RENDERER_H