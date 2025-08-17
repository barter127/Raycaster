#include "UIWrapper.h"

#include <iostream>

// ImGUI dependencies
using namespace ImGui;
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imfilebrowser.h"

#include "LMap.h"


ImVec4 UIWrapper::s_clearColour = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

UIWrapper::UIWrapper(SDL_Window* window, SDL_Renderer* renderer) : m_renderer(renderer)
{
	IMGUI_CHECKVERSION();

	// Get display DPI scaling
	float main_scale = 1.0f;
	int display_index = 0;
	float ddpi = 0.0f, hdpi = 0.0f, vdpi = 0.0f;
	if (SDL_GetDisplayDPI(display_index, &ddpi, &hdpi, &vdpi) == 0)
	{
		main_scale = ddpi / 96.0f; // 96 DPI is the default scaling baseline
	}

	CreateContext();
	m_io = GetIO();
	m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	m_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	m_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Viewports

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup scaling
	ImGuiStyle& style = GetStyle();
	style.ScaleAllSizes(main_scale);
	style.FontScaleDpi = main_scale;

	// Initialize ImGui for SDL and SDL_Renderer
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	m_initialised = true;
}

UIWrapper::~UIWrapper()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	DestroyContext();
}

void UIWrapper::Update(float deltaTime, SDL_Event event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}

#define MAX_FILE_NAME_LENGTH 25
char inputLabel[] = "##label";
char fileName[MAX_FILE_NAME_LENGTH];
bool displayNewPanel = false;

void NewHLVLPanel()
{
	Begin("New HLVL");

	InputText(inputLabel, fileName, MAX_FILE_NAME_LENGTH);
	SameLine();
	Text(".hlvl");

	if (Button("Create")) 
	{
		//LevelFileSystem::CreateFile(fileName); 

		std::cout << "[LevelFileSystem] Created new hlvl. " << fileName << ".hlvl";
		displayNewPanel = false;
	}

	End();
}

		FileBrowser fileDialog;

void UIWrapper::Render()
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	NewFrame();

	Begin("Editor");

	if (Button("New")) { displayNewPanel = !displayNewPanel; }
	if (displayNewPanel) { NewHLVLPanel(); }

	SameLine();
	if (Button("Save")) 
	{
		//Write current map data to file.
	}

	SameLine();
	if (Button("Load")) 
	{
		// Bring up prompt to select file.

		fileDialog.Open();
	}

	fileDialog.Display();

	if (fileDialog.HasSelected())
	{
		if (m_map != nullptr)
		{
			LMap::ReadFile(*m_map, fileDialog.GetSelected().string());
		}
		else
		{
			std::cerr << "[UIWrapper] Attempted to write to nullptr map data" << std::endl;
		}

		std::cout << "[UIWrapper] Selected filename " << fileDialog.GetSelected().string() << std::endl;
		fileDialog.ClearSelected();
	}

	End();

	ImGui::Render();
	SDL_RenderSetScale(m_renderer, m_io.DisplayFramebufferScale.x, m_io.DisplayFramebufferScale.y);
	SDL_SetRenderDrawColor(m_renderer, (Uint8)(s_clearColour.x * 255), (Uint8)(s_clearColour.y * 255), (Uint8)(s_clearColour.z * 255), (Uint8)(s_clearColour.w * 255));
	ImGui_ImplSDLRenderer2_RenderDrawData(GetDrawData(), m_renderer);
	SDL_RenderPresent(m_renderer);
}

void UIWrapper::LinkMapData(LMap* map)
{
	m_map = map;
}