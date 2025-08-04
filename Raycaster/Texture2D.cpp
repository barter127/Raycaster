#include "Texture2D.h"

#include <iostream>
#include <string>

#include <SDL_image.h>

Texture2D::Texture2D(SDL_Renderer* renderer) : m_renderer(renderer), m_texture(nullptr) {}

Texture2D::~Texture2D()
{
	// Free up memory.
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path)
{
	Free();

	// Load the image. 
	SDL_Surface* imgSurface = IMG_Load(path.c_str());

	// Create the texture from pixels on the surface.
	m_texture = SDL_CreateTextureFromSurface(m_renderer, imgSurface);
	if (imgSurface != nullptr)
	{
		SDL_SetColorKey(imgSurface, SDL_TRUE, SDL_MapRGB(imgSurface->format, 0, 0XFF, 0XFF));

		m_width = imgSurface->w;
		m_height = imgSurface->h;
	}
	else
	{
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError() << std::endl;
	}

	if (m_texture == nullptr)
	{
		std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl;
	}

	// Remove the loaded surface.
	SDL_FreeSurface(imgSurface);

	return m_texture != nullptr;
}

// Free up memory.
void Texture2D::Free()
{
	// Clear size vars.
	m_width = 0;
	m_height = 0;

	// Check texture exists before removal
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

#pragma region Render Overloads

//void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
//{
//	// Set render location and size.
//	SDL_Rect renderLocation{ newPosition.x, newPosition.y, m_width, m_height };
//
//	// Render to screen.
//	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, angle, nullptr, flip);
//}
//
//void Texture2D::Render(Vector2D newPosition, Vector2D imageSize, SDL_RendererFlip flip, double angle)
//{
//	// Set render location and size.
//	SDL_Rect renderLocation{ newPosition.x, newPosition.y, imageSize.x, imageSize.y };
//
//	// Render to screen.
//	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, angle, nullptr, flip);
//}

#pragma endregion
