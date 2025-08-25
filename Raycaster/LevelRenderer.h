#pragma once

#ifndef _LEVEL_RENDERER_H
#define _LEVEL_RENDERER_H

#include <vector>
#include "SDL.h"
#include "LMap.h"

class LevelTexture;
class Vector2D;

class LevelRenderer
{
public:
	LevelRenderer(SDL_Renderer* renderer, LMap* map);
	~LevelRenderer();

	void Render(Vector2D position, Vector2D direction, Vector2D plane);

private:
	/**
	 * \brief Render walls to backbuffer as described by the map layout.
	 * 
	 * Uses the indexes in the map data to determine the texture that will be rendererd. If texture is an invalid index wall is drawn as bright purple.
	 *
	 * \param Position Vector of the camera.
	 * \param Direction Vector the camera is facing.
	 * \param Camera Plane Vector for the size of the vision cone.
	 */
	void RenderWalls(Vector2D position, Vector2D direction, Vector2D plane);

	/**
	 * \brief Render ceiling and roof using the set ceiling and floor textures.
	 *
	 * \param Position Vector of the camera.
	 * \param Direction Vector the camera is facing.
	 * \param Camera Plane Vector for the size of the vision cone.
	 */
	void RenderCeilRoof(Vector2D position, Vector2D direction, Vector2D plane);

	Uint32 GetPixelColour(LevelTexture* levelTexture, int pixelX, int pixelY);
	void CopyPixel(SDL_Surface* buffer, LevelTexture* levelTexture, Uint32 colour, int xPos, int yPos);

	SDL_Renderer* m_renderer;

	// Screen Buffers.
	SDL_Surface* m_backBuffer = nullptr;
	SDL_Texture* m_frontBuffer = nullptr;

	// Level Textures.
	LevelTexture* m_floorTexture = nullptr; // Could expand to an array of surfaces.
	LevelTexture* m_ceilingTexture = nullptr; // Could expand to an array of surfaces.

	std::vector<LevelTexture*> m_levelTextureArray;

	LMap* m_map;
};

#endif // !_LEVEL_RENDERER_H