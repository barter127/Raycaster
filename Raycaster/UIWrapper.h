#pragma once

#ifndef _UI_WRAPPER_H
#define _UI_WRAPPER_H

#include "SDL.h"

#include "imgui.h"

class UIWrapper
{
public:
	UIWrapper(SDL_Window* window, SDL_Renderer* renderer);
	~UIWrapper();

	void Render();
	void Update(float deltaTime,  SDL_Event event);

private:
	bool m_initialised = false;

	SDL_Renderer* m_renderer;
	static ImVec4 s_clearColour;
	ImGuiIO m_io;
};

#endif