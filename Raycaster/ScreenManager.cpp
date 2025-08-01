#include "ScreenManager.h"
#include "Screen.h"

#include "Level1.h"

#include <iostream>

SDL_Renderer* ScreenManager::m_renderer = nullptr;
Screen* ScreenManager::m_currentScreen = nullptr;
SCREEN ScreenManager::m_currentScreenType = NO_SCREEN;

ScreenManager* ScreenManager::m_instance = nullptr;

void ScreenManager::DeleteCurrentScreen()
{
	// Delete the corresponding screen.
	switch (m_currentScreenType)
	{
		case LEVEL1_SCREEN:
			delete (Level1*)m_currentScreen;
			break;
	}
}

ScreenManager::ScreenManager(SDL_Renderer* renderer, SCREEN startScreen)
{
	m_renderer = renderer;
	m_instance = this;
	m_currentScreen = nullptr;

	ChangeScreen(LEVEL1_SCREEN);
}

ScreenManager::~ScreenManager()
{
	m_renderer = nullptr;
	m_currentScreen = nullptr;
}

ScreenManager* ScreenManager::Instance()
{
	if (m_instance != nullptr)
	{
		return m_instance;
	}

	return nullptr;
}


void ScreenManager::Render()
{
	if (m_currentScreen != nullptr)
	{
		m_currentScreen->Render();
	}
}

void ScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_currentScreen->Update(deltaTime, e);
}

void ScreenManager::ChangeScreen(SCREEN newScreen)
{	
	// Ensure current screen is valid.
	if (m_currentScreen != nullptr)
	{
		DeleteCurrentScreen();
	}

	m_currentScreenType = newScreen;

	Level1* tempLevel1;

	// Switch screen to parameter equivalent screen.
	switch (newScreen)
	{
		case LEVEL1_SCREEN:
			tempLevel1 = new Level1(m_renderer);
			m_currentScreen = (Screen*)tempLevel1;
			tempLevel1 = nullptr;

			std::cout << "[ScreenManager] Switching to Level 1." << std::endl;
			break;

		default:
			std::cout << "[GameScreenManager] Screen requested could not be found.";
			break;
	}
}