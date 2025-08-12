#include "Screen.h"

Screen::Screen(SDL_Renderer* renderer) 
	: m_renderer(renderer) {}

Screen::~Screen()
{
	m_renderer = nullptr;
}

void Screen::Render(){}

void Screen::Update(float deltaTime, SDL_Event e){}