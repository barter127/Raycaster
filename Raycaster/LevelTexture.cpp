#include "LevelTexture.h"

#include <SDL_image.h>
#include <SDL_surface.h>

#include <iostream>

LevelTexture::LevelTexture(SDL_Renderer* renderer) : m_renderer(renderer) {}

LevelTexture::~LevelTexture()
{

}

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