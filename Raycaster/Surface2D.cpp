#include "Surface2D.h"

#include <SDL_image.h>
#include <SDL_surface.h>

#include <iostream>

Surface2D::Surface2D(SDL_Renderer* renderer) : m_renderer(renderer) {}

Surface2D::~Surface2D()
{

}

bool Surface2D::LoadFromFile(std::string path)
{
	Free();

	// Load the image. 
	m_surface = IMG_Load(path.c_str());

	if (m_surface == nullptr)
	{
		std::cout << "Failed to load surface from path" << IMG_GetError() << std::endl;
		return false;
	}
	
	return true;
}

void Surface2D::Free()
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