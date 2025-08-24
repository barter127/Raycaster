#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "ScreenManager.h"
#include "WindowData.h"

bool InitSDL();
bool CloseSDL();

bool Update();
void Render();

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;

Uint32 g_oldTime;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;
Uint32 g_nextGameTick;

ScreenManager* g_screenManager = nullptr;
SDL_Event g_event;

int main(int argc, char* argv[])
{
	bool quit = false;

	if (InitSDL())
	{
		g_screenManager = new ScreenManager(g_window, g_renderer, LEVEL1_SCREEN);

		// Set old time.
		g_oldTime = SDL_GetTicks();

		std::cout << "[Main] !!! Update & Render Start !!!" << std::endl;

		while (!quit)
		{
			Render();
			quit = Update();

			// FPS Locking.
			g_nextGameTick += FRAME_DELAY;
			int frameTime = g_nextGameTick - SDL_GetTicks();

			if (frameTime <= 0)
			{
				std::cout << "We are <60 FPS." << std::endl;
			}
		}
	}

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
		std::cout << "[InitSDL] SDL did not initalise. Error: " << SDL_GetError();

		return false;
	}
	else
	{
		// Create Window.
		g_window = SDL_CreateWindow("Raycaster",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			g_windowData.width,
			g_windowData.height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);


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

		g_windowData.frontBuffer = SDL_CreateTexture(g_renderer, 
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 
			g_windowData.width, 
			g_windowData.height);

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

bool Update()
{
	Uint32 newTime = SDL_GetTicks();

	// Get the current event from the event queue.
	SDL_PollEvent(&g_event);

	// Check if event is SDL_QUIT.
	// If it is exit program.
	switch (g_event.type)
	{
	case SDL_QUIT:
		return true;
		break;

	case SDL_WINDOWEVENT:
		if (g_event.window.event == SDL_WINDOWEVENT_RESIZED) 
		{
			g_windowData.width = g_event.window.data1;
			g_windowData.height = g_event.window.data2;
			SDL_SetWindowSize(g_window, g_windowData.width, g_windowData.height);
		}
		break;
	}

	// Call Update for current scene.
	float deltaTime = (float)(newTime - g_oldTime) / 1000.0f;
	g_screenManager->Update(deltaTime, g_event);
	g_oldTime = newTime;

	return false;
}

#include "imgui.h"

void Render()
{
	// Clear buffer.
	SDL_SetRenderDrawColor(g_renderer, 221, 160, 221, 255);
	SDL_RenderClear(g_renderer);

	g_screenManager->Render();

	SDL_RenderPresent(g_renderer);

	// No RenderPresent as viewport rendering is handled in UIWrapper.
}