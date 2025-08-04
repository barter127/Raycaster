#pragma once

#ifndef _SURFACE_2D_H
#define _SURFACE_2D_H

#include "SDL.h"
#include <string>

class Surface2D
{
protected:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Surface* m_surface = nullptr;

	int m_width = 0, m_height = 0;

public:
	Surface2D(SDL_Renderer* renderer);
	~Surface2D();

	// Read image data using the path parameter.
	// Creates SDL_Sample and sets m_sample using image data.
	// Sets width and height member vars.
	bool LoadFromFile(std::string path);

	// Free up texture memory.
	// Set width and height to 0.
	void Free();

	inline void* GetPixelData() { return m_surface->pixels; }

	// Return textures width.
	inline int GetWidth() { return m_width; }

	// Returns textures height.
	inline int GetHeight() { return m_height; }
};

#endif // !_SURFACE_2D_H