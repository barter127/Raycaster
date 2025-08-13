#pragma once

#ifndef _LEVEL_RENDERER_H
#define _LEVEL_RENDERER_H

#include "SDL.h"

class LevelTexture;
class Vector2D;

class LevelRenderer
{
public:
	LevelRenderer(SDL_Renderer* renderer);
	~LevelRenderer();

	void Render(Vector2D position);

private:
	/**
	 * \brief Render walls to backbuffer as described by the map layout.
	 * 
	 * Uses the indexes in the map data to determine the texture that will be rendererd. If texture is an invalid index wall is drawn as bright purple.
	 *
	 * Sets width and height member vars.
	 */
	void RenderWalls(Vector2D position);

	/**
	 * \brief Render ceiling and roof using the set ceiling and floor textures.
	 *
	 * 
	 *
	 * Sets width and height member vars.
	 */
	void RenderCeilRoof(Vector2D position);

	Uint32 GetPixelColour(LevelTexture* levelTexture, int pixelX, int pixelY);
	void CopyPixel(SDL_Surface* buffer, LevelTexture* levelTexture, Uint32 colour, int xPos, int yPos);

	SDL_Renderer* m_renderer;

	// Screen buffers.
	SDL_Surface* m_backBuffer = nullptr;
	SDL_Texture* m_frontBuffer = nullptr;

	// Level Variables
	float m_dirX = -1, m_dirY = 0; // Initial direction vector.
	float m_planeX = 0, m_planeY = 0.66; // The 2d raycaster version of camera plane.
	float m_moveSpeed = 2.0f;
	float m_rotSpeed = 1.0f;

	bool m_floorIsCheckered = true;

	// Level Textures.
	LevelTexture* m_wallTexture = nullptr; // Could expand to an array of surfaces.
	LevelTexture* m_floorTexture = nullptr; // Could expand to an array of surfaces.
	LevelTexture* m_ceilingTexture = nullptr; // Could expand to an array of surfaces.

	LevelTexture* m_levelTextureArray[6];

	int* m_wallPixelData = nullptr;
	int* m_floor1PixelData = nullptr;
	int* m_floor2PixelData = nullptr;
	int* m_ceilPixelData = nullptr;

	int floorTex1Multiplier = 2;
	int floorTex2Multiplier = 1;
};

#endif // !_LEVEL_RENDERER_H