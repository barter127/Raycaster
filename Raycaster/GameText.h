#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

#ifndef _GAME_TEXT_H
#define _GAME_TEXT_H
class GameText
{
private:
	// Has TTF_Init() been called during the programs lifespan?
	static bool m_ttfHasInit;

	// Set to true if an error occured while read a font file.
	// Stops rendering from taking place if true.
	bool m_encounteredError = false;

	// Before any SDL_ttf function can be called TTF_Init() needs to be called.
	// Check if TTF_Init() has been called during the function runtime.
	// If not call it.
	bool InitTTF();
protected:
	SDL_Renderer* m_renderer = nullptr;

	SDL_Texture* m_texture = nullptr;
	TTF_Font* m_font = nullptr;
	SDL_Color m_colour = { 0,0,0,0 };

public:
	GameText(SDL_Renderer* renderer, std::string path, unsigned int fontSize);
	~GameText();

	// Load a ttf from path parameter. Set fonts size to fontSize parameter.
	// If ttf load fails, set m_encounteredError to true.
	bool LoadFont(const std::string& path, unsigned int fontSize);

	// Destroy the TTF_Font to free memory.
	void Destroy();

	// Render text parameter at (x, y) position on screen.
	void RenderAt(const std::string& text, int x, int y, bool centered = false);

	// Sets text colour to parameter.
	inline void SetColour(SDL_Color colour) { this->m_colour = colour; }
};
#endif

