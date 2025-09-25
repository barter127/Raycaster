#pragma once

#ifndef _LEVEL1_SCREEN_H
#define _LEVEL1_SCREEN_H

#include "SDL.h"

#include <vector>

#include "Screen.h"

class Player;
class UIWrapper;

class Level1 : Screen
{
public:
	Level1(SDL_Window* window, SDL_Renderer* renderer);
	~Level1();

	void Update(float deltaTime, SDL_Event event);
	void Render();

private:
	void CreateMapColliders();
	void CollisionLoop();

	UIWrapper* m_ui;

	LevelRenderer* m_levelRender;
	Player* m_player;
	LMap m_map;

	std::vector<BoxCollider> m_levelColliders;

	int m_textureAmount = 5;

	// std::vector<Texture2D*> m_activeTextures;
};

#endif