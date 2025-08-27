#include "GameText.h"
#include <iostream>

bool GameText::m_ttfHasInit = false;

GameText::GameText(SDL_Renderer* renderer, std::string path, unsigned int fontSize)
{
	if (!InitTTF())
	{
		std::cerr << "[!] Error. Couldn't init TTF. " << TTF_GetError() << std::endl;
		m_encounteredError = true;
		return;
	}

	this->m_renderer = renderer;

	this->LoadFont(path, fontSize);
}

GameText::~GameText()
{
	Destroy();
}

bool GameText::InitTTF()
{
	// TTF has already been initalised.
	if (m_ttfHasInit) return true;

	// Initalise TTF.
	return (TTF_Init() >= 0);
}

bool GameText::LoadFont(const std::string& path, unsigned int fontSize)
{
	// Load font from path.
	this->m_font = TTF_OpenFont(path.c_str(), fontSize);

	// If font failed loading return an error.
	if (!this->m_font)
	{
		std::cerr << "[!] Error. Couldn't load font path " << path << " " << TTF_GetError() << std::endl;
		m_encounteredError = true;
		return false;
	}

	return true;
}

void GameText::Destroy()
{
	TTF_CloseFont(m_font);
}

void GameText::RenderAt(const std::string& text, int x, int y, bool centered)
{
	// Kill if errors are present.
	if (m_encounteredError) return;

	if (m_texture != nullptr) SDL_DestroyTexture(m_texture);

	int w, h;
	TTF_SizeText(m_font, text.c_str(), &w, &h);

	// Load surface and texture.
	SDL_Surface* surface = TTF_RenderText_Blended(m_font, text.c_str(), m_colour);
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);

	// Copy texture to current renderer.

 	SDL_Rect renderingRect{ x, y, w, h };

	// If text centering is requested.
	if (centered)
	{
		// Alter x and y positions so the specified x an y pivot is in the centre.
		renderingRect.x -= (w/2);
		renderingRect.y -= (h/2);
	}

	SDL_RenderCopy(m_renderer, m_texture, NULL, &renderingRect);
}