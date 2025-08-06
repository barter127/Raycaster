#include "Level1.h"

#include <cmath>
#include <iostream>

#include "WindowConstants.h"
#include "LevelRenderer.h"

Level1::Level1(SDL_Renderer* renderer) : Screen(renderer)
{
    m_levelRender = new LevelRenderer(m_renderer);
}

Level1::~Level1()
{

}

void Level1::Update(float deltaTime, SDL_Event event)
{
    //switch (event.type)
    //{
    //    case SDL_KEYDOWN:
    //    {
    //        switch (event.key.keysym.sym) {

    //            case SDLK_UP:
    //            {
    //                if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    //                if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    //                break;
    //            }

    //                //move backwards if no wall behind you
    //            case SDLK_DOWN:
    //            {
    //                if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //                if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    //                break;
    //            }
    //                //rotate to the right
    //            case SDLK_RIGHT:
    //            {
    //                //both camera direction and camera plane must be rotated
    //                double oldDirX = dirX;
    //                dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //                dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //                double oldPlaneX = planeX;
    //                planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //                planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    //                break;
    //            }

    //                //rotate to the left
    //            case SDLK_LEFT:
    //            {
    //                //both camera direction and camera plane must be rotated
    //                double oldDirX = dirX;
    //                dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //                dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //                double oldPlaneX = planeX;
    //                planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //                planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    //                break;
    //            }

    //            case SDLK_EQUALS:
    //                floorTex1Multiplier++;
    //                break;

    //            case SDLK_MINUS:
    //                floorTex1Multiplier--;

    //                // Clamp to prevent negative values.
    //                if (floorTex1Multiplier < 0) floorTex1Multiplier = 0;
    //                break;
    //        }
    //    }
    //}
}

void Level1::Render()
{
    m_levelRender->Render();
    // Render Level Renderer()

}