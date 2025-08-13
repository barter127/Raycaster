#include "Level1.h"

#include <cmath>
#include <iostream>

#include "WindowConstants.h"
#include "LevelRenderer.h"
#include "Player.h"
#include "Vector2D.h"

Level1::Level1(SDL_Renderer* renderer) 
    : Screen(renderer)
{
    m_levelRender = new LevelRenderer(m_renderer);
    m_player = new Player(m_renderer, Vector2D(22,12) );
}

Level1::~Level1()
{
    delete m_levelRender;
    m_levelRender = nullptr;

    delete m_player;
    m_player = nullptr;
}

void Level1::Update(float deltaTime, SDL_Event event)
{
    m_player->Update(deltaTime, event);
}

void Level1::Render()
{
    m_levelRender->Render(m_player->m_position);
    m_player->Render();
}