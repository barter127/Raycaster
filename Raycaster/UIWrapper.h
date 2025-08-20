#pragma once

#ifndef _UI_WRAPPER_H
#define _UI_WRAPPER_H

#include <string>
#include "SDL.h"

#include "imgui.h"
#include "imfilebrowser.h"

#include "LMap.h"

#define MAX_FILE_NAME_LENGTH 25

class UIWrapper
{
public:
	UIWrapper(SDL_Window* window, SDL_Renderer* renderer, LMap* map);
	~UIWrapper();

	void Render();
	void Update(float deltaTime,  SDL_Event event);

private:
	void NewHLVLPanel(char* fileName);

	// Rendering and IO.
	SDL_Renderer* m_renderer;
	static ImVec4 s_clearColour;
	ImGuiIO m_io;

	// Map data.
	std::string m_currentMapFile = "";
	char m_fileName[MAX_FILE_NAME_LENGTH] = { '\0' }; // Imgui uses char[] by default.

	LMap* m_map;
	int m_mapWidth = 0;
	int m_mapHeight = 0;

	// Determine what UI panel should be shown currently.
	bool m_saved = false;
	bool m_creatingNewFile = false;
	bool m_displayNewPanel = false;


	// File broswer.
	ImGuiFileBrowserFlags flags = ImGuiFileBrowserFlags_CloseOnEsc | 
		ImGuiFileBrowserFlags_ConfirmOnEnter | 
		ImGuiFileBrowserFlags_SkipItemsCausingError;

	ImGui::FileBrowser m_fileDialog = ImGui::FileBrowser(flags);

};

#endif