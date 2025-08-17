#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "ScreenManager.h"
#include "WindowConstants.h"
#include "UIWrapper.h"

bool InitSDL();
bool CloseSDL();

bool Update();
void Render();

SDL_Window* g_window = nullptr;

SDL_Renderer* g_renderer = nullptr;

Uint32 g_oldTime;
const int FPS = 60;
const int SKIP_TICKS = 1000 / FPS;
Uint32 g_nextGameTick;

ScreenManager* g_screenManager = nullptr;
UIWrapper* g_ui;

int main(int argc, char* argv[])
{
	bool quit = false;

	if (InitSDL())
	{
		g_screenManager = new ScreenManager(g_renderer, LEVEL1_SCREEN);

		// Set old time.
		g_oldTime = SDL_GetTicks();

		std::cout << "[Main] !!! Update & Render Start !!!" << std::endl;

		g_ui = new UIWrapper(g_window, g_renderer);

		while (!quit)
		{
			Render();
			quit = Update();

			// FPS Locking.
			g_nextGameTick += SKIP_TICKS;
			int frameTime = g_nextGameTick + g_oldTime - SDL_GetTicks();

			if (frameTime <= 0)
			{
				std::cout << "We are <60 FPS." << std::endl;
			}
		}
	}

	delete g_ui;
	g_ui = nullptr;

	CloseSDL();

	// Release GameScreenManager
	delete g_screenManager;
	g_screenManager = nullptr;

	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "SDL did not initalise. Error: " << SDL_GetError();

		return false;
	}
	else
	{
		// Create Window.
		g_window = SDL_CreateWindow("Raycaster",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);


		// Check window was created.
		if (g_window == nullptr)
		{
			// Window failed.
			std::cout << "[InitSDL] Window wasn't created. Error: " << SDL_GetError() << std::endl;

			return false;
		}
		std::cout << "[InitSDL] Created window." << std::endl;

		g_renderer = SDL_CreateRenderer(g_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (g_renderer != nullptr)
		{
			// Initialise PNG loading.
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				std::cout << "[InitSDL] SDL_Image could not initalise. Error: " << IMG_GetError() << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "[InitSDL] Renderer could not initialise. Error: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}
}

bool CloseSDL()
{
	std::cout << "[CloseSDL] Quitting program." << std::endl;

	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	// Release renderer.
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	SDL_Quit();
	std::cout << "[CloseSDL] Program succesfully closed." << std::endl;

	return true;
}

	SDL_Event event;
bool Update()
{
	Uint32 newTime = SDL_GetTicks();

	// Get the current event from the event queue.
	SDL_PollEvent(&event);

	// Check if event is SDL_QUIT.
	// If it is exit program.
	switch (event.type)
	{
	case SDL_QUIT:
		return true;
		break;
	}

	// Call Update for current scene
	float deltaTime = (float)(newTime - g_oldTime) / 1000.0f;
	g_screenManager->Update(deltaTime, event);
	g_ui->Update(deltaTime, event);

	g_oldTime = newTime;

	return false;
}

void Render()
{
	// Clear buffer.
	SDL_SetRenderDrawColor(g_renderer, 221, 160, 221, 255);
	SDL_RenderClear(g_renderer);

	g_screenManager->Render();
	g_ui->Render();

	// Swap Buffer.
	SDL_RenderPresent(g_renderer);
}