#pragma once

#ifndef _UI_WRAPPER_H
#define _UI_WRAPPER_H

#define MAX_FILE_NAME_LENGTH 25

#include <string>

#include "SDL.h"

#include "LMap.h"

#include "imgui.h"
#include "imfilebrowser.h"

class UIWrapper
{
public:
	UIWrapper(SDL_Window* window, SDL_Renderer* renderer, LMap* map);
	~UIWrapper();

	void Render();
	void Update(float deltaTime,  SDL_Event event);

private:
	void NewHLVLPanel(char* fileName);

	std::string m_inputLabel = "##label";
	char m_fileName[25]; // Imgui uses char[] by default.
	bool m_displayNewPanel = false;

	ImGuiFileBrowserFlags_ flags = ImGuiFileBrowserFlags_CreateNewDir;
	ImGui::FileBrowser m_fileDialog = ImGui::FileBrowser(flags);

	bool m_initialised = false;

	SDL_Renderer* m_renderer;
	static ImVec4 s_clearColour;
	ImGuiIO m_io;

	LMap* m_map;
};

#endif