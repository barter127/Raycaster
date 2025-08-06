#include "LevelRenderer.h"

#include <iostream>

#include "WindowConstants.h"
#include "LevelTexture.h"

LevelRenderer::LevelRenderer(SDL_Renderer* renderer) : m_renderer(renderer)
{
    wallTexture = new LevelTexture(m_renderer);
    wallTexture->LoadFromFile("Assets/Brick_Wall_64x64.png");

    floorTexture = new LevelTexture(m_renderer);
    floorTexture->LoadFromFile("Assets/Dirt_Road_64x64.png");

    ceilingTexture = new LevelTexture(m_renderer);
    ceilingTexture->LoadFromFile("Assets/Wooden_Floor_Horizontal_64x64.png");

    m_wallPixelData = (int*)wallTexture->GetPixelData();
    m_floor1PixelData = (int*)floorTexture->GetPixelData();
    m_floor2PixelData = (int*)wallTexture->GetPixelData();
    m_ceilPixelData = (int*)ceilingTexture->GetPixelData();

    m_backBuffer = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 2, SDL_PIXELFORMAT_RGBA32);
}

LevelRenderer::~LevelRenderer()
{
    delete wallTexture;
    wallTexture = nullptr;
    wallTexture->Free();

    delete floorTexture;
    floorTexture = nullptr;
    floorTexture->Free();

    delete ceilingTexture;
    ceilingTexture = nullptr;
    ceilingTexture->Free();

    m_wallPixelData = nullptr;
    m_floor1PixelData = nullptr;
    m_floor2PixelData = nullptr;
    m_ceilPixelData = nullptr;
}

void LevelRenderer::Render()
{
    // Clear the buffer.
    SDL_LockSurface(m_backBuffer);
    SDL_FillRect(m_backBuffer, NULL, 0xe0afba);

    RenderCeilRoof();
    RenderWalls();

    // Unlock buffer.
    SDL_UnlockSurface(m_backBuffer);
    m_frontBuffer = SDL_CreateTextureFromSurface(m_renderer, m_backBuffer);

    // Render to screen
    SDL_RenderCopy(m_renderer, m_frontBuffer, NULL, NULL);

    // Destroy Texture for next render pass.
    SDL_DestroyTexture(m_frontBuffer);
}

// Temporary variables until UI and Map Editor is implemented.
int texWidth = 64;
int texHeight = 64;

bool floorIsCheckered = true;

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

void LevelRenderer::RenderWalls()
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        // GUT THIS AFTER RAYCAST FINISHED.
        // Calculate ray position and direction.
        float cameraX = 2 * x / float(SCREEN_WIDTH) - 1; // X coordinate in camera space.
        float rayDirX = m_dirX + m_planeX * cameraX;
        float rayDirY = m_dirY + m_planeY * cameraX;

        // Which box of the map we're in.
        int mapX = int(m_posX);
        int mapY = int(m_posY);

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
            sideDistX = (m_posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - m_posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (m_posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - m_posY) * deltaDistY;
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
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe.
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)drawEnd = SCREEN_HEIGHT - 1;

        Uint32 colour = 0;

        // Texturing calculations.
        int texNum = worldMap[mapX][mapY];

        // Calculate value of wallX.
        float wallX; //Where the wall was hit
        if (side == 0) wallX = m_posY + perpWallDist * rayDirY;
        else           wallX = m_posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        // X coordinate on the texture.
        int texX = int(wallX * float(texWidth));
        if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

        // How much to increase the texture coordinate per screen pixel
        float step = 1.0f * texHeight / lineHeight;
        //Starting texture coordinate
        float texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
        for (int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            colour = m_wallPixelData[texHeight * texY + texX];

            // Make colour darker for y-sides.
            if (side == 1) colour = colour / 2;

            // Copy buffer into locked texture memory.
            std::memcpy((int*)m_backBuffer->pixels + y * SCREEN_WIDTH + x, &colour, sizeof(colour));
        }

    }
}

void LevelRenderer::RenderCeilRoof()
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
        float rayDirX0 = m_dirX - m_planeX;
        float rayDirY0 = m_dirY - m_planeY;
        float rayDirX1 = m_dirX + m_planeX;
        float rayDirY1 = m_dirY + m_planeY;

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
        float floorX = m_posX + rowDistance * rayDirX0;
        float floorY = m_posY + rowDistance * rayDirY0;

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

            if (checkerBoardPattern < floorTex2Multiplier && floorIsCheckered) colour = m_floor2PixelData[texWidth * ty + tx];
            else colour = m_floor1PixelData[texWidth * ty + tx];

            // Floor
            std::memcpy((int*)m_backBuffer->pixels + y * SCREEN_WIDTH + x, &colour, sizeof(colour));

            // Ceiling
            colour = m_ceilPixelData[texWidth * ty + tx];
            std::memcpy((int*)m_backBuffer->pixels + (SCREEN_HEIGHT - y - 1) * SCREEN_WIDTH + x, &colour, sizeof(colour));
        }
    }
}