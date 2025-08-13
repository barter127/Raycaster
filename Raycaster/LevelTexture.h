#pragma once

#ifndef _SURFACE_2D_H
#define _SURFACE_2D_H

#include "SDL.h"
#include <string>

class LevelTexture
{
protected:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Surface* m_surface = nullptr;

	int m_width = 0, m_height = 0;

public:
	LevelTexture(SDL_Renderer* renderer);
	~LevelTexture();

	/**
	 * \brief Read image data using the path parameter.
	 *
	 * Creates SDL_Sample and sets m_surface using image data.
	 * 
	 * Sets width and height member vars.
	 *
	 * \param File path of image.
	 * 
	 * \returns True if file loaded successfully.
	 */
	bool LoadFromFile(std::string path);

	/**
	* \brief Frees m_surface member
	* 
	* Sets height and width to 0.
	*/
	void Free();

	inline void* GetPixelData() { return m_surface->pixels; }

	inline SDL_Surface* GetSurface() { return m_surface; }

	// \returns Surfaces width.
	inline int GetWidth() { return m_width; }

	// \returns Surfaces height.
	inline int GetHeight() { return m_height; }
};

#endif // !_SURFACE_2D_H