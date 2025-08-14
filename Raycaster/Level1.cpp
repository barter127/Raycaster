#include "Level1.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "WindowConstants.h"
#include "LevelRenderer.h"
#include "Player.h"
#include "Vector2D.h"
#include "Collisions.h"
#include "TempMap.h"

std::vector<BoxCollider> levelColliders;

void CreateMapColliders()
{
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            if (worldMap[x][y] > 0)
            {
                BoxCollider levelCollider = {true, nullptr, x, y, BLOCK_WIDTH, BLOCK_HEIGHT};
                levelColliders.push_back(levelCollider);
            }
        }
    }
}

void Level1::CollisionLoop()
{
    for (int i = 0; i < levelColliders.size(); i++)
    {
        Collisions::BoxHard(m_player->m_collider, levelColliders[i]);
    }
}

Level1::Level1(SDL_Renderer* renderer) 
    : Screen(renderer)
{
    m_levelRender = new LevelRenderer(m_renderer);
    m_player = new Player(m_renderer, Vector2D(22,12) );

    CreateMapColliders();
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

    CollisionLoop();
}

void Level1::Render()
{
    m_levelRender->Render(m_player->m_position, m_player->m_direction, m_player->m_plane);
    m_player->Render();
}