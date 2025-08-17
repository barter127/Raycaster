#pragma once

#ifndef _UI_WRAPPER_H
#define _UI_WRAPPER_H

#include "SDL.h"

#include "imgui.h"
#include "LMap.h"

class UIWrapper
{
public:
	UIWrapper(SDL_Window* window, SDL_Renderer* renderer);
	~UIWrapper();

	void Render();
	void Update(float deltaTime,  SDL_Event event);

	void LinkMapData(LMap* map);

private:
	bool m_initialised = false;

	SDL_Renderer* m_renderer;
	static ImVec4 s_clearColour;
	ImGuiIO m_io;

	LMap* m_map;
};

#endif