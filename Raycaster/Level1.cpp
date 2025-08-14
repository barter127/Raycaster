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

int numOfColliders = 0;
std::vector<BoxCollider> levelColliders;

void CreateMapColliders()
{
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            if (worldMap[x][y] > 0)
            {
                // levelColliders.push_back();
            }
        }
    }
}

void CollisionLoop()
{
    for (int i = 0; i < numOfColliders; i++)
    {

    }
}

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

    BoxCollider collider = {true, nullptr, 20, 12, 1, 1};

    std::cout << m_player->m_position.x << " " << m_player->m_position.y << std::endl;

    if (Collisions::BoxHard(m_player->m_collider, collider))
    {
        std::cout << "HIT" << std::endl;
    }
}

void Level1::Render()
{
    m_levelRender->Render(m_player->m_position, m_player->m_direction, m_player->m_plane);
    m_player->Render();
}