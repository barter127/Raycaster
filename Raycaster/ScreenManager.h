#pragma once

#ifndef _SCREEN_MANAGER_H
#define _SCREEN_MANAGER_H

#include "SDL.h"

class Screen;

enum SCREEN
{
	NO_SCREEN,
	LEVEL1_SCREEN
};

class ScreenManager
{
private:
	static SDL_Renderer* m_renderer;
	static SDL_Window* m_window;
	static Screen* m_currentScreen;

	static SCREEN m_currentScreenType;

	// Delete the current screen.
	static void DeleteCurrentScreen();

	static ScreenManager* m_instance;

public:
	ScreenManager(SDL_Window* window, SDL_Renderer* renderer, SCREEN startScreen);
	~ScreenManager();

	ScreenManager* Instance();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	// Change the current screen being rendered and updated to the corresponding newScreen.
	// If useTransitionScreen is true, fade screen to black during transition.
	static void ChangeScreen(SCREEN newScreen);
};
#endif

