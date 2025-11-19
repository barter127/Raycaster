#include "LevelTexture.h"

#include <SDL_image.h>
#include <SDL_surface.h>

#include <iostream>

LevelTexture::LevelTexture(SDL_Renderer* renderer) : m_renderer(renderer) {}

LevelTexture::~LevelTexture() {}

bool LevelTexture::LoadFromFile(std::string path)
{
	Free();

	// Load the image. 
	m_surface = IMG_Load(path.c_str());

	if (m_surface == nullptr)
	{
		std::cout << "Failed to load surface from path" << IMG_GetError() << std::endl;
		return false;
	}
	
	m_width = m_surface->w;
	m_height = m_surface->h;

	//CacheOptimiseLayout();

	return true;
}

void LevelTexture::Free()
{
	// Clear size vars.
	m_width = 0;
	m_height = 0;

	// Check texture exists before removal
	if (m_surface != nullptr)
	{
		SDL_FreeSurface(m_surface);
	}
}

void LevelTexture::CacheOptimiseLayout()
{
	char* pixels = (char*)m_surface->pixels;
	int pitch = m_surface->pitch;
	int bpp = m_surface->format->BytesPerPixel;

	// Swap texture X/Y since they'll be used as vertical stripes.
	for (size_t x = 0; x < m_width; x++)
		for (size_t y = 0; y < x; y++)
			for (int i = 0; i < bpp; ++i)
				std::swap(pixels[y * pitch + x * bpp], pixels[x * pitch + y * bpp]);
}