#include "Level1.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "LevelRenderer.h"

#include "Player.h"
#include "Vector2D.h"
#include "Collisions.h"
#include "UIWrapper.h"

#include "WindowData.h"

#include "BenchMarkTimer.h"

Level1::Level1(SDL_Window* window, SDL_Renderer* renderer) 
    : Screen(renderer)
{
    LMap::ReadFile(m_map, "Assets/Levels/Test.hlvl");
    
    m_ui = new UIWrapper(window, renderer, &m_map);

    m_levelRender = new LevelRenderer(m_renderer, &m_map);
    m_player = new Player(m_renderer, Vector2D(10,10) );

    m_textureAmount = m_map.GetTexturePaths().size();

    CreateMapColliders();
}

Level1::~Level1()
{
    delete m_levelRender;
    m_levelRender = nullptr;

    delete m_player;
    m_player = nullptr;

    delete m_ui;
    m_ui = nullptr;
}

void Level1::Update(float deltaTime, SDL_Event event)
{
    m_player->Update(deltaTime, event);
    CollisionLoop();
    m_ui->Update(deltaTime, event);

    if (m_textureAmount != m_map.GetTexturePaths().size())
    {
        m_textureAmount = m_map.GetTexturePaths().size();

        std::string path = m_map.GetTexturePaths()[m_textureAmount - 1];
        m_ui->AddTexture(path);
        m_levelRender->AddTexture(path);
    }
}

void Level1::Render()
{
    BenchmarkTimer timer;

    m_levelRender->Render(m_player->m_position, m_player->m_direction, m_player->m_plane);
    m_player->Render();

    m_ui->Render();

    std::cout << timer.Elapsed() << std::endl;
}

void Level1::CreateMapColliders()
{
    LevelArray lArray = m_map.GetLevelArray();

    for (int x = 0; x < m_map.GetWidth(); x++)
    {
        for (int y = 0; y < m_map.GetHeight(); y++)
        {
            if (lArray[x][y] > 0)
            {
                BoxCollider levelCollider = { true, nullptr, x, y, BLOCK_WIDTH, BLOCK_HEIGHT };
                m_levelColliders.push_back(levelCollider);
            }
        }
    }
}

void Level1::CollisionLoop()
{
    for (int i = 0; i < m_levelColliders.size(); i++)
    {
        Collisions::BoxHard(m_player->m_collider, m_levelColliders[i]);
    }
}