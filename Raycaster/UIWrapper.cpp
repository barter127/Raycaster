#include "UIWrapper.h"

#include <iostream>

// ImGUI dependencies
using namespace ImGui;
#include <imgui_internal.h>

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include "LMap.h"
#include "Texture2D.h"

ImVec4 UIWrapper::s_clearColour = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

SDL_Texture* wallTexture;

UIWrapper::UIWrapper(SDL_Window* window, SDL_Renderer* renderer, LMap* map) : m_window(window), m_renderer(renderer), m_map(map)
{
	IMGUI_CHECKVERSION();

	// Get display DPI scaling.
	float main_scale = 1.0f;
	int display_index = 0;
	float ddpi = 0.0f, hdpi = 0.0f, vdpi = 0.0f;
	if (SDL_GetDisplayDPI(display_index, &ddpi, &hdpi, &vdpi) == 0)
	{
		main_scale = ddpi / 96.0f; // 96 DPI is the default scaling baseline
	}

	CreateContext();
	ImGuiIO& io = GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Viewports
	m_io = io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup scaling
	ImGuiStyle& style = GetStyle();
	style.ScaleAllSizes(main_scale);
	style.FontScaleDpi = main_scale;

	// Initialize ImGui for SDL and SDL_Renderer
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	m_mapWidth = m_map->GetWidth();
	m_mapHeight = m_map->GetHeight();

	Texture2D* wallTexture = new Texture2D(m_renderer);
	wallTexture->LoadFromFile("Assets/Brick_Wall_64x64.png");
	m_paletteTextures.push_back(wallTexture);

	Texture2D* rockTexture = new Texture2D(m_renderer);
	rockTexture->LoadFromFile("Assets/Green_Wall_Rocks_64x64.png");
	m_paletteTextures.push_back(rockTexture);

	Texture2D* mossTexture = new Texture2D(m_renderer);
	mossTexture->LoadFromFile("Assets/Dirty_Mossy_Tiles_64x64.png");
	m_paletteTextures.push_back(mossTexture);

	Texture2D* earthTexture = new Texture2D(m_renderer);
	earthTexture->LoadFromFile("Assets/Dehydrated_Earth_64x64.png");
	m_paletteTextures.push_back(earthTexture);

	Texture2D* waterTexture = new Texture2D(m_renderer);
	waterTexture->LoadFromFile("Assets/Water_64x64.png");
	m_paletteTextures.push_back(waterTexture);
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

void UIWrapper::Render()
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	NewFrame();

	HandleDocking();
	SDL_Texture* texture;

	Begin("Editor");
	{
		m_fileDialog.Display();

		if (Button("New")) { m_displayNewPanel = !m_displayNewPanel; }
		if (m_displayNewPanel) { NewHLVLPanel(m_fileName); }

		SameLine();
		if (Button("Save")) 
		{
			bool success = LMap::SaveFile(*m_map, m_currentMapFile);

			if (success)
			{
				m_saved = true;
			}
		}

		SameLine();
		if (Button("Load")) 
		{
			m_fileDialog.Open();
			m_fileDialog.SetDirectory("Assets/Levels");
		}

		if (m_fileDialog.HasSelected())
		{
			if (m_map == nullptr)
			{
				std::cout << "[UIWrapper] m_map is nullptr" << std::endl;
				return;
			}


			if (m_fileDialog.GetSelected().extension() == ".hlvl")
			{
				LMap::ReadFile(*m_map, m_fileDialog.GetSelected().string());

				// Cache map dimensions for data locality.
				m_mapWidth = m_map->GetWidth();
				m_mapHeight = m_map->GetHeight();

				m_currentMapFile = m_fileDialog.GetSelected().string();
			}

			else
			{
				Texture2D* wallTexture = new Texture2D(m_renderer);
				wallTexture->LoadFromFile(m_fileDialog.GetSelected().string());
				m_paletteTextures.push_back(wallTexture);
			}

			std::cout << "[UIWrapper] Selected file " << m_fileDialog.GetSelected().string() << std::endl;
			m_fileDialog.ClearSelected();

			m_saved = true;
		}

		PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.75f, 0.75f));
		PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		Text("Palette");
		{
			ImVec2 buttonSize = ImVec2(20.0f, 20.0f);
			for (int i = 0; i < m_paletteTextures.size(); i++)
			{
				std::string label = "##Palette" + std::to_string(i);
				ImTextureID texID = (ImTextureID)(intptr_t)m_paletteTextures[i]->GetTexture();

				if (ImageButton(label.c_str(), texID, buttonSize))
				{
					m_selectedTexture = ++i;
				}
				
				if (i < m_paletteTextures.size() - 1) SameLine();
			}

			SameLine();
			if (Button("Add", ImVec2(30, 20)))
			{
				m_fileDialog.Open();
				m_fileDialog.SetDirectory("Assets");
			}
		}

		Text("Tile Map");
		{
			static ImGuiTableFlags tableFlags = ImGuiTableFlags_SizingFixedFit
				| ImGuiTableFlags_PadOuterX;

			BeginTable("Tile Map Table", m_mapWidth, tableFlags);

				std::string label = ""; // To prevent reinitialisation.
				ImTextureID texID = 0;
				ImVec2 buttonSize = ImVec2(15.0f, 15.0f);

				LevelArray lvlMap = m_map->GetLevelArray();

				for (int row = 0; row < m_mapWidth; row++)
				{
					TableNextRow();
					for (int column = 0; column < m_mapHeight; column++)
					{
						TableSetColumnIndex(column);

						label = "##TileMapButton " + std::to_string(row) + ", " + std::to_string(column);

						int textureIndex = lvlMap[column][row] - 1;

						if (textureIndex >= 0)
						{
							texID = (ImTextureID)(intptr_t)m_paletteTextures[textureIndex]->GetTexture();

							if (ImageButton(label.c_str(), texID, buttonSize))
							{
								lvlMap[column][row]= m_selectedTexture;
							}
						}
						else
						{
							if (Button(label.c_str(), buttonSize))
							{
								lvlMap[column][row]= m_selectedTexture;
							}
						}
					}
				}

				m_map->UpdateLevelArray(lvlMap);

			EndTable();
		}
		PopStyleVar();
		PopStyleVar();
		NewLine();

		Text("Floor");
		{
			m_floorData = m_map->GetFloorData();

			// Might be worth keeping these as members of UIWrapper.
			float dragIntSpeed = 0.1f;
			int minDragValue = 1;
			int maxDragValue = 10;

			Text("Floor Is Checkered:   ");
			SameLine();
			Checkbox("##FloorCheckered", &m_floorData.isCheckered);

			Text("Texture 1 Multiplier: ");
			SameLine();
			DragInt("##FloorTexMultiplier1", &m_floorData.multiplier1, dragIntSpeed, minDragValue, maxDragValue);

			Text("Texture 2 Multiplier: ");
			SameLine();
			DragInt("##FloorTexMultiplier2", &m_floorData.multiplier2, dragIntSpeed, minDragValue, maxDragValue);

			m_map->UpdateFloorData(m_floorData);
		}
		NewLine();

		Text("Ceiling");
		{
			m_ceilingData = m_map->GetCeilingData();

			float dragIntSpeed = 0.1f;
			int minDragValue = 1;
			int maxDragValue = 10;

			Text("Ceiling Is Checkered: ");
			SameLine();
			Checkbox("##CeilingCheckered", &m_ceilingData.isCheckered);

			Text("Texture 1 Multiplier: ");
			SameLine();
			DragInt("##CeilingTexMultiplier1", &m_ceilingData.multiplier1, dragIntSpeed, minDragValue, maxDragValue);

			Text("Texture 2 Multiplier: ");
			SameLine();
			DragInt("##CeilingTexMultiplier2", &m_ceilingData.multiplier2, dragIntSpeed, minDragValue, maxDragValue);

			m_map->UpdateCeilingData(m_ceilingData);
		}
		NewLine();
	}
	End();

	PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	Begin("Viewport");
	{
		int width, height;
		SDL_GetRendererOutputSize(m_renderer, &width, &height);
		SDL_PixelFormatEnum format = SDL_PIXELFORMAT_ARGB8888;
		int pitch = width * SDL_BYTESPERPIXEL(format);
		int bitDepth = 32;

		ImGuiViewport* viewport = ImGui::GetMainViewport();

		void* pixels = malloc(height * pitch);
		if (!pixels) 
		{
			std::cerr << "[UIWrapper] Failed to read allocate pixel array" << std::endl;
		}

		// Copy the pixels from the frontbuffer to pixels array.
		if (SDL_RenderReadPixels(m_renderer, NULL, 0, pixels, pitch) != 0) 
		{
			std::cerr << "[UIWrapper] Failed to read frontbuffer pixel data" << std::endl;
		}

		// Create a surface from the front buffer data.
		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
			pixels, width, height, bitDepth, pitch, format);

		if (!surface) 
		{
			std::cerr << "[UIWrapper] Failed to create frontbuffer surface" << std::endl;
		}

		texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		if (!texture) 
		{
			std::cerr << "[UIWrapper] Failed to create frontbuffer texture" << std::endl;
		}

		// Display buffer as ImGui Image.
		ImGui::Image((ImTextureID)(intptr_t)texture, viewport->Size);

		SDL_FreeSurface(surface);
		free(pixels);  // Important to free manually allocated memory
	}
	PopStyleVar(3);

	End();

	ImGui::Render();
	SDL_RenderSetScale(m_renderer, m_io.DisplayFramebufferScale.x, m_io.DisplayFramebufferScale.y);
	SDL_SetRenderDrawColor(m_renderer, (Uint8)(s_clearColour.x * 255), (Uint8)(s_clearColour.y * 255), (Uint8)(s_clearColour.z * 255), (Uint8)(s_clearColour.w * 255));
	ImGui_ImplSDLRenderer2_RenderDrawData(GetDrawData(), m_renderer);
	SDL_RenderPresent(m_renderer);

	SDL_DestroyTexture(texture);
}

bool dockspaceBuilt = false;

void UIWrapper::HandleDocking()
{
	ImGuiViewport* viewport = GetMainViewport();
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoTitleBar;

	SetNextWindowPos(viewport->Pos);
	SetNextWindowSize(viewport->Size);
	SetNextWindowViewport(viewport->ID);

	PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	Begin("DockSpace", nullptr, windowFlags);
	PopStyleVar(3);

	ImGuiID dockspaceId = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspaceId, ImVec2(0,0), ImGuiDockNodeFlags_NoTabBar);

	if (!dockspaceBuilt)
	{
		dockspaceBuilt = true;

		ImGui::DockBuilderRemoveNode(dockspaceId);
		ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);

		ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Left, 0.25f, nullptr, &dockspaceId);
		ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Right, 0.25f, nullptr, &dockspaceId);
		ImGuiID dock_id_center = dockspaceId;

		ImGui::DockBuilderDockWindow("Editor", dock_id_left);
		ImGui::DockBuilderDockWindow("Viewport", dock_id_center);
		//ImGui::DockBuilderDockWindow("Properties", dock_id_right); Maybe I add this.

		ImGui::DockBuilderFinish(dockspaceId);
	}

	ImGui::End();
}

// Consider expanding ImGuiFileBrowser to allow for the creation of files in the filebrowser.
void UIWrapper::NewHLVLPanel(char* fileName)
{
	m_saved = false;

	Begin("New HLVL");

	InputText("##label", fileName, MAX_FILE_NAME_LENGTH);
	SameLine();
	Text(".hlvl");

	if (Button("Create") && strcmp(fileName, ""))
	{
		std::cout << "[UIWrapper] Created new hlvl: " << fileName << ".hlvl";

		m_creatingNewFile = true;
	}

	if (!m_saved && m_creatingNewFile)
	{
		Begin("Unsaved Changes");

		Text("Save changes?");

		if (Button("Save"))
		{
			LMap::SaveFile(*m_map, m_currentMapFile);

			LMap::CreateFile(fileName);

			m_saved = true;
			m_displayNewPanel = false;
		}

		SameLine();
		if (Button("Don't Save"))
		{
			LMap::CreateFile(fileName);

			m_saved = true;
			m_displayNewPanel = false;
		}

		SameLine();
		if (Button("Cancel"))
		{
			m_creatingNewFile = false;
			m_displayNewPanel = false;
		}

		End();
	}

	End();
}