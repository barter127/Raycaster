#pragma once

#ifndef _UI_WRAPPER_H
#define _UI_WRAPPER_H

#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "imgui.h"
#include "imfilebrowser.h"

#include "LMap.h"

#define MAX_FILE_NAME_LENGTH 25

class Texture2D;

class UIWrapper
{
public:
	UIWrapper(SDL_Window* window, SDL_Renderer* renderer, LMap* map);
	~UIWrapper();

	void Render();
	void Update(float deltaTime,  SDL_Event event);
	
	void AddTexture(std::string path);
	// void RemoveTexture(std::string path);

private:
	void HandleDocking();

	void NewHLVLPanel(char* fileName);
	void TileMap();

	// Rendering and IO.
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;

	static ImVec4 s_clearColour;
	ImGuiIO m_io;

	std::vector<Texture2D*> m_paletteTextures;
	int m_selectedTexture = 1;

	// Map data.
	std::string m_currentMapFile = "";
	char m_fileName[MAX_FILE_NAME_LENGTH] = { '\0' }; // Imgui uses char[] by default.

	LMap* m_map;
	int m_mapWidth = 0;
	int m_mapHeight = 0;

	FloorData m_floorData;
	FloorData m_ceilingData;

	// Determine what UI panel should be shown currently.
	bool m_saved = true;
	bool m_creatingNewFile = false;
	bool m_displayNewPanel = false;

	SDL_Texture* m_viewportTexture = nullptr;

	// File broswer.
	ImGuiFileBrowserFlags m_flags = ImGuiFileBrowserFlags_CloseOnEsc | 
		ImGuiFileBrowserFlags_ConfirmOnEnter | 
		ImGuiFileBrowserFlags_SkipItemsCausingError;

	ImGui::FileBrowser m_fileDialog = ImGui::FileBrowser(m_flags);
};

#endif