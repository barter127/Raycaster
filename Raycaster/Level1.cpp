#include "Level1.h"

#include <cmath>
#include <iostream>

#include "WindowConstants.h"
#include "Surface2D.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Level1::Level1(SDL_Renderer* renderer) : Screen(renderer)
{
    wallTexture = new Surface2D(m_renderer);
    wallTexture->LoadFromFile("Assets/Brick_Wall_64x64.png");

    floorTexture = new Surface2D(m_renderer);
    floorTexture->LoadFromFile("Assets/Dirt_Road_64x64.png");

    ceilingTexture = new Surface2D(m_renderer);
    ceilingTexture->LoadFromFile("Assets/Wooden_Floor_Horizontal_64x64.png");

    screenBuffer = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 2, SDL_PIXELFORMAT_RGBA32);
}

Level1::~Level1()
{
    delete wallTexture;
    wallTexture = nullptr;

    wallTexture->Free();
}

int floorTex1Multiplier = 2;
int floorTex2Multiplier = 1;

void Level1::Update(float deltaTime, SDL_Event event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym) {

                case SDLK_UP:
                {
                    if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
                    if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
                    break;
                }

                    //move backwards if no wall behind you
                case SDLK_DOWN:
                {
                    if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
                    if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
                    break;
                }
                    //rotate to the right
                case SDLK_RIGHT:
                {
                    //both camera direction and camera plane must be rotated
                    double oldDirX = dirX;
                    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                    double oldPlaneX = planeX;
                    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
                    break;
                }

                    //rotate to the left
                case SDLK_LEFT:
                {
                    //both camera direction and camera plane must be rotated
                    double oldDirX = dirX;
                    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                    double oldPlaneX = planeX;
                    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
                    break;
                }

                case SDLK_EQUALS:
                    floorTex1Multiplier++;
                    break;

                case SDLK_MINUS:
                    floorTex1Multiplier--;

                    // Clamp to prevent negative values.
                    if (floorTex1Multiplier < 0) floorTex1Multiplier = 0;
                    break;
            }
        }
    }
}

void Level1::Render()
{
    int width = 640;
    int height = 480;

    int texWidth = 64;
    int texHeight = 64;

    bool floorIsCheckered = true;

    int* wallPixelData = (int*)wallTexture->GetPixelData();
    int* floor1PixelData = (int*)floorTexture->GetPixelData();
    int* floor2PixelData = (int*)wallTexture->GetPixelData();
    int* ceilPixelData = (int*)ceilingTexture->GetPixelData();

    // Clear the buffer.
    SDL_LockSurface(screenBuffer);
    SDL_FillRect(screenBuffer, NULL, 0xe0afba);

    for (int y = 0; y < height; y++)
    {
        // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
        float rayDirX0 = dirX - planeX;
        float rayDirY0 = dirY - planeY;
        float rayDirX1 = dirX + planeX;
        float rayDirY1 = dirY + planeY;

        // Current y position compared to the center of the screen (the horizon).
        int p = y - SCREEN_HEIGHT / 2;

        // Vertical position of the camera.
        float posZ = 0.5 * SCREEN_HEIGHT;

        // Horizontal distance from the camera to the floor for the current row.
        // 0.5 is the z position exactly in the middle between floor and ceiling.
        float rowDistance = posZ / p;

        // Calculate the real world step vector we have to add for each x (parallel to camera plane).
        // Adding step by step avoids multiplications with a weight in the inner loop.
        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

        // Real world coordinates of the leftmost column. This will be updated as we step to the right.
        float floorX = posX + rowDistance * rayDirX0;
        float floorY = posY + rowDistance * rayDirY0;

        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            // The cell coord is simply got from the integer parts of floorX and floorY.
            int cellX = int(floorX);
            int cellY = int(floorY);

            // Get the texture coordinate from the fractional part.
            int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
            int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            Uint32 colour;

            int checkerBoardPattern = (int(cellX + cellY)) % floorTex1Multiplier;

            if (checkerBoardPattern < floorTex2Multiplier && floorIsCheckered) colour = floor2PixelData[texWidth * ty + tx];
            else colour = floor1PixelData[texWidth * ty + tx];

            // Floor
            std::memcpy((int*)screenBuffer->pixels + y * SCREEN_WIDTH + x, & colour, sizeof(colour));

            // Ceiling
            colour = ceilPixelData[texWidth * ty + tx];
            std::memcpy((int*)screenBuffer->pixels + (SCREEN_HEIGHT - y - 1) * SCREEN_WIDTH + x, &colour, sizeof(colour));
        }
    }

    for (int x = 0; x < width; x++)
    {
        // GUT THIS AFTER RAYCAST FINISHED.
        // Calculate ray position and direction.
        float cameraX = 2 * x / float(width) - 1; // X coordinate in camera space.
        float rayDirX = dirX + planeX * cameraX;
        float rayDirY = dirY + planeY * cameraX;

        // Which box of the map we're in.
        int mapX = int(posX);
        int mapY = int(posY);

        // Length of ray from current position to next x or y side.
        float sideDistX;
        float sideDistY;

        // Length of ray from one x or y side to next x or y side.
        float deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
        float perpWallDist;

        // What direction to step in x or y-direction (either +1 or -1).
        int stepX;
        int stepY;

        int hit = 0; // Was there a wall hit?
        int side; // Was a NS or a EW wall hit?

        // Calculate step and initial sideDist.
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // Perform DDA.
        while (hit == 0)
        {
            // Jump to next map square, either in x-direction, or in y-direction.
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall.
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        // Calculate distance projected on camera direction.
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else  perpWallDist = (sideDistY - deltaDistY);


        // Calculate height of line to draw on screen.
        int lineHeight = (int)(height / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe.
        int drawStart = -lineHeight / 2 + height / 2;
        if (drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + height / 2;
        if (drawEnd >= height)drawEnd = height - 1;

        Uint32 colour = 0;

        // Texturing calculations.
        int texNum = worldMap[mapX][mapY];

        // Calculate value of wallX.
        float wallX; //Where the wall was hit
        if (side == 0) wallX = posY + perpWallDist * rayDirY;
        else           wallX = posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        // X coordinate on the texture.
       int texX = int(wallX * float(texWidth));
       if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
       if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

        // How much to increase the texture coordinate per screen pixel
        float step = 1.0f * texHeight / lineHeight;
        //Starting texture coordinate
        float texPos = (drawStart - height / 2 + lineHeight / 2) * step;
        for (int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            colour = wallPixelData[texHeight * texY + texX];

            // Make colour darker for y-sides.
            if (side == 1) colour = colour / 2;

            // Copy buffer into locked texture memory.
            std::memcpy((int*)screenBuffer->pixels + y * SCREEN_WIDTH + x, &colour, sizeof(colour));
        }

    }

    SDL_UnlockSurface(screenBuffer);
    screenTexture = SDL_CreateTextureFromSurface(m_renderer, screenBuffer);

    // Render to screen
    SDL_RenderCopy(m_renderer, screenTexture, NULL, NULL);

    SDL_DestroyTexture(screenTexture);
}