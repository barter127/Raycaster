#pragma once

#ifndef _TEXTURE_2D_H
#define _TEXTURE_2D_H

#include "SDL.h"
#include <string>

class Texture2D
{
protected:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;

	int m_width = 0;
	int m_height = 0;

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	// Read image data using the path parameter.
	// Creates SDL_Texture and sets m_texture using image data.
	// Sets width and height.
	bool LoadFromFile(std::string path);

	// Free up texture memory.
	// Set width and height to 0.
	void Free();

	//// Render texture at specified position, with flip, and rotated by angle.
	//void Render(Vector2D newPosition, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0f);

	//// Render texture at specified position, scaled by imageSize, with flip, and rotated by angle.
	//void Render(Vector2D newPosition, Vector2D imageSize, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0f);

	// ===== Getters =====

	// Return textures width.
	inline int GetWidth() { return m_width; }

	// Returns textures height.
	inline int GetHeight() { return m_height; }

	// Return textures SDL_Texture pointer.
	inline SDL_Texture* GetTexture() { return m_texture; }

	// Return textures SDL_Renderer pointer.
	inline SDL_Renderer* GetRenderer() { return m_renderer; }
};
#endif // _TEXTURE2D_H