#include "Level1.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "WindowConstants.h"
#include "LevelRenderer.h"

#include "Player.h"
#include "Vector2D.h"
#include "Collisions.h"
#include "UIWrapper.h"

std::vector<BoxCollider> levelColliders;

void Level1::CreateMapColliders()
{
    LevelArray lArray = m_map.GetLevelArray();

    for (int x = 0; x < m_map.GetWidth(); x++)
    {
        for (int y = 0; y < m_map.GetHeight(); y++)
        {
            if (lArray[x][y] > 0)
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
    LMap::ReadFile(m_map, "Levels/Test.hlvl");

    m_levelRender = new LevelRenderer(m_renderer, &m_map);
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
    CollisionLoop();
    m_player->Update(deltaTime, event);
}

void Level1::Render()
{
    m_levelRender->Render(m_player->m_position, m_player->m_direction, m_player->m_plane);
    m_player->Render();
}